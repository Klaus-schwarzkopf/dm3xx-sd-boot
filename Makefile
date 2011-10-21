

#arch=$(shell $(CC) -v 2>&1 | sed -n "s/.*target=\(\S\+\).*/\1/p" | sed -e "s/i.86.*/x86/" -e "s/arm.*/arm/" )
arch=$(shell uname  -m | sed -e "s/i.86.*/x86/" -e "s/arm.*/arm/" -e "s/x86.*/x86/")

BIN=bin.$(arch)

all: $(BIN)/dm3xx_boot_make_image
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
	rm -f dm3xx_boot_make_image
	rm -f -r bin.*

$(BIN)/dm3xx_boot_make_image:	dm3xx_boot_make_image.c
	@mkdir -p $(BIN)
	 $(CC) -g $< -o $@ -I sdcard_flash

install:
	./dm3xx_sd_boot data

$(BIN)/%.o: %.c
		@mkdir -p $(BIN)
		$(CC) $(CFLAGS) $< -c -o $@      
