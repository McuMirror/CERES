#include "mdb_bv.h"

/******************************************************************************/

static BOOL isSetMDBillType(BillType *billType)
{
    BYTE byAcknowledge;
    return ((byMDBSendCommand(BVADDRESS, CMD_BILL_TYPE, sizeof (BillType),
                              billType, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL isGetMDBStackerStatus(BYTE *stacker)
{
    if(byMDBSendCommand(BVADDRESS, CMD_STACKER, 0X00, NULL, stacker))
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

BOOL isEnableBillValidator(const BOOL isEnable, const BOOL isEscrow, BillType *billType)
{
    WORD wEnable;
    BOOL isResult = FALSE;
    if(isBillValidatorReseted)
    {
        wEnable = billType->wBillEnable;
        memset(&billType->byBillEscrow, isEscrow ? 0XFF : 0X00,
               sizeof (billType->byBillEscrow)); //Si l'escrow est validé il faut mettre l'escrow des billets.
        if(!isEnable)
        {
            memset(&billType->wBillEnable, 0X00, sizeof (billType->wBillEnable));
            memset(&billType->byBillEscrow, 0x00, sizeof (billType->byBillEscrow));
        }
        isResult = isSetMDBillType(billType);
        billType->wBillEnable = wEnable;
    }
    return isResult;
}

/******************************************************************************/

/*********************************************************************
 * Function:        BOOL isGetExId(EXID *exId)
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
BOOL isGetExId(EXID *exId)
{
    BYTE subCommand = SUB_CONFIG_DATA;;
    memset(exId, 0, sizeof (EXID));
    if(byMDBSendCommand(BVADDRESS, CMD_EXPANSION, 0X01, &subCommand, exId) == (sizeof (EXID) + 1))
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


