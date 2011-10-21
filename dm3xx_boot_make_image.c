// --------------------------------------------------------------------------
//  PROJECT     : TI Booting and Flashing Utilities
//  AUTHOR      : Constantine Shulyupin http://www.LinuxDriver.co.il/
//  DESC        : Generates boot record and data image for DM3xx boot from SD card
//  LICENSE     : GNU General Public License
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <sdboot_flash_cfg.h>
#include <string.h>
#include <errno.h>
//#include <ctracer.h>

#define trvx(x)	{ printf("%s %x\n",#x,x); }

int dm3xx_boot_data_addr;

char block[BLOCK];

char * getenv2(char * name)
{
	char * e = getenv(name);
	if (!e) {
		printf("please define environment variable \"%s\"\n",name);
		exit(1);
	}
	//printf("using %s=%s\n",name,e);	
	return e;
}

int fwrite_int(int i, FILE * f)
{
	printf("%x ",i);	
	return fwrite(&i,sizeof(i),1,f);
}

int dm3xx_boot_rec_make(char * rec_fn)
{
	// generates SD card boot header for RBL and additional  data
	FILE * f = fopen(rec_fn,"w+");
	struct stat s={0,0,0,0,0,0,0,0};
	stat(getenv2("sdboot"), &s);
	printf("Image %s:", rec_fn);
	dm3xx_boot_data_addr=strtol(getenv2("dm3xx_boot_data_addr"),0,0);
	//trvx(dm3xx_boot_data_addr);
	if (! dm3xx_boot_data_addr ) {
		printf("please define dm3xx_boot_data_addr \n");
		exit(1);
	}
	fwrite_int(MAGIC_NUMBER_VALID,f);
	fwrite_int(UBL_GNU_ENTRY,f);
	//fwrite_int(UBL_CCS_ENTRY,f);
	fwrite_int(SDBOOT_SIZE/BLOCK,f);
	assert(s.st_size  < SDBOOT_SIZE * BLOCK);
	//fwrite_int((s.st_size+BLOCK-1)/BLOCK,f);
	fwrite_int((dm3xx_boot_data_addr+SDBOOT_SDC) / BLOCK,f);
	fwrite_int(0,f);
	fwrite_int(0,f);
	fwrite_int(0,f);
	fwrite_int(0,f);
	fwrite_int(dm3xx_boot_data_addr,f); // sdboot looks for data at this address on SD card
	fclose(f);
	printf("\n", rec_fn);
	return 0;
}

int copy_file(char * src_fn, FILE * dst, int offset)
{

	FILE * s = fopen(src_fn,"r"); 
	int size, ret;
	int total=0;
	struct stat st;
	stat(src_fn, &st);
	if (!s) {
		printf("no file \"%s\"\n",src_fn);
		exit(1);
	}
	if (  ftell(dst) > offset ) {
		fprintf(stderr,"ERROR: overlapping at %x (ftell = %lx)\n",offset,ftell(dst));
	}
	printf("%06x-%06lx, %8li bytes <- %s\n",offset,offset+st.st_size,st.st_size,src_fn);
	fseek(dst,offset,SEEK_SET);
	while ( ( size = fread(block,1,sizeof(block),s)) > 0 ) {
		//usleep(10000);
		ret = fwrite(block,1,size,dst);
		//printf("%i %i ",size,ret);
		if (ret <=  0) {
			perror("writing data");
			printf("total %i\n",total);
			//ret = fwrite(block,1,size,dst);
			printf("%i %i ",size,ret);
			if (ret <=  0) {
				exit(1);
			}
		}
		total+= ret;
	}
	fclose(s);
	return 0;
}

int copy_123(FILE * dst, int offset)
{
	long size = 512;
	int ret;
	if (  ftell(dst) > offset ) {
		fprintf(stderr,"ERROR: overlapping at %x\n",offset);
	}
	printf("%06x-%06lx, %8li bytes <- test pattern 1 2 3\n",offset,offset+size, size);
	fseek(dst,offset,SEEK_SET);
	short int i;
	for ( i = 0 ; i < size/ sizeof(i); i ++ ) {
		ret = fwrite(&i,sizeof(i),1,dst);
		if (ret <0) {
			perror("writing data");
			exit(1);
		}
	}
	return 0;
}

int sdcard_build_data(char * data_fn)
{
	printf("Writing %s\n",data_fn);
	FILE * f = fopen(data_fn,"r+"); // r,w, don't truncate
	if (!f) {
		perror("openning data file");
		exit(1);
	}
	fprintf(f,"dm3xx_boot_magic: sdboot: %x UBL:%x test:%x U-boot:%x kernel:%x root FS:%x\n\n",
			SDBOOT_SDC,TEST_SDC, UBL_SDC, UBOOT_SDC, KERNEL_SDC, ROOTFS_SDC);
	copy_file(getenv2("sdboot"),f,SDBOOT_SDC);
	copy_123(f,TEST_SDC);
	copy_file(getenv2("ubl"),f,UBL_SDC);
	copy_file(getenv2("uboot"),f,UBOOT_SDC);
	if (getenv("kernel") && strlen(getenv("kernel"))) copy_file(getenv2("kernel"),f,KERNEL_SDC);
	if (getenv("rootfs") && strlen(getenv("rootfs"))) copy_file(getenv2("rootfs"),f,ROOTFS_SDC);
	fclose(f);
}

int main()
{
	if (! getenv("dm3xx_boot_rec") && ! getenv("dm3xx_boot_data") ) {
		printf("please define env var 'dm3xx_boot_rec' or 'dm3xx_boot_data'\n");
		exit(1);
	}
	if ( getenv("dm3xx_boot_rec") )
		dm3xx_boot_rec_make(getenv2("dm3xx_boot_rec"));
	if ( getenv("dm3xx_boot_data") )
		sdcard_build_data(getenv2("dm3xx_boot_data"));
	return 0;
}
