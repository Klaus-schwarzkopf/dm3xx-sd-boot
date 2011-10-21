#include "tistdtypes.h"
#include "uartboot.h"
#include "uart.h"
#include "util.h"
#include "debug.h"
//#include "sft.h"
#include "device.h"
#include "nand.h"
#include "device_nand.h"
#include "nandboot.h"

/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern VUint32 gMagicFlag,gBootCmd;
extern Uint32 gEntryPoint;

extern __FAR__ Uint32 DDRStart;
extern __FAR__ Uint32 EMIFStart;
extern __FAR__ Uint32 DDRSize;
extern __FAR__ Uint32 DRAMSize;

Uint32 LOCAL_NANDWriteHeaderAndData(NAND_InfoHandle hNandInfo, NANDBOOT_HeaderHandle nandBoot, Uint8 *srcBuf0)
{	
	Uint8 *srcBuf;
	Uint32    endBlockNum;
	Uint32    *ptr;
	Uint32    blockNum,pageNum,pageCnt,i;
	Uint32    numBlks;

	Uint8     *hNandWriteBuf,*hNandReadBuf;

	// Allocate mem for write and read buffers
	hNandWriteBuf = UTIL_allocMem(hNandInfo->dataBytesPerPage);
	hNandReadBuf  = UTIL_allocMem(hNandInfo->dataBytesPerPage);

	// Clear buffers
	for (i=0; i < hNandInfo->dataBytesPerPage; i++)
	{
		hNandWriteBuf[i] = 0xFF;
		hNandReadBuf[i] = 0xFF;
	}
	// Get total number of blocks needed
	numBlks = 0;
	while ( (numBlks * hNandInfo->pagesPerBlock)  < (nandBoot->numPage + 1) )
	{
		numBlks++;
	}
	//DEBUG_printString("Number of blocks needed for header and data: ");
	//printhex(numBlks);
	//DEBUG_printString("\r\n");

	// Check whether writing UBL or APP (based on destination block)
	blockNum = nandBoot->block;
	if (blockNum == DEVICE_NAND_RBL_SEARCH_START_BLOCK)
		endBlockNum = DEVICE_NAND_RBL_SEARCH_END_BLOCK;
	else if (blockNum == DEVICE_NAND_UBL_SEARCH_START_BLOCK)
		endBlockNum = DEVICE_NAND_UBL_SEARCH_END_BLOCK;
	else
		return E_FAIL; // Block number is out of range

NAND_WRITE_RETRY:
	srcBuf = srcBuf0;
	if (blockNum > endBlockNum)
		return E_FAIL;

	// Go to first good block
	if (NAND_badBlockCheck(hNandInfo,blockNum) != E_PASS)
	{  
		blockNum++;
		goto NAND_WRITE_RETRY;
	}

	//DEBUG_printString("Attempting to start in block number ");
	//printhex(blockNum);
	//DEBUG_printString(".\r\n");

	// Unprotect all needed blocks of the Flash 
	if (NAND_unProtectBlocks(hNandInfo,blockNum,numBlks) != E_PASS)
	{
		blockNum++;
		DEBUG_printString("Unprotect failed\r\n");
		goto NAND_WRITE_RETRY;
	}

	// Erase the block where the header goes and the data starts
	if (NAND_eraseBlocks(hNandInfo,blockNum,numBlks) != E_PASS)
	{
		blockNum++;
		DEBUG_printString("Erase failed\r\n");
		goto NAND_WRITE_RETRY;
	}

	// Setup header to be written
	ptr = (Uint32 *) hNandWriteBuf;
	ptr[0] = nandBoot->magicNum;
	ptr[1] = nandBoot->entryPoint;
	ptr[2] = nandBoot->numPage;
	ptr[3] = blockNum;  //always start data in current block
	ptr[4] = 1;      //always start data in page 1 (this header goes in page 0)
	ptr[5] = nandBoot->ldAddress;
	//trvx(nandBoot->magicNum);
	//trvx(nandBoot->entryPoint);
	//trvx(nandBoot->numPage);
	//trvx(nandBoot->ldAddress);
	int * src = (void*)srcBuf;
	//trvx(src[0]);
	// Write the header to page 0 of the current blockNum
	DEBUG_printString("Writing header data to Block ");
	print_hex(blockNum);
	//DEBUG_printString(", Page ");
	//print_hex(0);
	DEBUG_printString(", Offset ");
	print_hex(blockNum * hNandInfo->dataBytesPerPage * hNandInfo->pagesPerBlock);
	DEBUG_printString("\r\n");

	if (NAND_writePage(hNandInfo, blockNum, 0, hNandWriteBuf) != E_PASS)
	{
		blockNum++;
		DEBUG_printString("Write failed!\r\n");
		goto NAND_WRITE_RETRY;
	}

	UTIL_waitLoop(200);

	// Verify the page just written
	if (NAND_verifyPage(hNandInfo, blockNum, 0, hNandWriteBuf, hNandReadBuf) != E_PASS)
	{
		blockNum++;
		DEBUG_printString("Write verify failed!\r\n");
		goto NAND_WRITE_RETRY;
	}

	pageCnt = 1;
	pageNum = 1;

	do
	{
#if 0
		DEBUG_printString("Writing image data to Block ");
		DEBUG_printHexInt(blockNum);
		DEBUG_printString(", Page ");
		DEBUG_printHexInt(pageNum);
		DEBUG_printString("\r\n");
#endif

		// Write the UBL or APP data on a per page basis
		if (NAND_writePage(hNandInfo, blockNum, pageNum, srcBuf) != E_PASS)
		{
			blockNum++;
			DEBUG_printString("Write failed!\r\n");
			goto NAND_WRITE_RETRY;
		}

		UTIL_waitLoop(200);

		// Verify the page just written
		if (NAND_verifyPage(hNandInfo, blockNum, pageNum, srcBuf, hNandReadBuf) != E_PASS)
		{
			blockNum++;
			DEBUG_printString("\r\nWrite verify failed!\r\n");
			goto NAND_WRITE_RETRY;
		} else {
			//print("+");
		}
		UTIL_waitLoop(200);

		srcBuf += hNandInfo->dataBytesPerPage;
		pageCnt++;
		pageNum++;

		if (pageNum == hNandInfo->pagesPerBlock)
		{
			blockNum++;
			pageNum = 0;
			print("block="); 
			print_hex(blockNum); 
			print(" \r");
			//print("\r\n");
			//print(".");
		}

	}
	while (pageCnt < (nandBoot->numPage+1));
	print("                   \r");
	NAND_protectBlocks(hNandInfo);

	return E_PASS;
}
