/* 
 * File:   datetime.h
 * Author: Administrateur
 *
 * Created on 26 juillet 2014, 10:31
 */

#ifndef DATETIME_H
#define	DATETIME_H

#include <plib.h>

/*Enum*************************************************************************/

/**
 * \enum SEASONS
 * \brief Saisons du changement d'heure.
 */
typedef enum
{
    SUMMER,
    WINTER,
} __attribute__((packed)) SEASONS;

/**
 * \var Now
 * \brief Variable contenant une heure
 */
rtccTime Now;

/*Prototypes*******************************************************************/

/**
 * \fn getDSTDate
 * \brief Calcul du jour de passage à l'heure d'été
 * \param[in] wYear Année pour laquelle on calcul cette date.;
 * \param[in] season Saison pour laquelle la date est recherchée.
 * \return date au format rtcc de la date.
 */
rtccDate getDSTDate(const WORD wYear, const SEASONS season);

/******************************************************************************/
#endif	/* DATETIME_H */

