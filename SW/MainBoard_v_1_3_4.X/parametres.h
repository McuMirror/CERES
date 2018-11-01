
/** ****************************************************************************
 * \file            parametres.h                                                 
 * \brief			Header de la gestion des parametres de la centrale
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/

#ifndef PARAMETRES_H
#define	PARAMETRES_H

#include <plib.h>

#include "mdb_bv.h"
#include "mdb_cg.h"
#include "password.h"

/**
 * \defgroup PARAMETERS Gestion des param�tres.
 * @{
 */
/*Macros***********************************************************************/

/**
 * \brief Nombre maximum de machine.
 */
#define MAXMACHINES 64

/**
 * \def KBDTOBYDEFAUT
 * \brief Temps maximum sans utiliser le clavier en seconde avant de retour � l'�cran de initial.
 */
#define KBDTOBYDEFAUT 30

/**
 * \def OVERPAYTODEFAUT
 * \brief D�lai par d�faut pendant lequel le trop per�u sera disponible.
 */
#define OVERPAYTODEFAUT 0

/**
 * \def DEFAULTTOCUMUL
 * \brief D�lai par d�faut pendant lequel le cumul est autoris� le cas �ch�ant.
 */
#define DEFAULTTOCUMUL 60

/**
 * \def DELAY_FLIP
 * \brief D�lai entre l'inversion de la ligne basse et la ligne haute de l'afficheur.
 */
#define DELAY_FLIP (2 * SECONDE)

/**
 * \def DELAYCHECKCHANGE
 * \brief D�lai entre 2 v�rification pour effectuer un rendu
 */
#define DELAYCHECKCHANGE 500

/**
 * \def DELAYDISPLAYDEFAULT
 * \brief Temps d'affichage des saisies par d�faut en ms
 */
#define DELAYDISPLAYDEFAULT 1000

/**
 * \def DEFAUTAMOUNTEXACTCHANGE
 * \brief Montant par d�faut d�clenchant l'affichage du montant par d�faut.x
 */
#define DEFAUTAMOUNTEXACTCHANGE 2000

/**
 * \def TIME_TO_START
 * \brief Delai de d�marrage
 */
#define TIME_TO_START (5 * SECONDE)

/**
 * \def ADDRESS_CENTRAL_PARAMETERS
 * \brief Adresse de d�part du stockage des param�tres de la centrale dans l'eeprom.
 */
#define ADDRESS_CENTRAL_PARAMETERS (WORD)0

/**
 * \def ADDRESS_MACHINES_PARAMETERS
 * \brief Adresse de d�but dans l'eeprom des param�tres des machines.
 */
#define ADDRESS_MACHINES_PARAMETERS (WORD)1024

/**
 * \def ADDRESS_DEBUT_AUDIT
 * \brief Adresse de d�but dans l'eeprom des audits.
 */
#define ADDRESS_DEBUT_AUDIT (WORD)(ADDRESS_MACHINES_PARAMETERS + (64 * sizeof(SMACHINE_CONFIG)))

/**
 * \def ADDRESS_WNUMBERCHANNELGCIN
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pi�ce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCIN (WORD)ADDRESS_DEBUT_AUDIT

/**
 * \def ADDRESS_WNUMBERCHANNELGCOUT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pi�ce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCOUT (WORD)(ADDRESS_WNUMBERCHANNELGCIN + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERCHANNELBV
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de billet introduit.
 */
#define ADDRESS_WNUMBERCHANNELBV (WORD)(ADDRESS_WNUMBERCHANNELGCOUT + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERSERVICES
 * \brief Adresse dans l'eeprom des audit concernant le nombre de fois que chaque machine est selection�e.
 */
#define ADDRESS_WNUMBERSERVICES (WORD)(ADDRESS_WNUMBERCHANNELBV + (sizeof(WORD) * MAXNUMBERCHANNELSBV))

/**
 * \def ADDRESS_DWCASHLESSVEND
 * \brief Adresse dans l'eeprom du montant des effectu�es avec le syst�me cashless.
 */
#define ADDRESS_DWCASHLESSVEND (WORD)(ADDRESS_WNUMBERSERVICES + (sizeof(WORD) * MAXMACHINES))

/**
 * \def ADDRESS_DWCASHLESSREVALUE
 * \brief Adresse dans l'eeprom du montant des recharges effectu�es.
 */
#define ADDRESS_DWCASHLESSREVALUE (WORD)(ADDRESS_DWCASHLESSVEND + sizeof(DWORD))

/**
 * \def ADDRESS_DWCASHVEND
 * \brief Adresse dans l'eeprom du montant des ventes effectu�es en esp�ces.
 */
#define ADDRESS_DWCASHVEND (WORD)(ADDRESS_DWCASHLESSREVALUE + sizeof(DWORD))

/**
 * \def ADDRESS_DWOVERPAY
 * \brief Adresse dans l'eeprom du montant des trop per�us.
 */
#define ADDRESS_DWOVERPAY (WORD)(ADDRESS_DWCASHVEND + sizeof(DWORD))

/**
 * \def ADDRESS_DWREFILLING
 * \brief Adresse dans l'eeprom du montant recharg� dans le changer.
 */
#define ADDRESS_DWREFILLING (WORD)(ADDRESS_DWOVERPAY + sizeof(DWORD))

/**
 * \def ADDRESS_DWVENDUSB
 * \brief Adresse dans l'eeprom du montant des ventes effectu�es avec la cl� USB.
 */
#define ADDRESS_DWVENDUSB (WORD)(ADDRESS_DWREFILLING + sizeof(DWORD))

/**
 * \def ADDRESS_DEBUT_AUDIT_PERMANENT
 * \brief Adresse de d�but dans l'eeprom des audits.
 */
#define ADDRESS_DEBUT_AUDIT_PERMANENT (WORD)(ADDRESS_DEBUT_AUDIT + sizeof(AUDITDATA))

/**
 * \def ADDRESS_WNUMBERCHANNELGCIN_PERMANENT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pi�ce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCIN_PERMANENT (WORD)ADDRESS_DEBUT_AUDIT_PERMANENT

/**
 * \def ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pi�ce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT (WORD)(ADDRESS_WNUMBERCHANNELGCIN_PERMANENT + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERCHANNELBV_PERMANENT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de billet introduit.
 */
#define ADDRESS_WNUMBERCHANNELBV_PERMANENT (WORD)(ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERSERVICES_PERMANENT
 * \brief Adresse dans l'eeprom des audit concernant le nombre de fois que chaque machine est selection�e.
 */
#define ADDRESS_WNUMBERSERVICES_PERMANENT (WORD)(ADDRESS_WNUMBERCHANNELBV_PERMANENT + (sizeof(WORD) * MAXNUMBERCHANNELSBV))

/**
 * \def ADDRESS_DWCASHLESSVEND_PERMANENT
 * \brief Adresse dans l'eeprom du montant des effectu�es avec le syst�me cashless.
 */
#define ADDRESS_DWCASHLESSVEND_PERMANENT (WORD)(ADDRESS_WNUMBERSERVICES_PERMANENT + (sizeof(WORD) * MAXMACHINES))

/**
 * \def ADDRESS_DWCASHLESSREVALUE_PERMANENT
 * \brief Adresse dans l'eeprom du montant des recharges effectu�es.
 */
#define ADDRESS_DWCASHLESSREVALUE_PERMANENT (WORD)(ADDRESS_DWCASHLESSVEND_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWCASHVEND_PERMANENT
 * \brief Adresse dans l'eeprom du montant des ventes effectu�es en esp�ces.
 */
#define ADDRESS_DWCASHVEND_PERMANENT (WORD)(ADDRESS_DWCASHLESSREVALUE_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWOVERPAY_PERMANENT
 * \brief Adresse dans l'eeprom du montant des trop per�us.
 */
#define ADDRESS_DWOVERPAY_PERMANENT (WORD)(ADDRESS_DWCASHVEND_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWREFILLING
 * \brief Adresse dans l'eeprom du montant recharg� dans le changer.
 */
#define ADDRESS_DWREFILLING_PERMANENT (WORD)(ADDRESS_DWOVERPAY_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWVENDUSB
 * \brief Adresse dans l'eeprom du montant des ventes effectu�es avec la cl� USB.
 */
#define ADDRESS_DWVENDUSB_PERMANENT (WORD)(ADDRESS_DWREFILLING_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_END_AUDIT
 */
#define ADDRESS_END_AUDIT ADDRESS_DWVENDUSB_PERMANENT + sizeof(DWORD)

/**
 * \def ADDRESS_DEBUT_CODE
 * \brief Adresse de d�but des enregistrement des dates d'acc�s USB.
 */
#define ADDRESS_DEBUT_CODE 6184

//ADDRESSES CODES USB
/**
 * \def ADDRESS_DATE_AUDIT_USB
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s du fichier autorisation d'acc�s aux audits dans l'USB.
 */
#define ADDRESS_DATE_AUDIT_USB (WORD)(ADDRESS_DEBUT_CODE + sizeof(DWORD))

/**
 * \def ADDRESS_DATE_PARAMETRES_USB
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s du fichier autorisation d'acc�s aux param�tres dans l'USB.
 */
#define ADDRESS_DATE_PARAMETRES_USB (WORD)(ADDRESS_DATE_AUDIT_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_RAZ_USB
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s du fichier autorisation de la remise � z�ro dans l'USB.
 */
#define ADDRESS_DATE_RAZ_USB (WORD)(ADDRESS_DATE_PARAMETRES_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_REFFILLING_USB
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s du fichier autorisation des remplissages dans l'USB.
 */
#define ADDRESS_DATE_REFFILLING_USB (WORD)(ADDRESS_DATE_RAZ_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_HISTO_USB
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s du fichier autorisation des remplissages dans l'USB.
 */
#define ADDRESS_DATE_HISTO_USB (WORD)(ADDRESS_DATE_REFFILLING_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_CREDIT_USB
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s du fichier autorisation des remplissages dans l'USB.
 */
#define ADDRESS_DATE_CREDIT_USB (WORD)(ADDRESS_DATE_HISTO_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_REINIT_USB
 * \brief Adresse dans l'eeprom de la date fictive de reinitialisation
 */
#define ADDRESS_DATE_REINIT_USB (WORD)(ADDRESS_DATE_CREDIT_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_SAVE_AUDIT
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s au fichier d'autorisation de la sauvegarde des audits.
 */
#define ADDRESS_DATE_SAVE_AUDIT (WORD)(ADDRESS_DATE_REINIT_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_SAVE_HISTO
 * \brief Adresse dans l'eeprom de la derni�re date d'acc�s au fichier d'autorisation de la sauvegarde des audits.
 */
#define ADDRESS_DATE_SAVE_HISTO (WORD)(ADDRESS_DATE_SAVE_AUDIT + SIZECODE)

/*
 * \def ADDRESS_END_CODE
 * \brief Adresse dans l'eeprom de la fin de la zone des codes n�cessaires au fichier USB.
 */
#define ADDRESS_END_CODE ADDRESS_DATE_SAVE_HISTO + SIZECODE

/**
 * \def ADDRESS_LANGUE
 * \brief Adresse de d�but dans l'eeprom des textes.
 */
#define ADDRESS_LANGUE 6400

/**
 * \def ADDRESS_HISTO
 * \brief Adresse de d�but dans l'eeprom de l'historique.
 */
#define ADDRESS_HISTO 32768

/**
 * \def ADDRESS_HISTOEE_POINTER
 * \brief Adresse dans l'eeprom du pointeur de position de l'historique.
 */
#define ADDRESS_HISTOEE_POINTER (ADDRESS_HISTO - sizeof(DWORD))

/*End of macros***************************************************************/

/*Typedefs*********************************************************************/

/**
 * \brief Enum�ration contenant le type d'op�ration enregistr� dans l'historique.
 */
typedef enum
{
    UNKNOW, //0
    INITIALISATION, //1
    TEST_START, //2
    LANCEMENT, //3
    INCG, //4
    OUCG, //5
    INBV, //6
    OUTBV, //7
    PAYCASHLESS, //8
    REVALUECASHLESS, //9
    KEYPRESENT, //10
    OVERPAYOP, //11
    FILLINGOP, //12
    USBKEYINSERTED, //13
    USBPAY, //14
    USBSAVEAUDIT, //15
    USBREINITCODE, //16
    RAZAUDITOP, //17
    USBSAVEHISTO, //18
    SELECTION, //19
    REFUSED, //20
    TEST_LEFT, //21
    USB_LEFT, //22
    PULSE_END, //23
    PASSWORDENTRANCE, //24
    NONEOP = 0XFF /*!<Pas d'op�ration � cette endroit de l'eeprom.*/
} EHISTOOP;

/**
 * \brief enumeration des r�sultats possible pour les m�thodes g�n�rant un historique.
 */
typedef enum
{
    FAIL,       /*!<Indique une operation ayant �chou�e.*/
    SUCCESSFUL, /*!<Indique une op�ration r�ussie.*/
} ERESULT;

/**
 * \brief Structure contenant les param�tres de la centrale.
 * \details La seconde partie de l'union trnasforeme la structure en tableau d'octets.
 */
typedef struct __attribute__((packed))
{
    BOOL isBuzzer; /*!< Bool�en indiquant si le buzzer est activ� ou non.*/
    BYTE isEscrow; /*!< Bool�en indiquant si l'escrow des billets doit �tre utilis�.*/
    BYTE byCLAddress; /*!< Adresse MDB du syst�me cashless.*/
    COINTYPE coinType; /*!< Contient l'activation ou non des pi�ces.*/
    BILLTYPE billType; /*!< Contient l'activation ou non des billets.*/
    BYTE byKBDTO; /*!< D�lai pour utiliser une touche avant le retour � l'ecran de repos.*/
    BYTE byOverPayTO; /*!< D�lai pour conserver le trop per�u disponible.*/
    BYTE byCumulTO; /*!< D�lai pendant lequel le cumul est autoris�.*/
    long lDelayDisplay; /*!< Contient le d�lai pendant lequel sont affich�s les messages r�sultant des saisies.*/
    WORD wAmountExactChange; /*!< Contient le montant au-dessous duquel le montant exact est r�clam�.*/
    BYTE byTemoin; /*!< T�moin de r�glage d'usine. Si la valeur est � 0x55 indique que l'eeprom n'est pas vierge.*/
    PASSWORDS passWords; /*!<Passwords.*/
}
CENTRAL_PARAMETERS;

/**
 * \brief Structure contenant le d�tail d'une op�ration.
 * \details La seconde partie de l'union trnasforeme la structure en tableau d'octets.
 */
typedef union __attribute__((packed))
{

    struct __attribute__((packed))
    {
        rtccDate date; /*!< Date de l'op�ration.*/
        rtccTime time; /*!< Heure de l'op�ration.*/
        long lAmount; /*!< Montant de l'op�ration.*/
        EHISTOOP Operation; /*!< Type d'op�ration effectu�e.*/
        ERESULT result; /*!< R�sultat de l'op�ration.*/
        BYTE byMachine; /*!< Num�ro de la machine le cas �ch�ant.*/
        long lKeyNumber; /*!< Num�ro de cl� le cas �ch�ant.*/
    };
    BYTE byBufferOperation[32]; /*!<Tableau d'octets contenant les information sur l'op�ration.*/
}UOPERATION;

/**
 * \brief Union contenant les param�tres � sauvegarder d'une machine.
 * \details La seconde partie de l'union trnasforeme la structure en tableau d'octets.
 */
typedef union __attribute__((packed))
{

    struct __attribute__((packed))
    {
        BYTE byNumero; /*!< Adresse du satellite qui correspond aussi au num�ro de la machine pilot�e par ce satellite.*/
        WORD wCashPrice; /*!< Prix du service en esp�ce.*/
        WORD wCashLessPrice; /*!< Prix du service pay� avec le syst�me cashless.*/
        WORD wCashPriceHH; /*!< Prix du service en heures creuses.*/
        WORD wCashLessPriceHH; /*!< prix du service pay� avec le syst�me cashless en heure creuse.*/
        long lPulseInMS; /*!< Dur�e de l'impulsion pour activ� la machine en ms.*/
        long lOverBusy; /*!< Dur�e de la suroccupation en ms.*/
        long lTimeToDisplay; /*! Temps � afficher pour le client sans d�compte.*/
        rtccTime utBeginSelect; /*!< Heure de d�but de s�lection autoris�.*/
        rtccTime utEndSelect; /*!< Heure de  fin de s�lection autoris�.*/
        rtccTime utBeginHH; /*!< Heure de d�but de l'Happy Hour.*/
        rtccTime utEndHH; /*!< Heure de fin de l'Happy Hour.*/
        BOOL isCumulEnable; /*!< Autorise ou non le cumul du temps d'activation*/
        BOOL isDisplayedTimeRemaining; /*! Affiche le temps restant.*/
        BOOL isMachinePowered; /*!< Indique si le relais d'alimentation principale doit �tre aliment�.*/
        BOOL isBillAccepted; /*!<Indique si les billets sont accept�s pour cette machine.*/
        UBUSYLEVEL BusyLevel; /*!< Niveau de detection de l'occupation*/
    };
    BYTE sMachine_config_buffer[64]; /*!<Tableau d'octets contenant la structure.*/
}
SMACHINE_CONFIG;

/**
 * \brief Structure contenant les param�tres de  fonctionnement d'une machine.
 */
typedef struct __attribute__((packed))
{
    SMACHINE_CONFIG config; /*!< Param�tres enregistr�s. */
    TimerHandle_t timerBusyMachine; /*!< Handle du timer d'occupation de la machine.*/
    TimerHandle_t timerActivationMachine; /*!< Handle du timer d'activation du relais de la machine.*/
    long lEndActivation; /*!< Temps d'activation restant. */
}
SMODULE;

/**
 * \brief Type structure contenant les donn�es de l'audit.
 */
typedef struct __attribute__((packed))
{
    WORD wNumberChannelCGIn[MAXNUMBERCHANNELSCG]; /*!< Nombre de pi�ce introduit pour chaque canal du changer.*/
    WORD wNumberChannelCGOut[MAXNUMBERCHANNELSCG]; /*!< Nombre de pi�ce rendu pour chaque canal du changer.*/
    WORD wNumberChannelBV[MAXNUMBERCHANNELSBV]; /*!< Nombre de pi�ce introduit pour chaque canal du lecteur de billets.*/
    WORD wNumberServices[MAXMACHINES]; /*!< Nombre de consommations de chaque.*/
    DWORD dwVendCL; /*!< Montant des ventes avec une cl� cashless.*/
    DWORD dwRevalueCL; /*!< Montant recharg� dans les cl�s cashless.*/
    DWORD dwVendCash; /*!< Montant des ventes en esp�ces.*/
    DWORD dwOverPay; /*!< Montant trop-per�u.*/
    DWORD dwRefilling; /*!< Montant refilling.*/
    DWORD dwVendUSB; /*!< Montant des ventes avec une cl� USB.*/
}
SAUDITDATA;

/**
 * \brief Union permettant de g�rer la structure sAUDITDA comme un tableau d'octets
 */
typedef union
{
    SAUDITDATA data; /*!<Structure contenant les donn�es de l'audit.*/
    BYTE byAuditData[sizeof (SAUDITDATA)]; /*!< Tableau d'octets contenant les donn�es de l'audit.*/
} AUDITDATA;

/*End of typedefs**************************************************************/

/*Variables********************************************************************/
/**
 * \var modules
 * \brief Tableau contenant les param�tres de fonctionnement de toutes les machines.
 */
SMODULE modules[MAXMACHINES];

/**
 * \var centralParameters
 * \brief Param�tres de la centrale.
 */
CENTRAL_PARAMETERS centralParameters;

/**
 * \var auditData
 * \brief Structure contenant les audits.
 */
AUDITDATA auditData;

/**
 * \var auditDataPermanent
 * \brief Structure contenant les audits permanents.
 */
AUDITDATA auditDataPermanent;

/**
 * \var wCopyEnable
 * \brief Variable contenant temporairemnet l'activation des canaux des p�riph�riques
 */
WORD wCopyEnable;

/**
 * \var isFromCG
 * \brief Indique si la requ�te est faite pour le changeur ou le lecteur de billets.
 */
BOOL isFromCG;

/**@}*/

#endif	/* PARAMETRES_H */

