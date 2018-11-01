/* 
 * File:   mdb_cl.h
 * Author: RA
 *
 * Created on 21 janvier 2014, 19:58
 */

#ifndef MDB_CL_H
#define	MDB_CL_H

#include "MDB.h"

//Adresses périphériques

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
    WORD wMax; /*!< Prix du service le plus élevé.*/
    WORD wMin; /*!< Prix du service le moins élevé.*/
}
VMCMaxMin;

/**
 * \typedef READERConfig
 * \brief Structure contenant la configuration du lecteur cashless.
 */
typedef struct __attribute__((packed))
{
    MDBGenericDeviceConfig deviceConfig; /*!< Information générique sur la configuration du lecteur cashless.*/
    BYTE byMaxTimeResponse; /*!< Temps maximum accordé au lecteur pour répondre.*/
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
    BYTE bySN[12];  /*!< Numéro de série en code ASCII du lecteur cashless*/
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
 * \brief Indique si les opérations de reset ont été effectuées
 */
BOOL isCashLessReseted;

/**
 * \var dwMediaID
 * \brief Numéro du média présenté.
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
 * \brief Focntion appellé pour paramétrer les prix maximum et minimum
 * \param[in] byDeviceAddress Adresse du périphérique.
 * \param[in] vmcMaxMinPrice Pointeur sur la structure qui contient les valeurs.
 * \return TRUE Si le périphérique à acquiter la reception de la commande.
 */
BOOL isMDBSetupMaxMinPrice(const BYTE byDeviceAddress, const VMCMaxMin *vmcMaxMinPrice);

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

/**
 * \fn isMDBVendFailure
 * \brief Informe le lecteur de l'échec de la vente.
 * \param[in] byDeviceAddress Adresse du lecteur cashless.
 * \return True Si l'opération s'est effectuée correctement.
 */
BOOL isMDBVendFailure(const BYTE byDeviceAddress);

#endif	/* MDB_CL_H */

