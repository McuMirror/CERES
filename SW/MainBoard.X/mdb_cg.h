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
 * \brief Stucture contenant l'�tat des seuils et le niveau des tubes.
 */
typedef struct __attribute__((packed))
{
  BYTE byFull[2];
  BYTE byLevel[16];
}
TubeStatus;

/**
 * \typedef CoinType
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
 * \brief Indique si le niveau minimum est d�pass� ou non.
 */
BOOL boExactChange;

/**
 * \var boChangerReseted
 * \brief Indique si le rendeur a accept� la commande de reset.
 */
BOOL boChangerReseted;

/**
 * \var lAmountCG
 * \brief Montant ins�r� dans le rendeur
 */
long lAmountCG;

/*Prototypes*******************************************************************/

/**
 * \fn boGetMDBChangerID
 * \brief R�cup�re l'identification et les options du rendeur.
 * \param[out] byID Pointeur sur la structure qui contiendra l'identification et les options du rendeur.
 * \return True Si la lecture s'est termin�e correctement.
 */
BOOL boGetMDBChangerID(ChangerIdentification *byID);

/**
 * \fn boGetMDBTubeStatus
 * \brief R�cup�re les seuils et le niveau des tubes.
 * \param[out] tubeStatus Pointeur sur la structure qui contiendra les seuils et le niveau des tubes du rendeur.
 * \return True Si la lecture s'est termin�e correctement.
 */
BOOL boGetMDBTubeStatus(TubeStatus *tubeStatus);

/**
 * \fn boSetMDBCoinType
 * \brief Active ou non les pi�ces.
 * \param[in] coinType Structure contenant l'habilitation des pi�ces.
 * \return True si l'�criture s'est effectu�e correctement.
 */
BOOL boSetMDBCoinType(CoinType *coinType);

/**
 * \fn boDispenseMDBChanger
 * \brief Distribue un type de pi�ce.
 * \param[in] byCoin Num�ro de la pi�ce � distribuer.
 * \param[in] byNum Nombre de pi�ces � distribuer.
 */
BOOL boDispenseMDBChanger(const BYTE byCoin, const BYTE byNum);

/**
 * \fn boEnableChanger
 * \brief Active ou desactive le rendeur.
 * \param[in] boEnable Indique si le rendeur doit �tre activ� ou non.
 * \param[in] coinType Param�trage d'acceptation des pi�ces de la centrale.
 * \return FALSE si l'op�ration ne s'est pas d�roul�e correctement ou si le rendeur n'est pas initialis�.
 */
BOOL boEnableChanger(const BOOL boEnable, CoinType *coinType);

/**
 * \fn boEnableFeature
 * \brief Valide les options du niveau 3 du rendeur.
 * \return TRUE si l'op�ration s'est effectu�e correctement.
 */
BOOL boEnableFeature();

/**
 * \fn boAlternatePayout
 * \brief Demamde au rendeur d'effectuer une distribution .
 * \param[in] wAmount Montant � distribuer.
 * \return TRUE si l'instructuion � �t� comprise par le rendeur.
 */
BOOL boAlternatePayout(const WORD wAmount);

/**
 * \fn boPayoutStatus
 * \brief Retourne dans le param�tre le d�tails des pi�ces distribu�es.
 * \param[out] Buffer contenant le d�tail des pi�ces distribu�es.
 * \Retourne TRUE si l'op�ration est termin�e.
 */
BOOL boPayoutStatus(BYTE *byChannels);

BYTE byCoinsBuffer[MAXNUMBERCHANNELSCG + 1];

/******************************************************************************/

#endif	/* MDB_CG_H */

