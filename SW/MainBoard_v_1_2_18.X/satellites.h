/* 
 * File:   satellites.h
 * Author: RA
 *
 * Created on 28 f�vrier 2014, 10:15
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
#define HOST 0X01 /*!< Num�ro de la machine dans une transmission.*/

/**
 * \def SAT_TO
 * \brief Delai accord� au satelltite pour fournir une r�ponse.
 */
#define SAT_TO (1 * SECONDE)

/*Enumerations*****************************************************************/

/**
 * \enum ERSP_SAT
 * \brief R�ponse des satellites.
 */
enum
{
    MDI_ACK = 0, /*!< Instruction re�u correctement.*/
    MDI_NACK = 5, /*!< Instruction erron�e.*/
    MDI_BUSY = 6, /*!< Impossible de r�pondre pour cause d'occupation.*/
} __attribute__((packed)) ERSP_SAT;

/**
 * \enum ESTATUS
 * \brief Type enumeration des �tats d'occupation des machines
 */
typedef enum
{
    MACHINE_FREE = 0, /*!< Machine inoccup�e. */
    MACHINE_BUSY = 1, /*!< Machine occup�e.*/
} __attribute__((packed)) ESTATUS;

/**
 * \typedef ESTATE
 * \brief Type enumeration allum� ou �teint.
 */
typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON = 1,
} __attribute__((packed)) ESTATE;


/**
 * \typedef ePreseent
 * \brief Type enumeration de la pr�sence secteur.
 */
typedef enum
{
    ABSENT = 0, /*!<Courant secteur absent.*/
    PRESENT = 1, /*!<Courant secteur pr�sent.*/
} EPRESENT;

/**
 * \typedef eState
 * \brief Type enumeration allum� ou �teint.
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
    SIMPLEPOLL = 0xFE, /*!< V�rifie la communication, le satellite r�pond par un ack.*/

    MODIFY_MACHINE_NUMBER = SIMPLEPOLL - 1, /*!< Modifie le num�ro de la machine que contr�le le satellite adress�.*/
    REQUEST_MACHINE_NUMBER = MODIFY_MACHINE_NUMBER - 1, /*!< Demande le num�ro de la machine g�r�e par le satellite.*/

    MODIFY_MACHINE_RELAY_STATE = REQUEST_MACHINE_NUMBER - 1, /*!< Active ou desactive le relais qui contr�le la machine.*/
    REQUEST_MACHINE_RELAY_STATE = MODIFY_MACHINE_RELAY_STATE - 1, /*!< Le satellite renvoie en param�tre l'�tat du relais qui contr�le la machine.*/

    REQUEST_MACHINE_STATUS = REQUEST_MACHINE_RELAY_STATE - 1, /*!< Le satellite renvoie en param�tre l'�tat d'occupation de la machine.*/

    MODIFY_DELAY_OVER_BUSY = REQUEST_MACHINE_STATUS - 1, /*!< Modifie le temps de suroccupation du satellite.*/
    REQUEST_DELAY_OVER_BUSY = MODIFY_DELAY_OVER_BUSY - 1, /*!< Le satellite renvoie le temps suroccupation.*/

    MODIFY_BUSY_LEVEL = REQUEST_DELAY_OVER_BUSY - 1, /*!Modifie le niveau permettant de d�finir une occupation de la machine.*/
    REQUEST_BUSY_LEVEL = MODIFY_BUSY_LEVEL - 1, /*!< Renvoi le niveau permettant de d�finir une occupation de la machine.*/

    REQUEST_ISMAINPRESENT = REQUEST_BUSY_LEVEL - 1, /*!< Retourne la pr�sence du secteur.*/

    MODIFY_MAIN_POWER = REQUEST_ISMAINPRESENT - 1, /*!< D�fini la position du relais de fourniture de courant � la machine.*/
    REQUEST_MAIN_POWER = MODIFY_MAIN_POWER - 1, /*!< Retourne la position du relais de fourniture de courant � la machine.*/

    REQUEST_MACHINE_LEVEL = REQUEST_MAIN_POWER - 1, /*!< Retourne le niveau des produits dans la machine.*/
    REQUEST_FW_VERSION = REQUEST_MACHINE_LEVEL - 1, /*!<Retourne la version du satellite.*/

} __attribute__((packed)) EHEADER;

/*Variables********************************************************************/

/**
 * \var BYTE bySatBuffer[16];
 * \brief Buffer utilis� dans les communications avec les satellites.
 */
BYTE bySatBuffer[16];

//*Prototypes*******************************************************************

/**
 * \fn wCRC16
 * \brief Calcul du CRC du buffer re�u en param�tre.
 * @param[in] byData Buffer � traiter.
 * @param[in] byLen Nombre d'octet � calculer.
 * @return CRC16 du buffer.
 */
WORD wCRC16(const BYTE *byData, const BYTE byLen);

/**
 * \fn isSendCommand
 * \brief Envoie une commande � un satellite.
 * @param[in] byNumMachine Num�ro de la machine pilot�e par le satellite destinataire.
 * @param[in] byHeader Commande
 * @param[in] byLenData Longueur des param�tres.
 * @param[in] byData Param�tres.
 */
BOOL isSendCommand(const BYTE byNumMachine, const BYTE byHeader,
                  const BYTE byLenData, const void *byData);

/**
 * \fn boReceiveAnswer
 * \brief Reception d'une r�ponse d'un satellite.
 * @param byNumMachine Num�ro de la machine qui doit r�pondre.
 * @return True si la r�ponse est coh�rente.
 */
//BOOL boReceiveAnswer(const BYTE byNumMachine);

/**
 * \fn isModifyMachineNumber
 * \brief Affecte une adresse au satellite qui sera aussi le num�ro de la machine pilot� par ce satellite.
 * Le module doit r�pondre avec sa nouvelle adresse.
 * @param[in] byOldNumMachine Num�ro � modifier.
 * @param[in] byNewNumMachine Num�ro � affecter
 * @return TRUE si le num�ro est accept� par le module.
 */
BOOL isModifyMachineNumber(const BYTE byOldNumMachine, BYTE byNewNumMachine);

/**
 * \fn isSimplePoll
 * \brief V�rifie la communication entre la CPU et un satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \return TRUE si la communication s'effectue correctement.
 */
BOOL isSimplePoll(const BYTE byNumMachine);

/**
 * \fn isMainPresent
 * \brief V�rifie la pr�sence du secteur sur le satellite.
 * @param param[in] byNumMachine Adresse du satellite.
 * @return TRUE si le secteur est pr�sent sur le satellite.
 */
BOOL isMainPresent(const BYTE byNumMachine);

/**
 * \fn isModifyMachineRelayState
 * \brief Active ou desactive le relais du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] relayState Etat que devra prendre le relais.
 * \return TRUE si la commande s'est effectu�e correctement.
 */
BOOL isModifyMachineRelayState(const BYTE byNumMachine, const ESTATE relayState);

/**
 * \fn isExModifyMachineRelayState
 * \brief Active le relais du satellite pendant un temps d�termin�.
 * @param[in] byNumMachine Adresse du satellite.
 * @param[in] dwDelayActivation Temps pendant lequel sera activ� le relais sur le satellite.
 * @return TRUE si la commande s'est effectu�e correctement.
 */
BOOL isExModifyMachineRelayState(const BYTE byNumMachine, const DWORD dwDelayActivation);

/**
 * \fn getMachineRelayState
 * \brief Demande l'�tat du relais du satellite adress�.
 * \param[in] byNumMachine Adresse du satellite.
 * \return RELAY_ON si le relais est activ�. Dans le cas o� la communication est d�faillante la fonction retournera RELAY_OFF.
 */
ESTATE getMachineRelayState(const BYTE byNumMachine);

/**
 * \fn getMachineState
 * \brief Demande l'�tat de la machine adress�e.
 * \param[in] byNumMachine Adresse du satellite.
 * @return MACHINE_BUSY si la machine est occup�e ou si la communication ne fonctionne pas.
 */
ESTATUS getMachineState(const BYTE byNumMachine);

/**
 * \fn isSetMainPowerState
 * \brief Active ou desactive le relais d'alimentation principale de la machine.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] relayState Etat que devra prendre le relais.
 * \return TRUE si la commande s'est effectu�e correctement.
 */
BOOL isSetMainPowerState(const BYTE byNumMachine, const ESTATE relayState);

/**
 * \fn isSetOverBusyDelay
 * \brief Defini le temps de surouccpation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] dwOverBusyDelay Temps de suroccupation en milliseconde.
 * \return TRUE si l'op�ration s'est d�roul�e correctement.
 */
BOOL isSetOverBusyDelay(const BYTE byNumMachine, DWORD dwOverBusyDelay);

/**
 * \fn isSetSensibility
 * \brief Defini la sensibilit� � la consommation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] wSensibility Niveau de sensibilit�.
 * \return TRUE si l'op�ration s'est d�roul�e correctement.
 */
BOOL isSetSensibility(const BYTE byNumMachine, WORD wSensibility);

/**
 * \fn dwGetOverBusyDelay
 * \brief Demande le temps de suroccupation du satellite adress�.
 * \param[in] byNumMachine Adresse du satellite.
 * @return Le temps de suroccupation du satellite. 65535 si la communication ne fonctionne pas.
 */
DWORD dwGetOverBusyDelay(const BYTE byNumMachine);

/**
 * \fn getMachineFull
 * \brief Demande au satellite si le niveau n'est pas vide.
 * \detail Peut-�tre utile pour un distributeur.
 * \param[in] byNumMachine Adresse du satellite.
 * @return NOTEMPTY si la machine n'est occup�e ou si la communication ne fonctionne pas. EMPTY dans les autres cas.
 */
ELEVEL getMachineFull(const BYTE byNumMachine);

/**
 * \fn wGetSatelliteFWVersion
 * \brief Renvoi le num�ro de la version du FW du satellite.
 * @param byNumMachine Num�ro de la machine g�rer par le satellite utilis�.
 * @return Le num�ro de la r�vision FW du satellite concern�.
 */
WORD wGetSatelliteFWVersion(const BYTE byNumMachine);

/******************************************************************************/
#endif	/* SATELLITES_H */

