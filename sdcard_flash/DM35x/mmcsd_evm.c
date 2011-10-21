/*
 *  Copyright 2005 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

#include "mmcsd.h"

Uint16 MMCSD_clearResponse( )
{
    MMCSD_MMCRSP01 = 0;
    MMCSD_MMCRSP23 = 0;
    MMCSD_MMCRSP45 = 0;
    MMCSD_MMCRSP67 = 0;
    MMCSD_MMCCIDX &= 0xFFFFFFC0;
    return 0;
}

Uint16 MMCSD_setConfig( MMCSD_ConfigData* config )
{
    MMCSD_MMCCTL = 0
        | ( config->writeEndian << 10 )
        | ( config->readEndian  << 9 )
        | ( config->dat3Detect  << 6 )
        | ( config->busWidth    << 2 )
        ;

    MMCSD_MMCTOR = ( MMCSD_MMCTOR & 0xFFFFFF00 )
        | ( config->timeoutResponse )
        ;

    MMCSD_MMCTOD = config->timeoutRead;
    return 0;
}

/*
 *  Send Command to MMC/SD
 */
Uint16 MMCSD_sendCmd( Uint32 command, Uint32 argument, Uint8 checkStatus, Uint16 statusBits )
{
    Uint16 statusRegBits = 0;

    /* Clear Response Registers */
    MMCSD_clearResponse( );

    /* Setup the Argument Register and send CMD */
    MMCSD_MMCARGHL = ( MMCSD_MMCARGHL & 0xFFFF0000 ) | ( argument & 0x0000FFFF );
    MMCSD_MMCARGHL = ( MMCSD_MMCARGHL & 0x0000FFFF ) | ( argument & 0xFFFF0000 );
    MMCSD_MMCCMD = command;

    /* Delay loop allowing cards to respond */
    _wait( 20 );

    if ( checkStatus )
    {
        // Wait for RspDne; exit on RspTimeOut or RspCRCErr
        while ( ( statusRegBits & ( 0x00F8 | statusBits ) ) == 0 )
            statusRegBits = MMCSD_MMCST0;

        return ( ( statusRegBits & statusBits ) == statusBits ) ? 0 : E_DEVICE;
    }

    return 0;
}

/*
 *  Parse the Card Status value, sent to the MMC/SD card, in response to a command
 */
Uint16 MMCSD_getCardStatus( MMCSD_ResponseData* mmcsdResponse, MMCSD_cardStatusReg* cardStatus )
{
    Uint16 response6;
    Uint16 response7;

    response6 = MMCSD_MMCRSP67;
    response7 = MMCSD_MMCRSP67 >> 16;

    cardStatus->appSpecific = ( response6 & 0xff );
    cardStatus->ready       = ( response6 >> 8 ) & 1;
    cardStatus->currentState= ( response6 >> 9 ) & 0xf;
    cardStatus->eraseReset  = ( response6 >> 13 ) & 1;
    cardStatus->eccDisabled = ( response6 >> 14 ) & 1;
    cardStatus->wpEraseSkip = ( response6 >> 15 ) & 1;
    cardStatus->errorFlags  =  response7;
    return 0;
}

/*
 *  Read the CID information from the Response Registers of MMC/SD controller
 */
Uint16 MMCSD_getCardCID( MMCSD_ResponseData* mmcsdResponse, Uint16* cardCID )
{
    Uint16 i;

    for ( i = 0 ; i < 8 ; i++ )
        cardCID[i] = *( Uint16* )( MMCSD_MMCRSP_BASE + 2 * i );

    return 0;
}

/*
 *  Read the CSD information from the Response Registers of MMC/SD controller
 */
Uint16 MMCSD_getCardCSD( MMCSD_ResponseData* mmcsdResponse, Uint16* cardCSD, MMCSD_csdRegInfo* localCSDInfo )
{
    Uint16 i;

    /* Read CSD from response R2 */
    for ( i = 0 ; i < 8 ; i++ )
        cardCSD[i] = *( Uint16* )( MMCSD_MMCRSP_BASE + 2 * i );

    localCSDInfo->permWriteProtect  = ( cardCSD[0] >> 13 ) & 1;
    localCSDInfo->tmpWriteProtect   = ( cardCSD[0] >> 12 ) & 1;
    localCSDInfo->writeBlkPartial   = ( cardCSD[1] >> 5 ) & 1;
    localCSDInfo->writeBlkLenBytes  = 1 << ( ( cardCSD[1]>>6 ) & 0xF );
    localCSDInfo->wpGrpEnable       = ( cardCSD[1] >> 15 ) & 1;
    // Extracting 7 bits: For MMC - 5 bits reqd; For SD - 7 bits reqd.( have to be taken care by user )
    localCSDInfo->wpGrpSize         = ( cardCSD[2] & 0x7F ) + 1;
    localCSDInfo->dsrImp            = ( cardCSD[4] >> 12 ) & 1;
    localCSDInfo->readBlkMisalign   = ( cardCSD[4] >> 13 ) & 1;
    localCSDInfo->writeBlkMisalign  = ( cardCSD[4] >> 14 ) & 1;
    localCSDInfo->readBlkPartial    = ( cardCSD[4] >> 15 ) & 1;
    localCSDInfo->readBlkLenBytes   = 1 << ( cardCSD[5] & 0xF );
    // These bits are reserved in the case of SD card
    localCSDInfo->sysSpecVersion    = ( cardCSD[7] >> 10 ) & 0xF;
    return 0;
}

/*
 *  Read N words from the MMC Controller Register
 */
Uint16 MMCSD_readNWords( Uint32* data, Uint32 numofBytes, Uint32 cardMemAddr )
{
    Uint16 i, j;
    Uint16 fifoDxrRdCnt;
    Uint32 fifoReadItrCount;
    Uint32 extraBytes;
    Uint8  fifoBuff[32] = {0};
    Uint8* fifoBuffPtr  = ( Uint8* )fifoBuff;
    Uint16 fifoThrlevel;

    /* Check the FIFO level to used. This is set in MMCSD_init */
    fifoThrlevel = ( MMCSD_MMCFIFOCTL >> 2 ) & 1;

    /* Check if the FIFO Threshold Level is default( 16bytes ),otherwise set it to 32Bytes*/
    if ( fifoThrlevel )
    {
        MMCSD_MMCFIFOCTL |= 0x0004; // FIFO 32 bytes
        fifoReadItrCount = numofBytes >> 5;
        extraBytes       = numofBytes & 0x1F;
        fifoDxrRdCnt     = 8;
        fifoReadItrCount = numofBytes >> 5;

        if ( extraBytes )
            fifoReadItrCount++;
    }
    else
    {
        fifoReadItrCount = numofBytes >> 4;
        extraBytes       = numofBytes & 0xF;
        fifoDxrRdCnt     = 4;
        fifoReadItrCount = numofBytes >> 4;

        if ( extraBytes )
            fifoReadItrCount++;
    }

    for ( i = 0 ; i < fifoReadItrCount ; i++ )
    {
        if ( fifoThrlevel )
        {
            if ( i != ( fifoReadItrCount - 1 ) )
                while ( ( MMCSD_MMCST0 & 0x0400 ) == 0 ); //  DRRDY
        }
        else
        {
            if ( i < ( fifoReadItrCount - 2 ) )
                while ( ( MMCSD_MMCST0 & 0x0400 ) == 0 ); //  DRRDY
        }

        for ( j = 0 ; j < fifoDxrRdCnt ; j++ )
            *data++ = MMCSD_MMCDRR;

        if ( extraBytes )
        {
            if ( i == ( fifoReadItrCount - 1 ) )
                for ( j = 0 ; j < fifoDxrRdCnt ; j++ )
                    *fifoBuffPtr++ = MMCSD_MMCDRR;

            for ( j = 0 ; j < extraBytes ; j++ )
                *data++ = *fifoBuffPtr++;
        }
    }

    return 0;
}

/*
 *  Write N words to the MMC Controller Register
 */
Uint16 MMCSD_writeNWords( Uint32* data, Uint32 numofBytes, Uint32 cardMemAddr )
{
    Uint16 i, j, status = 0;
    Uint16 fifoDxrWrCnt;
    Uint32 fifoWriteItrCount;
    Uint32 extraBytes;
    Uint8  fifoBuff[32] = {0};
    Uint8* fifoBuffPtr  = ( Uint8* )fifoBuff;
    Uint16 fifoThrlevel;
    Uint8* data8;

    /* Check the FIFO level to used. This is set in MMCSD_init */
    fifoThrlevel = ( MMCSD_MMCFIFOCTL >> 2 ) & 1;

    /* Reset the FIFO  */
    MMCSD_MMCFIFOCTL |= 1;

    /* Set the Transfer direction from the FIFO as transmit*/
    MMCSD_MMCFIFOCTL |= 2;

    /* Check the FIFO Threshold Level is not as default( 16bytes )set it to 32Bytes*/
    if ( fifoThrlevel )
    {
        MMCSD_MMCFIFOCTL |= 0x0004;         // FIFO 32 bytes
        fifoWriteItrCount = numofBytes >> 5;
        extraBytes        = numofBytes & 0x1F;
        fifoDxrWrCnt      = 8;
        fifoWriteItrCount = numofBytes >> 5;

        if ( extraBytes )
            fifoWriteItrCount++;
    }
    else
    {
        fifoWriteItrCount = numofBytes >> 4;
        extraBytes        = numofBytes & 0xF;
        fifoDxrWrCnt      = 4;
        fifoWriteItrCount = numofBytes >> 4;

        if ( extraBytes )
            fifoWriteItrCount++;
    }

    for ( i = 0 ; i < fifoWriteItrCount ; i++ )
    {
        if ( i == 0 )
        {
            if ( numofBytes == 512 )
                status = MMCSD_sendCmd( 0x12800 | MMCSD_WRITE_BLOCK, cardMemAddr, 0, MMCSD_STAT0_RSPDNE );
            else
                status = MMCSD_sendCmd( 0x12880 | MMCSD_WRITE_MULTIPLE_BLOCK, cardMemAddr, 0, MMCSD_STAT0_RSPDNE );
        }

        for ( j = 0 ; j < fifoDxrWrCnt ; j++ )
            MMCSD_MMCDXR = *data++;

        if ( i != ( fifoWriteItrCount - 1 ) )
            while ( ( MMCSD_MMCST0 & 0x0200 ) == 0 ); // DXRDY

        if ( extraBytes )
        {
            if ( i == ( fifoWriteItrCount - 1 ) )
                for ( j = 0 ; j < fifoDxrWrCnt ; j++ )
                    MMCSD_MMCDXR = *fifoBuffPtr++;

            data8 = ( Uint8* )data;
            for ( j = 0 ; j < extraBytes ; j++ )
                *fifoBuffPtr++ = *data8++;
        }
    }

    return 0;
}

void _wait( Uint32 delay )
{
    volatile Uint32 i;
    for ( i = 0 ; i < delay ; i++ ){ };
}

void _waitusec( Uint32 usec )
{
    _wait( usec * 8 );
}
