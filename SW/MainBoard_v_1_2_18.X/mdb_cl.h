/* 
 * File:   mdb_cl.h
 * Author: RA
 *
 * Created on 21 janvier 2014, 19:58
 */

#ifndef MDB_CL_H
#define	MDB_CL_H

#include "MDB.h"

//Adresses p�riph�riques

/*Defines**********************************************************************/
#define CASHLESS1 0X10 /*!< Adresse cashless 1. */
#define CASHLESS2 0X60 /*!< Adresse cashless 2. */
//#define CASHLESSPOLLINGINMS (150 * MILLISEC)

/*Typedef**********************************************************************/

/**
 * \typedef VMCMaxMin
 * \brief Structure contenant le prix maximum et le prix minimum des services.
 */
typedef struct __attribute__((packed))
{
    WORD wMax; /*!< Prix du service le plus �lev�.*/
    WORD wMin; /*!< Prix du service le moins �lev�.*/
}
VMCMaxMin;

/**
 * \typedef READERConfig
 * \brief Structure contenant la configuration du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    MDBGenericDeviceConfig deviceConfig; /*!< Information g�n�rique sur la configuration du lecteur cashless.*/
    BYTE byMaxTimeResponse; /*!< Temps maximum accord� au lecteur pour r�pondre.*/
    BYTE byMiscellaneous; /*!< Options du lecteur cashless.*/
}
READERConfig;

/**
 * \typedef PeripheralID
 * \brief Structure contenant les identifiants du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    BYTE byManufacturer[3]; /*!< Code NAMA du fabricant du lecteur cashless.*/
    BYTE bySN[12];  /*!< Num�ro de s�rie en code ASCII du lecteur cashless*/
    BYTE byModel[12]; /*!< Model en code ASCII.*/
    BYTE bySWVersion[2]; /*!< Revision software.*/
}
PeripheralID;

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
 * \var dwMediaID
 * \brief Num�ro du m�dia pr�sent�.
 */
DWORD dwMediaID;

/**
 * \var wmcMaxMinPrices
 * \brief Prix maximum et minimum des services.
 */
VMCMaxMin wmcMaxMinPrices;

/**
 * \var readerConfig
 * \brief Configuration du lecteur.
 */
READERConfig readerConfig;

/**
 * \var peripheralID
 * \brief Identifiants du lecteur.
 */
PeripheralID peripheralID;

BOOL isVendRequested;

//*Prototypes******************************************************************/

/**
 * \fn isMDBSetupMaxMinPrice
 * \brief Focntion appell� pour param�trer les prix maximum et minimum
 * \param[in] byDeviceAddress Adresse du p�riph�rique.
 * \param[in] vmcMaxMinPrice Pointeur sur la structure qui contient les valeurs.
 * \return TRUE Si le p�riph�rique � acquiter la reception de la commande.
 */
BOOL isMDBSetupMaxMinPrice(const BYTE byDeviceAddress, const VMCMaxMin *vmcMaxMinPrice);

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

/**
 * \fn isMDBVendFailure
 * \brief Informe le lecteur de l'�chec de la vente.
 * \param[in] byDeviceAddress Adresse du lecteur cashless.
 * \return True Si l'op�ration s'est effectu�e correctement.
 */
BOOL isMDBVendFailure(const BYTE byDeviceAddress);

#endif	/* MDB_CL_H */

