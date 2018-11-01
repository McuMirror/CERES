
/** ****************************************************************************
 * \file            exception.h                                                     
 * \brief			Header de la gestion des exceptions
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/

#ifndef EXCEPTION_H
#define	EXCEPTION_H

#include <plib.h>
#include "lcd4u.h"

/**
 * \defgroup EXCEPTION Gestion des exceptions
 * \details seulement en mode debuggage.
 * @{
 */

#ifdef __L_DEBUG
/*Enumeration**************************************************************/

/**
 * \brief liste des cas d'exception.
 */
static enum _excep_code
{
    EXCEP_IRQ = 0, /*!< interrupt*/
    EXCEP_AdEL = 4, /*!< address error exception (load or ifetch)*/
    EXCEP_AdES, /*!< address error exception (store)*/
    EXCEP_IBE, /*!< bus error (ifetch)*/
    EXCEP_DBE, /*!< bus error (load/store)*/
    EXCEP_Sys, /*!< syscall*/
    EXCEP_Bp, /*!< breakpoint*/
    EXCEP_RI, /*!< reserved instruction*/
    EXCEP_CpU, /*!< coprocessor unusable*/
    EXCEP_Overflow, /*!< arithmetic overflow*/
    EXCEP_Trap, /*!< trap (possible divide by zero)*/
    EXCEP_IS1 = 16, /*!< implementation specfic 1*/
    EXCEP_CEU, /*!< CorExtend Unuseable*/
    EXCEP_C2E /*!< coprocessor 2*/
} _excep_code;
/*End of enumeration*******************************************************/

/*Variables****************************************************************/

/**
 * \var _epc_code
 * \brief code remvoyé par le micro.
 */
static unsigned int _epc_code;

/**
 * \var _excep_addr
 * \brief adresse de l'exception.
 */
static unsigned int _excep_addr;
/*End of variables*********************************************************/

/*Prototypes***************************************************************/

/**
 * \brief traitement de l'exception
 */
void _general_exception_handler(void);
/*End of prototypes********************************************************/

#endif
/**@}*/
#endif	/* EXCEPTION_H */

