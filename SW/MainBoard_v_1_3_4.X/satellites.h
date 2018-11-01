
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
#define HOST 0X01 /*!< Num�ro de la machine dans une transmission.*/

/**
 * \brief Delai accord� au satelltite pour fournir une r�ponse.
 */
#define SAT_TO (1 * SECONDE)
/*End of macros****************************************************************/

/*Enumerations*****************************************************************/

/**
 * \brief R�ponse des satellites.
 */
enum ERSP_SAT
{
    MDI_ACK = 0, /*!< Instruction re�u correctement.*/
    MDI_NACK = 5, /*!< Instruction erron�e.*/
    MDI_BUSY = 6, /*!< Impossible de r�pondre pour cause d'occupation.*/
};

/*End of enumerations**********************************************************/

/*Typedef**********************************************************************/

/**
 * \brief Type enumeration des �tats d'occupation des machines
 */
typedef enum
{
    MACHINE_FREE = 0, /*!< Machine inoccup�e. */
    MACHINE_BUSY = 1, /*!< Machine occup�e.*/
} ESTATUS;

/**
 * \brief Type indiquant un relai activ� ou non.
 */
typedef enum
{
    RELAY_OFF = 0, /*!<Le relay est desactiv�.*/
    RELAY_ON = 1, /*!<Le relay est activ�.*/
} ESTATE;

/**
 * \brief Type enumeration de la pr�sence secteur.
 */
typedef enum
{
    ABSENT = 0, /*!<Courant secteur absent.*/
    PRESENT = 1, /*!<Courant secteur pr�sent.*/
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
 * \brief Enumeration des commandes pouvant �tre envoy�es aux satellites.
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

} EHEADER;
/*End Typedef******************************************************************/

/*Variables********************************************************************/

/**
 * \var BYTE bySatBuffer[16];
 * \brief Buffer utilis� dans les communications avec les satellites.
 */
BYTE bySatBuffer[16];
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * \brief Affecte une adresse au satellite qui sera aussi le num�ro de la machine pilot� par ce satellite.
 * Le module doit r�pondre avec sa nouvelle adresse.
 * \param[in] byOldNumMachine Num�ro � modifier.
 * \param[in] byNewNumMachine Num�ro � affecter
 * @return TRUE si le num�ro est accept� par le module.
 */
BOOL isModifyMachineNumber(const BYTE byOldNumMachine, BYTE byNewNumMachine);

/**
 * \brief V�rifie la communication entre la CPU et un satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \return TRUE si la communication s'effectue correctement.
 */
BOOL isSimplePoll(const BYTE byNumMachine);

/**
 * \brief V�rifie la pr�sence du secteur sur le satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * @return TRUE si le secteur est pr�sent sur le satellite.
 */
BOOL isMainPresent(const BYTE byNumMachine);

/**
 * \brief Active ou desactive le relais du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] relayState Etat que devra prendre le relais.
 * \return TRUE si la commande s'est effectu�e correctement.
 */
BOOL isModifyMachineRelayState(const BYTE byNumMachine, const ESTATE relayState);

/**
 * \brief Active le relais du satellite pendant un temps d�termin�.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] dwDelayActivation Temps pendant lequel sera activ� le relais sur le satellite.
 * @return TRUE si la commande s'est effectu�e correctement.
 */
BOOL isExModifyMachineRelayState(const BYTE byNumMachine, const DWORD dwDelayActivation);

/**
 * \brief Demande l'�tat du relais du satellite adress�.
 * \param[in] byNumMachine Adresse du satellite.
 * \return RELAY_ON si le relais est activ�. Dans le cas o� la communication est d�faillante la fonction retournera RELAY_OFF.
 */
ESTATE getMachineRelayState(const BYTE byNumMachine);

/**
 * \brief Demande l'�tat de la machine adress�e.
 * \param[in] byNumMachine Adresse du satellite.
 * @return MACHINE_BUSY si la machine est occup�e ou si la communication ne fonctionne pas.
 */
ESTATUS getMachineState(const BYTE byNumMachine);

/**
 * \brief Defini le temps de surouccpation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] dwOverBusyDelay Temps de suroccupation en milliseconde.
 * \return TRUE si l'op�ration s'est d�roul�e correctement.
 */
BOOL isSetOverBusyDelay(const BYTE byNumMachine, DWORD dwOverBusyDelay);

/**
 * \brief Defini la sensibilit� � la consommation du satellite.
 * \param[in] byNumMachine Adresse du satellite.
 * \param[in] wSensibility Niveau de sensibilit�.
 * \return TRUE si l'op�ration s'est d�roul�e correctement.
 */
BOOL isSetSensibility(const BYTE byNumMachine, WORD wSensibility);

/**
 * \brief Demande au satellite si le niveau n'est pas vide.
 * \details Peut-�tre utile pour un distributeur qui contient des produits 
 * comme des cartouches de lessive.
 * \param[in] byNumMachine Adresse du satellite.
 * @return NOTEMPTY si la machine n'est occup�e ou si la communication ne fonctionne pas. EMPTY dans les autres cas.
 */
ELEVEL getMachineFull(const BYTE byNumMachine);

/**
 * \brief Renvoi le num�ro de la version du FW du satellite.
 * \param byNumMachine Num�ro de la machine g�rer par le satellite utilis�.
 * @return Le num�ro de la r�vision FW du satellite concern�.
 */
WORD wGetSatelliteFWVersion(const BYTE byNumMachine);
/*End of prototypes************************************************************/

/**@}*/
#endif	/* SATELLITES_H */

