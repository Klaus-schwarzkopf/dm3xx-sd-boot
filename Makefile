

#arch=$(shell $(CC) -v 2>&1 | sed -n "s/.*target=\(\S\+\).*/\1/p" | sed -e "s/i.86.*/x86/" -e "s/arm.*/arm/" )
arch=$(shell uname  -m | sed -e "s/i.86.*/x86/" -e "s/arm.*/arm/" -e "s/x86.*/x86/")

BIN=bin.$(arch)
 
all: $(BIN)/dm3xx_boot_make_image flash_dm365_leopardboard.src
	make -C sdcard_flash PLATFORM=DM36x $@
	make -C sdcard_flash PLATFORM=DM35x $@
	@printf  "\\033[2;32mOK \\033[0;39m\n"

dirs=.
tags:
	ctags -Ru  $(dirs) 
	ctags -Rua --c-kinds=px $(dirs)


clean:
	make -C sdcard_flash PLATFORM=DM36x $@
	make -C sdcard_flash PLATFORM=DM35x $@
	#make -C ti-flash-utils/DM36x/GNU/ $@
	rm -f dm3xx_boot_make_image
	rm -f -r bin.*
	rm -f flash_dm365_leopardboard.src

$(BIN)/dm3xx_boot_make_image:	dm3xx_boot_make_image.c
	@mkdir -p $(BIN)
	 $(CC) -g $< -o $@ -I sdcard_flash

install:
	./dm3xx_sd_boot data
	./dm3xx_sd_boot copy

$(BIN)/%.o: %.c
		@mkdir -p $(BIN)
		$(CC) $(CFLAGS) $< -c -o $@   
		
%.src: %.cmd
		mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "flash-all" -d $< $@

#build_ubl:
	#make  -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=nand 
	#make  -C ti-flash-utils/DM36x/GNU/ubl/build/ TYPE=sdmmc 

#build_bc:
	#make -C ti-flash-utils/DM36x/GNU/bc/
	
