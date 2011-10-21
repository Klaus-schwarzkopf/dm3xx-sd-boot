CROSSCOMPILE?= arm-none-linux-gnueabi-
CC= $(CROSSCOMPILE)gcc
OBJCOPY= $(CROSSCOMPILE)objcopy
OBJDUMP= $(CROSSCOMPILE)objdump

PLATFORM?= DM36x
CFLAGS+= -DUBL_NAND=1
CFLAGS+= -Os
CFLAGS+= -mabi=aapcs-linux
CFLAGS+= -I$(PLATFORM) -D$(PLATFORM)
CFLAGS+= -g -DANSI_COLORS
CFLAGS+= --include sdc_debug.h
LDFLAGS= -Wl,-T$(LDS) -nostdlib 
ENTRYPOINT= boot

SUBS+= ../flash_utils/Common
SUBS+= ../flash_utils/$(PLATFORM)/Common
SUBS+= ../flash_utils/Common/arch/arm926ejs
SUBS+= ../flash_utils/Common/sft
#SUBS+= ../flash_utils/Common/ubl
SUBS+= ../flash_utils/Common/gnu
SUBS+= ../flash_utils/Common/drivers
LDS= ../flash_utils/$(PLATFORM)/GNU/ubl/ubl.lds

SOURCES+= boot.c selfcopy.c device.c debug.c uart.c util.c memory_test.c sdcard_flash.c
SOURCES+= mmcsd_protocol.c mmcsd_evm.c
SOURCES+= nand.c device_nand.c sdc_debug.c
#SOURCES+= uartboot.c
SOURCES+= nand_copy.c

VPATH+= $(addprefix ,$(addsuffix /src/,$(SUBS))) 
VPATH+= $(PLATFORM)
CFLAGS+= $(addprefix -I,$(addsuffix /include,$(SUBS)))
CFLAGS+=  -I ../flash_utils/Common/ubl/include
OBJECTS+= $(patsubst %.c,$(PLATFORM)/%.o,$(SOURCES))
NAME= sdcard_flash
BINARY= $(NAME)_$(PLATFORM).bin
EXECUTABLE= $(PLATFORM)/$(NAME)

.PHONY : clean all

all: $(BINARY)

clean:
		-rm -rf -v $(OBJECTS) $(BINARY) $(EXECUTABLE)
		
$(BINARY): $(EXECUTABLE)
		$(OBJCOPY) --gap-fill 0xFF -S -O binary $< $@
		@echo -n "The entry point of the binary is 0x"
		@$(OBJDUMP) -t $< | grep -E '[0-9a-f]{8}*[0-9a-f]{8} \.$(ENTRYPOINT)' | sed  's/^\([0-9a-f]\{4\}\)\([0-9a-f]\{4\}\).*/\2/'
		ls -l $@

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(PLATFORM)/%.o: %.c
		@mkdir -p $(PLATFORM)
		$(CC) $(CFLAGS) $< -c -o $@      

show:
	# VPATH $(VPATH)
	# CFLAGS $(CFLAGS)
	# CURDIR $(CURDIR)
