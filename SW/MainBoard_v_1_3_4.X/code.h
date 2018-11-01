/** ****************************************************************************
 * \file            code.h                                                     
 * \brief			Header de la gestion des codes USB                         
 * \date            2012.11.15                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef CODE_H
#define	CODE_H

#include <plib.h>
#include "I2CE2PROML.h"

/**
 * \defgroup CODE Gestion du codage des fichiers USB
 * \brief Gestion des codes concernant les cl�s USB
 * @{
 */

/*Macros**********************************************************************/
/**
 * \def SIZECODE
 * \brief Nombre d'octet des codes.
 */
#define SIZECODE 6
/*End defines******************************************************************/

/*Variables********************************************************************/

/**
 * \var BYTE codeCredit[SIZECODE];
 * \brief code utilis� pour enregistrer le cr�dit sur la cl�.
 */
BYTE codeCredit[SIZECODE];

/**
 * \var codeInter
 * \brief code utils� pour coder la zone interm�diaire.
 */
BYTE codeInter[SIZECODE];

/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * \brief Cr�e et enregistre un code
 * \param[in] wAddress adresse dans l'eeprom qui contiendra le code.
 * \param[in] ptrCode pointeur sur le buffer qui contiendra le code.
 */
void vCreateCode(const WORD wAddress, void *ptrCode);
/*End of prototypes************************************************************/
/**@}*/

#endif	/* CODE_H */

