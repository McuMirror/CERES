#include "MDB.h"

//******************************************************************************

void InitMDB(const UART_MODULE Port)
{
    MDBUART = Port;
    OpenUART(MDBUART, configPERIPHERAL_CLOCK_HZ, 9600,
            UART_DATA_SIZE_9_BITS, UART_PARITY_NONE, UART_STOP_BITS_1);
    xTimerMDBNAK = xTimerCreate((const char * const)"TIMER_MDB", MDB_TO, pdFALSE,
            NULL, vNAKTO_MDB);
}

/******************************************************************************/

BYTE byMDBSendCommand(const BYTE byAddress, const BYTE byCommand,
        BYTE byLenParameters, void *ptrParameters, void *ptrAnswer)
{
    BYTE byIndex;
    UART_DATA wBuffer[32];
    BYTE *byPtrParameters, *byPtrAnswer;
    byPtrParameters = ptrParameters;
    byPtrAnswer = ptrAnswer;
    DelayMs(10);
    memset(wBuffer, 0XFF, sizeof (wBuffer));

    wBuffer[0].data9bit = 0x0100 + byAddress + byCommand;
    for(byIndex = 1; byIndex <= byLenParameters; byIndex++)
    {
        wBuffer[byIndex].__data = (BYTE)byPtrParameters[byIndex - 1];
    }
    wBuffer[byLenParameters + 1].__data = byCheckSum(byLenParameters + 1, wBuffer);
    for(byIndex = 0; byIndex < (byLenParameters + 2); byIndex++)
    {
        boNAKMDB = FALSE;
        xTimerStart(xTimerMDBNAK, 1000);
        while(!UARTTransmitterIsReady(MDBUART) && !boNAKMDB);
        if(!boNAKMDB)
        {
                UARTSendData(MDBUART, wBuffer[byIndex]);
        }
        else
        {
            byPtrAnswer[0] = NAK;
            return 0;
        }
    }
    byIndex = 0;
    memset(wBuffer, 0X00, sizeof (wBuffer));
    do
    {
        boNAKMDB = FALSE;
        xTimerStart(xTimerMDBNAK, 1000);
        while(!UARTReceivedDataIsAvailable(MDBUART) && !boNAKMDB);
        if(!boNAKMDB)
        {
            wBuffer[byIndex] = UARTGetData(MDBUART);
            byPtrAnswer[byIndex] = (BYTE)wBuffer[byIndex].__data;
        }
        else
        {
            byPtrAnswer[0] = NAK;
            byIndex = 0;
        }
    }while(!boNAKMDB && !(wBuffer[byIndex++].__data & 0x0100));
    return byIndex;
}

/******************************************************************************/

BYTE byCheckSum(BYTE byLen, const UART_DATA* ptrBuffer)
{
    BYTE byResult = 0;
    while(byLen--)
    {
        byResult += (ptrBuffer[byLen].__data & 0X00FF);
    }
    return byResult;
}

/******************************************************************************/

BOOL boMDBReset(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    return ((byMDBSendCommand(byDeviceAddress, CMD_RESET, 0, NULL, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BYTE byMDBPoll(const BYTE byDeviceAddress, BYTE *byResponse)
{
    BYTE lResponse;

    BYTE lenAnswer = byMDBSendCommand(byDeviceAddress,
            byDeviceAddress == 0x08 || byDeviceAddress == 0x30 ? CMD_CHANGER_POLL : CMD_POLL,
            0, NULL, byResponse != NULL ? byResponse : &lResponse);
    DelayMs(10); //Laisse le temps de  compléter la réponse.
    if(lenAnswer > 1)
    {
        vVMCAcknowledge(ACK);
    }
    return lenAnswer;
}

/******************************************************************************/

void vVMCAcknowledge(const BYTE byAcknowledge)
{
    UART_DATA uaAcknowledge;
    uaAcknowledge.__data = byAcknowledge;
    boNAKMDB = FALSE;
    xTimerStart(xTimerMDBNAK, 1000);
    while(!UARTTransmitterIsReady(MDBUART) && !boNAKMDB);
    UARTSendData(MDBUART, uaAcknowledge);
    while(!(UARTGetLineStatus(MDBUART) & UART_TRANSMITTER_EMPTY));
}

/******************************************************************************/

void vNAKTO_MDB(const TimerHandle_t HandleTimer)
{
    boNAKMDB = TRUE;
}

/******************************************************************************/

BOOL boMDBSetupConfig(const BYTE byDeviceAddress, void *byStatus, const BYTE byLen)
{
    if(byMDBSendCommand(byDeviceAddress, CMD_SETUP, 0, NULL, byStatus) == byLen + 1)
    {
        vVMCAcknowledge(ACK);
        return TRUE;
    }
    else
    {
        vVMCAcknowledge(NAK);
    }
    return FALSE;
}

/******************************************************************************/

WORD wDecimalDivider(BYTE byDecimal)
{
    WORD wResult = 1;
    while(byDecimal--)
    {
        wResult *= 10;
    }
    return wResult;
}

/******************************************************************************/

