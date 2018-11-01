
/** ****************************************************************************
 * \file            satellites.h                                                 
 * \brief			Header de la gestion des satellites.
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/

#ifndef SATELLITES_H
#define	SATELLITES_H

#include "RAdefine.h"
#include "timers.h"
#include "RS485.h"
#include <limits.h>
#include "MDD File System/FSIO.h"
#include "TCPIP Stack/Delay.h"


/**\defgroup SATELLITES Gestion des satellites.
 * @{
 */
//Format message :
//[DESTINATAIRE][DIMENSION DATA][EXPEDITEUR][HEADER/STATUS][DATA]..[DATA][CRC16][CRC16]

/*Macros**********************************************************************/

/**
 * \brief Identicateur de la carte principale.
 */
#define HOST 0X01 /*!< Numéro de la machine dans une transmission.*/

/**
 * \brief Delai accordé au satelltite pour fournir une réponse.
 */
#define SAT_TO (1 * SECONDE)
/*End of macros****************************************************************/

/*Enumerations*****************************************************************/

/**
 * \brief Réponse des satellites.
 */
enum ERSP_SAT
{
    MDI_ACK = 0, /*!< Instruction reçu correctement.*/
    MDI_NACK = 5, /*!< Instruction erronée.*/
    MDI_BUSY = 6, /*!< Impossible de répondre pour cause d'occupation.*/
};

/*End of enumerations**********************************************************/

/*Typedef**********************************************************************/

/**
 * \brief Type enumeration des états d'occupation des machines
 */
typedef enum
{
    MACHINE_FREE = 0, /*!< Machine inoccupée. */
    MACHINE_BUSY = 1, /*!< Machine occupée.*/
} ESTATUS;

/**
 * \brief Type indiquant un relai activé ou non.
 */
typedef enum
{
    RELAY_OFF = 0, /*!<Le relay est desactivé.*/
    RELAY_ON = 1, /*!<Le relay est activé.*/
} ESTATE;

/**
 * \brief Type enumeration de la présence secteur.
 */
typedef enum
{
    ABSENT = 0, /*!<Courant secteur absent.*/
    PRESENT = 1, /*!<Courant secteur présent.*/
} EPRESENT;

/**
 * \brief Type enumeration indiqunant une machine vide.
 */
typedef enum
{
    NOTEMPTY, /*!<La machine n'est pas vide.*/
    EMPTY, /*!<La machine est vide.*/
} ELEVEL;

/**
 * \brief Enumeration des commandes pouvant être envoyées aux satellites.
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

} EHEADER;
/*End Typedef******************************************************************/

/*Variables********************************************************************/

/**
 * \var BYTE bySatBuffer[16];
 * \brief Buffer utilisé dans les communications avec les satellites.
 */
BYTE bySatBuffer[16];
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * \brief Affecte une adresse au satellite qui sera aussi le numéro de la machine piloté par ce satellite.
 * Le module doit répondre avec sa nouvelle adresse.
 * \param[in] byOldNumMachine Numéro à modifier.
 * \param[in] byNewNumMachine Numéro à affecter
 * @return TRUE si le numéro est accepté par le module.
 */
BOOL isModifyMachineNumber(const BYTE byOldNumMachine, BYTE byNewNumMachine);

/**
 * \brief Vérifie la communication entre la CPU et un satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \return TRUE si la communication s'effectue correctement.
 */
BOOL isSimplePoll(const BYTE byNumMachine);

/**
 * \brief Vérifie la présence du secteur sur le satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * @return TRUE si le secteur est présent sur le satellite.
 */
BOOL isMainPresent(const BYTE byNumMachine);

/**
 * \brief Active ou desactive le relais du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] relayState Etat que devra prendre le relais.
 * \return TRUE si la commande s'est effectuée correctement.
 */
BOOL isModifyMachineRelayState(const BYTE byNumMachine, const ESTATE relayState);

/**
 * \brief Active le relais du satellite pendant un temps déterminé.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] dwDelayActivation Temps pendant lequel sera activé le relais sur le satellite.
 * @return TRUE si la commande s'est effectuée correctement.
 */
BOOL isExModifyMachineRelayState(const BYTE byNumMachine, const DWORD dwDelayActivation);

/**
 * \brief Demande l'état du relais du satellite adressé.
 * \param[in] byNumMachine Adresse du satellite.
 * \return RELAY_ON si le relais est activé. Dans le cas où la communication est défaillante la fonction retournera RELAY_OFF.
 */
ESTATE getMachineRelayState(const BYTE byNumMachine);

/**
 * \brief Demande l'état de la machine adressée.
 * \param[in] byNumMachine Adresse du satellite.
 * @return MACHINE_BUSY si la machine est occupée ou si la communication ne fonctionne pas.
 */
ESTATUS getMachineState(const BYTE byNumMachine);

/**
 * \brief Defini le temps de surouccpation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] dwOverBusyDelay Temps de suroccupation en milliseconde.
 * \return TRUE si l'opération s'est déroulée correctement.
 */
BOOL isSetOverBusyDelay(const BYTE byNumMachine, DWORD dwOverBusyDelay);

/**
 * \brief Defini la sensibilité à la consommation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] wSensibility Niveau de sensibilité.
 * \return TRUE si l'opération s'est déroulée correctement.
 */
BOOL isSetSensibility(const BYTE byNumMachine, WORD wSensibility);

/**
 * \brief Demande au satellite si le niveau n'est pas vide.
 * \details Peut-être utile pour un distributeur qui contient des produits 
 * comme des cartouches de lessive.
 * \param[in] byNumMachine Adresse du satellite.
 * @return NOTEMPTY si la machine n'est occupée ou si la communication ne fonctionne pas. EMPTY dans les autres cas.
 */
ELEVEL getMachineFull(const BYTE byNumMachine);

/**
 * \brief Renvoi le numéro de la version du FW du satellite.
 * \param byNumMachine Numéro de la machine gérer par le satellite utilisé.
 * @return Le numéro de la révision FW du satellite concerné.
 */
WORD wGetSatelliteFWVersion(const BYTE byNumMachine);
/*End of prototypes************************************************************/

/**@}*/
#endif	/* SATELLITES_H */

