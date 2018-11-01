/*
 * File:   mdb_cg.h
 * Author: RA
 *
 * Created on 21 janvier 2014, 19:57
 */

#ifndef MDB_CG_H
  #define	MDB_CG_H

  #include "MDB.h"

/*Defines**********************************************************************/
/**
 * \def CGADDRESS
 * \brief Adresse du rendeur.
 */
  #define CGADDRESS 0X08


//Status rendeur
  #define ESCROW_REQUEST      0b00000001
  #define CHANGERPAYOUTBUS    0b00000010
  #define CHANGERNOCREDIT     0b00000011
  #define CHANGETUBESENSORHS  0b00000100
  #define CHANGERDOUBLECOINS  0b00000101
  #define CHANGERUNPLUGGED    0b00000110
  #define CHANGERTUBEJAM      0b00000111
  #define CHANGERROMERROR     0b00001000
  #define CHANGERROUTEERROR   0b00001001
  #define CHANGERBUSY         0b00001010
  #define JUST_RESET_CG       0b00001011
  #define COINJAM             0b00001100
  #define COINREMOVAL         0b00001101

/**
 * \def MAXNUMBERCHANNELSCG
 * \brief Nombre de canaux pour le changer
 */
  #define MAXNUMBERCHANNELSCG 16

/*Typedef**********************************************************************/
/**
 * \typedef ChangeGiverConfig
 * \brief structure contenant la configuration des rendeurs
 */
typedef struct __attribute__((packed))
{
  MDBGenericDeviceConfig deviceConfig;
  BYTE byCoinTypeRouting[2];
  BYTE byCoinValue[MAXNUMBERCHANNELSCG];
}
ChangeGiverConfig;

/**
 * \typedef TubeStatus
 * \brief Stucture contenant l'état des seuils et le niveau des tubes.
 */
typedef struct __attribute__((packed))
{
  BYTE byFull[2];
  BYTE byLevel[16];
}
TubeStatus;

/**
 * \typedef CoinType
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
CoinType;

/**
 * \typedef ChangerIdentification
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
ChangerIdentification;

/*Variables********************************************************************/

/**
 * \var changerId
 * \brief Identification et options du rendeur.
 */
ChangerIdentification changerId;

/**
 * \var changeGiverConfig
 * \brief Configuration du rendeur.
 */
ChangeGiverConfig changeGiverConfig;

/**
 * \var tubeStatus
 * \brief Seuils et niveau des tubes du rendeur.
 */
TubeStatus tubeStatus;

/**
 * \var boExactChange
 * \brief Indique si le niveau minimum est dépassé ou non.
 */
BOOL boExactChange;

/**
 * \var boChangerReseted
 * \brief Indique si le rendeur a accepté la commande de reset.
 */
BOOL boChangerReseted;

/**
 * \var lAmountCG
 * \brief Montant inséré dans le rendeur
 */
long lAmountCG;

/*Prototypes*******************************************************************/

/**
 * \fn boGetMDBChangerID
 * \brief Récupère l'identification et les options du rendeur.
 * \param[out] byID Pointeur sur la structure qui contiendra l'identification et les options du rendeur.
 * \return True Si la lecture s'est terminée correctement.
 */
BOOL boGetMDBChangerID(ChangerIdentification *byID);

/**
 * \fn boGetMDBTubeStatus
 * \brief Récupère les seuils et le niveau des tubes.
 * \param[out] tubeStatus Pointeur sur la structure qui contiendra les seuils et le niveau des tubes du rendeur.
 * \return True Si la lecture s'est terminée correctement.
 */
BOOL boGetMDBTubeStatus(TubeStatus *tubeStatus);

/**
 * \fn boSetMDBCoinType
 * \brief Active ou non les pièces.
 * \param[in] coinType Structure contenant l'habilitation des pièces.
 * \return True si l'écriture s'est effectuée correctement.
 */
BOOL boSetMDBCoinType(CoinType *coinType);

/**
 * \fn boDispenseMDBChanger
 * \brief Distribue un type de pièce.
 * \param[in] byCoin Numéro de la pièce à distribuer.
 * \param[in] byNum Nombre de pièces à distribuer.
 */
BOOL boDispenseMDBChanger(const BYTE byCoin, const BYTE byNum);

/**
 * \fn boEnableChanger
 * \brief Active ou desactive le rendeur.
 * \param[in] boEnable Indique si le rendeur doit être activé ou non.
 * \param[in] coinType Paramètrage d'acceptation des pièces de la centrale.
 * \return FALSE si l'opération ne s'est pas déroulée correctement ou si le rendeur n'est pas initialisé.
 */
BOOL boEnableChanger(const BOOL boEnable, CoinType *coinType);

/**
 * \fn boEnableFeature
 * \brief Valide les options du niveau 3 du rendeur.
 * \return TRUE si l'opération s'est effectuée correctement.
 */
BOOL boEnableFeature();

/**
 * \fn boAlternatePayout
 * \brief Demamde au rendeur d'effectuer une distribution .
 * \param[in] wAmount Montant à distribuer.
 * \return TRUE si l'instructuion à été comprise par le rendeur.
 */
BOOL boAlternatePayout(const WORD wAmount);

/**
 * \fn boPayoutStatus
 * \brief Retourne dans le paramètre le détails des pièces distribuées.
 * \param[out] Buffer contenant le détail des pièces distribuées.
 * \Retourne TRUE si l'opération est terminée.
 */
BOOL boPayoutStatus(BYTE *byChannels);

BYTE byCoinsBuffer[MAXNUMBERCHANNELSCG + 1];

/******************************************************************************/

#endif	/* MDB_CG_H */

