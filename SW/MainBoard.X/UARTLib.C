#include "UARTLIB.h"

//******************************************************************************

void __ISR(_TIMER_3_VECTOR) ISRTimer3(void)
{
  if(wTORequest)
  {
    wTORequest--;
  }
  mT3ClearIntFlag();
}

//******************************************************************************

void InitIntTimer3(void)
{
  OpenTimer3(T3_ON | T3_PS_1_2, 10000);
  ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_5 | T3_INT_SUB_PRIOR_2);
  EnableINT3;
}

//******************************************************************************

void OpenUART(const UART_MODULE UART, const DWORD dwSYS_FREQ,
              const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
              const UART_LINE_CONTROL_MODE parity,
              const UART_LINE_CONTROL_MODE stop_bits)
{
  UARTConfigure(UART, UART_ENABLE_PINS_TX_RX_ONLY);
  UARTSetLineControl(UART, dataSize | parity | stop_bits);
  UARTSetDataRate(UART, dwSYS_FREQ, dwBAUDRATE);
  UARTEnable(UART, UART_ENABLE | UART_PERIPHERAL | UART_RX | UART_TX);
  InitIntTimer3();
}

//******************************************************************************

BYTE UARTGetS(const UART_MODULE UART, BYTE *pBuffer)
{
  BYTE byLen = 0;
  while((*pBuffer++ = UARTGetByte(UART)))
  {
    ++byLen;
  }
  return byLen++;
}

//******************************************************************************

void UARTGetBuffer(const UART_MODULE UART, WORD wLen, BYTE *pBuffer)
{
  while(wLen--)
  {
    while(!UARTReceivedDataIsAvailable(UART));
    *pBuffer++ = UARTGetByte(UART);
  }
}

//******************************************************************************

BYTE UARTWriteS(const UART_MODULE UART, const BYTE *pBuffer)
{
  BYTE byLen = 0;
  do
  {
    ++byLen;
    UARTWriteByte(UART, *pBuffer);
  }while(*++pBuffer);
  return byLen;
}

//******************************************************************************

void UARTWriteBuffer(const UART_MODULE UART, const BYTE *pBuffer, BYTE byLen)
{
  while(byLen--)
  {
    UARTWriteByte(UART, *pBuffer++);
  }
}

//******************************************************************************

void UARTWriteByte(const UART_MODULE UART, const BYTE cData)
{
  while(!UARTTransmitterIsReady(UART));
  UARTSendDataByte(UART, cData);
  while(!(UARTGetLineStatus(UART) & UART_TRANSMITTER_EMPTY));
}

//******************************************************************************

BYTE UARTGetByte(const UART_MODULE UART)
{
  while(!UARTReceivedDataIsAvailable(UART));
  return UARTGetDataByte(UART);
}

//******************************************************************************
