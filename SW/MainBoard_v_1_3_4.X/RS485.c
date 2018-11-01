
/** ****************************************************************************
 * \file            RS485.c                                                 
 * \brief			Sources de la gestion des parametres du port RS485
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/

#include "RS485.h"

/******************************************************************************/

void InitRS485(const UART_MODULE UART, const DWORD dwSYS_FREQ,
               const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
               const UART_LINE_CONTROL_MODE parity,
               const UART_LINE_CONTROL_MODE stop_bits, const IoPortId EnablePort,
               DWORD dwEnableBit)
{
    UART485 = UART;

    OpenUART(UART485, dwSYS_FREQ, dwBAUDRATE, dataSize, parity, stop_bits);
    RS485port = EnablePort;
    RS485Io = dwEnableBit;
    PORTSetPinsDigitalOut(RS485port, RS485Io);
}

//******************************************************************************

BOOL RS485GetBuffer(void *pBuffer, WORD wLen)
{
    BYTE *byLBuffer = pBuffer;
    SETREAD();
    //vTaskSuspendAll();
    while(wLen-- && wTORequest)
    {
        while(wTORequest && !UARTReceivedDataIsAvailable(UART485));
        if(wTORequest)
        {
            *byLBuffer++ = UARTGetByte(UART485);
        }
    }
    //xTaskResumeAll();
    return (wTORequest != 0);
}

//******************************************************************************

void RS485WriteBuffer(const void *pBuffer, const BYTE byLen)
{
    SETWRITE();
    UARTWriteBuffer(UART485, pBuffer, byLen);
}

//******************************************************************************
