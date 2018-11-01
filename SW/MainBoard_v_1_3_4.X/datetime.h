/** ****************************************************************************
 * \file            datetime.h                                                     
 * \brief			Header de la gestion de la date et de l'heure                     
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef DATETIME_H
#define	DATETIME_H

#include <plib.h>

/**
 * \defgroup DATE_TIME Gestion de la date et de l'heure de la carte
 * @{
 */

/*Typedefs*********************************************************************/

/**
 * \brief Saisons du changement d'heure.
 */
typedef enum
{
    SUMMER, /*!<Heure d'été.*/
    WINTER, /*!<Heure d'hiver.*/
} SEASONS;
/*End of typedefs**************************************************************/

/*Variables********************************************************************/
/**
 * \var Now
 * \brief Variable contenant une heure
 */
rtccTime Now;
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/
/**
 * \brief Calcul du jour de passage à l'heure d'été
 * \param[in] wYear Année pour laquelle on calcul cette date.;
 * \param[in] season Saison pour laquelle la date est recherchée.
 * \return date au format rtcc de la date.
 */
rtccDate getDSTDate(const WORD wYear, const SEASONS season);
/*End of prototypes*******************************************************************/
/**@}*/
#endif	/* DATETIME_H */

