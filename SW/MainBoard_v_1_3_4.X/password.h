
/** ****************************************************************************
 * \file            password.h                                                 
 * \brief			Header de la gestion des mots de passe
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/

#ifndef PASSWORD_H
#define	PASSWORD_H
#include "GenericTypeDefs.h"

/**
 * \defgroup PASSWORD Gestion des mots de passe
 * @{
 */

/*Typedefs*********************************************************************/

/**
 * \typedef PASSWORDS
 * \brief type de structure contenant les mots de passe.
 */
typedef struct __attribute__((packed)) PASSWORDS
{
    short localTechnician; /*!<Mot de passe technicien sur site.*/
    short localAccountant; /*!<Mot de passe permettant l'acc�s � la comptabilit� sur site.*/
    short httpTechnician; /*!<Mot de passe technicien par internet.*/
    short httpAccountant; /*!<Mot de passe permettant l'acc�s � la compabilit� apr internet.*/
}
PASSWORDS;
/*End of typedefs**************************************************************/

/*Variables********************************************************************/

/**
 * \var isLocalAccountantEnable
 * \brief Indique si l'acc�s � la comptablit� est autoris�
 * \details Concerne l'acc�s sur site.
 */
BOOL isLocalAccountantEnable;

/**
 * \var isHttpAccountantEnable
 * \brief Indique si l'acc�s � la comptablit� est autoris�
 * \details Concerne l'acc�s par internet
 */
BOOL isHttpAccountantEnable;
/*End of variables*************************************************************/
/**@}*/

#endif
