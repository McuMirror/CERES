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
     * \brief Position du séparateur décimal.
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

    #ifdef	__cplusplus
}
    #endif

#endif	/* GLOBAL_H */

