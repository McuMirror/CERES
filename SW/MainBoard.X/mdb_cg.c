#include "mdb_cg.h"

/******************************************************************************/

BOOL boGetMDBChangerID(ChangerIdentification *Idenfication)
{
    BYTE byParameter = SUB_REQUEST_ID;
    if(byMDBSendCommand(CGADDRESS, CMD_EXPANSION, 0x01, &byParameter,
                        Idenfication) == sizeof (ChangerIdentification) + 1)
    {
        vVMCAcknowledge(ACK);
        return (TRUE);
    }
    else
    {
        vVMCAcknowledge(NAK);
    }
    return FALSE;
}

/******************************************************************************/

BOOL boGetMDBTubeStatus(TubeStatus *tubesStatus)
{
    if(byMDBSendCommand(CGADDRESS, CMD_TUBE_STATUS, 0x00, NULL,
                        tubesStatus) == sizeof (TubeStatus) + 1)
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

BOOL boSetMDBCoinType(CoinType *coinType)
{
    BYTE byAcknowledge;
    return ((byMDBSendCommand(CGADDRESS, CMD_COIN_TYPE, sizeof (CoinType),
                              coinType, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL boDispenseMDBChanger(const BYTE byCoin, const BYTE byNum)
{
    BYTE byParameter = byCoin | (byNum << 4);
    BYTE byAcknowledge;
    return ((byMDBSendCommand(CGADDRESS, CMD_DISPENSE, sizeof (byParameter),
                            &byParameter, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL boEnableChanger(const BOOL boEnable, CoinType *coinType)
{
    WORD wEnable;
    BOOL boResult = FALSE;
    wEnable = coinType->wCoinEnable;
    if(boChangerReseted)
    {
        if(!boEnable)
        {
            memset(&coinType->wCoinEnable, 0, sizeof (coinType->wCoinEnable));
            memset(&coinType->byDispenseEnable, 0xFF, sizeof (coinType->byDispenseEnable));
        }
        boResult = boSetMDBCoinType(coinType);
    }
    coinType->wCoinEnable = wEnable;
    return boResult;
}

/******************************************************************************/

BOOL boEnableFeature()
{
    BYTE byAcknowledge;
    BYTE byParameters[5] = {SUB_CHANGER_FEATURE_ENABLE, 0X00, 0X00, 0X00, 0X0F};
    return ((byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameters),
                              byParameters, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL boAlternatePayout(const WORD wAmount)
{
    BYTE byNumberScalingFactor = (BYTE)(wAmount / changeGiverConfig.deviceConfig.byScaleFactor);
    BYTE byAcknowledge;
    BYTE byParameters[2] = {SUB_ALTERNATIVE_PAYOUT, byNumberScalingFactor};
    return ((byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameters),
                              byParameters, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL boPayoutStatus(BYTE *byChannels)
{
    BYTE byParameter = SUB_ALT_PAYOUT_STATUS;

    return(byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameter), &byParameter, byChannels) >= MAXNUMBERCHANNELSCG);
}

/******************************************************************************/
