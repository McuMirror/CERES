
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
 * \details Le levier de remboursement à été activé.
 */
#define ESCROW_REQUEST       0b00000001

/**
 \brief CHANGER PAYOUT BUSY
 \details Le changeur est occupé à rembourser.
 */
#define CHANGERPAYOUTBUSY    0b00000010

/**
 * \brief NO CREDIT
 * \details Une pièce a été validée mais ne s'est pas positionné quand le crédit a été donné.
 */
#define CHANGERNOCREDIT      0b00000011

/**
 * \brief DEFECTIVE TUBE SENSOR
 * \details Le changer a détecté un comportement anormale de l'un des tubes
 */
#define CHANGETUBESENSORHS   0b00000100

/**
 * \brief DOUBLE ARRIVAL
 * \details 2 pièces sont arrivées trop proches l'une de l'autre
 */
#define CHANGERDOUBLECOINS   0b00000101

/**
 * \brief ACCEPTOR UNPLUGGED
 * \details Le changeur a détecté que le validteur a été deconnecté.
 */
#define CHANGERUNPLUGGED     0b00000110

/**
 * \brief TUBE JAM
 * \details Un tube est coincé.
 */
#define CHANGERTUBEJAM       0b00000111

/**
 * \brief ROM CHECKSUM ERROR
 * \details Le checksum du software du changeur est erroné.
 */
#define CHANGERROMERROR      0b00001000

/**
 * \brief COIN ROUTING ERROR
 * \details Une pièce a été validée, mais n'a pas suivi le routage prévu.
 */
#define CHANGERROUTEERROR    0b00001001

/**
 * \brief CHANGER BUSY
 * \details Le changer est occupé est ne peut donner une réponse exacte.
 */
#define CHANGERBUSY          0b00001010

/**
 * \brief CHANGER WAS RESET
 * \details Le changer a detecté un reset et est retourné en position d'attente d'initialisation
 */
#define JUST_RESET_CG        0b00001011

/**
 * \brief COIN JAM
 * \details Une pièce est coincée dans la zone d'acceptation.
 */
#define COINJAM              0b00001100

/**
 * \brief POSSIBLE CREDITED COIN REMOVAL
 * \details Il y a eu une tentative de récupération d'une pièce créditée.
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
 * \brief Stucture contenant l'état des seuils et le niveau des tubes.
 */
typedef struct __attribute__((packed))
{
    BYTE byFull[2];
    BYTE byLevel[16];
}
TUBESSTATUS;

/**
 * \brief Strucute contenant la validation des pièces.
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
 * \brief Indique si le rendeur a accepté la commande de reset.
 */
BOOL isChangerReseted;

/**
 * \var lAmountCG
 * \brief Montant inséré dans le rendeur
 */
long lAmountCG;

/**
 * \var isCGPolled
 * \brief Indique si le rendeur a été pollé.
 */
BOOL isCGPolled;

/**
 * \var byCoinsBuffer
 * \brief Pointeur sur le buffer qui contiendra les  résultats le nombre de pièces pendant la période de distribution.
 */
BYTE byCoinsBuffer[MAXNUMBERCHANNELSCG + 1];

/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * \brief Récupère l'identification et les options du rendeur.
 * \param[out] byID Pointeur sur la structure qui contiendra l'identification et les options du rendeur.
 * \return True Si la lecture s'est terminée correctement.
 */
BOOL isGetMDBChangerID(CHANGERID *byID);

/**
 * \brief Récupère les seuils et le niveau des tubes.
 * \param[out] tubeStatus Pointeur sur la structure qui contiendra les seuils et le niveau des tubes du rendeur.
 * \return True Si la lecture s'est terminée correctement.
 */
BOOL isGetMDBTubeStatus(TUBESSTATUS *tubeStatus);

/**
 * \brief Active ou desactive le rendeur.
 * \param[in] isEnable Indique si le rendeur doit être activé ou non.
 * \param[in] coinType Paramètrage d'acceptation des pièces de la centrale.
 * \return FALSE si l'opération ne s'est pas déroulée correctement ou si le rendeur n'est pas initialisé.
 */
BOOL isEnableChanger(const BOOL isEnable, COINTYPE *coinType);

/**
 * \brief Valide les options du niveau 3 du rendeur.
 * \return TRUE si l'opération s'est effectuée correctement.
 */
BOOL isEnableFeature();

/**
 * \brief Demamde au rendeur d'effectuer une distribution .
 * \param[in] byAmount Montant à distribuer.
 * \return TRUE si l'instructuion à été comprise par le rendeur.
 */
BOOL isAlternatePayout(const BYTE byAmount);

/**
 * \brief Retourne dans le paramètre le détails des pièces distribuées.
 * \param[out] byChannels contenant le détail des pièces distribuées.
 * \return TRUE si l'opération est terminée.
 */
BOOL isPayoutStatus(BYTE *byChannels);

/*End of prototypes************************************************************/
/**@}*/
#endif	/* MDB_CG_H */

