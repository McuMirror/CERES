/* 
 * File:   satellites.h
 * Author: RA
 *
 * Created on 28 février 2014, 10:15
 */

#ifndef SATELLITES_H
#define	SATELLITES_H

#include "RAdefine.h"
#include "timers.h"
#include "RS485.h"
#include <limits.h>
#include "MDD File System/FSIO.h"
#include "TCPIP Stack/Delay.h"



//Format message :
//[DESTINATAIRE][DIMENSION DATA][EXPEDITEUR][HEADER/STATUS][DATA]..[DATA][CRC16][CRC16]

/*Defines**********************************************************************/

/**
 * \def HOST
 * \brief Identicateur de la carte principale.
 */
#define HOST 0X01 /*!< Numéro de la machine dans une transmission.*/

/**
 * \def SAT_TO
 * \brief Delai accordé au satelltite pour fournir une réponse.
 */
#define SAT_TO (1 * SECONDE)

/*Enumerations*****************************************************************/

/**
 * \enum ERSP_SAT
 * \brief Réponse des satellites.
 */
enum
{
    MDI_ACK = 0, /*!< Instruction reçu correctement.*/
    MDI_NACK = 5, /*!< Instruction erronée.*/
    MDI_BUSY = 6, /*!< Impossible de répondre pour cause d'occupation.*/
} __attribute__((packed)) ERSP_SAT;

/**
 * \enum ESTATUS
 * \brief Type enumeration des états d'occupation des machines
 */
typedef enum
{
    MACHINE_FREE = 0, /*!< Machine inoccupée. */
    MACHINE_BUSY = 1, /*!< Machine occupée.*/
} __attribute__((packed)) ESTATUS;

/**
 * \typedef ESTATE
 * \brief Type enumeration allumé ou éteint.
 */
typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON = 1,
} __attribute__((packed)) ESTATE;


/**
 * \typedef ePreseent
 * \brief Type enumeration de la présence secteur.
 */
typedef enum
{
    ABSENT = 0, /*!<Courant secteur absent.*/
    PRESENT = 1, /*!<Courant secteur présent.*/
} EPRESENT;

/**
 * \typedef eState
 * \brief Type enumeration allumé ou éteint.
 */
typedef enum
{
    NOTEMPTY,
    EMPTY,
} ELEVEL;

/**
 * \enum EHEADER
 * \bief Type enumeration des commandes.
 */
typedef enum
{
    SIMPLEPOLL = 0xFE, /*!< Vérifie la communication, le satellite répond par un ack.*/

    MODIFY_MACHINE_NUMBER = SIMPLEPOLL - 1, /*!< Modifie le numéro de la machine que contrôle le satellite adressé.*/
    REQUEST_MACHINE_NUMBER = MODIFY_MACHINE_NUMBER - 1, /*!< Demande le numéro de la machine gérée par le satellite.*/

    MODIFY_MACHINE_RELAY_STATE = REQUEST_MACHINE_NUMBER - 1, /*!< Active ou desactive le relais qui contrôle la machine.*/
    REQUEST_MACHINE_RELAY_STATE = MODIFY_MACHINE_RELAY_STATE - 1, /*!< Le satellite renvoie en paramètre l'état du relais qui contrôle la machine.*/

    REQUEST_MACHINE_STATUS = REQUEST_MACHINE_RELAY_STATE - 1, /*!< Le satellite renvoie en paramètre l'état d'occupation de la machine.*/

    MODIFY_DELAY_OVER_BUSY = REQUEST_MACHINE_STATUS - 1, /*!< Modifie le temps de suroccupation du satellite.*/
    REQUEST_DELAY_OVER_BUSY = MODIFY_DELAY_OVER_BUSY - 1, /*!< Le satellite renvoie le temps suroccupation.*/

    MODIFY_BUSY_LEVEL = REQUEST_DELAY_OVER_BUSY - 1, /*!Modifie le niveau permettant de définir une occupation de la machine.*/
    REQUEST_BUSY_LEVEL = MODIFY_BUSY_LEVEL - 1, /*!< Renvoi le niveau permettant de définir une occupation de la machine.*/

    REQUEST_ISMAINPRESENT = REQUEST_BUSY_LEVEL - 1, /*!< Retourne la présence du secteur.*/

    MODIFY_MAIN_POWER = REQUEST_ISMAINPRESENT - 1, /*!< Défini la position du relais de fourniture de courant à la machine.*/
    REQUEST_MAIN_POWER = MODIFY_MAIN_POWER - 1, /*!< Retourne la position du relais de fourniture de courant à la machine.*/

    REQUEST_MACHINE_LEVEL = REQUEST_MAIN_POWER - 1, /*!< Retourne le niveau des produits dans la machine.*/
    REQUEST_FW_VERSION = REQUEST_MACHINE_LEVEL - 1, /*!<Retourne la version du satellite.*/

} __attribute__((packed)) EHEADER;

/*Variables********************************************************************/

/**
 * \var BYTE bySatBuffer[16];
 * \brief Buffer utilisé dans les communications avec les satellites.
 */
BYTE bySatBuffer[16];

//*Prototypes*******************************************************************

/**
 * \fn wCRC16
 * \brief Calcul du CRC du buffer reçu en paramètre.
 * @param[in] byData Buffer à traiter.
 * @param[in] byLen Nombre d'octet à calculer.
 * @return CRC16 du buffer.
 */
WORD wCRC16(const BYTE *byData, const BYTE byLen);

/**
 * \fn isSendCommand
 * \brief Envoie une commande à un satellite.
 * @param[in] byNumMachine Numéro de la machine pilotée par le satellite destinataire.
 * @param[in] byHeader Commande
 * @param[in] byLenData Longueur des paramètres.
 * @param[in] byData Paramètres.
 */
BOOL isSendCommand(const BYTE byNumMachine, const BYTE byHeader,
                  const BYTE byLenData, const void *byData);

/**
 * \fn boReceiveAnswer
 * \brief Reception d'une réponse d'un satellite.
 * @param byNumMachine Numéro de la machine qui doit répondre.
 * @return True si la réponse est cohérente.
 */
//BOOL boReceiveAnswer(const BYTE byNumMachine);

/**
 * \fn isModifyMachineNumber
 * \brief Affecte une adresse au satellite qui sera aussi le numéro de la machine piloté par ce satellite.
 * Le module doit répondre avec sa nouvelle adresse.
 * @param[in] byOldNumMachine Numéro à modifier.
 * @param[in] byNewNumMachine Numéro à affecter
 * @return TRUE si le numéro est accepté par le module.
 */
BOOL isModifyMachineNumber(const BYTE byOldNumMachine, BYTE byNewNumMachine);

/**
 * \fn isSimplePoll
 * \brief Vérifie la communication entre la CPU et un satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \return TRUE si la communication s'effectue correctement.
 */
BOOL isSimplePoll(const BYTE byNumMachine);

/**
 * \fn isMainPresent
 * \brief Vérifie la présence du secteur sur le satellite.
 * @param param[in] byNumMachine Adresse du satellite.
 * @return TRUE si le secteur est présent sur le satellite.
 */
BOOL isMainPresent(const BYTE byNumMachine);

/**
 * \fn isModifyMachineRelayState
 * \brief Active ou desactive le relais du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] relayState Etat que devra prendre le relais.
 * \return TRUE si la commande s'est effectuée correctement.
 */
BOOL isModifyMachineRelayState(const BYTE byNumMachine, const ESTATE relayState);

/**
 * \fn isExModifyMachineRelayState
 * \brief Active le relais du satellite pendant un temps déterminé.
 * @param[in] byNumMachine Adresse du satellite.
 * @param[in] dwDelayActivation Temps pendant lequel sera activé le relais sur le satellite.
 * @return TRUE si la commande s'est effectuée correctement.
 */
BOOL isExModifyMachineRelayState(const BYTE byNumMachine, const DWORD dwDelayActivation);

/**
 * \fn getMachineRelayState
 * \brief Demande l'état du relais du satellite adressé.
 * \param[in] byNumMachine Adresse du satellite.
 * \return RELAY_ON si le relais est activé. Dans le cas où la communication est défaillante la fonction retournera RELAY_OFF.
 */
ESTATE getMachineRelayState(const BYTE byNumMachine);

/**
 * \fn getMachineState
 * \brief Demande l'état de la machine adressée.
 * \param[in] byNumMachine Adresse du satellite.
 * @return MACHINE_BUSY si la machine est occupée ou si la communication ne fonctionne pas.
 */
ESTATUS getMachineState(const BYTE byNumMachine);

/**
 * \fn isSetMainPowerState
 * \brief Active ou desactive le relais d'alimentation principale de la machine.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] relayState Etat que devra prendre le relais.
 * \return TRUE si la commande s'est effectuée correctement.
 */
BOOL isSetMainPowerState(const BYTE byNumMachine, const ESTATE relayState);

/**
 * \fn isSetOverBusyDelay
 * \brief Defini le temps de surouccpation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] dwOverBusyDelay Temps de suroccupation en milliseconde.
 * \return TRUE si l'opération s'est déroulée correctement.
 */
BOOL isSetOverBusyDelay(const BYTE byNumMachine, DWORD dwOverBusyDelay);

/**
 * \fn isSetSensibility
 * \brief Defini la sensibilité à la consommation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] wSensibility Niveau de sensibilité.
 * \return TRUE si l'opération s'est déroulée correctement.
 */
BOOL isSetSensibility(const BYTE byNumMachine, WORD wSensibility);

/**
 * \fn dwGetOverBusyDelay
 * \brief Demande le temps de suroccupation du satellite adressé.
 * \param[in] byNumMachine Adresse du satellite.
 * @return Le temps de suroccupation du satellite. 65535 si la communication ne fonctionne pas.
 */
DWORD dwGetOverBusyDelay(const BYTE byNumMachine);

/**
 * \fn getMachineFull
 * \brief Demande au satellite si le niveau n'est pas vide.
 * \detail Peut-être utile pour un distributeur.
 * \param[in] byNumMachine Adresse du satellite.
 * @return NOTEMPTY si la machine n'est occupée ou si la communication ne fonctionne pas. EMPTY dans les autres cas.
 */
ELEVEL getMachineFull(const BYTE byNumMachine);

/**
 * \fn wGetSatelliteFWVersion
 * \brief Renvoi le numéro de la version du FW du satellite.
 * @param byNumMachine Numéro de la machine gérer par le satellite utilisé.
 * @return Le numéro de la révision FW du satellite concerné.
 */
WORD wGetSatelliteFWVersion(const BYTE byNumMachine);

/******************************************************************************/
#endif	/* SATELLITES_H */

