
/** ****************************************************************************
 * \file            MDB.c                                                 
 * \brief			Sources de la gestion de la chaine MDB
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#include "MDB.h"
#include "mdb_cg.h"
#include "mdb_bv.h"
#include "mdb_cl.h"
#include "parametres.h"

WORD wDecimalFactor[5] = {1, 10, 100, 1000, 10000};

//******************************************************************************

static void vNAKTO_MDB(const TimerHandle_t HandleTimer)
{
    isNAKMDB = TRUE;
}

/******************************************************************************/

static BYTE byCheckSum(BYTE byLen, const UART_DATA* ptrBuffer)
{
    BYTE byResult = 0;
    while(byLen--)
    {
        byResult += (ptrBuffer[byLen].__data & 0X00FF);
    }
    return byResult;
}

/******************************************************************************/

void InitMDB(const UART_MODULE port)
{

    isCGPolled = isBVPolled = isCLPolled = FALSE;
    dwMaxReturn = 0;
    MDBUART = port;
    OpenUART(MDBUART, configPERIPHERAL_CLOCK_HZ, 9600,
             UART_DATA_SIZE_9_BITS, UART_PARITY_NONE, UART_STOP_BITS_1);
    xTimerMDBNAK = xTimerCreate((const char * const)"TIMER_MDB", MDB_TO, pdFALSE,
                                NULL, vNAKTO_MDB);
    hSemaphoreMDB = xSemaphoreCreateMutex();
    vQueueAddToRegistry(hSemaphoreMDB, "SEMDB");

}

/******************************************************************************/

BYTE byMDBSendCommand(const BYTE byAddress, const BYTE byCommand,
                      BYTE byLenParameters, void *ptrParameters, void *ptrAnswer)
{
    BYTE byIndex;
    xSemaphoreTake(hSemaphoreMDB, 15000);
    UART_DATA wBuffer[32] = {0};
    BYTE *byPtrParameters, *byPtrAnswer;
    byPtrParameters = ptrParameters;
    byPtrAnswer = ptrAnswer;
    //DelayMs(10);
    //    memset(wBuffer, 0XFF, sizeof (wBuffer));

    wBuffer[0].data9bit = 0x0100 + byAddress + byCommand;
    for(byIndex = 1; byIndex <= byLenParameters; byIndex++)
    {
        wBuffer[byIndex].__data = (BYTE)byPtrParameters[byIndex - 1];
    }
    wBuffer[byLenParameters + 1].__data = byCheckSum(byLenParameters + 1, wBuffer);
    for(byIndex = 0; byIndex < (byLenParameters + 2); byIndex++)
    {
        isNAKMDB = FALSE;
        xTimerStart(xTimerMDBNAK, 1000);
        while(!UARTTransmitterIsReady(MDBUART) && !isNAKMDB);
        if(!isNAKMDB)
        {
            UARTSendData(MDBUART, wBuffer[byIndex]);
        }
        else
        {
            byPtrAnswer[0] = RSP_NAK;
            xSemaphoreGive(hSemaphoreMDB);
            return 0;
        }
    }
    byIndex = 0;
    memset(wBuffer, 0X00, sizeof (wBuffer));
    do
    {
        isNAKMDB = FALSE;
        xTimerStart(xTimerMDBNAK, 1000);
        while(!UARTReceivedDataIsAvailable(MDBUART) && !isNAKMDB);
        if(!isNAKMDB)
        {
            wBuffer[byIndex] = UARTGetData(MDBUART);
            byPtrAnswer[byIndex] = (BYTE)wBuffer[byIndex].__data;
        }
        else
        {
            byPtrAnswer[0] = RSP_NAK;
            byIndex = 0;
        }
    }while(!isNAKMDB && !(wBuffer[byIndex++].__data & 0x0100));
    xSemaphoreGive(hSemaphoreMDB);
    return byIndex;
}

/******************************************************************************/

BOOL isMDBReset(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    return ((byMDBSendCommand(byDeviceAddress, CMD_RESET, 0, NULL, &byAcknowledge) == 1) && (byAcknowledge == RSP_ACK));
}

/******************************************************************************/

BYTE byMDBPoll(const BYTE byDeviceAddress, BYTE *byResponse)
{
    BYTE lResponse;

    BYTE lenAnswer = byMDBSendCommand(byDeviceAddress,
                                      byDeviceAddress == 0x08 || byDeviceAddress == 0x30 ? CMD_CHANGER_POLL : CMD_POLL,
                                      0, NULL, byResponse != NULL ? byResponse : &lResponse);
    DelayMs(100); //Laisse le temps de  compléter la réponse.
    if(lenAnswer > 1)
    {
        vVMCAcknowledge(RSP_ACK);
    }
    //TODO à supprimer
    if(lenAnswer == 0)
    {
        Nop();
    }
    //-----------
    return lenAnswer;
}

/******************************************************************************/

void vVMCAcknowledge(const BYTE byAcknowledge)
{
    UART_DATA uaAcknowledge;
    uaAcknowledge.__data = byAcknowledge;
    isNAKMDB = FALSE;
    xTimerStart(xTimerMDBNAK, 1000);
    while(!UARTTransmitterIsReady(MDBUART) && !isNAKMDB);
    UARTSendData(MDBUART, uaAcknowledge);
    while(!(UARTGetLineStatus(MDBUART) & UART_TRANSMITTER_EMPTY));
}

/******************************************************************************/

BOOL isMDBSetupConfig(const BYTE byDeviceAddress, void *byStatus, const BYTE byLen)
{
    if(byMDBSendCommand(byDeviceAddress, CMD_SETUP, 0, NULL, byStatus) > 1)
    {
        vVMCAcknowledge(RSP_ACK);
        return TRUE;
    }
    else
    {
        vVMCAcknowledge(RSP_NAK);
    }
    return FALSE;
}

/******************************************************************************/

WORD wDecimalDivider(BYTE byDecimal)
{
    return wDecimalFactor[byDecimal];
}

/******************************************************************************/

DWORD dwGetMaxReturn(void)
{
    BYTE byIndex;
    DWORD result = 200;
    if(isBillValidatorReseted)
    {
        for(byIndex = 0; byIndex < 16; byIndex++)
        {
            if(((centralParameters.billType.byBillEnable[1] >> byIndex) & 0x01) && billValidatorSetup.byBillValue[byIndex])
            {
                result = billValidatorSetup.byBillValue[byIndex] * billValidatorSetup.wScaleFactor;
            }

        }
    }
    return result;
}