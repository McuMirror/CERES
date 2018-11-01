/*
 * File:   global.h
 * Author: Administrateur
 *
 * Created on 14 novembre 2014, 11:14
 */

#ifndef GLOBAL_H
    #define	GLOBAL_H

    #ifdef	__cplusplus
extern "C"
{
    #endif
    
    /*Defines**********************************************************************/

    #define HistoSheetSize 20

    /*Variables********************************************************************/

    /**
     * \var byDecimalPos
     * \brief Position du s�parateur d�cimal.
     */
    BYTE byDecimalPos;

    WORD wCurrencyDivider;

    BYTE byIndHisto;

    BYTE byNummch;

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

    #ifdef	__cplusplus
}
    #endif

#endif	/* GLOBAL_H */

