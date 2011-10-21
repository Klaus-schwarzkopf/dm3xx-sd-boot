/*
 *  Copyright 2007 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  Definitions & Register
 *
 */

#ifndef EVMDM355_
#define EVMDM355_

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Variable types                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */

#define Uint32  unsigned int
#define Uint16  unsigned short
#define Uint8   unsigned char
#define Int32   int
#define Int16   short
#define Int8    char


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Software Breakpoint code                                                *
 *      Uses inline assembly command                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */

#define SW_BREAKPOINT    asm( " .long 0xE1200070" );


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  AEMIF Controller                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define AEMIF_BASE              0x01E10000
#define AEMIF_AWCCR             *( volatile Uint32* )( AEMIF_BASE + 0x04 )
#define AEMIF_A1CR              *( volatile Uint32* )( AEMIF_BASE + 0x10 )
#define AEMIF_A2CR              *( volatile Uint32* )( AEMIF_BASE + 0x14 )
#define AEMIF_A3CR              *( volatile Uint32* )( AEMIF_BASE + 0x18 )
#define AEMIF_A4CR              *( volatile Uint32* )( AEMIF_BASE + 0x1C )
#define AEMIF_EIRR              *( volatile Uint32* )( AEMIF_BASE + 0x40 )
#define AEMIF_EIMR              *( volatile Uint32* )( AEMIF_BASE + 0x44 )
#define AEMIF_EIMSR             *( volatile Uint32* )( AEMIF_BASE + 0x48 )
#define AEMIF_EIMCR             *( volatile Uint32* )( AEMIF_BASE + 0x4C )
#define AEMIF_NANDFCR           *( volatile Uint32* )( AEMIF_BASE + 0x60 )
#define AEMIF_NANDFSR           *( volatile Uint32* )( AEMIF_BASE + 0x64 )
#define AEMIF_NANDECC2          *( volatile Uint32* )( AEMIF_BASE + 0x70 )
#define AEMIF_NANDECC3          *( volatile Uint32* )( AEMIF_BASE + 0x74 )
#define AEMIF_NANDECC4          *( volatile Uint32* )( AEMIF_BASE + 0x78 )
#define AEMIF_NANDECC5          *( volatile Uint32* )( AEMIF_BASE + 0x7C )

#define AEMIF_MAX_TIMEOUT_8BIT  0x3FFFFFFC
#define AEMIF_MAX_TIMEOUT_16BIT 0x3FFFFFFD

#define EMIF_CS2                2
#define EMIF_CS3                3
#define EMIF_CS4                4
#define EMIF_CS5                5

#define EMIF_CS0_BASE           0x02000000
#define EMIF_CS1_BASE           0x04000000

#define EMIF_NAND_MODE          1
#define EMIF_NORMAL_MODE        0

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Device System Controller                                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define SYSTEM_BASE         0x01C40000
#define PINMUX0             *( volatile Uint32* )( SYSTEM_BASE + 0x00 )
#define PINMUX1             *( volatile Uint32* )( SYSTEM_BASE + 0x04 )
#define PINMUX2             *( volatile Uint32* )( SYSTEM_BASE + 0x08 )
#define PINMUX3             *( volatile Uint32* )( SYSTEM_BASE + 0x0C )
#define PINMUX4             *( volatile Uint32* )( SYSTEM_BASE + 0x10 )
#define BOOTCFG             *( volatile Uint32* )( SYSTEM_BASE + 0x14 )
#define ARM_INTMUX          *( volatile Uint32* )( SYSTEM_BASE + 0x18 )
#define EDMA_INTMUX         *( volatile Uint32* )( SYSTEM_BASE + 0x1C )
#define DDR_SLEW            *( volatile Uint32* )( SYSTEM_BASE + 0x20 )
#define CLKOUT              *( volatile Uint32* )( SYSTEM_BASE + 0x24 )
#define DEVICE_ID           *( volatile Uint32* )( SYSTEM_BASE + 0x28 )
#define VDAC_CONFIG         *( volatile Uint32* )( SYSTEM_BASE + 0x2C )
#define TIMER64_CTL         *( volatile Uint32* )( SYSTEM_BASE + 0x30 )
#define USBPHY_CTL          *( volatile Uint32* )( SYSTEM_BASE + 0x34 )
#define MISC                *( volatile Uint32* )( SYSTEM_BASE + 0x38 )
#define MSTPRI0             *( volatile Uint32* )( SYSTEM_BASE + 0x3C )
#define MSTPRI1             *( volatile Uint32* )( SYSTEM_BASE + 0x40 )
#define VPSS_CLKCTL         *( volatile Uint32* )( SYSTEM_BASE + 0x44 )
#define DEEPSLEEP           *( volatile Uint32* )( SYSTEM_BASE + 0x48 )
#define DEBOUNCE0           *( volatile Uint32* )( SYSTEM_BASE + 0x50 )
#define DEBOUNCE1           *( volatile Uint32* )( SYSTEM_BASE + 0x54 )
#define DEBOUNCE2           *( volatile Uint32* )( SYSTEM_BASE + 0x58 )
#define DEBOUNCE3           *( volatile Uint32* )( SYSTEM_BASE + 0x5C )
#define DEBOUNCE4           *( volatile Uint32* )( SYSTEM_BASE + 0x60 )
#define DEBOUNCE5           *( volatile Uint32* )( SYSTEM_BASE + 0x64 )
#define DEBOUNCE6           *( volatile Uint32* )( SYSTEM_BASE + 0x68 )
#define DEBOUNCE7           *( volatile Uint32* )( SYSTEM_BASE + 0x6C )
#define VTPIOCR             *( volatile Uint32* )( SYSTEM_BASE + 0x70 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  DDR Controller                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define DDR_REG_BASE            0x20000000
#define DDR_DDRVTPER            *( volatile Uint32* )( 0x01C4004C )
#define DDR_DDRVTPR             *( volatile Uint32* )( 0x01C42038 )
#define DDR_SDRSTAT             *( volatile Uint32* )( DDR_REG_BASE + 0x04 )
#define DDR_SDBCR               *( volatile Uint32* )( DDR_REG_BASE + 0x08 )
#define DDR_SDRCR               *( volatile Uint32* )( DDR_REG_BASE + 0x0C )
#define DDR_SDTIMR              *( volatile Uint32* )( DDR_REG_BASE + 0x10 )
#define DDR_SDTIMR2             *( volatile Uint32* )( DDR_REG_BASE + 0x14 )
#define DDR_VBPR                *( volatile Uint32* )( DDR_REG_BASE + 0x20 )
#define DDR_IRR                 *( volatile Uint32* )( DDR_REG_BASE + 0xC0 )
#define DDR_IMR                 *( volatile Uint32* )( DDR_REG_BASE + 0xC4 )
#define DDR_IMSR                *( volatile Uint32* )( DDR_REG_BASE + 0xC8 )
#define DDR_IMCR                *( volatile Uint32* )( DDR_REG_BASE + 0xCC )
#define DDR_DDRPHYCR            *( volatile Uint32* )( DDR_REG_BASE + 0xE4 )
#define DDR_VTPIOCR             *( volatile Uint32* )( DDR_REG_BASE + 0xF0 )

#define DDR_BASE                0x80000000  // Start of SDRAM range
#define DDR_SIZE                0x08000000  // 128 MB

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  EDMA Controller                                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define EDMA_3CC_BASE           0x01C00000
#define EDMA_3CC_CCCFG          *( volatile Uint32* )( EDMA_3CC_BASE + 0x0004 )

/* Global Controller */
#define EDMA_3CC_ER             *( volatile Uint32* )( EDMA_3CC_BASE + 0x1000 )
#define EDMA_3CC_ERH            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1004 )
#define EDMA_3CC_ECR            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1008 )
#define EDMA_3CC_ECRH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x100C )
#define EDMA_3CC_ESR            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1010 )
#define EDMA_3CC_ESRH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1014 )
#define EDMA_3CC_CER            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1018 )
#define EDMA_3CC_CERH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x101C )
#define EDMA_3CC_EER            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1020 )
#define EDMA_3CC_EERH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1024 )
#define EDMA_3CC_EECR           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1028 )
#define EDMA_3CC_EECRH          *( volatile Uint32* )( EDMA_3CC_BASE + 0x102C )
#define EDMA_3CC_EESR           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1030 )
#define EDMA_3CC_EESRH          *( volatile Uint32* )( EDMA_3CC_BASE + 0x1034 )
#define EDMA_3CC_SER            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1038 )
#define EDMA_3CC_SERH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x103C )
#define EDMA_3CC_SECR           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1040 )
#define EDMA_3CC_SECRH          *( volatile Uint32* )( EDMA_3CC_BASE + 0x1044 )
#define EDMA_3CC_IER            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1050 )
#define EDMA_3CC_IERH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1054 )
#define EDMA_3CC_IECR           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1058 )
#define EDMA_3CC_IECRH          *( volatile Uint32* )( EDMA_3CC_BASE + 0x105C )
#define EDMA_3CC_IESR           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1060 )
#define EDMA_3CC_IESRH          *( volatile Uint32* )( EDMA_3CC_BASE + 0x1064 )
#define EDMA_3CC_IPR            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1068 )
#define EDMA_3CC_IPRH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x106C )
#define EDMA_3CC_ICR            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1070 )
#define EDMA_3CC_ICRH           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1074 )
#define EDMA_3CC_IEVAL          *( volatile Uint32* )( EDMA_3CC_BASE + 0x1078 )
#define EDMA_3CC_QER            *( volatile Uint32* )( EDMA_3CC_BASE + 0x1080 )
#define EDMA_3CC_QEER           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1084 )
#define EDMA_3CC_QEECR          *( volatile Uint32* )( EDMA_3CC_BASE + 0x1088 )
#define EDMA_3CC_QEESR          *( volatile Uint32* )( EDMA_3CC_BASE + 0x108C )
#define EDMA_3CC_QSER           *( volatile Uint32* )( EDMA_3CC_BASE + 0x1090 )
#define EDMA_3CC_QSECR          *( volatile Uint32* )( EDMA_3CC_BASE + 0x1094 )

#define EDMA_TC0_BASE           0x01C10000
#define EDMA_TC1_BASE           0x01C10400


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  GPIO Control                                                            *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define GPIO_BASE               0x01C67000

#define GPIO_PCR                *( volatile Uint32* )( GPIO_BASE + 0x04 )
#define GPIO_BINTEN             *( volatile Uint32* )( GPIO_BASE + 0x08 )

// For GPIO[0:31]
#define GPIO_DIR_BASE           ( 0x10 )   // Direction Cntl
#define GPIO_OUT_DATA_BASE      ( 0x14 )   // Output data
#define GPIO_SET_DATA_BASE      ( 0x18 )   // Set data
#define GPIO_CLR_DATA_BASE      ( 0x1C )   // Clear data
#define GPIO_IN_DATA_BASE       ( 0x20 )   // Input data
#define GPIO_SET_RIS_TRIG_BASE  ( 0x24 )   // Set rising edge intr
#define GPIO_CLR_RIS_TRIG_BASE  ( 0x28 )   // Clear rising edge intr
#define GPIO_SET_FAL_TRIG_BASE  ( 0x2C )   // Set falling edge intr
#define GPIO_CLR_FAL_TRIG_BASE  ( 0x30 )   // Clear falling edge intr
#define GPIO_INSTAT_BASE        ( 0x34 )   // Intr status
#define GPIO_BASE_OFFSET        0x28

#define GPIO_01_BASE            ( GPIO_BASE + 0x10 )
#define GPIO_23_BASE            ( GPIO_01_BASE + GPIO_BASE_OFFSET )
#define GPIO_45_BASE            ( GPIO_23_BASE + GPIO_BASE_OFFSET )
#define GPIO_6_BASE             ( GPIO_45_BASE + GPIO_BASE_OFFSET )

// For GPIO[0:31]
#define GPIO_DIR01              *( volatile Uint32* )( GPIO_BASE + 0x10 )
#define GPIO_OUT_DATA01         *( volatile Uint32* )( GPIO_BASE + 0x14 )
#define GPIO_SET_DATA01         *( volatile Uint32* )( GPIO_BASE + 0x18 )
#define GPIO_CLR_DATA01         *( volatile Uint32* )( GPIO_BASE + 0x1C )
#define GPIO_IN_DATA01          *( volatile Uint32* )( GPIO_BASE + 0x20 )
#define GPIO_SET_RIS_TRIG01     *( volatile Uint32* )( GPIO_BASE + 0x24 )
#define GPIO_CLR_RIS_TRIG01     *( volatile Uint32* )( GPIO_BASE + 0x28 )
#define GPIO_SET_FAL_TRIG01     *( volatile Uint32* )( GPIO_BASE + 0x2C )
#define GPIO_CLR_FAL_TRIG01     *( volatile Uint32* )( GPIO_BASE + 0x30 )
#define GPIO_INSTAT01           *( volatile Uint32* )( GPIO_BASE + 0x34 )

// For GPIO[32:63]
#define GPIO_DIR23              *( volatile Uint32* )( GPIO_BASE + 0x38 )
#define GPIO_OUT_DATA23         *( volatile Uint32* )( GPIO_BASE + 0x3C )
#define GPIO_SET_DATA23         *( volatile Uint32* )( GPIO_BASE + 0x40 )
#define GPIO_CLR_DATA23         *( volatile Uint32* )( GPIO_BASE + 0x44 )
#define GPIO_IN_DATA23          *( volatile Uint32* )( GPIO_BASE + 0x48 )
#define GPIO_SET_RIS_TRIG23     *( volatile Uint32* )( GPIO_BASE + 0x4C )
#define GPIO_CLR_RIS_TRIG23     *( volatile Uint32* )( GPIO_BASE + 0x50 )
#define GPIO_SET_FAL_TRIG23     *( volatile Uint32* )( GPIO_BASE + 0x54 )
#define GPIO_CLR_FAL_TRIG23     *( volatile Uint32* )( GPIO_BASE + 0x58 )
#define GPIO_INSTAT23           *( volatile Uint32* )( GPIO_BASE + 0x5C )

// For GPIO[64:70]
#define GPIO_DIR45              *( volatile Uint32* )( GPIO_BASE + 0x60 )
#define GPIO_OUT_DATA45         *( volatile Uint32* )( GPIO_BASE + 0x64 )
#define GPIO_SET_DATA45         *( volatile Uint32* )( GPIO_BASE + 0x68 )
#define GPIO_CLR_DATA45         *( volatile Uint32* )( GPIO_BASE + 0x6C )
#define GPIO_IN_DATA45          *( volatile Uint32* )( GPIO_BASE + 0x70 )
#define GPIO_SET_RIS_TRIG45     *( volatile Uint32* )( GPIO_BASE + 0x74 )
#define GPIO_CLR_RIS_TRIG45     *( volatile Uint32* )( GPIO_BASE + 0x78 )
#define GPIO_SET_FAL_TRIG45     *( volatile Uint32* )( GPIO_BASE + 0x7C )
#define GPIO_CLR_FAL_TRIG45     *( volatile Uint32* )( GPIO_BASE + 0x80 )
#define GPIO_INSTAT45           *( volatile Uint32* )( GPIO_BASE + 0x84 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  I2C Controller                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define I2C_BASE                0x01C21000
#define I2C_OAR                 *( volatile Uint32* )( I2C_BASE + 0x00 )
#define I2C_ICIMR               *( volatile Uint32* )( I2C_BASE + 0x04 )
#define I2C_ICSTR               *( volatile Uint32* )( I2C_BASE + 0x08 )
#define I2C_ICCLKL              *( volatile Uint32* )( I2C_BASE + 0x0C )
#define I2C_ICCLKH              *( volatile Uint32* )( I2C_BASE + 0x10 )
#define I2C_ICCNT               *( volatile Uint32* )( I2C_BASE + 0x14 )
#define I2C_ICDRR               *( volatile Uint32* )( I2C_BASE + 0x18 )
#define I2C_ICSAR               *( volatile Uint32* )( I2C_BASE + 0x1C )
#define I2C_ICDXR               *( volatile Uint32* )( I2C_BASE + 0x20 )
#define I2C_ICMDR               *( volatile Uint32* )( I2C_BASE + 0x24 )
#define I2C_ICIVR               *( volatile Uint32* )( I2C_BASE + 0x28 )
#define I2C_ICEMDR              *( volatile Uint32* )( I2C_BASE + 0x2C )
#define I2C_ICPSC               *( volatile Uint32* )( I2C_BASE + 0x30 )
#define I2C_ICPID1              *( volatile Uint32* )( I2C_BASE + 0x34 )
#define I2C_ICPID2              *( volatile Uint32* )( I2C_BASE + 0x38 )

/* I2C Field Definitions */
#define ICOAR_MASK_7                    0x007F
#define ICOAR_MASK_10                   0x03FF
#define ICSAR_MASK_7                    0x007F
#define ICSAR_MASK_10                   0x03FF
#define ICOAR_OADDR                     0x007f
#define ICSAR_SADDR                     0x0050

#define ICSTR_SDIR                      0x4000
#define ICSTR_NACKINT                   0x2000
#define ICSTR_BB                        0x1000
#define ICSTR_RSFULL                    0x0800
#define ICSTR_XSMT                      0x0400
#define ICSTR_AAS                       0x0200
#define ICSTR_AD0                       0x0100
#define ICSTR_SCD                       0x0020
#define ICSTR_ICXRDY                    0x0010
#define ICSTR_ICRRDY                    0x0008
#define ICSTR_ARDY                      0x0004
#define ICSTR_NACK                      0x0002
#define ICSTR_AL                        0x0001

#define ICMDR_NACKMOD                   0x8000
#define ICMDR_FREE                      0x4000
#define ICMDR_STT                       0x2000
#define ICMDR_IDLEEN                    0x1000
#define ICMDR_STP                       0x0800
#define ICMDR_MST                       0x0400
#define ICMDR_TRX                       0x0200
#define ICMDR_XA                        0x0100
#define ICMDR_RM                        0x0080
#define ICMDR_DLB                       0x0040
#define ICMDR_IRS                       0x0020
#define ICMDR_STB                       0x0010
#define ICMDR_FDF                       0x0008
#define ICMDR_BC_MASK                   0x0007

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  INTC controller                                                         *
 *      Controls the Interrupts                                             *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define INTC_BASE               0x01C48000
#define INTC_FIQ0               *( volatile Uint32* )( INTC_BASE + 0x00 )
#define INTC_FIQ1               *( volatile Uint32* )( INTC_BASE + 0x04 )
#define INTC_IRQ0               *( volatile Uint32* )( INTC_BASE + 0x08 )
#define INTC_IRQ1               *( volatile Uint32* )( INTC_BASE + 0x0C )
#define INTC_FIQENTRY           *( volatile Uint32* )( INTC_BASE + 0x10 )
#define INTC_IRQENTRY           *( volatile Uint32* )( INTC_BASE + 0x14 )
#define INTC_EINT0              *( volatile Uint32* )( INTC_BASE + 0x18 )
#define INTC_EINT1              *( volatile Uint32* )( INTC_BASE + 0x1C )
#define INTC_INTCTL             *( volatile Uint32* )( INTC_BASE + 0x20 )
#define INTC_EABASE             *( volatile Uint32* )( INTC_BASE + 0x24 )
#define INTC_INTPRI0            *( volatile Uint32* )( INTC_BASE + 0x30 )
#define INTC_INTPRI1            *( volatile Uint32* )( INTC_BASE + 0x34 )
#define INTC_INTPRI2            *( volatile Uint32* )( INTC_BASE + 0x38 )
#define INTC_INTPRI3            *( volatile Uint32* )( INTC_BASE + 0x3C )
#define INTC_INTPRI4            *( volatile Uint32* )( INTC_BASE + 0x40 )
#define INTC_INTPRI5            *( volatile Uint32* )( INTC_BASE + 0x44 )
#define INTC_INTPRI6            *( volatile Uint32* )( INTC_BASE + 0x48 )
#define INTC_INTPRI7            *( volatile Uint32* )( INTC_BASE + 0x4C )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  ASP Controllers                                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define MCBSP0_BASE              0x01E02000
#define MCBSP0_DRR_32BIT         *( volatile Uint32* )( MCBSP0_BASE + 0x00 )
#define MCBSP0_DRR_16BIT         *( volatile Uint16* )( MCBSP0_BASE + 0x00 )
#define MCBSP0_DRR_8BIT          *( volatile Uint8* ) ( MCBSP0_BASE + 0x00 )
#define MCBSP0_DXR_32BIT         *( volatile Uint32* )( MCBSP0_BASE + 0x04 )
#define MCBSP0_DXR_16BIT         *( volatile Uint16* )( MCBSP0_BASE + 0x04 )
#define MCBSP0_DXR_8BIT          *( volatile Uint8* ) ( MCBSP0_BASE + 0x04 )
#define MCBSP0_SPCR              *( volatile Uint32* )( MCBSP0_BASE + 0x08 )
#define MCBSP0_RCR               *( volatile Uint32* )( MCBSP0_BASE + 0x0C )
#define MCBSP0_XCR               *( volatile Uint32* )( MCBSP0_BASE + 0x10 )
#define MCBSP0_SRGR              *( volatile Uint32* )( MCBSP0_BASE + 0x14 )
#define MCBSP0_MCR               *( volatile Uint32* )( MCBSP0_BASE + 0x18 )
#define MCBSP0_PCR               *( volatile Uint32* )( MCBSP0_BASE + 0x24 )

#define MCBSP1_BASE              0x01E04000
#define MCBSP1_DRR_32BIT         *( volatile Uint32* )( MCBSP1_BASE + 0x00 )
#define MCBSP1_DRR_16BIT         *( volatile Uint16* )( MCBSP1_BASE + 0x00 )
#define MCBSP1_DRR_8BIT          *( volatile Uint8* ) ( MCBSP1_BASE + 0x00 )
#define MCBSP1_DXR_32BIT         *( volatile Uint32* )( MCBSP1_BASE + 0x04 )
#define MCBSP1_DXR_16BIT         *( volatile Uint16* )( MCBSP1_BASE + 0x04 )
#define MCBSP1_DXR_8BIT          *( volatile Uint8* ) ( MCBSP1_BASE + 0x04 )
#define MCBSP1_SPCR              *( volatile Uint32* )( MCBSP1_BASE + 0x08 )
#define MCBSP1_RCR               *( volatile Uint32* )( MCBSP1_BASE + 0x0C )
#define MCBSP1_XCR               *( volatile Uint32* )( MCBSP1_BASE + 0x10 )
#define MCBSP1_SRGR              *( volatile Uint32* )( MCBSP1_BASE + 0x14 )
#define MCBSP1_MCR               *( volatile Uint32* )( MCBSP1_BASE + 0x18 )
#define MCBSP1_PCR               *( volatile Uint32* )( MCBSP1_BASE + 0x24 )

#define MCBSP_SPCR_FREE                     0x02000000
#define MCBSP_SPCR_SOFT                     0x01000000
#define MCBSP_SPCR_FRST                     0x00800000
#define MCBSP_SPCR_GRST                     0x00400000
#define MCBSP_SPCR_XSYNCERR                 0x00080000
#define MCBSP_SPCR_XEMPTY                   0x00040000
#define MCBSP_SPCR_XRDY                     0x00020000
#define MCBSP_SPCR_XRST                     0x00010000
#define MCBSP_SPCR_DLB                      0x00008000
#define MCBSP_SPCR_DXENA                    0x00000020
#define MCBSP_SPCR_ABIS                     0x00000010
#define MCBSP_SPCR_RSYNCERR                 0x00000008
#define MCBSP_SPCR_RFULL                    0x00000004
#define MCBSP_SPCR_RRDY                     0x00000002
#define MCBSP_SPCR_RRST                     0x00000001


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  MMC Controller                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define MMC_BASE                0x01E11000
#define MMC_MMCCTL              *( volatile Uint32* )( MMC_BASE + 0x00 )
#define MMC_MMCCLK              *( volatile Uint32* )( MMC_BASE + 0x04 )
#define MMC_MMCST0              *( volatile Uint32* )( MMC_BASE + 0x08 )
#define MMC_MMCST1              *( volatile Uint32* )( MMC_BASE + 0x0C )
#define MMC_MMCIM               *( volatile Uint32* )( MMC_BASE + 0x10 )
#define MMC_MMCTOR              *( volatile Uint32* )( MMC_BASE + 0x14 )
#define MMC_MMCTOD              *( volatile Uint32* )( MMC_BASE + 0x18 )
#define MMC_MMCBLEN             *( volatile Uint32* )( MMC_BASE + 0x1C )
#define MMC_MMCNBLK             *( volatile Uint32* )( MMC_BASE + 0x20 )
#define MMC_MMCNBLC             *( volatile Uint32* )( MMC_BASE + 0x24 )
#define MMC_MMCDRR              *( volatile Uint32* )( MMC_BASE + 0x28 )
#define MMC_MMCDXR              *( volatile Uint32* )( MMC_BASE + 0x2C )
#define MMC_MMCCMD              *( volatile Uint32* )( MMC_BASE + 0x30 )
#define MMC_MMCARGHL            *( volatile Uint32* )( MMC_BASE + 0x34 )
#define MMC_MMCRSP01            *( volatile Uint32* )( MMC_BASE + 0x38 )
#define MMC_MMCRSP23            *( volatile Uint32* )( MMC_BASE + 0x3C )
#define MMC_MMCRSP45            *( volatile Uint32* )( MMC_BASE + 0x40 )
#define MMC_MMCRSP67            *( volatile Uint32* )( MMC_BASE + 0x44 )
#define MMC_MMCDRSP             *( volatile Uint32* )( MMC_BASE + 0x48 )
#define MMC_MMCCIDX             *( volatile Uint32* )( MMC_BASE + 0x50 )
#define MMC_SDIOCTL             *( volatile Uint32* )( MMC_BASE + 0x64 )
#define MMC_SDIOST0             *( volatile Uint32* )( MMC_BASE + 0x68 )
#define MMC_SDIOIEN             *( volatile Uint32* )( MMC_BASE + 0x6C )
#define MMC_SDIOIST             *( volatile Uint32* )( MMC_BASE + 0x70 )
#define MMC_MMCFIFOCTL          *( volatile Uint32* )( MMC_BASE + 0x74 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  MemStick controller                                                     *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define MS_BASE                 0x01E12000
#define MS_MSCMD                *( volatile Uint32* )( MS_BASE + 0x00 )
#define MS_MSDATA               *( volatile Uint32* )( MS_BASE + 0x04 )
#define MS_MSSTAT               *( volatile Uint32* )( MS_BASE + 0x08 )
#define MS_MSSYST               *( volatile Uint32* )( MS_BASE + 0x0C )
#define MS_MSMC                 *( volatile Uint32* )( MS_BASE + 0x20 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  PLL1 Controller                                                         *
 *      Generates DSP, ARM clocks                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define PLL1_BASE               0x01C40800
#define PLL1_PID                *( volatile Uint32* )( PLL1_BASE + 0x000 )
#define PLL1_RSTYPE             *( volatile Uint32* )( PLL1_BASE + 0x0E4 )
#define PLL1_PLLCTL             *( volatile Uint32* )( PLL1_BASE + 0x100 )
#define PLL1_PLLM               *( volatile Uint32* )( PLL1_BASE + 0x110 )
#define PLL1_PLLDIV1            *( volatile Uint32* )( PLL1_BASE + 0x118 )
#define PLL1_PLLDIV2            *( volatile Uint32* )( PLL1_BASE + 0x11C )
#define PLL1_PLLDIV3            *( volatile Uint32* )( PLL1_BASE + 0x120 )
#define PLL1_POSTDIV            *( volatile Uint32* )( PLL1_BASE + 0x128 )
#define PLL1_BPDIV              *( volatile Uint32* )( PLL1_BASE + 0x12C )
#define PLL1_PLLCMD             *( volatile Uint32* )( PLL1_BASE + 0x138 )
#define PLL1_PLLSTAT            *( volatile Uint32* )( PLL1_BASE + 0x13C )
#define PLL1_CKEN               *( volatile Uint32* )( PLL1_BASE + 0x148 )
#define PLL1_CKSTAT             *( volatile Uint32* )( PLL1_BASE + 0x14C )
#define PLL1_SYSTAT             *( volatile Uint32* )( PLL1_BASE + 0x150 )
#define PLL1_PLLDIV4            *( volatile Uint32* )( PLL1_BASE + 0x160 )
#define PLL1_PLLDIV5            *( volatile Uint32* )( PLL1_BASE + 0x164 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  PLL2 Controller                                                         *
 *      Generates DDR2, VPBE clocks                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define PLL2_BASE               0x01C40C00
#define PLL2_PID                *( volatile Uint32* )( PLL2_BASE + 0x000 )
#define PLL2_RSTYPE             *( volatile Uint32* )( PLL2_BASE + 0x0E4 )
#define PLL2_PLLCTL             *( volatile Uint32* )( PLL2_BASE + 0x100 )
#define PLL2_PLLM               *( volatile Uint32* )( PLL2_BASE + 0x110 )
#define PLL2_PLLDIV1            *( volatile Uint32* )( PLL2_BASE + 0x118 )
#define PLL2_PLLDIV2            *( volatile Uint32* )( PLL2_BASE + 0x11C )
#define PLL2_PLLDIV3            *( volatile Uint32* )( PLL2_BASE + 0x120 )
#define PLL2_POSTDIV            *( volatile Uint32* )( PLL2_BASE + 0x128 )
#define PLL2_BPDIV              *( volatile Uint32* )( PLL2_BASE + 0x12C )
#define PLL2_PLLCMD             *( volatile Uint32* )( PLL2_BASE + 0x138 )
#define PLL2_PLLSTAT            *( volatile Uint32* )( PLL2_BASE + 0x13C )
#define PLL2_CKEN               *( volatile Uint32* )( PLL2_BASE + 0x148 )
#define PLL2_CKSTAT             *( volatile Uint32* )( PLL2_BASE + 0x14C )
#define PLL2_SYSTAT             *( volatile Uint32* )( PLL2_BASE + 0x150 )
#define PLL2_PLLDIV4            *( volatile Uint32* )( PLL2_BASE + 0x160 )
#define PLL2_PLLDIV5            *( volatile Uint32* )( PLL2_BASE + 0x164 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  PSC ( Power and Sleep Controller )                                      *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define PSC_BASE                0x01C41000
#define PSC_INTEVAL             *( volatile Uint32* )( PSC_BASE + 0x018 )
#define PSC_MERRPR0             *( volatile Uint32* )( PSC_BASE + 0x040 )
#define PSC_MERRPR1             *( volatile Uint32* )( PSC_BASE + 0x044 )
#define PSC_MERRCR0             *( volatile Uint32* )( PSC_BASE + 0x050 )
#define PSC_MERRCR1             *( volatile Uint32* )( PSC_BASE + 0x054 )
#define PSC_PERRPR              *( volatile Uint32* )( PSC_BASE + 0x060 )
#define PSC_PERRCR              *( volatile Uint32* )( PSC_BASE + 0x068 )
#define PSC_EPCPR               *( volatile Uint32* )( PSC_BASE + 0x070 )
#define PSC_EPCcR               *( volatile Uint32* )( PSC_BASE + 0x078 )
#define PSC_PTCMD               *( volatile Uint32* )( PSC_BASE + 0x120 )
#define PSC_PTSTAT              *( volatile Uint32* )( PSC_BASE + 0x128 )
#define PSC_PDSTAT0             *( volatile Uint32* )( PSC_BASE + 0x200 )
#define PSC_PDSTAT1             *( volatile Uint32* )( PSC_BASE + 0x204 )
#define PSC_PDCTL0              *( volatile Uint32* )( PSC_BASE + 0x300 )
#define PSC_PDCTL1              *( volatile Uint32* )( PSC_BASE + 0x304 )
#define PSC_MDSTAT_BASE         ( PSC_BASE + 0x800 )
#define PSC_MDCTL_BASE          ( PSC_BASE + 0xA00 )

#define PSC_MDSTAT_DSP          *( volatile Uint32* )( PSC_MDSTAT_BASE + ( 4 * 39 ) )
#define PSC_MDCTL_DSP           *( volatile Uint32* )( PSC_MDCTL_BASE  + ( 4 * 39 ) )
#define PSC_MDSTAT_IMCOP        *( volatile Uint32* )( PSC_MDSTAT_BASE + ( 4 * 40 ) )
#define PSC_MDCTL_IMCOP         *( volatile Uint32* )( PSC_MDCTL_BASE  + ( 4 * 40 ) )

/* Power Domains */
#define ALWAYSON_POWER_DOMAIN   0
#define DSP_POWER_DOMAIN        1

/* Module Domains */
#define LPSC_VPSSMSTR           0   // VPSS Master
#define LPSC_VPSSSLV            1   // VPSS Slave
#ifndef LPSC_TPCC
#define LPSC_TPCC               2   // TPCC
#define LPSC_TPTC0              3   // TPTC0
#define LPSC_TPTC1              4   // TPTC1
#define LPSC_EMAC               5   // EMAC
#define LPSC_EMAC_WRAPPER       6   // EMAC WRAPPER
#define LPSC_USB                9   // USB
#define LPSC_ATA                10  // ATA
#define LPSC_VLYNQ              11  // VLYNQ
#define LPSC_DDR_EMIF           13  // DDR_EMIF
#define LPSC_AEMIF              14  // AEMIF
#define LPSC_MMC_SD             15  // MMC_SD
#define LPSC_ASP                17  // McBSP
#define LPSC_I2C                18  // I2C
#define LPSC_UART0              19  // UART0
#define LPSC_UART1              20  // UART1
#define LPSC_UART2              21  // UART2
#define LPSC_SPI                22  // SPI
#define LPSC_PWM0               23  // PWM0
#define LPSC_PWM1               24  // PWM1
#define LPSC_PWM2               25  // PWM2
#define LPSC_GPIO               26  // GPIO
#define LPSC_TIMER0             27  // TIMER0
#define LPSC_TIMER1             28  // TIMER1
#define LPSC_TIMER2             29  // TIMER2
#define LPSC_SYSTEM_SUBSYS      30  // SYSTEM SUBSYSTEM
#define LPSC_ARM                31  // ARM
#define LPSC_DSP                39  // GEM
#endif
#define LPSC_VICP               40  // IMCOP

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  PWM Controller                                                          *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define PWM0_BASE               0x01C22000
#define PWM0_PID                *( volatile Uint32* )( PWM0_BASE + 0x00 )
#define PWM0_PCR                *( volatile Uint32* )( PWM0_BASE + 0x04 )
#define PWM0_CFG                *( volatile Uint32* )( PWM0_BASE + 0x08 )
#define PWM0_START              *( volatile Uint32* )( PWM0_BASE + 0x0C )
#define PWM0_RPT                *( volatile Uint32* )( PWM0_BASE + 0x10 )
#define PWM0_PER                *( volatile Uint32* )( PWM0_BASE + 0x14 )
#define PWM0_PH1D               *( volatile Uint32* )( PWM0_BASE + 0x18 )

#define PWM1_BASE               0x01C22400
#define PWM1_PID                *( volatile Uint32* )( PWM1_BASE + 0x00 )
#define PWM1_PCR                *( volatile Uint32* )( PWM1_BASE + 0x04 )
#define PWM1_CFG                *( volatile Uint32* )( PWM1_BASE + 0x08 )
#define PWM1_START              *( volatile Uint32* )( PWM1_BASE + 0x0C )
#define PWM1_RPT                *( volatile Uint32* )( PWM1_BASE + 0x10 )
#define PWM1_PER                *( volatile Uint32* )( PWM1_BASE + 0x14 )
#define PWM1_PH1D               *( volatile Uint32* )( PWM1_BASE + 0x18 )

#define PWM2_BASE               0x01C22800
#define PWM2_PID                *( volatile Uint32* )( PWM2_BASE + 0x00 )
#define PWM2_PCR                *( volatile Uint32* )( PWM2_BASE + 0x04 )
#define PWM2_CFG                *( volatile Uint32* )( PWM2_BASE + 0x08 )
#define PWM2_START              *( volatile Uint32* )( PWM2_BASE + 0x0C )
#define PWM2_RPT                *( volatile Uint32* )( PWM2_BASE + 0x10 )
#define PWM2_PER                *( volatile Uint32* )( PWM2_BASE + 0x14 )
#define PWM2_PH1D               *( volatile Uint32* )( PWM2_BASE + 0x18 )

#define PWM_PID                 ( 0x00 )
#define PWM_PCR                 ( 0x04 )
#define PWM_CFG                 ( 0x08 )
#define PWM_START               ( 0x0C )
#define PWM_RPT                 ( 0x10 )
#define PWM_PER                 ( 0x14 )
#define PWM_PH1D                ( 0x18 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Timer Controller                                                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define TIMER0_BASE         0x01C21400
#define TIMER0_EMUMGT       *( volatile Uint32* )( TIMER0_BASE + 0x04 )
#define TIMER0_TIM12        *( volatile Uint32* )( TIMER0_BASE + 0x10 )
#define TIMER0_TIM34        *( volatile Uint32* )( TIMER0_BASE + 0x14 )
#define TIMER0_PRD12        *( volatile Uint32* )( TIMER0_BASE + 0x18 )
#define TIMER0_PRD34        *( volatile Uint32* )( TIMER0_BASE + 0x1C )
#define TIMER0_TRC          *( volatile Uint32* )( TIMER0_BASE + 0x20 )
#define TIMER0_TGCR         *( volatile Uint32* )( TIMER0_BASE + 0x24 )

#define TIMER1_BASE         0x01C21800
#define TIMER1_EMUMGT       *( volatile Uint32* )( TIMER1_BASE + 0x04 )
#define TIMER1_TIM12        *( volatile Uint32* )( TIMER1_BASE + 0x10 )
#define TIMER1_TIM34        *( volatile Uint32* )( TIMER1_BASE + 0x14 )
#define TIMER1_PRD12        *( volatile Uint32* )( TIMER1_BASE + 0x18 )
#define TIMER1_PRD34        *( volatile Uint32* )( TIMER1_BASE + 0x1C )
#define TIMER1_TRC          *( volatile Uint32* )( TIMER1_BASE + 0x20 )
#define TIMER1_TGCR         *( volatile Uint32* )( TIMER1_BASE + 0x24 )

#define TIMER2_BASE         0x01C21C00
#define TIMER2_EMUMGT       *( volatile Uint32* )( TIMER2_BASE + 0x04 )
#define TIMER2_TIM12        *( volatile Uint32* )( TIMER2_BASE + 0x10 )
#define TIMER2_TIM34        *( volatile Uint32* )( TIMER2_BASE + 0x14 )
#define TIMER2_PRD12        *( volatile Uint32* )( TIMER2_BASE + 0x18 )
#define TIMER2_PRD34        *( volatile Uint32* )( TIMER2_BASE + 0x1C )
#define TIMER2_TRC          *( volatile Uint32* )( TIMER2_BASE + 0x20 )
#define TIMER2_TGCR         *( volatile Uint32* )( TIMER2_BASE + 0x24 )
#define TIMER2_WDTCR            *( volatile Uint32* )( TIMER2_BASE + 0x28 )

#define TIMER_EMUMGT            ( 0x04 )
#define TIMER_TIM12             ( 0x10 )
#define TIMER_TIM34             ( 0x14 )
#define TIMER_PRD12             ( 0x18 )
#define TIMER_PRD34             ( 0x1C )
#define TIMER_TRC               ( 0x20 )
#define TIMER_TGCR              ( 0x24 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  UART Controller                                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define UART0_BASE          0x01C20000
#define UART0_RBR           *( volatile Uint32* )( UART0_BASE + 0x00 )
#define UART0_THR           *( volatile Uint32* )( UART0_BASE + 0x00 )
#define UART0_IER           *( volatile Uint32* )( UART0_BASE + 0x04 )
#define UART0_IIR           *( volatile Uint32* )( UART0_BASE + 0x08 )
#define UART0_FCR           *( volatile Uint32* )( UART0_BASE + 0x08 )
#define UART0_LCR           *( volatile Uint32* )( UART0_BASE + 0x0C )
#define UART0_MCR           *( volatile Uint32* )( UART0_BASE + 0x10 )
#define UART0_LSR           *( volatile Uint32* )( UART0_BASE + 0x14 )
#define UART0_DLL           *( volatile Uint32* )( UART0_BASE + 0x20 )
#define UART0_DLH           *( volatile Uint32* )( UART0_BASE + 0x24 )
#define UART0_PID1          *( volatile Uint32* )( UART0_BASE + 0x28 )
#define UART0_PID2          *( volatile Uint32* )( UART0_BASE + 0x2C )
#define UART0_PWREMU_MGMT   *( volatile Uint32* )( UART0_BASE + 0x30 )

#define UART1_BASE          0x01C20400
#define UART1_RBR           *( volatile Uint32* )( UART1_BASE + 0x00 )
#define UART1_THR           *( volatile Uint32* )( UART1_BASE + 0x00 )
#define UART1_IER           *( volatile Uint32* )( UART1_BASE + 0x04 )
#define UART1_IIR           *( volatile Uint32* )( UART1_BASE + 0x08 )
#define UART1_FCR           *( volatile Uint32* )( UART1_BASE + 0x08 )
#define UART1_LCR           *( volatile Uint32* )( UART1_BASE + 0x0C )
#define UART1_MCR           *( volatile Uint32* )( UART1_BASE + 0x10 )
#define UART1_LSR           *( volatile Uint32* )( UART1_BASE + 0x14 )
#define UART1_DLL           *( volatile Uint32* )( UART1_BASE + 0x20 )
#define UART1_DLH           *( volatile Uint32* )( UART1_BASE + 0x24 )
#define UART1_PID1          *( volatile Uint32* )( UART1_BASE + 0x28 )
#define UART1_PID2          *( volatile Uint32* )( UART1_BASE + 0x2C )
#define UART1_PWREMU_MGMT   *( volatile Uint32* )( UART1_BASE + 0x30 )

#define UART_RBR                ( 0x00 )
#define UART_THR                ( 0x00 )
#define UART_IER                ( 0x04 )
#define UART_IIR                ( 0x08 )
#define UART_FCR                ( 0x08 )
#define UART_LCR                ( 0x0C )
#define UART_MCR                ( 0x10 )
#define UART_LSR                ( 0x14 )
#define UART_DLL                ( 0x20 )
#define UART_DLH                ( 0x24 )
#define UART_PID1               ( 0x28 )
#define UART_PID2               ( 0x2C )
#define UART_PWREMU_MGMT        ( 0x30 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *   VPSS Control                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define VPSS_CLK_CTRL           *( volatile Uint32* )0x01C40044

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *   VPBE Control                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define VPBE_BASE               0x01C70400
#define VPBE_PID                *( volatile Uint32* )( VPBE_BASE + 0x00 )
#define VPBE_PCR                *( volatile Uint32* )( VPBE_BASE + 0x04 )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *   VPBE On-Screen Display                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define VPBE_OSD_BASE           0x01C70200
#define VPBE_OSD_MODE           *( volatile Uint32* )( VPBE_OSD_BASE + 0x00 )
#define VPBE_OSD_VIDWINMD       *( volatile Uint32* )( VPBE_OSD_BASE + 0x04 )
#define VPBE_OSD_OSDWIN0MD      *( volatile Uint32* )( VPBE_OSD_BASE + 0x08 )
#define VPBE_OSD_OSDWIN1MD      *( volatile Uint32* )( VPBE_OSD_BASE + 0x0C )
#define VPBE_OSD_RECTCUR        *( volatile Uint32* )( VPBE_OSD_BASE + 0x10 )
#define VPBE_OSD_VIDWIN0OFST    *( volatile Uint32* )( VPBE_OSD_BASE + 0x18 )
#define VPBE_OSD_VIDWIN1OFST    *( volatile Uint32* )( VPBE_OSD_BASE + 0x1C )
#define VPBE_OSD_OSDWIN0OFST    *( volatile Uint32* )( VPBE_OSD_BASE + 0x20 )
#define VPBE_OSD_OSDWIN1OFST    *( volatile Uint32* )( VPBE_OSD_BASE + 0x24 )
#define VPBE_OSD_VIDWIN0ADR     *( volatile Uint32* )( VPBE_OSD_BASE + 0x2C )
#define VPBE_OSD_VIDWIN1ADR     *( volatile Uint32* )( VPBE_OSD_BASE + 0x30 )
#define VPBE_OSD_VIDWINADH      *( volatile Uint32* )( VPBE_OSD_BASE + 0x34 )
#define VPBE_OSD_OSDWIN0ADL     *( volatile Uint32* )( VPBE_OSD_BASE + 0x38 )
#define VPBE_OSD_OSDWIN1ADL     *( volatile Uint32* )( VPBE_OSD_BASE + 0x3C )
#define VPBE_OSD_BASEPX         *( volatile Uint32* )( VPBE_OSD_BASE + 0x40 )
#define VPBE_OSD_BASEPY         *( volatile Uint32* )( VPBE_OSD_BASE + 0x44 )
#define VPBE_OSD_VIDWIN0XP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x48 )
#define VPBE_OSD_VIDWIN0YP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x4C )
#define VPBE_OSD_VIDWIN0XL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x50 )
#define VPBE_OSD_VIDWIN0YL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x54 )
#define VPBE_OSD_VIDWIN1XP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x58 )
#define VPBE_OSD_VIDWIN1YP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x5C )
#define VPBE_OSD_VIDWIN1XL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x60 )
#define VPBE_OSD_VIDWIN1YL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x64 )
#define VPBE_OSD_OSDWIN0XP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x68 )
#define VPBE_OSD_OSDWIN0YP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x6C )
#define VPBE_OSD_OSDWIN0XL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x70 )
#define VPBE_OSD_OSDWIN0YL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x74 )
#define VPBE_OSD_OSDWIN1XP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x78 )
#define VPBE_OSD_OSDWIN1YP      *( volatile Uint32* )( VPBE_OSD_BASE + 0x7C )
#define VPBE_OSD_OSDWIN1XL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x80 )
#define VPBE_OSD_OSDWIN1YL      *( volatile Uint32* )( VPBE_OSD_BASE + 0x84 )
#define VPBE_OSD_CURXP          *( volatile Uint32* )( VPBE_OSD_BASE + 0x88 )
#define VPBE_OSD_CURYP          *( volatile Uint32* )( VPBE_OSD_BASE + 0x8C )
#define VPBE_OSD_CURXL          *( volatile Uint32* )( VPBE_OSD_BASE + 0x90 )
#define VPBE_OSD_CURYL          *( volatile Uint32* )( VPBE_OSD_BASE + 0x94 )
#define VPBE_OSD_W0BMP01        *( volatile Uint32* )( VPBE_OSD_BASE + 0xA0 )
#define VPBE_OSD_W0BMP23        *( volatile Uint32* )( VPBE_OSD_BASE + 0xA4 )
#define VPBE_OSD_W0BMP45        *( volatile Uint32* )( VPBE_OSD_BASE + 0xA8 )
#define VPBE_OSD_W0BMP67        *( volatile Uint32* )( VPBE_OSD_BASE + 0xAC )
#define VPBE_OSD_W0BMP89        *( volatile Uint32* )( VPBE_OSD_BASE + 0xB0 )
#define VPBE_OSD_W0BMPAB        *( volatile Uint32* )( VPBE_OSD_BASE + 0xB4 )
#define VPBE_OSD_W0BMPCD        *( volatile Uint32* )( VPBE_OSD_BASE + 0xB8 )
#define VPBE_OSD_W0BMPEF        *( volatile Uint32* )( VPBE_OSD_BASE + 0xBC )
#define VPBE_OSD_W1BMP01        *( volatile Uint32* )( VPBE_OSD_BASE + 0xC0 )
#define VPBE_OSD_W1BMP23        *( volatile Uint32* )( VPBE_OSD_BASE + 0xC4 )
#define VPBE_OSD_W1BMP45        *( volatile Uint32* )( VPBE_OSD_BASE + 0xC8 )
#define VPBE_OSD_W1BMP67        *( volatile Uint32* )( VPBE_OSD_BASE + 0xCC )
#define VPBE_OSD_W1BMP89        *( volatile Uint32* )( VPBE_OSD_BASE + 0xD0 )
#define VPBE_OSD_W1BMPAB        *( volatile Uint32* )( VPBE_OSD_BASE + 0xD4 )
#define VPBE_OSD_W1BMPCD        *( volatile Uint32* )( VPBE_OSD_BASE + 0xD8 )
#define VPBE_OSD_W1BMPEF        *( volatile Uint32* )( VPBE_OSD_BASE + 0xDC )
#define VPBE_OSD_TI_TEST        *( volatile Uint32* )( VPBE_OSD_BASE + 0xE0 )
#define VPBE_OSD_MISCCTL        *( volatile Uint32* )( VPBE_OSD_BASE + 0xE8 )
#define VPBE_OSD_CLUTRAMYCB     *( volatile Uint32* )( VPBE_OSD_BASE + 0xEC )
#define VPBE_OSD_CLUTRAMCR      *( volatile Uint32* )( VPBE_OSD_BASE + 0xF0 )
#define VPBE_OSD_TRANSPVAL      *( volatile Uint32* )( VPBE_OSD_BASE + 0xF0 )
#define VPBE_OSD_PPVWIN0ADR     *( volatile Uint32* )( VPBE_OSD_BASE + 0xFC )

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *   VPBE Video Encoder                                                     *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define VPBE_VENC_BASE          0x01C70400
#define VPBE_VENC_VMOD          *( volatile Uint32* )( VPBE_VENC_BASE + 0x000 )
#define VPBE_VENC_VIOCTL        *( volatile Uint32* )( VPBE_VENC_BASE + 0x004 )
#define VPBE_VENC_VDPRO         *( volatile Uint32* )( VPBE_VENC_BASE + 0x008 )
#define VPBE_VENC_SYNCCTL       *( volatile Uint32* )( VPBE_VENC_BASE + 0x00C )
#define VPBE_VENC_HSPLS         *( volatile Uint32* )( VPBE_VENC_BASE + 0x010 )
#define VPBE_VENC_VSPLS         *( volatile Uint32* )( VPBE_VENC_BASE + 0x014 )
#define VPBE_VENC_HINT          *( volatile Uint32* )( VPBE_VENC_BASE + 0x018 )
#define VPBE_VENC_HSTART        *( volatile Uint32* )( VPBE_VENC_BASE + 0x01C )
#define VPBE_VENC_HVALID        *( volatile Uint32* )( VPBE_VENC_BASE + 0x020 )
#define VPBE_VENC_VINT          *( volatile Uint32* )( VPBE_VENC_BASE + 0x024 )
#define VPBE_VENC_VSTART        *( volatile Uint32* )( VPBE_VENC_BASE + 0x028 )
#define VPBE_VENC_VVALID        *( volatile Uint32* )( VPBE_VENC_BASE + 0x02C )
#define VPBE_VENC_HSDLY         *( volatile Uint32* )( VPBE_VENC_BASE + 0x030 )
#define VPBE_VENC_VSDLY         *( volatile Uint32* )( VPBE_VENC_BASE + 0x034 )
#define VPBE_VENC_YCCCTL        *( volatile Uint32* )( VPBE_VENC_BASE + 0x038 )
#define VPBE_VENC_RGBCTL        *( volatile Uint32* )( VPBE_VENC_BASE + 0x03C )
#define VPBE_VENC_RGBCLP        *( volatile Uint32* )( VPBE_VENC_BASE + 0x040 )
#define VPBE_VENC_LINECTL       *( volatile Uint32* )( VPBE_VENC_BASE + 0x044 )
#define VPBE_VENC_CULLLINE      *( volatile Uint32* )( VPBE_VENC_BASE + 0x048 )
#define VPBE_VENC_LCDOUT        *( volatile Uint32* )( VPBE_VENC_BASE + 0x04C )
#define VPBE_VENC_BRTS          *( volatile Uint32* )( VPBE_VENC_BASE + 0x050 )
#define VPBE_VENC_BRTW          *( volatile Uint32* )( VPBE_VENC_BASE + 0x054 )
#define VPBE_VENC_ACCTL         *( volatile Uint32* )( VPBE_VENC_BASE + 0x058 )
#define VPBE_VENC_PWMP          *( volatile Uint32* )( VPBE_VENC_BASE + 0x05C )
#define VPBE_VENC_PWMW          *( volatile Uint32* )( VPBE_VENC_BASE + 0x060 )
#define VPBE_VENC_DCLKCTL       *( volatile Uint32* )( VPBE_VENC_BASE + 0x064 )
#define VPBE_VENC_DCLKPTN0      *( volatile Uint32* )( VPBE_VENC_BASE + 0x068 )
#define VPBE_VENC_DCLKPTN1      *( volatile Uint32* )( VPBE_VENC_BASE + 0x06C )
#define VPBE_VENC_DCLKPTN2      *( volatile Uint32* )( VPBE_VENC_BASE + 0x070 )
#define VPBE_VENC_DCLKPTN3      *( volatile Uint32* )( VPBE_VENC_BASE + 0x074 )
#define VPBE_VENC_DCLKPTN0A     *( volatile Uint32* )( VPBE_VENC_BASE + 0x078 )
#define VPBE_VENC_DCLKPTN1A     *( volatile Uint32* )( VPBE_VENC_BASE + 0x07C )
#define VPBE_VENC_DCLKPTN2A     *( volatile Uint32* )( VPBE_VENC_BASE + 0x080 )
#define VPBE_VENC_DCLKPTN3A     *( volatile Uint32* )( VPBE_VENC_BASE + 0x084 )
#define VPBE_VENC_DCLKHS        *( volatile Uint32* )( VPBE_VENC_BASE + 0x088 )
#define VPBE_VENC_DCLKHSA       *( volatile Uint32* )( VPBE_VENC_BASE + 0x08C )
#define VPBE_VENC_DCLKHR        *( volatile Uint32* )( VPBE_VENC_BASE + 0x090 )
#define VPBE_VENC_DCLKVS        *( volatile Uint32* )( VPBE_VENC_BASE + 0x094 )
#define VPBE_VENC_DCLKVR        *( volatile Uint32* )( VPBE_VENC_BASE + 0x098 )
#define VPBE_VENC_CAPCTL        *( volatile Uint32* )( VPBE_VENC_BASE + 0x09C )
#define VPBE_VENC_CAPDO         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0A0 )
#define VPBE_VENC_CAPDE         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0A4 )
#define VPBE_VENC_ATR0          *( volatile Uint32* )( VPBE_VENC_BASE + 0x0A8 )
#define VPBE_VENC_ATR1          *( volatile Uint32* )( VPBE_VENC_BASE + 0x0AC )
#define VPBE_VENC_ATR2          *( volatile Uint32* )( VPBE_VENC_BASE + 0x0B0 )
#define VPBE_VENC_EPSON_LCDCTL  *( volatile Uint32* )( VPBE_VENC_BASE + 0x0B4 )
#define VPBE_VENC_VSTAT         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0B8 )
#define VPBE_VENC_RAMADR        *( volatile Uint32* )( VPBE_VENC_BASE + 0x0BC )
#define VPBE_VENC_RAMPORT       *( volatile Uint32* )( VPBE_VENC_BASE + 0x0C0 )
#define VPBE_VENC_DACTST        *( volatile Uint32* )( VPBE_VENC_BASE + 0x0C4 )
#define VPBE_VENC_YCOLVL        *( volatile Uint32* )( VPBE_VENC_BASE + 0x0C8 )
#define VPBE_VENC_SCPROG        *( volatile Uint32* )( VPBE_VENC_BASE + 0x0CC )
#define VPBE_VENC_CVBS          *( volatile Uint32* )( VPBE_VENC_BASE + 0x0DC )
#define VPBE_VENC_CMPNT         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0E0 )
#define VPBE_VENC_ETMG0         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0E4 )
#define VPBE_VENC_ETMG1         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0E8 )
#define VPBE_VENC_ETMG2         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0EC )
#define VPBE_VENC_ETMG3         *( volatile Uint32* )( VPBE_VENC_BASE + 0x0F0 )
#define VPBE_VENC_DACSEL        *( volatile Uint32* )( VPBE_VENC_BASE + 0x0F4 )
#define VPBE_VENC_ARGBX0        *( volatile Uint32* )( VPBE_VENC_BASE + 0x100 )
#define VPBE_VENC_ARGBX1        *( volatile Uint32* )( VPBE_VENC_BASE + 0x104 )
#define VPBE_VENC_ARGBX2        *( volatile Uint32* )( VPBE_VENC_BASE + 0x108 )
#define VPBE_VENC_ARGBX3        *( volatile Uint32* )( VPBE_VENC_BASE + 0x10C )
#define VPBE_VENC_ARGBX4        *( volatile Uint32* )( VPBE_VENC_BASE + 0x110 )
#define VPBE_VENC_DRGBX0        *( volatile Uint32* )( VPBE_VENC_BASE + 0x114 )
#define VPBE_VENC_DRGBX1        *( volatile Uint32* )( VPBE_VENC_BASE + 0x118 )
#define VPBE_VENC_DRGBX2        *( volatile Uint32* )( VPBE_VENC_BASE + 0x11C )
#define VPBE_VENC_DRGBX3        *( volatile Uint32* )( VPBE_VENC_BASE + 0x120 )
#define VPBE_VENC_DRGBX4        *( volatile Uint32* )( VPBE_VENC_BASE + 0x124 )
#define VPBE_VENC_VSTARTA       *( volatile Uint32* )( VPBE_VENC_BASE + 0x128 )
#define VPBE_VENC_OSDCLK0       *( volatile Uint32* )( VPBE_VENC_BASE + 0x12C )
#define VPBE_VENC_OSDCLK1       *( volatile Uint32* )( VPBE_VENC_BASE + 0x130 )
#define VPBE_VENC_HVLDCL0       *( volatile Uint32* )( VPBE_VENC_BASE + 0x134 )
#define VPBE_VENC_HVLDCL1       *( volatile Uint32* )( VPBE_VENC_BASE + 0x138 )
#define VPBE_VENC_OSDHADV       *( volatile Uint32* )( VPBE_VENC_BASE + 0x13C )
#define VPBE_VENC_SCTEST0       *( volatile Uint32* )( VPBE_VENC_BASE + 0x140 )
#define VPBE_VENC_SCTEST1       *( volatile Uint32* )( VPBE_VENC_BASE + 0x144 )
#define VPBE_VENC_SCTEST2       *( volatile Uint32* )( VPBE_VENC_BASE + 0x148 )
#define VPBE_VENC_VTEST0        *( volatile Uint32* )( VPBE_VENC_BASE + 0x14C )
#define VPBE_VENC_VTEST1        *( volatile Uint32* )( VPBE_VENC_BASE + 0x150 )
#define VPBE_VENC_VTEST2        *( volatile Uint32* )( VPBE_VENC_BASE + 0x154 )


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *   VPFE CCD Controller                                                    *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define VPFE_CCDC_BASE          0x01C70600
#define VPFE_CCDC_PID           *( volatile Uint32* )( VPFE_CCDC_BASE + 0x00 )
#define VPFE_CCDC_PCR           *( volatile Uint32* )( VPFE_CCDC_BASE + 0x04 )
#define VPFE_CCDC_SYN_MODE      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x08 )
#define VPFE_CCDC_HD_VD_WID     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x0c )
#define VPFE_CCDC_PIX_LINES     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x10 )
#define VPFE_CCDC_HORZ_INFO     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x14 )
#define VPFE_CCDC_VERT_START    *( volatile Uint32* )( VPFE_CCDC_BASE + 0x18 )
#define VPFE_CCDC_VERT_LINES    *( volatile Uint32* )( VPFE_CCDC_BASE + 0x1C )
#define VPFE_CCDC_CULLING       *( volatile Uint32* )( VPFE_CCDC_BASE + 0x20 )
#define VPFE_CCDC_HSIZE_OFF     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x24 )
#define VPFE_CCDC_SDOFST        *( volatile Uint32* )( VPFE_CCDC_BASE + 0x28 )
#define VPFE_CCDC_SDR_ADDR      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x2c )
#define VPFE_CCDC_CLAMP         *( volatile Uint32* )( VPFE_CCDC_BASE + 0x30 )
#define VPFE_CCDC_DCSUB         *( volatile Uint32* )( VPFE_CCDC_BASE + 0x34 )
#define VPFE_CCDC_COLPTN        *( volatile Uint32* )( VPFE_CCDC_BASE + 0x38 )
#define VPFE_CCDC_BLKCMP        *( volatile Uint32* )( VPFE_CCDC_BASE + 0x3c )
#define VPFE_CCDC_FPC_ADDR      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x40 )
#define VPFE_CCDC_FPC           *( volatile Uint32* )( VPFE_CCDC_BASE + 0x44 )
#define VPFE_CCDC_VDINT         *( volatile Uint32* )( VPFE_CCDC_BASE + 0x48 )
#define VPFE_CCDC_ALAW          *( volatile Uint32* )( VPFE_CCDC_BASE + 0x4c )
#define VPFE_CCDC_REC656IF      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x50 )
#define VPFE_CCDC_CCDCFG        *( volatile Uint32* )( VPFE_CCDC_BASE + 0x54 )
#define VPFE_CCDC_FMTCFG        *( volatile Uint32* )( VPFE_CCDC_BASE + 0x58 )
#define VPFE_CCDC_FMT_HORZ      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x5c )
#define VPFE_CCDC_FMT_VERT      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x60 )
#define VPFE_CCDC_FMT_ADDR0     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x64 )
#define VPFE_CCDC_FMT_ADDR1     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x68 )
#define VPFE_CCDC_FMT_ADDR2     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x6c )
#define VPFE_CCDC_FMT_ADDR3     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x70 )
#define VPFE_CCDC_FMT_ADDR4     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x74 )
#define VPFE_CCDC_FMT_ADDR5     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x78 )
#define VPFE_CCDC_FMT_ADDR6     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x7c )
#define VPFE_CCDC_FMT_ADDR7     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x80 )
#define VPFE_CCDC_PRGEVEN_0     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x84 )
#define VPFE_CCDC_PRGEVEN_1     *( volatile Uint32* )( VPFE_CCDC_BASE + 0x88 )
#define VPFE_CCDC_PRGODD_0      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x8c )
#define VPFE_CCDC_PRGODD_1      *( volatile Uint32* )( VPFE_CCDC_BASE + 0x90 )
#define VPFE_CCDC_VP_OUT        *( volatile Uint32* )( VPFE_CCDC_BASE + 0x94 )


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *   VPFE Hardware 3A ( Auto-Focus / WB / Exposure )                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
#define VPFE_H3A_BASE           0x01C70080
#define VPFE_H3A_PID            *( volatile Uint32* )( VPFE_H3A_BASE + 0x00 )
#define VPFE_H3A_PCR            *( volatile Uint32* )( VPFE_H3A_BASE + 0x04 )
#define VPFE_H3A_AFPAX1         *( volatile Uint32* )( VPFE_H3A_BASE + 0x08 )
#define VPFE_H3A_AFPAX2         *( volatile Uint32* )( VPFE_H3A_BASE + 0x0C )
#define VPFE_H3A_AFPAXSTART     *( volatile Uint32* )( VPFE_H3A_BASE + 0x10 )
#define VPFE_H3A_AFIIRSH        *( volatile Uint32* )( VPFE_H3A_BASE + 0x14 )
#define VPFE_H3A_AFBUFST        *( volatile Uint32* )( VPFE_H3A_BASE + 0x18 )
#define VPFE_H3A_AFCOEF010      *( volatile Uint32* )( VPFE_H3A_BASE + 0x1C )
#define VPFE_H3A_AFCOEF032      *( volatile Uint32* )( VPFE_H3A_BASE + 0x20 )
#define VPFE_H3A_AFCOEFF054     *( volatile Uint32* )( VPFE_H3A_BASE + 0x24 )
#define VPFE_H3A_AFCOEFF076     *( volatile Uint32* )( VPFE_H3A_BASE + 0x28 )
#define VPFE_H3A_AFCOEFF098     *( volatile Uint32* )( VPFE_H3A_BASE + 0x2C )
#define VPFE_H3A_AFCOEFF0010    *( volatile Uint32* )( VPFE_H3A_BASE + 0x30 )
#define VPFE_H3A_AFCOEF110      *( volatile Uint32* )( VPFE_H3A_BASE + 0x34 )
#define VPFE_H3A_AFCOEF132      *( volatile Uint32* )( VPFE_H3A_BASE + 0x38 )
#define VPFE_H3A_AFCOEFF154     *( volatile Uint32* )( VPFE_H3A_BASE + 0x3C )
#define VPFE_H3A_AFCOEFF176     *( volatile Uint32* )( VPFE_H3A_BASE + 0x40 )
#define VPFE_H3A_AFCOEFF198     *( volatile Uint32* )( VPFE_H3A_BASE + 0x44 )
#define VPFE_H3A_AFCOEFF1010    *( volatile Uint32* )( VPFE_H3A_BASE + 0x48 )
#define VPFE_H3A_AEWWIN1        *( volatile Uint32* )( VPFE_H3A_BASE + 0x4C )
#define VPFE_H3A_AEWINSTART     *( volatile Uint32* )( VPFE_H3A_BASE + 0x50 )
#define VPFE_H3A_AEWINBLK       *( volatile Uint32* )( VPFE_H3A_BASE + 0x54 )
#define VPFE_H3A_AEWSUBWIN      *( volatile Uint32* )( VPFE_H3A_BASE + 0x58 )
#define VPFE_H3A_AEWBUFST       *( volatile Uint32* )( VPFE_H3A_BASE + 0x5C )


/* ------------------------------------------------------------------------ *
 *  Function Renaming                                                       *
 * ------------------------------------------------------------------------ */
#define EVMDM355_wait          _wait
#define EVMDM355_waitusec      _waitusec

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
/* Board Initialization */
Int16 EVMDM355_init( );

/* Wait Functions */
void _wait( Uint32 delay );
void _waitusec( Uint32 usec );

#endif
