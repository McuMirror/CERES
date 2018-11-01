#include "satellites.h"

/******************************************************************************/

WORD wCRC16(const BYTE *byData, const BYTE byLen)
{
    BYTE byIndex, byIndex2;
    WORD wLCRC = 0;
    for(byIndex = 0; byIndex < byLen; ++byIndex)
    {
        wLCRC ^= (byData[ byIndex ] << 8);
        for(byIndex2 = 0; byIndex2 < 8; ++byIndex2)
        {
            (wLCRC & 0x8000) ? (wLCRC = ((wLCRC << 1) ^ 0x1021)) : /* 0001.0000 0010.0001 = x^12 + x^5 +1 (+x^16)*/ (wLCRC <<= 1);
        }
    }
    return wLCRC;
}

/******************************************************************************/

BOOL isReceiveAnswer(BYTE byNumMachine, BYTE byNewNumMachine)
{
    BYTE byToto, byToto1;
    byToto = byNumMachine;
    byToto1 = byNewNumMachine;
    WORD wCRC;
    SETREAD();
    while(!UARTReceivedDataIsAvailable(UART485) && wTORequest);
    if(!RS485GetBuffer(bySatBuffer, 6))
    {
        return FALSE;
    }
    if(!RS485GetBuffer(&bySatBuffer[6], bySatBuffer[1]))
    {
        return FALSE;
    }
    if(bySatBuffer[0] != HOST)
    {
        return FALSE;
    }
    if(bySatBuffer[1] > 10)
    {
        return FALSE;
    }
    if(!((bySatBuffer[2] == byNumMachine) || (bySatBuffer[2] == byNewNumMachine)))
    {
        Nop();
        return FALSE;
    }
    if(bySatBuffer[3] != MDI_ACK)
    {
        return FALSE;
    }
    memmove(&wCRC, &bySatBuffer[bySatBuffer[1] + 4], sizeof (WORD));
    if(wCRC != wCRC16(bySatBuffer, bySatBuffer[1] + 4))
    {
        return FALSE;
    }
    return TRUE;
}

/******************************************************************************/

//void vSendCommand(const BYTE byNumMachine, const BYTE byHeader,
//                  const BYTE byLenData, const void *byData)
//{
//    WORD wLCRC;
//    uartReg[UART485]->sta.reg = 0;
//    uartReg[UART485]->sta.set = _U1STA_UTXEN_MASK;
//    uartReg[UART485]->sta.set = _U1STA_URXEN_MASK;
//    memset(bySatBuffer, 0, sizeof(bySatBuffer));
//    bySatBuffer[0] = byNumMachine;
//    bySatBuffer[1] = byLenData;
//    bySatBuffer[2] = HOST;
//    bySatBuffer[3] = byHeader;
//    memmove(&bySatBuffer[4], byData, byLenData);
//    wLCRC = wCRC16(bySatBuffer, byLenData + 4);
//    memmove(&bySatBuffer[byLenData + 4], &wLCRC, sizeof(WORD));
//    vTaskSuspendAll();
//
//    RS485WriteBuffer(bySatBuffer, byLenData + 6);
//    xTaskResumeAll();
//    wTORequest = SAT_TO;
//}
//
///******************************************************************************/
//
//BOOL boReceiveAnswer(const BYTE byNumMachine)
//{
//    WORD wCRC;
//    SETREAD();
//    while(!UARTReceivedDataIsAvailable(UART485) && wTORequest);
//    if(!RS485GetBuffer(bySatBuffer, 6))
//    {
//        return FALSE;
//    }
//    if(!RS485GetBuffer(&bySatBuffer[6], bySatBuffer[1]))
//    {
//        return FALSE;
//    }
//
//    if(bySatBuffer[0] != HOST)
//    {
//        return FALSE;
//    }
//    if(bySatBuffer[1] > 10)
//    {
//        return FALSE;
//    }
//    if(bySatBuffer[2] != byNumMachine)
//    {
//        return FALSE;
//    }
//    if(bySatBuffer[3] != MDI_ACK)
//    {
//        return FALSE;
//    }
//    memmove(&wCRC, &bySatBuffer[bySatBuffer[1] + 4], sizeof(WORD));
//    if(wCRC != wCRC16(bySatBuffer, bySatBuffer[1] + 4))
//    {
//        return FALSE;
//    }
//    return TRUE;
//}
//
///******************************************************************************/

BOOL isSendCommand(const BYTE byNumMachine, const BYTE byHeader,
                   const BYTE byLenData, const void *byData)
{
    WORD wLCRC;
    BYTE byRetry = 4;
    BYTE byNewMachine = 0XFF;
    do
    {
        DelayMs(20);
        uartReg[UART485]->sta.reg = 0;
        uartReg[UART485]->sta.set = _U1STA_UTXEN_MASK;
        uartReg[UART485]->sta.set = _U1STA_URXEN_MASK;
        memset(bySatBuffer, 0, sizeof (bySatBuffer));
        bySatBuffer[0] = byNumMachine;
        bySatBuffer[1] = byLenData;
        bySatBuffer[2] = HOST;
        bySatBuffer[3] = byHeader;
        memmove(&bySatBuffer[4], byData, byLenData);
        wLCRC = wCRC16(bySatBuffer, byLenData + 4);
        memmove(&bySatBuffer[byLenData + 4], &wLCRC, sizeof (WORD));
        vTaskSuspendAll();
        RS485WriteBuffer(bySatBuffer, byLenData + 6);
        xTaskResumeAll();
        wTORequest = SAT_TO;
        if(byHeader == MODIFY_MACHINE_NUMBER)
        {
            byNewMachine = bySatBuffer[4];
        }
        memset(bySatBuffer, 0, sizeof (bySatBuffer));
    }
    while(!isReceiveAnswer(byNumMachine, byNewMachine) && --byRetry);
    return (byRetry > 0);
}

/******************************************************************************/

BOOL isModifyMachineNumber(const BYTE byOldNumMachine, BYTE byNewNumMachine)
{
    BOOL isResult;
    //    vSendCommand(byOldNumMachine, MODIFY_MACHINE_NUMBER, sizeof (byNewNumMachine), &byNewNumMachine);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNewNumMachine);
    isResult = isSendCommand(byOldNumMachine, MODIFY_MACHINE_NUMBER, sizeof (byNewNumMachine), &byNewNumMachine);
    return isResult;
}

/******************************************************************************/

BOOL isSimplePoll(const BYTE byNumMachine)
{
    //    vSendCommand(byNumMachine, SIMPLEPOLL, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNumMachine);
    return isSendCommand(byNumMachine, SIMPLEPOLL, 0, NULL);
}

/******************************************************************************/

BOOL isMainPresent(const BYTE byNumMachine)
{
    //    vSendCommand(byNumMachine, REQUEST_ISMAINPRESENT, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    if(boReceiveAnswer(byNumMachine))
    //    {
    //        return (EPRESENT)bySatBuffer[4];
    //    }
    //    return ABSENT;
    if(isSendCommand(byNumMachine, REQUEST_ISMAINPRESENT, 0, NULL))
    {
        return (EPRESENT)bySatBuffer[4];
    }
    return ABSENT;
}

/******************************************************************************/

BOOL isModifyMachineRelayState(const BYTE byNumMachine, const ESTATE relayState)
{
    //    BYTE byRelayState = (BYTE)relayState;
    //    vSendCommand(byNumMachine, MODIFY_MACHINE_RELAY_STATE, 1, &byRelayState);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNumMachine);
    BYTE byRelayState = (BYTE)relayState;
    return isSendCommand(byNumMachine, MODIFY_MACHINE_RELAY_STATE, 1, &byRelayState);
}

/******************************************************************************/

BOOL isExModifyMachineRelayState(const BYTE byNumMachine, const DWORD dwDelayActivation)
{
    //    DWORD dwActivation = dwDelayActivation;
    //    vSendCommand(byNumMachine, MODIFY_MACHINE_RELAY_STATE, sizeof (dwActivation), &dwActivation);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNumMachine);
    DWORD dwActivation = dwDelayActivation;
    return isSendCommand(byNumMachine, MODIFY_MACHINE_RELAY_STATE, sizeof (dwActivation), &dwActivation);
}

/******************************************************************************/

ESTATE getMachineRelayState(const BYTE byNumMachine)
{
    //    vSendCommand(byNumMachine, REQUEST_MACHINE_RELAY_STATE, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    if(boReceiveAnswer(byNumMachine))
    //    {
    //        return (ESTATE)bySatBuffer[4];
    //    }
    //    return RELAY_OFF;
    if(isSendCommand(byNumMachine, REQUEST_MACHINE_RELAY_STATE, 0, NULL))
    {
        return (ESTATE)bySatBuffer[4];
    }
    return RELAY_OFF;
}

/*****************************************************************************/

BOOL vSetMainPowerRelayState(const BYTE byNumMachine, const ESTATE relayState)
{
    //    BYTE byRelayState = (BYTE)relayState;
    //    vSendCommand(byNumMachine, MODIFY_MAIN_POWER, 1, &byRelayState);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNumMachine);
    BYTE byRelayState = (BYTE)relayState;
    return isSendCommand(byNumMachine, MODIFY_MAIN_POWER, 1, &byRelayState);
}

/******************************************************************************/

ESTATUS getMachineState(const BYTE byNumMachine)
{
    //    vSendCommand(byNumMachine, REQUEST_MACHINE_STATUS, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    if(boReceiveAnswer(byNumMachine))
    //    {
    //        return (ESTATUS)bySatBuffer[4];
    //    }
    //    return MACHINE_BUSY;
    if(isSendCommand(byNumMachine, REQUEST_MACHINE_STATUS, 0, NULL))
    {
        return (ESTATUS)bySatBuffer[4];
    }
    return MACHINE_BUSY;
}

/******************************************************************************/

BOOL isSetOverBusyDelay(const BYTE byNumMachine, DWORD dwOverBusyDelay)
{
    //    vSendCommand(byNumMachine, MODIFY_DELAY_OVER_BUSY, sizeof (dwOverBusyDelay),
    //            &dwOverBusyDelay);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNumMachine);
    return isSendCommand(byNumMachine, MODIFY_DELAY_OVER_BUSY, sizeof (dwOverBusyDelay),
                         &dwOverBusyDelay);
}

/******************************************************************************/

BOOL isSetSensibility(const BYTE byNumMachine, WORD wSensibility)
{
    //    vSendCommand(byNumMachine, MODIFY_BUSY_LEVEL, sizeof (wSensibility),
    //            &wSensibility);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    return boReceiveAnswer(byNumMachine);
    return isSendCommand(byNumMachine, MODIFY_BUSY_LEVEL, sizeof (wSensibility),
                         &wSensibility);
}

/******************************************************************************/

DWORD dwGetOverBusyDelay(const BYTE byNumMachine)
{
    DWORD dwResult;
    //    vSendCommand(byNumMachine, REQUEST_DELAY_OVER_BUSY, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    if(boReceiveAnswer(byNumMachine))
    //    {
    //        memmove(&dwResult, &bySatBuffer[4], sizeof (dwResult));
    //        return dwResult;
    //    }
    if(isSendCommand(byNumMachine, REQUEST_DELAY_OVER_BUSY, 0, NULL))
    {
        memmove(&dwResult, &bySatBuffer[4], sizeof (dwResult));
        return dwResult;
    }
    return ULONG_MAX;
}

/******************************************************************************/

ELEVEL getMachineFull(const BYTE byNumMachine)
{
    //    vSendCommand(byNumMachine, REQUEST_MACHINE_LEVEL, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    if(boReceiveAnswer(byNumMachine))
    //    {
    //        return (ELEVEL)bySatBuffer[4];
    //    }
    if(isSendCommand(byNumMachine, REQUEST_MACHINE_LEVEL, 0, NULL))
    {
        return (ELEVEL)bySatBuffer[4];
    }
    return NOTEMPTY;
}

/******************************************************************************/

WORD wGetSatelliteFWVersion(const BYTE byNumMachine)
{
    WORD wResult;
    //    vSendCommand(byNumMachine, REQUEST_FW_VERSION, 0, NULL);
    //    memset(bySatBuffer, 0, sizeof (bySatBuffer));
    //    if(boReceiveAnswer(byNumMachine))
    //    {
    //        memmove(&wResult, &bySatBuffer[4], sizeof (wResult));
    //        return wResult;
    //    }
    if(isSendCommand(byNumMachine, REQUEST_FW_VERSION, 0, NULL))
    {
        memmove(&wResult, &bySatBuffer[4], sizeof (wResult));
        return wResult;
    }
    return 0XFFFF;
}

/******************************************************************************/
