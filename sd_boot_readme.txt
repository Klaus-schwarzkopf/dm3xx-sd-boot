This program is to burn the NAND flash from SD card. The SD card contains UBL, u-boot, kernel and filesys, and it is bootable. It is based on http://wiki.davincidsp.com/index.php/SD_card_boot_and_flashing_tool_for_DM355_and_DM365 with modifications to make it work with Leopard board.

edit dm3xx_sd_.config to choose the platform (DM36X or DM35X)

To prepare the SD card
1. insert a SD card ( SDHC is not supported) to a Linux PC
2. find out the device name of this SD card by looking at /dev/sd*
3. export PATH=$PATH:./bin.x86
4. make
5. sudo ./dm3xx_sd_boot format /dev/sdX (replace sdX with the SD device name)
6. remove the SD card, and plug it back in
7. make install
 
To burn NAND flash:
1. insert the SD card to Leopard 365
2. set position 2 of DIPSW1 (the 3 pos switch) to ON, 1 and 3 to OFF. This is SD card boot mode
3. power up the board, it will automatically erase the NAND flash, and burn UBL, u-boot, kernel and filesys
4. set all pos of DIPSW1 to OFF for NAND boot mode
5. connect serial cable to PC, power cycle the board, it should boot up.

Leopard Imaging, Inc
02/14/2010
