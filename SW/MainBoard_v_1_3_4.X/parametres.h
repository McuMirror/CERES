
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
 * \defgroup PARAMETERS Gestion des paramètres.
 * @{
 */
/*Macros***********************************************************************/

/**
 * \brief Nombre maximum de machine.
 */
#define MAXMACHINES 64

/**
 * \def KBDTOBYDEFAUT
 * \brief Temps maximum sans utiliser le clavier en seconde avant de retour à l'écran de initial.
 */
#define KBDTOBYDEFAUT 30

/**
 * \def OVERPAYTODEFAUT
 * \brief Délai par défaut pendant lequel le trop perçu sera disponible.
 */
#define OVERPAYTODEFAUT 0

/**
 * \def DEFAULTTOCUMUL
 * \brief Délai par défaut pendant lequel le cumul est autorisé le cas échéant.
 */
#define DEFAULTTOCUMUL 60

/**
 * \def DELAY_FLIP
 * \brief Délai entre l'inversion de la ligne basse et la ligne haute de l'afficheur.
 */
#define DELAY_FLIP (2 * SECONDE)

/**
 * \def DELAYCHECKCHANGE
 * \brief Délai entre 2 vérification pour effectuer un rendu
 */
#define DELAYCHECKCHANGE 500

/**
 * \def DELAYDISPLAYDEFAULT
 * \brief Temps d'affichage des saisies par défaut en ms
 */
#define DELAYDISPLAYDEFAULT 1000

/**
 * \def DEFAUTAMOUNTEXACTCHANGE
 * \brief Montant par défaut déclenchant l'affichage du montant par défaut.x
 */
#define DEFAUTAMOUNTEXACTCHANGE 2000

/**
 * \def TIME_TO_START
 * \brief Delai de démarrage
 */
#define TIME_TO_START (5 * SECONDE)

/**
 * \def ADDRESS_CENTRAL_PARAMETERS
 * \brief Adresse de départ du stockage des paramètres de la centrale dans l'eeprom.
 */
#define ADDRESS_CENTRAL_PARAMETERS (WORD)0

/**
 * \def ADDRESS_MACHINES_PARAMETERS
 * \brief Adresse de début dans l'eeprom des paramètres des machines.
 */
#define ADDRESS_MACHINES_PARAMETERS (WORD)1024

/**
 * \def ADDRESS_DEBUT_AUDIT
 * \brief Adresse de début dans l'eeprom des audits.
 */
#define ADDRESS_DEBUT_AUDIT (WORD)(ADDRESS_MACHINES_PARAMETERS + (64 * sizeof(SMACHINE_CONFIG)))

/**
 * \def ADDRESS_WNUMBERCHANNELGCIN
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pièce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCIN (WORD)ADDRESS_DEBUT_AUDIT

/**
 * \def ADDRESS_WNUMBERCHANNELGCOUT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pièce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCOUT (WORD)(ADDRESS_WNUMBERCHANNELGCIN + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERCHANNELBV
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de billet introduit.
 */
#define ADDRESS_WNUMBERCHANNELBV (WORD)(ADDRESS_WNUMBERCHANNELGCOUT + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERSERVICES
 * \brief Adresse dans l'eeprom des audit concernant le nombre de fois que chaque machine est selectionée.
 */
#define ADDRESS_WNUMBERSERVICES (WORD)(ADDRESS_WNUMBERCHANNELBV + (sizeof(WORD) * MAXNUMBERCHANNELSBV))

/**
 * \def ADDRESS_DWCASHLESSVEND
 * \brief Adresse dans l'eeprom du montant des effectuées avec le système cashless.
 */
#define ADDRESS_DWCASHLESSVEND (WORD)(ADDRESS_WNUMBERSERVICES + (sizeof(WORD) * MAXMACHINES))

/**
 * \def ADDRESS_DWCASHLESSREVALUE
 * \brief Adresse dans l'eeprom du montant des recharges effectuées.
 */
#define ADDRESS_DWCASHLESSREVALUE (WORD)(ADDRESS_DWCASHLESSVEND + sizeof(DWORD))

/**
 * \def ADDRESS_DWCASHVEND
 * \brief Adresse dans l'eeprom du montant des ventes effectuées en espèces.
 */
#define ADDRESS_DWCASHVEND (WORD)(ADDRESS_DWCASHLESSREVALUE + sizeof(DWORD))

/**
 * \def ADDRESS_DWOVERPAY
 * \brief Adresse dans l'eeprom du montant des trop perçus.
 */
#define ADDRESS_DWOVERPAY (WORD)(ADDRESS_DWCASHVEND + sizeof(DWORD))

/**
 * \def ADDRESS_DWREFILLING
 * \brief Adresse dans l'eeprom du montant rechargé dans le changer.
 */
#define ADDRESS_DWREFILLING (WORD)(ADDRESS_DWOVERPAY + sizeof(DWORD))

/**
 * \def ADDRESS_DWVENDUSB
 * \brief Adresse dans l'eeprom du montant des ventes effectuées avec la clé USB.
 */
#define ADDRESS_DWVENDUSB (WORD)(ADDRESS_DWREFILLING + sizeof(DWORD))

/**
 * \def ADDRESS_DEBUT_AUDIT_PERMANENT
 * \brief Adresse de début dans l'eeprom des audits.
 */
#define ADDRESS_DEBUT_AUDIT_PERMANENT (WORD)(ADDRESS_DEBUT_AUDIT + sizeof(AUDITDATA))

/**
 * \def ADDRESS_WNUMBERCHANNELGCIN_PERMANENT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pièce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCIN_PERMANENT (WORD)ADDRESS_DEBUT_AUDIT_PERMANENT

/**
 * \def ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de pièce introduite.
 */
#define ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT (WORD)(ADDRESS_WNUMBERCHANNELGCIN_PERMANENT + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERCHANNELBV_PERMANENT
 * \brief Adresse dans l'eeprom des audits concernant le nombre de chaque type de billet introduit.
 */
#define ADDRESS_WNUMBERCHANNELBV_PERMANENT (WORD)(ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT + (sizeof(WORD) * MAXNUMBERCHANNELSCG))

/**
 * \def ADDRESS_WNUMBERSERVICES_PERMANENT
 * \brief Adresse dans l'eeprom des audit concernant le nombre de fois que chaque machine est selectionée.
 */
#define ADDRESS_WNUMBERSERVICES_PERMANENT (WORD)(ADDRESS_WNUMBERCHANNELBV_PERMANENT + (sizeof(WORD) * MAXNUMBERCHANNELSBV))

/**
 * \def ADDRESS_DWCASHLESSVEND_PERMANENT
 * \brief Adresse dans l'eeprom du montant des effectuées avec le système cashless.
 */
#define ADDRESS_DWCASHLESSVEND_PERMANENT (WORD)(ADDRESS_WNUMBERSERVICES_PERMANENT + (sizeof(WORD) * MAXMACHINES))

/**
 * \def ADDRESS_DWCASHLESSREVALUE_PERMANENT
 * \brief Adresse dans l'eeprom du montant des recharges effectuées.
 */
#define ADDRESS_DWCASHLESSREVALUE_PERMANENT (WORD)(ADDRESS_DWCASHLESSVEND_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWCASHVEND_PERMANENT
 * \brief Adresse dans l'eeprom du montant des ventes effectuées en espèces.
 */
#define ADDRESS_DWCASHVEND_PERMANENT (WORD)(ADDRESS_DWCASHLESSREVALUE_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWOVERPAY_PERMANENT
 * \brief Adresse dans l'eeprom du montant des trop perçus.
 */
#define ADDRESS_DWOVERPAY_PERMANENT (WORD)(ADDRESS_DWCASHVEND_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWREFILLING
 * \brief Adresse dans l'eeprom du montant rechargé dans le changer.
 */
#define ADDRESS_DWREFILLING_PERMANENT (WORD)(ADDRESS_DWOVERPAY_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_DWVENDUSB
 * \brief Adresse dans l'eeprom du montant des ventes effectuées avec la clé USB.
 */
#define ADDRESS_DWVENDUSB_PERMANENT (WORD)(ADDRESS_DWREFILLING_PERMANENT + sizeof(DWORD))

/**
 * \def ADDRESS_END_AUDIT
 */
#define ADDRESS_END_AUDIT ADDRESS_DWVENDUSB_PERMANENT + sizeof(DWORD)

/**
 * \def ADDRESS_DEBUT_CODE
 * \brief Adresse de début des enregistrement des dates d'accés USB.
 */
#define ADDRESS_DEBUT_CODE 6184

//ADDRESSES CODES USB
/**
 * \def ADDRESS_DATE_AUDIT_USB
 * \brief Adresse dans l'eeprom de la dernière date d'accès du fichier autorisation d'accès aux audits dans l'USB.
 */
#define ADDRESS_DATE_AUDIT_USB (WORD)(ADDRESS_DEBUT_CODE + sizeof(DWORD))

/**
 * \def ADDRESS_DATE_PARAMETRES_USB
 * \brief Adresse dans l'eeprom de la dernière date d'accès du fichier autorisation d'accès aux paramètres dans l'USB.
 */
#define ADDRESS_DATE_PARAMETRES_USB (WORD)(ADDRESS_DATE_AUDIT_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_RAZ_USB
 * \brief Adresse dans l'eeprom de la dernière date d'accès du fichier autorisation de la remise à zéro dans l'USB.
 */
#define ADDRESS_DATE_RAZ_USB (WORD)(ADDRESS_DATE_PARAMETRES_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_REFFILLING_USB
 * \brief Adresse dans l'eeprom de la dernière date d'accès du fichier autorisation des remplissages dans l'USB.
 */
#define ADDRESS_DATE_REFFILLING_USB (WORD)(ADDRESS_DATE_RAZ_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_HISTO_USB
 * \brief Adresse dans l'eeprom de la dernière date d'accès du fichier autorisation des remplissages dans l'USB.
 */
#define ADDRESS_DATE_HISTO_USB (WORD)(ADDRESS_DATE_REFFILLING_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_CREDIT_USB
 * \brief Adresse dans l'eeprom de la dernière date d'accès du fichier autorisation des remplissages dans l'USB.
 */
#define ADDRESS_DATE_CREDIT_USB (WORD)(ADDRESS_DATE_HISTO_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_REINIT_USB
 * \brief Adresse dans l'eeprom de la date fictive de reinitialisation
 */
#define ADDRESS_DATE_REINIT_USB (WORD)(ADDRESS_DATE_CREDIT_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_SAVE_AUDIT
 * \brief Adresse dans l'eeprom de la dernière date d'accès au fichier d'autorisation de la sauvegarde des audits.
 */
#define ADDRESS_DATE_SAVE_AUDIT (WORD)(ADDRESS_DATE_REINIT_USB + SIZECODE)

/**
 * \def ADDRESS_DATE_SAVE_HISTO
 * \brief Adresse dans l'eeprom de la dernière date d'accès au fichier d'autorisation de la sauvegarde des audits.
 */
#define ADDRESS_DATE_SAVE_HISTO (WORD)(ADDRESS_DATE_SAVE_AUDIT + SIZECODE)

/*
 * \def ADDRESS_END_CODE
 * \brief Adresse dans l'eeprom de la fin de la zone des codes nécessaires au fichier USB.
 */
#define ADDRESS_END_CODE ADDRESS_DATE_SAVE_HISTO + SIZECODE

/**
 * \def ADDRESS_LANGUE
 * \brief Adresse de début dans l'eeprom des textes.
 */
#define ADDRESS_LANGUE 6400

/**
 * \def ADDRESS_HISTO
 * \brief Adresse de début dans l'eeprom de l'historique.
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
 * \brief Enumération contenant le type d'opération enregistré dans l'historique.
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
    NONEOP = 0XFF /*!<Pas d'opération à cette endroit de l'eeprom.*/
} EHISTOOP;

/**
 * \brief enumeration des résultats possible pour les méthodes générant un historique.
 */
typedef enum
{
    FAIL,       /*!<Indique une operation ayant échouée.*/
    SUCCESSFUL, /*!<Indique une opération réussie.*/
} ERESULT;

/**
 * \brief Structure contenant les paramètres de la centrale.
 * \details La seconde partie de l'union trnasforeme la structure en tableau d'octets.
 */
typedef struct __attribute__((packed))
{
    BOOL isBuzzer; /*!< Booléen indiquant si le buzzer est activé ou non.*/
    BYTE isEscrow; /*!< Booléen indiquant si l'escrow des billets doit être utilisé.*/
    BYTE byCLAddress; /*!< Adresse MDB du système cashless.*/
    COINTYPE coinType; /*!< Contient l'activation ou non des pièces.*/
    BILLTYPE billType; /*!< Contient l'activation ou non des billets.*/
    BYTE byKBDTO; /*!< Délai pour utiliser une touche avant le retour à l'ecran de repos.*/
    BYTE byOverPayTO; /*!< Délai pour conserver le trop perçu disponible.*/
    BYTE byCumulTO; /*!< Délai pendant lequel le cumul est autorisé.*/
    long lDelayDisplay; /*!< Contient le délai pendant lequel sont affichés les messages résultant des saisies.*/
    WORD wAmountExactChange; /*!< Contient le montant au-dessous duquel le montant exact est réclamé.*/
    BYTE byTemoin; /*!< Témoin de réglage d'usine. Si la valeur est à 0x55 indique que l'eeprom n'est pas vierge.*/
    PASSWORDS passWords; /*!<Passwords.*/
}
CENTRAL_PARAMETERS;

/**
 * \brief Structure contenant le détail d'une opération.
 * \details La seconde partie de l'union trnasforeme la structure en tableau d'octets.
 */
typedef union __attribute__((packed))
{

    struct __attribute__((packed))
    {
        rtccDate date; /*!< Date de l'opération.*/
        rtccTime time; /*!< Heure de l'opération.*/
        long lAmount; /*!< Montant de l'opération.*/
        EHISTOOP Operation; /*!< Type d'opération effectuée.*/
        ERESULT result; /*!< Résultat de l'opération.*/
        BYTE byMachine; /*!< Numéro de la machine le cas échéant.*/
        long lKeyNumber; /*!< Numéro de clé le cas échéant.*/
    };
    BYTE byBufferOperation[32]; /*!<Tableau d'octets contenant les information sur l'opération.*/
}UOPERATION;

/**
 * \brief Union contenant les paramètres à sauvegarder d'une machine.
 * \details La seconde partie de l'union trnasforeme la structure en tableau d'octets.
 */
typedef union __attribute__((packed))
{

    struct __attribute__((packed))
    {
        BYTE byNumero; /*!< Adresse du satellite qui correspond aussi au numéro de la machine pilotée par ce satellite.*/
        WORD wCashPrice; /*!< Prix du service en espèce.*/
        WORD wCashLessPrice; /*!< Prix du service payé avec le système cashless.*/
        WORD wCashPriceHH; /*!< Prix du service en heures creuses.*/
        WORD wCashLessPriceHH; /*!< prix du service payé avec le système cashless en heure creuse.*/
        long lPulseInMS; /*!< Durée de l'impulsion pour activé la machine en ms.*/
        long lOverBusy; /*!< Durée de la suroccupation en ms.*/
        long lTimeToDisplay; /*! Temps à afficher pour le client sans décompte.*/
        rtccTime utBeginSelect; /*!< Heure de début de sélection autorisé.*/
        rtccTime utEndSelect; /*!< Heure de  fin de sélection autorisé.*/
        rtccTime utBeginHH; /*!< Heure de début de l'Happy Hour.*/
        rtccTime utEndHH; /*!< Heure de fin de l'Happy Hour.*/
        BOOL isCumulEnable; /*!< Autorise ou non le cumul du temps d'activation*/
        BOOL isDisplayedTimeRemaining; /*! Affiche le temps restant.*/
        BOOL isMachinePowered; /*!< Indique si le relais d'alimentation principale doit être alimenté.*/
        BOOL isBillAccepted; /*!<Indique si les billets sont acceptés pour cette machine.*/
        UBUSYLEVEL BusyLevel; /*!< Niveau de detection de l'occupation*/
    };
    BYTE sMachine_config_buffer[64]; /*!<Tableau d'octets contenant la structure.*/
}
SMACHINE_CONFIG;

/**
 * \brief Structure contenant les paramètres de  fonctionnement d'une machine.
 */
typedef struct __attribute__((packed))
{
    SMACHINE_CONFIG config; /*!< Paramètres enregistrés. */
    TimerHandle_t timerBusyMachine; /*!< Handle du timer d'occupation de la machine.*/
    TimerHandle_t timerActivationMachine; /*!< Handle du timer d'activation du relais de la machine.*/
    long lEndActivation; /*!< Temps d'activation restant. */
}
SMODULE;

/**
 * \brief Type structure contenant les données de l'audit.
 */
typedef struct __attribute__((packed))
{
    WORD wNumberChannelCGIn[MAXNUMBERCHANNELSCG]; /*!< Nombre de pièce introduit pour chaque canal du changer.*/
    WORD wNumberChannelCGOut[MAXNUMBERCHANNELSCG]; /*!< Nombre de pièce rendu pour chaque canal du changer.*/
    WORD wNumberChannelBV[MAXNUMBERCHANNELSBV]; /*!< Nombre de pièce introduit pour chaque canal du lecteur de billets.*/
    WORD wNumberServices[MAXMACHINES]; /*!< Nombre de consommations de chaque.*/
    DWORD dwVendCL; /*!< Montant des ventes avec une clé cashless.*/
    DWORD dwRevalueCL; /*!< Montant rechargé dans les clés cashless.*/
    DWORD dwVendCash; /*!< Montant des ventes en espèces.*/
    DWORD dwOverPay; /*!< Montant trop-perçu.*/
    DWORD dwRefilling; /*!< Montant refilling.*/
    DWORD dwVendUSB; /*!< Montant des ventes avec une clé USB.*/
}
SAUDITDATA;

/**
 * \brief Union permettant de gérer la structure sAUDITDA comme un tableau d'octets
 */
typedef union
{
    SAUDITDATA data; /*!<Structure contenant les données de l'audit.*/
    BYTE byAuditData[sizeof (SAUDITDATA)]; /*!< Tableau d'octets contenant les données de l'audit.*/
} AUDITDATA;

/*End of typedefs**************************************************************/

/*Variables********************************************************************/
/**
 * \var modules
 * \brief Tableau contenant les paramètres de fonctionnement de toutes les machines.
 */
SMODULE modules[MAXMACHINES];

/**
 * \var centralParameters
 * \brief Paramètres de la centrale.
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
 * \brief Variable contenant temporairemnet l'activation des canaux des périphériques
 */
WORD wCopyEnable;

/**
 * \var isFromCG
 * \brief Indique si la requête est faite pour le changeur ou le lecteur de billets.
 */
BOOL isFromCG;

/**@}*/

#endif	/* PARAMETRES_H */

