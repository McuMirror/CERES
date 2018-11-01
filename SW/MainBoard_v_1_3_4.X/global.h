
/** ****************************************************************************
 * \file            global.h                                                     
 * \brief			Header contenant les variables globales
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef GLOBAL_H
#define	GLOBAL_H

#ifdef	__cplusplus
extern "C"
{
#endif

    /*Variables********************************************************************/
    /**
     * \var byNumRefMachine
     * \brief Numéro de la machine de  référence.
     */
    BYTE byNumRefMachine;

    /**
     * \var byNumMachine
     * \brief Numéro de la machine en cours de sélection.
     */
    BYTE byNumMachine;

    /**
     * \var byIndexSelectedMachine
     * \brief Index dans la liste de la machine en cours de traitement.
     */
    BYTE byIndexSelectedMachine;

    /**
     * \var isFromHTTP
     * \brief Boolén indiquant si la demande vient d'un client HTTP.
     */
    BOOL isFromHTTP;

    /**
     * \var byIndexMachineHTPP
     * \brief Index de la machine en mode FTTP
     */
    BYTE byIndexMachineHTPP;

    /**
     * \var byNumMachineHTTP
     * \brief Numéro de la machine en cours sous HTTP
     */
    BYTE byNumMachineHTTP;

    /**
     * \var byHTTPNumMachine
     * \brief Copie du numéro de machine pour l'affichage dans le serveur.
     */
    BYTE byHTTPNumMachine;

    /**
     * \var wE2OperationPosRead
     * \brief Adresse eeprom à partir de laquelle il  faut lire l'opération.
     */
    WORD wE2OperationPosRead;

    /**
     * \var wE2OperationPos
     * \brief Adresse eeprom à partir de laquelle il faut écrire la dernière opéation
     */
    WORD wE2OperationPos;

    /**
     * \var wE2OperationPosBack
     * \brief Sauvegarde de l'adresse eeprom à partir de laquelle il faut écrire la dernière opéation
     */
    WORD wE2OperationPosBack;

    /**
     * \var byDecimalPos
     * \brief Position du séparateur décimal.
     */
    BYTE byDecimalPos;

    /**\var wCurrencyDivider
     * \brief Variable contenant la valeur du diviseur pour obtenir la valeur en devise
     */
    WORD wCurrencyDivider;

    /**
     * \var lAmountInCashDispo
     * \brief Montant disponible en cash.
     */
    long lAmountInCashDispo;

    /**
     * \var isChangeAutorized
     * \brief Indique si une opération de rendu peut-être effectuée.
     * Autorisé seulement si une pièce a été insérée.
     */
    BOOL isChangeAutorized;

    BYTE byDir;

    /**
     * \var hTimerTOKBD
     * \brief Handle du timer gérant le time-out du clavier
     */
    TimerHandle_t hTimerTOKBD;

    /**
     * \var hTimerTOOverpay
     * \brief Handle du timer gérant le time-out du trop perçu.
     */
    TimerHandle_t hTimerTOOverpay;

    /**
     * \var hTimerTOCumul
     * \brief Handle du timer gérant le time-out du cumul.
     */
    TimerHandle_t hTimerTOCumul;

    /**
     * \var hTimerDispense
     * \brief handle di timer de TO de la distribution.
     */
    TimerHandle_t hTimerDispense;

    /*End of variables*************************************************************/

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_H */

