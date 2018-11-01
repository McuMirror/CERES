
/** ****************************************************************************
 * \file            mdb_cg.h                                                 
 * \brief			Header de la gestion du changeur
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef MDB_CG_H
#define	MDB_CG_H

#include "MDB.h"

/**
 * \defgroup CG Gestion du rendeur
 * \ingroup MDB
 * @{
 */

/*Macros**********************************************************************/
/**
 * \def CGADDRESS
 * \brief Adresse du rendeur.
 */
#define CGADDRESS 0X08

//Status rendeur
/**
 * \addtogroup MDB_ANSWER 
 * @{
 */
/**
 * \brief ESCROW REQUEST
 * \details Le levier de remboursement � �t� activ�.
 */
#define ESCROW_REQUEST       0b00000001

/**
 \brief CHANGER PAYOUT BUSY
 \details Le changeur est occup� � rembourser.
 */
#define CHANGERPAYOUTBUSY    0b00000010

/**
 * \brief NO CREDIT
 * \details Une pi�ce a �t� valid�e mais ne s'est pas positionn� quand le cr�dit a �t� donn�.
 */
#define CHANGERNOCREDIT      0b00000011

/**
 * \brief DEFECTIVE TUBE SENSOR
 * \details Le changer a d�tect� un comportement anormale de l'un des tubes
 */
#define CHANGETUBESENSORHS   0b00000100

/**
 * \brief DOUBLE ARRIVAL
 * \details 2 pi�ces sont arriv�es trop proches l'une de l'autre
 */
#define CHANGERDOUBLECOINS   0b00000101

/**
 * \brief ACCEPTOR UNPLUGGED
 * \details Le changeur a d�tect� que le validteur a �t� deconnect�.
 */
#define CHANGERUNPLUGGED     0b00000110

/**
 * \brief TUBE JAM
 * \details Un tube est coinc�.
 */
#define CHANGERTUBEJAM       0b00000111

/**
 * \brief ROM CHECKSUM ERROR
 * \details Le checksum du software du changeur est erron�.
 */
#define CHANGERROMERROR      0b00001000

/**
 * \brief COIN ROUTING ERROR
 * \details Une pi�ce a �t� valid�e, mais n'a pas suivi le routage pr�vu.
 */
#define CHANGERROUTEERROR    0b00001001

/**
 * \brief CHANGER BUSY
 * \details Le changer est occup� est ne peut donner une r�ponse exacte.
 */
#define CHANGERBUSY          0b00001010

/**
 * \brief CHANGER WAS RESET
 * \details Le changer a detect� un reset et est retourn� en position d'attente d'initialisation
 */
#define JUST_RESET_CG        0b00001011

/**
 * \brief COIN JAM
 * \details Une pi�ce est coinc�e dans la zone d'acceptation.
 */
#define COINJAM              0b00001100

/**
 * \brief POSSIBLE CREDITED COIN REMOVAL
 * \details Il y a eu une tentative de r�cup�ration d'une pi�ce cr�dit�e.
 */
#define COINREMOVAL          0b00001101

/**
 * \brief Nombre de canaux pour le changer
 */
#define MAXNUMBERCHANNELSCG 16
/**@}*/

/*End of macros***************************************************************/

/*Typedef**********************************************************************/

/**
 * \brief structure contenant la configuration des rendeurs
 */
typedef struct __attribute__((packed))
{
    MDBGenericDeviceConfig deviceConfig;
    BYTE byCoinTypeRouting[2];
    BYTE byCoinValue[MAXNUMBERCHANNELSCG];
}
CHANGEGIVERSETUP;

/**
 * \brief Stucture contenant l'�tat des seuils et le niveau des tubes.
 */
typedef struct __attribute__((packed))
{
    BYTE byFull[2];
    BYTE byLevel[16];
}
TUBESSTATUS;

/**
 * \brief Strucute contenant la validation des pi�ces.
 */
typedef struct __attribute__((packed))
{

    union
    {
        BYTE byCoinEnable[2];
        WORD wCoinEnable;
    };
    BYTE byDispenseEnable[2];
}
COINTYPE;

/**
 * \brief Structure contenant l'identification et les options du rendeur.
 */
typedef struct __attribute__((packed))
{
    BYTE ManufacturerCode[3];
    BYTE SerialNumber[12];
    BYTE Model[12];
    BYTE SWVersion[2];
    BYTE Optionnal[4];
}
CHANGERID;

/*End of typedefs**************************************************************/

/*Variables********************************************************************/

/**
 * \var changerId
 * \brief Identification et options du rendeur.
 */
CHANGERID changerId;

/**
 * \var changeGiverConfig
 * \brief Configuration du rendeur.
 */
CHANGEGIVERSETUP changeGiverConfig;

/**
 * \var tubeStatus
 * \brief Seuils et niveau des tubes du rendeur.
 */
TUBESSTATUS tubeStatus;

/**
 * \var isChangerReseted
 * \brief Indique si le rendeur a accept� la commande de reset.
 */
BOOL isChangerReseted;

/**
 * \var lAmountCG
 * \brief Montant ins�r� dans le rendeur
 */
long lAmountCG;

/**
 * \var isCGPolled
 * \brief Indique si le rendeur a �t� poll�.
 */
BOOL isCGPolled;

/**
 * \var byCoinsBuffer
 * \brief Pointeur sur le buffer qui contiendra les  r�sultats le nombre de pi�ces pendant la p�riode de distribution.
 */
BYTE byCoinsBuffer[MAXNUMBERCHANNELSCG + 1];

/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * \brief R�cup�re l'identification et les options du rendeur.
 * \param[out] byID Pointeur sur la structure qui contiendra l'identification et les options du rendeur.
 * \return True Si la lecture s'est termin�e correctement.
 */
BOOL isGetMDBChangerID(CHANGERID *byID);

/**
 * \brief R�cup�re les seuils et le niveau des tubes.
 * \param[out] tubeStatus Pointeur sur la structure qui contiendra les seuils et le niveau des tubes du rendeur.
 * \return True Si la lecture s'est termin�e correctement.
 */
BOOL isGetMDBTubeStatus(TUBESSTATUS *tubeStatus);

/**
 * \brief Active ou desactive le rendeur.
 * \param[in] isEnable Indique si le rendeur doit �tre activ� ou non.
 * \param[in] coinType Param�trage d'acceptation des pi�ces de la centrale.
 * \return FALSE si l'op�ration ne s'est pas d�roul�e correctement ou si le rendeur n'est pas initialis�.
 */
BOOL isEnableChanger(const BOOL isEnable, COINTYPE *coinType);

/**
 * \brief Valide les options du niveau 3 du rendeur.
 * \return TRUE si l'op�ration s'est effectu�e correctement.
 */
BOOL isEnableFeature();

/**
 * \brief Demamde au rendeur d'effectuer une distribution .
 * \param[in] byAmount Montant � distribuer.
 * \return TRUE si l'instructuion � �t� comprise par le rendeur.
 */
BOOL isAlternatePayout(const BYTE byAmount);

/**
 * \brief Retourne dans le param�tre le d�tails des pi�ces distribu�es.
 * \param[out] byChannels contenant le d�tail des pi�ces distribu�es.
 * \return TRUE si l'op�ration est termin�e.
 */
BOOL isPayoutStatus(BYTE *byChannels);

/*End of prototypes************************************************************/
/**@}*/
#endif	/* MDB_CG_H */

