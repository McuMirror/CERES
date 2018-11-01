/** ****************************************************************************
 * \file            datetime.c 
 * \brief			Sources de la gestion de la date et de l'heure de la carte                        
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
*******************************************************************************/

#include "datetime.h"

rtccDate getDSTDate(const WORD wYear, const SEASONS season)
{
    BYTE byDay;
    rtccDate date;
    date.mday = 0x31;
    date.mon = season == SUMMER ? 0X03 : 0X10;
    date.year = (((wYear - 2000) / 10) << 4) + (wYear % 10);
    //byDay = 31 - getDayOfWeek(date);
    byDay = 31 - RtccWeekDay(wYear, ((date.mon >> 4) * 10) + (date.mon & 0X0F),
                             ((date.mday >> 4) * 10) + (date.mday & 0X0F));
    date.mday = ((byDay / 10) << 4)+(byDay % 10);
    return date;
}

/******************************************************************************/
