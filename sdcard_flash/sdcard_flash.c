// --------------------------------------------------------------------------
//  FILE        : sdcard_flash.c
//  PROJECT     : TI Booting and Flashing Utilities
//  AUTHOR      : Constantine Shulyupin http://www.LinuxDriver.co.il/
//  DESC        : Boots DM3xx from SD card and programms NAND flash
//  LICENSE     : GNU General Public License
//-----------------------------------------------------------------------------

#include "tistdtypes.h"
#include "sdcard_flash.h"
#include "sdboot_flash_cfg.h"
#include <device.h>
#include "util.h"
#include <debug.h>
//#include "uartboot.h"
#include "nand.h"
#include "device_nand.h"
#include "nandboot.h"
#include "mmcsd.h"
#include "sdc_debug.h"

#ifdef DM35x
#define PLL1DIV1	2
#define PLL1DIV2	4
#define PRE_DIV 	8
#define POST_DIV 	1
// Accordingly 
// TMS320DM355 DMSoC 
//      3.5 Device Clocking
//      3.5.4 Supported Clocking Configurations for DM355-270, p71
#define DEVICE_OSC_MHZ	24
//#define DM355_MHZ     (DEVICE_PLL1_MULTIPLIER * DEVICE_OSC_MHZ / ( PRE_DIV * POST_DIV * PLL1DIV1))
#define DM355_MHZ	((PLL1->PLLM+1) * DEVICE_OSC_MHZ / ( PRE_DIV * POST_DIV * PLL1DIV1))
//#define DDR_MHZ               ((DEVICE_PLL2_MULTIPLIER * DEVICE_OSC_MHZ) / 8 / 2 )
#define DDR_MHZ		(((PLL2->PLLM+1) * DEVICE_OSC_MHZ) / 8 / 2 )
#endif

typedef void (*jumpf) (void);

extern __FAR__ Uint32 EMIFStart;

static int flasher_data = 0;
int sdcard_init()
{
	trl();
	Uint16 i;
	Uint32 relCardAddr = 2;

	MMCSD_cardStatusReg cardStatus;
	MMCSD_ConfigData mmcsdConfig2 = {
		MMCSD_LITTLE_ENDIAN,	// write Endian
		MMCSD_LITTLE_ENDIAN,	// read Endian
		MMCSD_DAT3_DISABLE,	// Edge Detection disbale
		0,		// SpiModeEnable
		0,		// csEnable
		0,		// spiCrcEnable
		0,
		0,		// SpiModeEnable
		0,		// csEnable
		0,		// spiCrcEnable
		MMCSD_DATA_BUS_4,	// data bus width
		0xFF,		// response timeout
		0xFFFF		// data read timeout
	};

	if (MMCSD_initCard(&relCardAddr, &cardStatus, &mmcsdConfig2, MMCSD_FIFOLEVEL_32BYTES)) {
		error("SD Card Initialization failed\n");
		return -1;
	}
	return 0;
}

int sdcard_read(int sdc_src, void *dst, int len)
{
	trl_();
	trvx_(sdc_src);
	trvx_(dst);
	trvx_(len);
	trvx_(dst + len);
	//trvx_(sdc_src>>20); trvx(len>>20);
	int *data0 = dst;
	while (len > 0) {
		if (E_PASS != MMCSD_singleBlkRead(sdc_src, dst, len > BLOCK ? BLOCK : len, 0)) {
			puts("FAIL");
			return -1;
		}
		if (data0) {
			trvx_(*data0);
			print("\n");
			data0 = 0;
		}
		if ((sdc_src & ((1 << 16) - 1)) == 0) {
			print("src=");
			print_hex(sdc_src);
			print(" ");
			print("\r");
		}
		dst += BLOCK;
		len -= BLOCK;
		sdc_src += BLOCK;
	}
	print("                          \r");
}

/*
 * ffs: find first bit set.
 */

static inline int generic_ffs(int x)
{
	int r = 1;

	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}

#define ffs(x)		generic_ffs(x)

#define page_shift(nand) (ffs(nand->dataBytesPerPage) - 1)
#define block_shift(nand) (ffs(nand->dataBytesPerPage  * nand->pagesPerBlock ) -1)

char *hNandWriteBuf, *hNandReadBuf;
int nand_write(NAND_InfoHandle nand, int dst_nand, Uint8 * src_ptr, int len)
{				// like LOCAL_NANDWriteHeaderAndData
	Uint32 block_idx = dst_nand >> block_shift(nand);
	int page_idx = ((1 << block_shift(nand) - page_shift(nand)) - 1) & (dst_nand >> page_shift(nand));
	trl_();
	trvx_(dst_nand);
	trvx_(block_idx);
	//trvx_(page_idx);
	trvx(len);
	//trvx(block_idx*nand->pagesPerBlock*nand->dataBytesPerPage);
	Uint32 pages, i;
	//trvx(*(int*)src_ptr);
	NAND_unProtectBlocks(nand, block_idx, (len >> block_shift(nand)) + 1);
	NAND_eraseBlocks(nand, block_idx, (len >> block_shift(nand)) + 1);
	while (len > 0) {
		if (NAND_writePage(nand, block_idx, page_idx, src_ptr) != E_PASS) {
			print("Write failed!\n");
			return -1;
		}
		UTIL_waitLoop(200);
		if (NAND_verifyPage(nand, block_idx, page_idx, src_ptr, hNandReadBuf) != E_PASS) {
			print(RED "Write verify failed!\n" NOCOLOR);
			trvx(block_idx);
			trvx(page_idx);
			//return -1;
		} else {
			//print(".");
		}
		src_ptr += nand->dataBytesPerPage;
		pages++;
		page_idx++;
		len -= nand->dataBytesPerPage;

		if (page_idx == nand->pagesPerBlock) {
			block_idx++;
			page_idx = 0;
			print("block=");
			print_hex(block_idx);
			print(" ");
			print("\r");
		}
	}
	print("                            \r");
	NAND_protectBlocks(nand);
	//print("\n");
	return 0;
}

int nand_read(NAND_InfoHandle nand, int src, void *dst, int len)
{
	int status;
	Uint32 block_idx = src >> block_shift(nand);
	trvx(src);
	int page_idx = ((1 << block_shift(nand) - page_shift(nand)) - 1) & (src >> page_shift(nand));
	trl_();
	trvx_(block_idx);
	trvx_(page_idx);
	trvx(len);
	//trvx(block_idx*nand->pagesPerBlock*nand->dataBytesPerPage);
	Uint32 pages, i;
	while (len > 0) {
		if (NAND_readPage(nand, block_idx, page_idx, dst) != E_PASS) {
			if (!status) {
				// report only once
				trvx_(block_idx);
				trvx_(page_idx);
				error("Read failed!");
				status = -1;
			}
		}
		UTIL_waitLoop(200);
		dst += nand->dataBytesPerPage;
		pages++;
		page_idx++;
		len -= nand->dataBytesPerPage;

		if (page_idx == nand->pagesPerBlock) {
			block_idx++;
			page_idx = 0;
			//print(".");
			print("block=");
			print_hex(block_idx);
			print(" ");
			print("\r");
		}
	}
	print("\n");
	return status;
}

int check_pattern_123(void *buf, int size)
{
entry:	;
	int errors = 0;
	short int *ibuf = buf;
	int i;
	for (i = 0; i < size / sizeof(ibuf[0]); i++) {
		if ((short int)i != ibuf[i]) {
			error("SD card read check failed");
			trvx(i);
			trvx(i * sizeof(ibuf[0]));
			trvx((int)&ibuf[i]);
			trvx(ibuf[i]);
			errors++;
			getch();
		}
	}
	if (errors) {
		trvx(errors);
	}
	return -errors;
}

int sdcard_boot()
{
entry:
	print(" u-boot  ");
	sdcard_read(flasher_data + UBOOT_SDC, UBOOT_ADDR, UBOOT_SIZE);
	print(" kernel  ");
	sdcard_read(flasher_data + KERNEL_SDC, KERNEL_ADDR, KERNEL_SIZE);
	print(" root FS ");
	sdcard_read(flasher_data + ROOTFS_SDC, ROOTFS_ADDR, ROOTFS_SIZE);
	((jumpf) UBOOT_ADDR) ();
}

int kerne_boot(nand)
{
	print(" kernel  ");
	sdcard_read(flasher_data + KERNEL_SDC, KERNEL_ADDR, KERNEL_SIZE);
	print(" root FS ");
	sdcard_read(flasher_data + ROOTFS_SDC, ROOTFS_ADDR, ROOTFS_SIZE);
	((jumpf) KERNEL_ADDR) ();
}

enum ubl_type_e {
	ccs_ubl,
	ubl_gnu
} ubl_type;

int ubl_install(NAND_InfoHandle nand)
{
	NANDBOOT_HeaderObj header;
	int status = 0;
	print(BOLD " * Flashing UBL\n" NOCOLOR);
	int *ubl_buf;
	ubl_buf = UTIL_callocMem(UBL_SIZE);
	sdcard_read(flasher_data + UBL_SDC, ubl_buf, UBL_SIZE);
	switch (ubl_buf[0]) {
	case UBL_CCS_MAGIC:
		header.entryPoint = UBL_CCS_ENTRY;
		ubl_type = ccs_ubl;
		break;
	default:
	case UBL_GNU_MAGIC:
		header.entryPoint = UBL_GNU_ENTRY;
		ubl_type = ubl_gnu;
		break;
	}
	header.magicNum = UBL_MAGIC_SAFE;
	header.page = 1;	// The page is always page 0 for the UBL header, so we use page 1 for data
	header.block = DEVICE_NAND_RBL_SEARCH_START_BLOCK;
	header.ldAddress = 0;	// This field doesn't matter for the UBL header
	header.numPage = (UBL_SIZE + nand->dataBytesPerPage - 1) >> page_shift(nand);
	header.forceContigImage = TRUE;
	header.startBlock = DEVICE_NAND_RBL_SEARCH_START_BLOCK;
	header.endBlock = DEVICE_NAND_RBL_SEARCH_END_BLOCK;

	if (LOCAL_NANDWriteHeaderAndData(nand, &header, ubl_buf) != E_PASS) {
		status = -1;
	}
	return status;
}

Uint32 uboot_install_for_ccs_ubl(NAND_InfoHandle nand, NANDBOOT_HeaderHandle nandBoot, Uint8 * src_ptr0)
{
	trl();
	// like NANDProg appdesc appdat appdatPtr, readed by NANDBoot, gEntryPoint
	// derived from LOCAL_NANDWriteHeaderAndData
#define APP_DESC_START_BLOCK_NUM 8
#define APP_DESC_END_BLOCK_NUM 9
#define APP_START_BLOCK_NUM 0x19
#define APP_MAGIC_NUMBER_VALID (0xB1ACED00)
#define APP_MAGIC_DMA_IC_FAST  (0x55)	/* DMA + I Cache + Fast EMIF boot mode */
#define APP_MAGIC_IC  		   (0x22)	/* I Cache boot mode */
	// for ccs ubl
	Uint8 *src_ptr;
	Uint32 endBlockNum;
	Uint32 *ptr;
	Uint32 block_idx, page_idx, pages, i;
	Uint32 numBlks;
	for (i = 0; i < nand->dataBytesPerPage; i++) {
		hNandWriteBuf[i] = 0xFF;
		hNandReadBuf[i] = 0xFF;
	}
	numBlks = 0;
	while ((numBlks * nand->pagesPerBlock) < (nandBoot->numPage + 1)) {
		numBlks++;
	}
	trvx(nandBoot->numPage);
	trvx(numBlks);

	//block_idx = nandBoot->block;
	block_idx = APP_DESC_START_BLOCK_NUM + 1;
	endBlockNum = APP_DESC_END_BLOCK_NUM;

NAND_WRITE_RETRY:
	src_ptr = src_ptr0;
	trvx(block_idx);

	// Go to first good block
	if (NAND_badBlockCheck(nand, block_idx) != E_PASS) {
		block_idx++;
		goto NAND_WRITE_RETRY;
	}

	if (NAND_unProtectBlocks(nand, block_idx, numBlks) != E_PASS) {
		block_idx++;
		DEBUG_printString("Unprotect failed\n");
		goto NAND_WRITE_RETRY;
	}
	// Erase the block where the header goes and the data starts
	if (NAND_eraseBlocks(nand, block_idx, 1) != E_PASS) {
		block_idx++;
		DEBUG_printString("Erase failed\n");
		goto NAND_WRITE_RETRY;
	}

	ptr = (Uint32 *) hNandWriteBuf;
	ptr[0] = APP_MAGIC_NUMBER_VALID | APP_MAGIC_IC;	// 0xB1ACED22; like appdesc
	ptr[1] = APP_START_BLOCK_NUM;
	ptr[2] = ptr[3] = (int)UBOOT_ADDR;
	ptr[4] = nandBoot->numPage;
	ptr[5] = 0;
	trvx_(ptr[0]);
	trvx_(ptr[1]);;
	trvx_(ptr[2]);
	trvx_(ptr[3]);
	trvx_(ptr[4]);
	trvx(ptr[5]);
	if (NAND_writePage(nand, block_idx, 0, hNandWriteBuf) != E_PASS) {
		block_idx++;
		DEBUG_printString("Write failed!\n");
		goto NAND_WRITE_RETRY;
	}

	UTIL_waitLoop(200);

	// Verify the page just written
	if (NAND_verifyPage(nand, block_idx, 0, hNandWriteBuf, hNandReadBuf) != E_PASS) {
		block_idx++;
		DEBUG_printString("Write verify failed!\n");
		goto NAND_WRITE_RETRY;
	}

	pages = 0;
	page_idx = 0;
	block_idx = APP_START_BLOCK_NUM;
	if (NAND_eraseBlocks(nand, block_idx, numBlks) != E_PASS) {
		block_idx++;
		DEBUG_printString("Erase failed\n");
		goto NAND_WRITE_RETRY;
	}
	do {
		//trvx(page_idx);
		if (NAND_writePage(nand, block_idx, page_idx, src_ptr) != E_PASS) {
			block_idx++;
			DEBUG_printString("Write failed!\n");
			goto NAND_WRITE_RETRY;
		}
		UTIL_waitLoop(200);

		if (NAND_verifyPage(nand, block_idx, page_idx, src_ptr, hNandReadBuf) != E_PASS) {
			block_idx++;
			DEBUG_printString(RED "\nWrite verify failed!\n" NOCOLOR);
			goto NAND_WRITE_RETRY;
		} else {
			//print("+");
		}
		UTIL_waitLoop(200);

		src_ptr += nand->dataBytesPerPage;
		pages++;
		page_idx++;
		if (page_idx == nand->pagesPerBlock) {
			block_idx++;
			page_idx = 0;
			print("block=");
			print_hex(block_idx);
			print(" ");
			print("\r");
			//print("\n");
			//print(".");
		}
	} while (pages < nandBoot->numPage);
	puts("");
	NAND_protectBlocks(nand);

	return E_PASS;
}

int nand_boot(NAND_InfoHandle nand)
{
entry:
	print(" u-boot  ");
	if (nand_read
	    (nand,
	     DEVICE_NAND_UBL_SEARCH_START_BLOCK * nand->pagesPerBlock *
	     nand->dataBytesPerPage + nand->dataBytesPerPage, UBOOT_ADDR, UBOOT_SIZE) < 0) {
		nand_read(nand,
			  APP_START_BLOCK_NUM * nand->pagesPerBlock * nand->dataBytesPerPage, UBOOT_ADDR, UBOOT_SIZE);
	}
	((jumpf) UBOOT_ADDR) ();
}

int nand_dump(NAND_InfoHandle nand, int addr)
{
	//int size=nand->dataBytesPerPage * nand->pagesPerBlock * nand->numBlocks;
	int size = 10 * MB;
	int i, skipped;
	int *buff = UTIL_allocMem(size);
	for (i = 0; i < size >> 2; i++)
		buff[i] = -1;
	if (nand_read(nand, addr, buff, size) < 0) {
		for (i = 0; i < size >> 2; i++) {
			if ((i & 0x7) == 0) {
				do {
					skipped = 0;
					while ((buff[i] & buff[i + 1] & buff[i + 2] & buff[i + 3]
						& buff[i + 4] & buff[i + 5] & buff[i + 6]
						& buff[i + 7]) == -1) {
						if (!skipped) {
							print_hex(addr + i << 2);
							print(": ");
							print("FFFFFFFF ....\n");
						}
						skipped++;
						i += 8;
					}
					skipped = 0;
					while ((buff[i] | buff[i + 1] | buff[i + 2] | buff[i + 3]
						| buff[i + 4] | buff[i + 5] | buff[i + 6]
						| buff[i + 7]) == 0) {
						if (!skipped) {
							print_hex(addr + i << 2);
							print(": ");
							print("00000000 ....\n");
						}
						i += 8;
						skipped++;
					}
				} while (skipped);
				print_hex(addr + i << 2);
				print(": ");
			}
			print_hex(buff[i]);
			if (i && (((i + 1) & 0x7) == 0))
				print("\n");
			else
				print(" ");
		}
	}
}

int uboot_install(NAND_InfoHandle nand)
{
	NANDBOOT_HeaderObj header;
	int status = 0;

	print(BOLD " * Flashing u-boot\n" NOCOLOR);
	sdcard_read(flasher_data + UBOOT_SDC, UBOOT_ADDR, UBOOT_SIZE);

	header.magicNum = UBL_MAGIC_BIN_IMG;
	header.entryPoint = (int)UBOOT_ADDR; /* UBOOT_FLASH; */
	header.page = 1;	// The page is always page 0 for the header, so we use page 1 for data
	header.block = DEVICE_NAND_UBL_SEARCH_START_BLOCK;
	header.ldAddress = (int)UBOOT_ADDR;
	header.numPage = (UBOOT_SIZE + nand->dataBytesPerPage - 1) >> page_shift(nand);
	header.startBlock = DEVICE_NAND_UBL_SEARCH_START_BLOCK;
	header.endBlock = DEVICE_NAND_UBL_SEARCH_END_BLOCK;
	switch (ubl_type) {
	case ccs_ubl:
		print("Assuming CCS UBL ");
		trvx(UBL_CCS_ENTRY);
		if (uboot_install_for_ccs_ubl(nand, &header, UBOOT_ADDR) != E_PASS) {
			status = -1;
		}
		break;
	default:
	case ubl_gnu:
		print("Assuming GNU UBL ");
		trvx(UBL_GNU_ENTRY);
		if (LOCAL_NANDWriteHeaderAndData(nand, &header, UBOOT_ADDR) != E_PASS) {
			status = -1;
		}
		break;
	}
	return status;
}

int sdcard_install(NAND_InfoHandle nand)
{
entry:	;

	int i;
	int status = 0;
	ubl_install(nand);
	uboot_install(nand);

	print(BOLD " * Flashing kernel\n" NOCOLOR);
	sdcard_read(flasher_data + KERNEL_SDC, KERNEL_ADDR, KERNEL_SIZE);
	status = nand_write(nand, KERNEL_FLASH, KERNEL_ADDR, KERNEL_SIZE);

	print(BOLD " * Flashing Root FS\n" NOCOLOR);
	sdcard_read(flasher_data + ROOTFS_SDC, ROOTFS_ADDR, ROOTFS_SIZE);
	status = nand_write(nand, ROOTFS_FLASH, ROOTFS_ADDR, ROOTFS_SIZE);

	return status;
}

int sdc_prepare()
{
	int i;
	int status;
	if (sdcard_init()) {
		//print(RED "sdcard_init failed\n" NOCOLOR);
		return -1;
	}
	int *block;
	block = UTIL_callocMem(BLOCK);

	// read flasher_data value
	for (i = RBL_RECORD_SDC; i <= DEVICE_NAND_RBL_SEARCH_END_BLOCK * BLOCK; i += BLOCK) {
		sdcard_read(i, block, BLOCK);
		if ((block[0] & ~0xFF) == MAGIC_NUMBER_VALID) {
			flasher_data = block[8];
			break;
		}
	}
	trvx(flasher_data);
	if (!flasher_data) {
		error("flasher_data not found");
	}
	// test sd card with test block
	sdcard_read(flasher_data + TEST_SDC, block, BLOCK);
	status = check_pattern_123(block, BLOCK);
	if (status < 0) {
		puts("Error checking test pattern on SD card");
	}
	return 0;
}

NAND_InfoHandle nand;
char mode[2] = { 0, 0 };

int sdcard_nand_user(void)	//      copy from SDC to NAND flash
{
	print("1 - boot; 2 - install; 3 - erase flash, 4 - nand boot, 5 - test first 16MB of RAM\n");
	print("u - install ubl only, ");
	//print("k - boot kernel from Image by direct jump, ");
	print("d - nand flash dump\n");
	print("9 - install to leopardboard, no kernel or fs (ECC error)\n");
	char *modes = mode;
	do {
		print(" > ");
		mode[0] = getch();
		print((char *)modes);
	} while (mode[0] < 1);
	print("\r        \r");
	switch ((int)mode[0]) {
	case '\r':
	case -1:
	case 0:
	case '1':
		sdc_prepare();
		sdcard_boot();
		break;
	case '3':
		// see nanderaser
		{
			NAND_InfoHandle hNandInfo;
			hNandInfo = NAND_open((int)&EMIFStart, (Uint8) DEVICE_emifBusWidth());

			if (!hNandInfo) {
				error("NAND Initialization failed.");
			}
			NAND_globalErase_with_bb_check(hNandInfo);
/*
#ifdef DM36x
			hNandInfo = NAND_open(0x02004000, (Uint8) DEVICE_emifBusWidth());
			if (!hNandInfo) {
				error("NAND Initialization failed.");
			}
			NAND_globalErase_with_bb_check(hNandInfo);
#endif
*/
		}
		//NAND_unProtectBlocks(nand, 0, nand->numBlocks - 1);
		//NAND_globalErase(nand);
		//NAND_protectBlocks(nand);
		break;
	case '2':
		sdc_prepare();
		sdcard_install(nand);
		break;
	case 'u':
		sdc_prepare();
		ubl_install(nand);
		break;
	case 'k':
		sdc_prepare();
		kerne_boot(nand);
		break;
	case '4':
		nand_boot(nand);
		break;
	case '5':
		memory_test(DEVICE_DDR2_START_ADDR, 16 * MB);
		break;

	case '9':
		// erase flash
		NAND_globalErase_with_bb_check(nand);
		// install UBL, u-boot, kernel, and file sys
		//sdcard_install(nand);
		int status = 0;
		print(BOLD " * Flashing ubl\n" NOCOLOR);
		sdcard_read(flasher_data + UBL_SDC, UBL_ADDR, UBL_SIZE);
		status = nand_write(nand, UBL_FLASH, UBL_ADDR, UBL_SIZE);

		print(BOLD " * Flashing u-boot\n" NOCOLOR);
		sdcard_read(flasher_data + UBOOT_SDC, UBOOT_ADDR, UBOOT_SIZE);
		status = nand_write(nand, UBOOT_FLASH, UBOOT_ADDR, UBOOT_SIZE);

//		print(BOLD " * Flashing kernel\n" NOCOLOR);
//		sdcard_read(flasher_data + KERNEL_SDC, KERNEL_ADDR, KERNEL_SIZE);
//		status = nand_write(nand, KERNEL_FLASH, KERNEL_ADDR, KERNEL_SIZE);
//
//		print(BOLD " * Flashing Root FS\n" NOCOLOR);
//		sdcard_read(flasher_data + ROOTFS_SDC, ROOTFS_ADDR, ROOTFS_SIZE);
//		status = nand_write(nand, ROOTFS_FLASH, ROOTFS_ADDR, ROOTFS_SIZE);
//
//		print("Start u-boot at: ");
//		print_hex(UBOOT_ADDR);
//		((jumpf) UBOOT_ADDR + 0x800) ();
		print(BOLD "\nRestart me from nand\n" NOCOLOR);
		break;
	case 'd':
		trvx(DEVICE_NAND_RBL_SEARCH_START_BLOCK * nand->dataBytesPerPage * nand->pagesPerBlock);
		nand_dump(nand, 0);
		//nand_dump(nand, DEVICE_NAND_RBL_SEARCH_START_BLOCK  * (nand->dataBytesPerPage * nand->pagesPerBlock));
		break;
	}

	return 0;
}

/*
int mem_test()
{
	print("memory test\n");
	volatile int * mem = (void*) DEVICE_DDR2_START_ADDR;
	int i;
	for ( i = 0; i < (1<<20); i++)  {
		*(mem+i)=0x5555AAAA;
		if ( *(mem+i) != 0x5555AAAA ) {
			print("memory error ");
			trvx((int)(mem+i))		
		}
	}
}
*/

void nand_prepare()
{
	trvx(&EMIFStart);
	nand = NAND_open((Uint32) & EMIFStart, (Uint8) DEVICE_emifBusWidth());
	if (!nand) {
		error("NAND_open() failed!");
		//UTIL_waitLoop(100000);
		getch();
	}
	if (nand) {
		trvx_(nand->devID);
		trvi_(nand->dataBytesPerPage);
		trvi_(nand->pagesPerBlock);
		trvi_(nand->numBlocks);
		int nand_size = nand->dataBytesPerPage * nand->pagesPerBlock * nand->numBlocks;
		trvi(nand_size);
		hNandWriteBuf = UTIL_allocMem(nand->dataBytesPerPage);
		hNandReadBuf = UTIL_allocMem(nand->dataBytesPerPage);
	}
}

static int sdcard_flash_boot(void)
{
	int status;
	if (DEVICE_init() != E_PASS) {
		print("Chip initialization failed!\n");
		asm(" MOV PC, #0");
	} else {
		//for ( status = 0; status < 30; status ++ ) print("\n");
		print("-------------------------------------------------------\n");
		print("\n" CLS);
	}
	UTIL_setCurrMemPtr(0);

	print(GREEN "SD card boot and flashing tool for DM355 and DM365\n" NOCOLOR);
	print("by Constantine Shulyupin http://www.LinuxDriver.co.il/\n");
	print("Online manual: http://wiki.davincidsp.com/index.php/SD_card_boot_and_flashing_tool_for_DM355_and_DM365\n");
	// print(SFT_VERSION_STRING);
	print("based on TI DM35x FlashAndBootUtils 1.10 SFT, TI flash_utils ");
	print("and SpectrumDigital evmdm355, evmdm365\n");
	print("Compiled on ");
	print(__DATE__);
	print(" at ");
	print(__TIME__);
	print(" with gcc ");
	print(__VERSION__);
	print("\n");
#undef DEVICE_ID
	trvx(SYSTEM->DEVICE_ID);
#ifdef DM35x
	trvi_(DM355_MHZ);
	trvi(DDR_MHZ);
	trvi_(PLL1->PLLM);
	trvi_(PLL2->PLLM);
	trvx_(PLL1->PLLDIV3);
	trvx_(DDR->SDTIMR);
	trvx(DDR->SDTIMR2);
#endif
	nand_prepare();
	sdc_prepare();

	return E_PASS;
}

void *memset(void *s, int c, int count)
{
	char *xs = (char *)s;
	while (count--)
		*xs++ = c;
	return s;
}

Uint32 gEntryPoint;
int main(void)
{
	sdcard_flash_boot();
	while (1) {
		if (sdcard_nand_user() >= 0) {
			print(GREEN"DONE\n\n"NOCOLOR);
		} else {
			print(RED"FAIL\n\n"NOCOLOR);
		}
	}
	return 0;
}
