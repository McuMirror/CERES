
/** ****************************************************************************
 * \file            mdb_cl.h                                                 
 * \brief			Header de la gestion du cashless
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/
#ifndef MDB_CL_H
#define	MDB_CL_H

#include "MDB.h"

/**
 * \defgroup CL Gestion du cashless
 * \ingroup MDB
 * @{
 */

/*Macros***********************************************************************/

//Adresses périphériques
#define CASHLESS1 0X10 /*!< Adresse cashless 1. */
#define CASHLESS2 0X60 /*!< Adresse cashless 2. */

/**
 * \ingroup MDB_ANSWER
 * @{
 */
/**
 * \brief JUST RESET
 * \details Indique que le lecteur de moyens de paiement a été réinitialisé.
 */
#define RSP_JUST_RESET              0x00    

/**
 * \brief CONFIGURATION DATA.
 * \details Indique que le cashless répond à une demande de données de configuration de la VMC
 */
#define RSP_READER_CONFIG_DATA      0x01

/**
 * \brief DISPLAY REQUEST
 * \details Le lecteur de moyens de paiement demande un message à afficher sur l'écran de la VMC.
 */
#define RSP_DISPLAY_REQUEST         0x02

/**
 * \brief BEGIN SESSION
 * \details Permettre à un client de faire une sélection, mais ne distribue le produit avant que le paiement soit approuvé.
 */
#define RSP_BEGIN_SESSION           0x03

/**
 * \brief SESSION CANCEL REQUEST
 * \details La VMC demande au cashless d'annuler la session. Le VMC devrait amorcer une SESSION COMPLETE. Cette réponse est envoyée à la VMC chaque fois que le media de paiement est retiré ou qu'une demande s'annulation est effectuée par l'utilisateur (par exemple, si le bouton de retour rdy utilisé).
est appuyé).
 */
#define RSP_SESSION_CANCEL_REQUEST  0x04

/**
 * \brief VEND REQUEST
 * \details Le client a fait une sélection. La VMC demande l'approbation de la vente avant de distribuer le produit.
 */
#define RSP_VEND_APPROVED           0x05

/**
 * \brief VEND DENIED
 * \details La vente est refusée pour la sélection du client. Le produit n'est pas distibrué.
 */
#define RSP_VEND_DENIED             0x06

/**
 * \brief END SESSION
 * \details Cette commande est émise en réponse à une demande de SESSION COMPLETE. La réponse END SESSION  indique que le lecteur est retourné à l'état activé. Si la "END SESSION" n'est pas reçue par la VMC dans le délai maximal de non-réponse, le VMC doit émettre une commande "RESET".
du lecteur.
 */
#define RSP_END_SESSION             0x07

/**
 * \brief READER CANCEL
 * \details Cette commande est émise pour interrompre les activités de lecture du cashless qui se produisent dans l'état activé. C'est la première partie d'une séquence commande/réponse qui nécessite une réponse CANCELLED de la part du lecteur
 */
#define RSP_CANCELLED               0x08

/**
 * \brief PERIPHERAL ID
 * \details Le lecteur envoie les informations d'identification périphérique.
 */
#define RSP_PERIPHERAL_ID           0x09

/**
 * \brief MALFUNCTION/ERROR
 * \details Le lecteur cashless signale un dysfonctionnement ou une erreur.
 */
#define RSP_MALFUNCTION_ERROR       0x0A

/**
 * \brief COMMAND OUT OF SEQUENCE
 * \details Le lecteur de moyens de paiement a reçu une commande qui n'est pas exécutable dans son état actuel, ou qui viole l'une des séquences ininterrompues. La commande incriminée doit être ackée mais ne doit pas être exécutée sur le lecteur. La VMC enverra la commande RESET au lecteur dès réception de cette réponse. Il est à noter que le lecteur poursuivra tout processus de mise à jour du crédit avant la réinitialisation.
 */
#define RSP_CMD_OUT_OF_SEQUENCE     0x0B

/**
 * \brief REVALUE APPROVED
 * \details Il y a un montant dans la VMC parce que des pièces ou des billets ont été acceptés ou qu'il y a un reste après une vente. La VMC a émis un REVALUE REQUEST au cashless pour lui transférer le solde. Le cashless a accepté la demande et a ajouté le montant au solde du moyen de paiement. Le lecteur répond alors avec REVALUE APPROVED de sorte que la VMC puisse effectuer l'ajustement.
 */
#define RSP_REVALUE_APPROVED        0x0D

/**
 * \brief REVALUE DENIED
 * \details Il y a un montant dans la VMC parce que des pièces ou des billets ont été acceptés ou qu'il y a un reste après une vente. La VMC a émis un REVALUE REQUEST au cashless pour lui transférer le solde. Le cashless a refusé la demande est répond avec REVALUE DENIED, de cette manière la VMC n'effectue pas l'ajustement. C'est une situation qui se produit lorsqu'il n'ya pas de media pr'sent.
 */
#define RSP_REVALUE_DENIED          0x0E

/**
 * \brief REVALUE LIMIT REQUEST
 * \note Pour une réavulation faire suivre BEGINS SESSION par cette commande.
 * \details Permet de connaître la limite de reévaluation.
 */
#define RSP_REVALUE_LIMIT_AMOUNT    0x0F

/**
 * \brief USER FILE DATA
 * \details Commande obsolète
 */
#define RSP_USER_FILE_DATA          0x10

/**
 * \brief TIME DATE REQUEST
 * \details Dans certaines circonstances, il sera nécessaire de synchroniser l'horloge du cashless avecl'horloge le la VMC. Le cashlessle lecteur répondra à l'aide de la réponse TIME DATE REQUEST à une commande POLL de la VMC. 
 */
#define RSP_TIME_DATE_REQUEST       0x11

/**
 * \brief DATA ENTRY REQUEST
 * \details
 */
#define RSP_DATA_ENTRY_REQUEST      0x12

/**
 * \brief DATA ENTRY CANCEL
 * \details
 */
#define RSP_DATA_ENTRY_CANCEL       0x13

/**
 * \brief FTL REQ TO RCV
 * \details
 */
#define RSP_FTL_REQ_TO_RCV          0x1B

/**
 * \brief FTL RETRY / DENY
 * \details
 */
#define RSP_FTL_RETRY_DENY          0x1C

/**
 * \brief FTL SEND BLOCK
 * \details
 */
#define RSP_FTL_SEND_BLOCK          0x1D

/**
 * \brief FTL OK TO SEND
 * \details
 */
#define RSP_FTL_OK_TO_SEND          0x1E

/**
 * \brief FTL REQ TO SEND
 * \details
 */
#define RSP_FTL_REQ_TO_SEND         0x1F

/**
 * \brief DIAGNOSTICS RESPONSE
 * \details
 */
#define RSP_DIAGNOSTIC_RESPONSE     0xFF

/**@}*/

/*End of macros****************************************************************/

/*Typedef**********************************************************************/

/**
 * \brief Structure contenant le prix maximum et le prix minimum des services.
 */
typedef struct __attribute__((packed))
{
    WORD wMax; /*!< Prix du service le plus élevé.*/
    WORD wMin; /*!< Prix du service le moins élevé.*/
}
VMCMAXMIN;

/**
 * \brief Structure contenant la configuration du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    MDBGenericDeviceConfig deviceConfig; /*!< Information générique sur la configuration du lecteur cashless.*/
    BYTE byMaxTimeResponse; /*!< Temps maximum accordé au lecteur pour répondre.*/
    BYTE byMiscellaneous; /*!< Options du lecteur cashless.*/
}
READERSETUP;

/**
 * \brief Structure contenant les identifiants du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    BYTE byManufacturer[3]; /*!< Code NAMA du fabricant du lecteur cashless.*/
    BYTE bySN[12]; /*!< Numéro de série en code ASCII du lecteur cashless*/
    BYTE byModel[12]; /*!< Model en code ASCII.*/
    BYTE bySWVersion[2]; /*!< Revision software.*/
}
PERIPHERALID;
/*End of typedegs**************************************************************/

/*Varialbes********************************************************************/

/**
 * \var lAmountCL
 * \brief Montant disponible dans le media
 */
long lAmountCL;

/**
 * \var isCashLessReseted
 * \brief Indique si les opérations de reset ont été effectuées
 */
BOOL isCashLessReseted;

/**
 * \var isCLPolled
 * \brief Indique si le cashless a été pollé.
 */
BOOL isCLPolled;

/**
 * \var dwMediaID
 * \brief Numéro du média présenté.
 */
DWORD dwMediaID;

/**
 * \var wmcMaxMinPrices
 * \brief Prix maximum et minimum des services.
 */
VMCMAXMIN wmcMaxMinPrices;

/**
 * \var readerConfig
 * \brief Configuration du lecteur.
 */
READERSETUP readerConfig;

/**
 * \var peripheralID
 * \brief Identifiants du lecteur.
 */
PERIPHERALID peripheralID;

/*End of variables*************************************************************/

//*Prototypes******************************************************************/

/**
 * \fn isMDBSetupMaxMinPrice
 * \brief Focntion appellé pour paramétrer les prix maximum et minimum
 * \param[in] byDeviceAddress Adresse du périphérique.
 * \param[in] vmcMaxMinPrice Pointeur sur la structure qui contient les valeurs.
 * \return TRUE Si le périphérique à acquiter la reception de la commande.
 */
BOOL isMDBSetupMaxMinPrice(const BYTE byDeviceAddress, const VMCMAXMIN *vmcMaxMinPrice);

/**
 * \fn isMDBRevalueRequest
 * \brief Demande de réevaluation d'une clé.
 * \param[in] byDeviceAddress Adresse du périphérique.
 * \param[int] wAmount Montant de la réévaluation.
 * \return TRUE si le montant à été additionné dans la clé.
 */
BOOL isMDBRevalueRequest(const BYTE byDeviceAddress, const long *lAmount);

/**
 * \fn isMDBCLEnable
 * \brief Active le cashless
 * \param[in] byDeviceAddress Adresse du périphérique.
 */
BOOL isMDBCLEnable(const BYTE byDeviceAddress);

/**
 * \fn isMDBSessionComplete
 * \brief Fin de la session.
 * \param[in] byDeviceAddress Adresse du périphérique.
 */
BOOL isMDBSessionComplete(const BYTE byDeviceAddress);

/**
 * \fn isMDBVendRequest
 * \brief Envoi une demande de débit.
 * \param[in] byDeviceAddress Adresse du périphérique.
 * \param[int] wAmount Montant de la vente.
 * \return TRUE si la fonction s'est effectuée correctement.
 */
BOOL isMDBVendRequest(const BYTE byDeviceAddress, const long *lAmount);

/**
 * \fn isMDBLimitRevalueRequest
 * \brief Demande le montant maximum possible dans la clé.
 * \param[in] byDeviceAddress Adresse du périphérique.
 */
BOOL isMDBLimitRevalueRequest(const BYTE byDeviceAddress);

/**
 * \fn isMDBSetupCLConfig
 * \brief Fonction appelée pour paramétrer et lire le paramétrage du périphérique.
 * \param[in] byDeviceAddress Adresse du périphérique.
 * \param[in] ptrParameters Paramètres transmis au périphérique.
 * \param[out] byResponse Pointeur sur le buffer qui contiendra la réponse.
 * \return TRUE Si la réponse est correcte.
 */
BOOL isMDBSetupCLConfig(const BYTE byDeviceAddress, VMCConfig *ptrParameters);

/**
 * \fn isMDBVendSuccess
 * \brief Informe le lecteur que la vente s'est effectuée correctement.
 * \param[in] byDeviceAddress Adresse du lecteur cashless.
 * \return True Si l'opération s'est effectuée correctement.
 */
BOOL isMDBVendSuccess(const BYTE byDeviceAddress);
/*End of prototypes************************************************************/
/**@}*/
#endif	/* MDB_CL_H */

