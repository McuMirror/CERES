#include "code.h"

/*********************************************************************
 * Function:        void vCreateCode(const WORD wAddress, void *timeDateCode)
 *
 * PreCondition:    None
 *
 * Input:           const WORD wAddress
 *                        Adresse dans l'eeprom où sera enregistré le code.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/

void vCreateCode(const WORD wAddress, void *ptrCode)
{
  rtccTime time;
  rtccDate date;

  BYTE *code;
  code = ptrCode;

  RtccGetTimeDate(&time, &date);
  memmove(code, &time.b[1], 3);
  memmove(&code[3], &date.b[1], 3);
  I2CE2promLWriteBuffer(wAddress, code, SIZECODE);
  code[0] = time.hour ^ (BYTE)rand();
  code[1] = date.year ^ EMAC1SA2 / 256;
  code[2] = time.min ^ EMAC1SA1 % 256;
  code[3] = date.mon ^ EMAC1SA1 / 256;
  code[4] = time.sec ^ EMAC1SA0 % 256;
  code[5] = date.mday ^ EMAC1SA0 / 256;
}
/******************************************************************************/