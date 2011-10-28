#preconf environment 
setenv mtdparts mtdparts=davinci_nand.0:4m(bootloader)ro,4m(kernel),-(filesystem)
setenv loadaddr 0x82000000
setenv autostart no

#flash kernel
fatload mmc 0 ${loadaddr} uImage
nand erase.part kernel
nand write ${loadaddr} 0x400000 ${filesize}

#flash filesystem 
fatload mmc 0 ${loadaddr} rootfs.ubi
nand erase.part filesystem
nand write ${loadaddr} 0x800000 ${filesize}

#postconf environment 
setenv bootargs mem=80M console=ttyS0,115200n8 ubi.mtd=2 root=ubi0:rootfs rootfstype=ubifs davinci_enc_mngr.ch0_output=LCD vpfe_capture.interface=1 video=davincifb:vid1=off ${mtdparts}
setenv bootcmd 'nboot 0x87000000 0 0x00400000; bootm'
setenv autostart yes
setenv bootdelay 0
saveenv

