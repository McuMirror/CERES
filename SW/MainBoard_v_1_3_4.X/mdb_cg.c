
/** ****************************************************************************
 * \file            mdb_cg.c                                                 
 * \brief			Sources de la gestion du changeur
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/
#include "mdb_cg.h"

/******************************************************************************/

/*********************************************************************
 * Function:        static BOOL isSetMDBCoinType(COINTYPE *coinType)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
static BOOL isSetMDBCoinType(COINTYPE *coinType)
{
    BYTE byAcknowledge;
    return ((byMDBSendCommand(CGADDRESS, CMD_COIN_TYPE, sizeof (COINTYPE),
                              coinType, &byAcknowledge) == 1) && (byAcknowledge == RSP_ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        BOOL isGetMDBChangerID(CHANGERID *byID)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
BOOL isGetMDBChangerID(CHANGERID *byID)
{
    BYTE byParameter = SUB_REQUEST_ID;
    if(byMDBSendCommand(CGADDRESS, CMD_EXPANSION, 0x01, &byParameter,
                        byID) == sizeof (CHANGERID) + 1)
    {
        vVMCAcknowledge(RSP_ACK);
        return (TRUE);
    }
    else
    {
        vVMCAcknowledge(RSP_NAK);
    }
    return FALSE;
}

/******************************************************************************/

/*********************************************************************
 * Function:        BOOL isGetMDBTubeStatus(TUBESSTATUS *tubeStatus)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
BOOL isGetMDBTubeStatus(TUBESSTATUS *tubeStatus)
{
    if(byMDBSendCommand(CGADDRESS, CMD_TUBE_STATUS, 0x00, NULL,
                        tubeStatus) == sizeof (TUBESSTATUS) + 1)
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

/*********************************************************************
 * Function:        BOOL isEnableChanger(const BOOL isEnable, COINTYPE *coinType)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
BOOL isEnableChanger(const BOOL isEnable, COINTYPE *coinType)
{
    WORD wEnable;
    BOOL isResult = FALSE;
    if(isChangerReseted)
    {
        wEnable = coinType->wCoinEnable;
        if(!isEnable)
        {
            memset(&coinType->wCoinEnable, 0, sizeof (coinType->wCoinEnable));
            memset(&coinType->byDispenseEnable, 0xFF, sizeof (coinType->byDispenseEnable));
        }
        isResult = isSetMDBCoinType(coinType);
        coinType->wCoinEnable = wEnable;
    }
    return isResult;
}

/******************************************************************************/

/*********************************************************************
 * Function:        BOOL isEnableFeature()
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
BOOL isEnableFeature()
{
    BYTE byAcknowledge;
    BYTE byParameters[5] = {SUB_CHANGER_FEATURE_ENABLE, 0X00, 0X00, 0X00, 0X0F};
    return ((byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameters),
                              byParameters, &byAcknowledge) == 1) && (byAcknowledge == RSP_ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        BOOL isAlternatePayout(const BYTE byAmount)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
BOOL isAlternatePayout(const BYTE byAmount)
{
    //BYTE byNumberScalingFactor = (BYTE)(wAmount / changeGiverConfig.deviceConfig.byScaleFactor);
    BYTE byAcknowledge;
    BYTE byParameters[2] = {SUB_ALTERNATIVE_PAYOUT, byAmount};
    return ((byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameters),
                              byParameters, &byAcknowledge) == 1) && (byAcknowledge == RSP_ACK));
}

/******************************************************************************/

/*********************************************************************
 * Function:        BOOL isPayoutStatus(BYTE *byChannels)
 * 
 * Version:         1.0
 * 
 * Date:            01/01/2017
 * 
 * Author:          Rachid AKKOUCHE    
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
BOOL isPayoutStatus(BYTE *byChannels)
{
    BYTE byParameter = SUB_ALT_PAYOUT_STATUS;

    if(byMDBSendCommand(CGADDRESS, CMD_EXPANSION, sizeof (byParameter), &byParameter, byChannels) >= MAXNUMBERCHANNELSCG)
    {
        vVMCAcknowledge(RSP_ACK);
        return TRUE;
    }
    return FALSE;
}

/******************************************************************************/
