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

BYTE RS485GetS(BYTE pBuffer[])
{
    SETREAD();
    return UARTGetS(UART485, pBuffer);
}

//******************************************************************************

BOOL RS485GetBuffer(void *pBuffer, WORD wLen)
{
    BYTE *byLBuffer = pBuffer;
    SETREAD();
    vTaskSuspendAll();
    while(wLen-- && wTORequest)
    {
        while(wTORequest && !UARTReceivedDataIsAvailable(UART485));
        if(wTORequest)
        {
            *byLBuffer++ = UARTGetByte(UART485);
        }
    }
    xTaskResumeAll();
    return(wTORequest != 0);
}

//******************************************************************************

BYTE RS485WriteS(const BYTE *pBuffer)
{
    SETWRITE();
    return UARTWriteS(UART485, pBuffer);
}

//******************************************************************************

void RS485WriteBuffer(const void *pBuffer, const BYTE byLen)
{
    SETWRITE();
    UARTWriteBuffer(UART485, pBuffer, byLen);
}

//******************************************************************************

void RS485WriteByte(const BYTE cData)
{
    SETWRITE();
    UARTWriteByte(UART485, cData);
}

//******************************************************************************

BYTE RS485GetByte(void)
{
    SETREAD();
    while(!UARTReceivedDataIsAvailable(UART485));
    return UARTGetByte(UART485);
}

//******************************************************************************
