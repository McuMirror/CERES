
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
     * \brief Num�ro de la machine de  r�f�rence.
     */
    BYTE byNumRefMachine;

    /**
     * \var byNumMachine
     * \brief Num�ro de la machine en cours de s�lection.
     */
    BYTE byNumMachine;

    /**
     * \var byIndexSelectedMachine
     * \brief Index dans la liste de la machine en cours de traitement.
     */
    BYTE byIndexSelectedMachine;

    /**
     * \var isFromHTTP
     * \brief Bool�n indiquant si la demande vient d'un client HTTP.
     */
    BOOL isFromHTTP;

    /**
     * \var byIndexMachineHTPP
     * \brief Index de la machine en mode FTTP
     */
    BYTE byIndexMachineHTPP;

    /**
     * \var byNumMachineHTTP
     * \brief Num�ro de la machine en cours sous HTTP
     */
    BYTE byNumMachineHTTP;

    /**
     * \var byHTTPNumMachine
     * \brief Copie du num�ro de machine pour l'affichage dans le serveur.
     */
    BYTE byHTTPNumMachine;

    /**
     * \var wE2OperationPosRead
     * \brief Adresse eeprom � partir de laquelle il  faut lire l'op�ration.
     */
    WORD wE2OperationPosRead;

    /**
     * \var wE2OperationPos
     * \brief Adresse eeprom � partir de laquelle il faut �crire la derni�re op�ation
     */
    WORD wE2OperationPos;

    /**
     * \var wE2OperationPosBack
     * \brief Sauvegarde de l'adresse eeprom � partir de laquelle il faut �crire la derni�re op�ation
     */
    WORD wE2OperationPosBack;

    /**
     * \var byDecimalPos
     * \brief Position du s�parateur d�cimal.
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
     * \brief Indique si une op�ration de rendu peut-�tre effectu�e.
     * Autoris� seulement si une pi�ce a �t� ins�r�e.
     */
    BOOL isChangeAutorized;

    BYTE byDir;

    /**
     * \var hTimerTOKBD
     * \brief Handle du timer g�rant le time-out du clavier
     */
    TimerHandle_t hTimerTOKBD;

    /**
     * \var hTimerTOOverpay
     * \brief Handle du timer g�rant le time-out du trop per�u.
     */
    TimerHandle_t hTimerTOOverpay;

    /**
     * \var hTimerTOCumul
     * \brief Handle du timer g�rant le time-out du cumul.
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

