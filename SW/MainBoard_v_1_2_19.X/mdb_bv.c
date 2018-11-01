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
    if(byMDBSendCommand(BVADDRESS, CMD_STACKER, 0X00, NULL, (BYTE*)stacker) == sizeof (byStacker) + 1)
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
