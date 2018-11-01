#include "mdb_cg.h"

/******************************************************************************/

BOOL isGetMDBChangerID(ChangerIdentification *Idenfication)
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

BOOL isGetMDBTubeStatus(TubeStatus *tubesStatus)
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

BOOL isSetMDBCoinType(CoinType *coinType)
{
    BYTE byAcknowledge;
    return ((byMDBSendCommand(CGADDRESS, CMD_COIN_TYPE, sizeof (CoinType),
                              coinType, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isDispenseMDBChanger(const BYTE byCoin, const BYTE byNum)
{
    BYTE byParameter = byCoin | (byNum << 4);
    BYTE byAcknowledge;
    return ((byMDBSendCommand(CGADDRESS, CMD_DISPENSE, sizeof (byParameter),
                            &byParameter, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isEnableChanger(const BOOL isEnable, CoinType *coinType)
{
    WORD wEnable;
    BOOL isResult = FALSE;
    wEnable = coinType->wCoinEnable;
    if(isChangerReseted)
    {
        if(!isEnable)
        {
            memset(&coinType->wCoinEnable, 0, sizeof (coinType->wCoinEnable));
            memset(&coinType->byDispenseEnable, 0xFF, sizeof (coinType->byDispenseEnable));
        }
        isResult = isSetMDBCoinType(coinType);
    }
    coinType->wCoinEnable = wEnable;
    return isResult;
}

/******************************************************************************/

BOOL isEnableFeature()
{
    BYTE byAcknowledge;
    BYTE byParameters[5] = {SUB_CHANGER_FEATURE_ENABLE, 0X00, 0X00, 0X00, 0X0F};
    return ((byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameters),
                              byParameters, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isAlternatePayout(const BYTE byAmount)
{
    //BYTE byNumberScalingFactor = (BYTE)(wAmount / changeGiverConfig.deviceConfig.byScaleFactor);
    BYTE byAcknowledge;
    BYTE byParameters[2] = {SUB_ALTERNATIVE_PAYOUT, byAmount};
    return ((byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameters),
                              byParameters, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isPayoutStatus(BYTE *byChannels)
{
    BYTE byParameter = SUB_ALT_PAYOUT_STATUS;

    return(byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameter), &byParameter, byChannels) >= MAXNUMBERCHANNELSCG);
}

/******************************************************************************/
