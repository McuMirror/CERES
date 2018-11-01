#include "mdb_bv.h"

/******************************************************************************/

BOOL boSetMDBillType(BillType *billType)
{
    BYTE byAcknowledge;
    return((byMDBSendCommand(BVADDRESS, CMD_BILL_TYPE, sizeof(BillType),
                             billType, &byAcknowledge) == 1) && (byAcknowledge == ACK));
}

/******************************************************************************/

BOOL boGetMDBStackerStatus(BYTE *stacker)
{
    if(byMDBSendCommand(BVADDRESS, CMD_STACKER, 0X00, NULL, (BYTE*)stacker) == sizeof(byStacker) + 1)
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

BOOL boEnableBillValidator(const BOOL boEnable, const BOOL boEscrow, BillType *billType)
{
    WORD wEnable;
    BOOL boResult = FALSE;
    wEnable = billType->wBillEnable;
    memset(&billType->byBillEscrow, boEscrow ? 0XFF : 0X00, sizeof(billType->byBillEscrow)); //Si l'escrow est validé il faut mettre l'escrow des billets.
    if(boBillValidatorReseted)
    {
        if(!boEnable)
        {
            memset(&billType->wBillEnable, 0X00, sizeof(billType->wBillEnable));
            memset(&billType->byBillEscrow, 0x00, sizeof(billType->byBillEscrow));
        }
        boResult = boSetMDBillType(billType);
    }
    billType->wBillEnable = wEnable;
    return boResult;
}


/******************************************************************************/
