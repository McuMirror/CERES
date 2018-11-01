#include "mdb_cl.h"

/******************************************************************************/

BOOL isMDBSetupMaxMinPrice(const BYTE byDeviceAddress, const VMCMaxMin *vmcMaxMinPrice)
{
    BYTE byAcknowledge;
    BYTE byBuff[5];
    byBuff[0] = SUB_MAX_MIN_PRICE;
    memmove(&byBuff[1], &vmcMaxMinPrice->wMax, 2);
    memmove(&byBuff[3], &vmcMaxMinPrice->wMin, 2);
    return ((byMDBSendCommand(byDeviceAddress, CMD_SETUP, 0x05, byBuff, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBLimitRevalueRequest(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    BYTE byParameter = {SUB_REVALUE_LIMIT_REQUEST};
    return ((byMDBSendCommand(byDeviceAddress, CMD_REVALUE, 0x01, &byParameter, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBCLEnable(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    BYTE byParameter = SUB_READER_ENABLE;
    return ((byMDBSendCommand(byDeviceAddress, CMD_READER, 0X01, &byParameter, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBSessionComplete(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    BYTE byParameter = SUB_VEND_SESSION_COMPLETE;
    return ((byMDBSendCommand(byDeviceAddress, CMD_VEND, 0X01, &byParameter, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBVendRequest(const BYTE byDeviceAddress, const long *lAmount)
{
    BYTE byAcknowledge;
    BYTE byBuff[5];
    byBuff[0] = SUB_VEND_REQUEST;
    byBuff[1] = (BYTE)(*lAmount / 256);
    byBuff[2] = (BYTE)(*lAmount % 256);
    byBuff[3] = byBuff[4] = 0xFF;
    return ((byMDBSendCommand(byDeviceAddress, CMD_VEND, 0x05, byBuff, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBRevalueRequest(const BYTE byDeviceAddress, const long *lAmount)
{
    BYTE byAcknowledge;
    BYTE byBuff[3];
    byBuff[0] = SUB_REVALUE_REQUEST;
    byBuff[1] = (BYTE)(*lAmount / 256);
    byBuff[2] = (BYTE)(*lAmount % 256);
    return ((byMDBSendCommand(byDeviceAddress, CMD_REVALUE, 0x03, byBuff, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBSetupCLConfig(const BYTE byDeviceAddress, VMCConfig *ptrParameters)
{
    BYTE byAcknowledge;
    ptrParameters->byCmd = SUB_CONFIG_DATA;
    return ((byMDBSendCommand(byDeviceAddress, CMD_SETUP, sizeof (VMCConfig), ptrParameters, &byAcknowledge) == 1)) &&
        ((byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isMDBVendSuccess(const BYTE byDeviceAddress)
{
    BYTE byAcknowledge;
    BYTE byBuff[3];
    byBuff[0] = SUB_VEND_SUCCESS;
    byBuff[1] = byBuff[2] = 0XFF;
    return ((byMDBSendCommand(byDeviceAddress, CMD_VEND, 0x03, byBuff, &byAcknowledge) == 1) &&
            (byAcknowledge == ACK));
}

/******************************************************************************/

