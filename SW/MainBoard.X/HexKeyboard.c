#include "HexKeyboard.h"

/******************************************************************************/

BYTE byGetKey(void)
{
    BYTE byIndex, byIndexLignes, byIndexCols, byKeyHit = 0;
    for(byIndexLignes = 0; byIndexLignes < 4; byIndexLignes++)
    {
        PORTClearBits(ROWPORT, 1 << (LINESSHIFT + byIndexLignes));
        for(byIndexCols = 0; byIndexCols < NUMCOLONNES; byIndexCols++)
        {
            byIndex = byIndexCols + (byIndexLignes * NUMCOLONNES);
            if(!PORTReadBits(COLUMNPORT, 1 << (COLUMNSHIFT + byIndexCols)))
            {
                if(kbdButton[byIndex].boNotUsed)
                {
                    if(kbdButton[byIndex].byLevel == (BOOL)LO)
                    {
                        if(kbdButton[byIndex].boTreated == FALSE)
                        {
                            byKeyHit = byKeyHitBack = (byIndex + 1);
                            kbdButton[byIndex].boNotUsed = FALSE;
                            break;
                        }
                        else
                        {
                            kbdButton[byIndex].boTreated = FALSE;
                            xTimerChangePeriod(hTimerKBDRepeat, lRepeatKBD, 100);
                        }
                    }
                    else
                    {
                        kbdButton[byIndex].byLevel = LO;
                    }
                }
            }
            else
            {
                if(kbdButton[byIndex].byLevel == LO)
                {
                    xTimerStop(hTimerKBDRepeat, 100);
                    lRepeatKBD = REPEATDELAYKBDBYDEFAULT;
                }
                kbdButton[byIndex].byLevel = HI;
                kbdButton[byIndex].boTreated = TRUE;
                kbdButton[byIndex].boNotUsed = TRUE;
            }
        }
        PORTSetBits(ROWPORT, LIGNES);
        if(byKeyHit)
        {
            break;
        }
    }
    return byKeyHit;
}

/******************************************************************************/

void vTimerRepeat(TimerHandle_t pxTimer)
{
    lRepeatKBD = lRepeatKBD > 100 ? lRepeatKBD - 200 : 100;
    kbdButton[byKeyHitBack - 1].boNotUsed = TRUE;
    kbdButton[byKeyHitBack - 1].boTreated = TRUE;
}

/******************************************************************************/
