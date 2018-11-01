
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

//Adresses p�riph�riques
#define CASHLESS1 0X10 /*!< Adresse cashless 1. */
#define CASHLESS2 0X60 /*!< Adresse cashless 2. */

/**
 * \ingroup MDB_ANSWER
 * @{
 */
/**
 * \brief JUST RESET
 * \details Indique que le lecteur de moyens de paiement a �t� r�initialis�.
 */
#define RSP_JUST_RESET              0x00    

/**
 * \brief CONFIGURATION DATA.
 * \details Indique que le cashless r�pond � une demande de donn�es de configuration de la VMC
 */
#define RSP_READER_CONFIG_DATA      0x01

/**
 * \brief DISPLAY REQUEST
 * \details Le lecteur de moyens de paiement demande un message � afficher sur l'�cran de la VMC.
 */
#define RSP_DISPLAY_REQUEST         0x02

/**
 * \brief BEGIN SESSION
 * \details Permettre � un client de faire une s�lection, mais ne distribue le produit avant que le paiement soit approuv�.
 */
#define RSP_BEGIN_SESSION           0x03

/**
 * \brief SESSION CANCEL REQUEST
 * \details La VMC demande au cashless d'annuler la session. Le VMC devrait amorcer une SESSION COMPLETE. Cette r�ponse est envoy�e � la VMC chaque fois que le media de paiement est retir� ou qu'une demande s'annulation est effectu�e par l'utilisateur (par exemple, si le bouton de retour rdy utilis�).
est appuy�).
 */
#define RSP_SESSION_CANCEL_REQUEST  0x04

/**
 * \brief VEND REQUEST
 * \details Le client a fait une s�lection. La VMC demande l'approbation de la vente avant de distribuer le produit.
 */
#define RSP_VEND_APPROVED           0x05

/**
 * \brief VEND DENIED
 * \details La vente est refus�e pour la s�lection du client. Le produit n'est pas distibru�.
 */
#define RSP_VEND_DENIED             0x06

/**
 * \brief END SESSION
 * \details Cette commande est �mise en r�ponse � une demande de SESSION COMPLETE. La r�ponse END SESSION  indique que le lecteur est retourn� � l'�tat activ�. Si la "END SESSION" n'est pas re�ue par la VMC dans le d�lai maximal de non-r�ponse, le VMC doit �mettre une commande "RESET".
du lecteur.
 */
#define RSP_END_SESSION             0x07

/**
 * \brief READER CANCEL
 * \details Cette commande est �mise pour interrompre les activit�s de lecture du cashless qui se produisent dans l'�tat activ�. C'est la premi�re partie d'une s�quence commande/r�ponse qui n�cessite une r�ponse CANCELLED de la part du lecteur
 */
#define RSP_CANCELLED               0x08

/**
 * \brief PERIPHERAL ID
 * \details Le lecteur envoie les informations d'identification p�riph�rique.
 */
#define RSP_PERIPHERAL_ID           0x09

/**
 * \brief MALFUNCTION/ERROR
 * \details Le lecteur cashless signale un dysfonctionnement ou une erreur.
 */
#define RSP_MALFUNCTION_ERROR       0x0A

/**
 * \brief COMMAND OUT OF SEQUENCE
 * \details Le lecteur de moyens de paiement a re�u une commande qui n'est pas ex�cutable dans son �tat actuel, ou qui viole l'une des s�quences ininterrompues. La commande incrimin�e doit �tre ack�e mais ne doit pas �tre ex�cut�e sur le lecteur. La VMC enverra la commande RESET au lecteur d�s r�ception de cette r�ponse. Il est � noter que le lecteur poursuivra tout processus de mise � jour du cr�dit avant la r�initialisation.
 */
#define RSP_CMD_OUT_OF_SEQUENCE     0x0B

/**
 * \brief REVALUE APPROVED
 * \details Il y a un montant dans la VMC parce que des pi�ces ou des billets ont �t� accept�s ou qu'il y a un reste apr�s une vente. La VMC a �mis un REVALUE REQUEST au cashless pour lui transf�rer le solde. Le cashless a accept� la demande et a ajout� le montant au solde du moyen de paiement. Le lecteur r�pond alors avec REVALUE APPROVED de sorte que la VMC puisse effectuer l'ajustement.
 */
#define RSP_REVALUE_APPROVED        0x0D

/**
 * \brief REVALUE DENIED
 * \details Il y a un montant dans la VMC parce que des pi�ces ou des billets ont �t� accept�s ou qu'il y a un reste apr�s une vente. La VMC a �mis un REVALUE REQUEST au cashless pour lui transf�rer le solde. Le cashless a refus� la demande est r�pond avec REVALUE DENIED, de cette mani�re la VMC n'effectue pas l'ajustement. C'est une situation qui se produit lorsqu'il n'ya pas de media pr'sent.
 */
#define RSP_REVALUE_DENIED          0x0E

/**
 * \brief REVALUE LIMIT REQUEST
 * \note Pour une r�avulation faire suivre BEGINS SESSION par cette commande.
 * \details Permet de conna�tre la limite de re�valuation.
 */
#define RSP_REVALUE_LIMIT_AMOUNT    0x0F

/**
 * \brief USER FILE DATA
 * \details Commande obsol�te
 */
#define RSP_USER_FILE_DATA          0x10

/**
 * \brief TIME DATE REQUEST
 * \details Dans certaines circonstances, il sera n�cessaire de synchroniser l'horloge du cashless avecl'horloge le la VMC. Le cashlessle lecteur r�pondra � l'aide de la r�ponse TIME DATE REQUEST � une commande POLL de la VMC. 
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
    WORD wMax; /*!< Prix du service le plus �lev�.*/
    WORD wMin; /*!< Prix du service le moins �lev�.*/
}
VMCMAXMIN;

/**
 * \brief Structure contenant la configuration du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    MDBGenericDeviceConfig deviceConfig; /*!< Information g�n�rique sur la configuration du lecteur cashless.*/
    BYTE byMaxTimeResponse; /*!< Temps maximum accord� au lecteur pour r�pondre.*/
    BYTE byMiscellaneous; /*!< Options du lecteur cashless.*/
}
READERSETUP;

/**
 * \brief Structure contenant les identifiants du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    BYTE byManufacturer[3]; /*!< Code NAMA du fabricant du lecteur cashless.*/
    BYTE bySN[12]; /*!< Num�ro de s�rie en code ASCII du lecteur cashless*/
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
 * \brief Indique si les op�rations de reset ont �t� effectu�es
 */
BOOL isCashLessReseted;

/**
 * \var isCLPolled
 * \brief Indique si le cashless a �t� poll�.
 */
BOOL isCLPolled;

/**
 * \var dwMediaID
 * \brief Num�ro du m�dia pr�sent�.
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
 * \brief Focntion appell� pour param�trer les prix maximum et minimum
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 * \param[in] vmcMaxMinPrice Pointeur sur la structure qui contient les valeurs.
 * \return TRUE Si le p�riph�rique � acquiter la reception de la commande.
 */
BOOL isMDBSetupMaxMinPrice(const BYTE byDeviceAddress, const VMCMAXMIN *vmcMaxMinPrice);

/**
 * \fn isMDBRevalueRequest
 * \brief Demande de r�evaluation d'une cl�.
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 * \param[int] wAmount Montant de la r��valuation.
 * \return TRUE si le montant � �t� additionn� dans la cl�.
 */
BOOL isMDBRevalueRequest(const BYTE byDeviceAddress, const long *lAmount);

/**
 * \fn isMDBCLEnable
 * \brief Active le cashless
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 */
BOOL isMDBCLEnable(const BYTE byDeviceAddress);

/**
 * \fn isMDBSessionComplete
 * \brief Fin de la session.
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 */
BOOL isMDBSessionComplete(const BYTE byDeviceAddress);

/**
 * \fn isMDBVendRequest
 * \brief Envoi une demande de d�bit.
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 * \param[int] wAmount Montant de la vente.
 * \return TRUE si la fonction s'est effectu�e correctement.
 */
BOOL isMDBVendRequest(const BYTE byDeviceAddress, const long *lAmount);

/**
 * \fn isMDBLimitRevalueRequest
 * \brief Demande le montant maximum possible dans la cl�.
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 */
BOOL isMDBLimitRevalueRequest(const BYTE byDeviceAddress);

/**
 * \fn isMDBSetupCLConfig
 * \brief Fonction appel�e pour param�trer et lire le param�trage du p�riph�rique.
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 * \param[in] ptrParameters Param�tres transmis au p�riph�rique.
 * \param[out] byResponse Pointeur sur le buffer qui contiendra la r�ponse.
 * \return TRUE Si la r�ponse est correcte.
 */
BOOL isMDBSetupCLConfig(const BYTE byDeviceAddress, VMCConfig *ptrParameters);

/**
 * \fn isMDBVendSuccess
 * \brief Informe le lecteur que la vente s'est effectu�e correctement.
 * \param[in] byDeviceAddress Adresse du lecteur cashless.
 * \return True Si l'op�ration s'est effectu�e correctement.
 */
BOOL isMDBVendSuccess(const BYTE byDeviceAddress);
/*End of prototypes************************************************************/
/**@}*/
#endif	/* MDB_CL_H */

