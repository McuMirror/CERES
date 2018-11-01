/*
 * File:   MDB.h
 * Author: RA
 *
 * Created on 2 décembre 2013, 11:49
 */

#ifndef MDB_H
#define	MDB_H

#include <plib.h>
#include "FreeRTOS.h"
#include "timers.h"
#include "RAdefine.h"
#include "TCPIP Stack/Delay.h"
#include "UARTLib.h"
#include "global.h"

/**
 * \def MAXCASHCHANNELS
 * \brief Nombre maximum de canaux pour le changer et le lecteur de billet
 */
#define MAXCASHCHANNELS 16

/**
 * \def MDB_TO
 * \brief delay mamixmum de réponse du CL
 */
#define MDB_TO 100 * MILLISEC

/**
 * \def BAUDRATE
 \brief Vitesse de transmission sériel.
 */
#define BAUDRATE 9600

/**
 * \def MDBPOLLINMS
 * \brief temps de polling en ms du lecteur cashless.
 */
#define MDBPOLLINMS (200 * MILLISEC)

/**
 * \def MDBRETRY
 * \brief Nombre de loop avant de vérifier si un périphérique est disponible
 */
#define MDBRETRY ((60 * SECONDE) / MDBPOLLINMS)

//Réponses
#define ACK 0x00 /*!< Réponse OK. */
#define RET 0xAA, /*!< Retransmettre les données. */
#define NAK 0XFF /*!< Réponse incorrecte. */

//Réponses POLL
#define RSP_NAK                     0xFF
#define RSP_RET                     0xAA
#define RSP_JUST_RESET              0x00
#define RSP_READER_CONFIG_DATA      0x01
#define RSP_DISPLAY_REQUEST         0x02
#define RSP_BEGIN_SESSION           0x03
#define RSP_SESSION_CANCEL_REQUEST  0x04
#define RSP_VEND_APPROVED           0x05
#define RSP_VEND_DENIED             0x06
#define RSP_END_SESSION             0x07
#define RSP_CANCELLED               0x08
#define RSP_PERIPHERAL_ID           0x09
#define RSP_MALFUNCTION_ERROR       0x0A
#define RSP_CMD_OUT_OF_SEQUENCE     0x0B
#define RSP_BUSY                    0x0C
#define RSP_REVALUE_APPROVED        0x0D
#define RSP_REVALUE_DENIED          0x0E
#define RSP_REVALUE_LIMIT_AMOUNT    0x0F
#define RSP_USER_FILE_DATA          0x10
#define RSP_TIME_DATE_REQUEST       0x11
#define RSP_DATA_ENTRY_REQUEST      0x12
#define RSP_DATA_ENTRY_CANCEL       0x13
#define RSP_FTL_REQ_TO_RCV          0x1B
#define RSP_FTL_RETRY_DENY          0x1C
#define RSP_FTL_SEND_BLOCK          0x1D
#define RSP_FTL_OK_TO_SEND          0x1E
#define RSP_FTL_REQ_TO_SEND         0x1F
#define RSP_DIAGNOSTIC_RESPONSE     0xFF

// Commandes MDB.
#define CMD_RESET                   0x00 /*!< Reset le périphérique. */
#define CMD_SETUP                   0x01 /*!< Lecture des paramètres du périphérique. */
#define CMD_STATUS                  0x01 /*!< Lecture des paramètres du périphérique. */
#define CMD_POLL                    0x02 /*!< Obtient les informations du périphérique. */
#define CMD_TUBE_STATUS             0x02
#define CMD_SECURITY                0x02
#define CMD_VEND                    0x03 /*!< Demande d'approbation d'une vente. */
#define CMD_CHANGER_POLL            0x03 /*!< Demande d'approbation d'une vente. */
#define CMD_BILL_POLL               0x03
#define CMD_READER                  0x04 /*!< Active desactive le lecteur. */
#define CMD_COIN_TYPE               0x04
#define CMD_BILL_TYPE               0x04
#define CMD_REVALUE                 0x05 /*!< Réevaluation de la clé. */
#define CMD_ESCROW                  0x05 /*!< Encaisse le billet*/
#define CMD_DISPENSE                0x05
#define CMD_STACKER                 0x06
#define CMD_EXPANSION               0x07 /*!< Commandes étendues. Voir la documentation MDB. */
#define CMD_NO_PENDING              0xFF

// MDB sous commandes.
#define SUB_CONFIG_DATA             0x00
#define SUB_MAX_MIN_PRICE 0x01
#define SUB_VEND_REQUEST 0x00
#define SUB_VEND_CANCEL 0x01
#define SUB_VEND_SUCCESS 0x02
#define SUB_VEND_FAILURE 0x03
#define SUB_VEND_SESSION_COMPLETE 0x04
#define SUB_VEND_CASH_SALE 0x05
#define SUB_NEGATIVE_VEND_REQUEST 0x06
#define SUB_READER_DISABLE 0x00
#define SUB_READER_ENABLE 0x01
#define SUB_READER_CANCEL 0x02
#define SUB_REVALUE_REQUEST 0x00
#define SUB_REVALUE_LIMIT_REQUEST 0x01
#define SUB_REQUEST_ID 0x00
#define SUB_READ_USER_FILE 0x01
#define SUB_WRITE_USER_FILE 0x02
#define SUB_WRITE_TIME_DATE 0x03
#define SUB_CHANGER_IDENTIFICATION 0x00
#define SUB_FEATURE_ENABLE 0x01
#define SUB_ALTERNATIVE_PAYOUT 0x02
#define SUB_ALT_PAYOUT_STATUS 0x03
#define SUB_PAYOUT_VALUE_POLL 0x04
#define SUB_DIAGNOSTIC_STATUS 0x05
#define SUB_MANUAL_FILL_REPORT 0x06
#define SUB_MANUAL_PAYOUT_REPORT 0x07
#define SUB_IDENTIFICATION 0x00
#define SUB_IDENTIFICATION_2 0x02
#define SUB_READER_FEATURE_ENABLE 0x04
#define SUB_CHANGER_FEATURE_ENABLE 0x01
#define SUB_BILL_FEATURE_ENABLE 0x01
#define SUB_FTL_REQ_TO_RCV 0xFA
#define SUB_FTL_RETRY_DENY 0xFB
#define SUB_FTL_SEND_BLOCK 0xFC
#define SUB_FTL_OK_TO_SEND 0xFD
#define SUB_FTL_REQ_TO_SEND 0xFE
#define SUB_DIAGNOSTICS 0xFF

//Structures

typedef struct __attribute__((packed))
{
    BYTE byCmd;
    BYTE byLevel; /*!< Niveau de la vmc.*/
    BYTE byDisplayColumns; /*!< Nombre de caractères par ligne.*/
    BYTE byDisplayRows; /*!< Nombre de ligne.*/
    BYTE byDisplayInfo; /*!< Information concernant les données de configuration du cashless.*/
}
VMCConfig;

typedef struct __attribute__((packed))
{
    BYTE byLevel; /*!< Niveau MDB du périphérique.*/
    BYTE byCountryCode[2]; /*!< Currency code. Cf l'appendix 1 de la documentation MDB. */
    BYTE byScaleFactor; /*!< Facteur de multiplication appliqué à tous les montants du périphérique.*/
    BYTE byDecimalPlace; /*!< Position de la virgule en partant du chiffre le moins significatif. */
}MDBGenericDeviceConfig;


/******************************************************************************/

/**
 * \var isMDBPolled
 * \brief Indique si la chaine MDB est pollée.
 */
BOOL isMDBPolled;

/**
 \brief Indique le TO pour la réponse du périphérique MDB est atteint.
 */
BOOL isNAKMDB;

/**
 *\brief Handle du timer utilisé pour le TO de la réponse d'un périphérique MDB.
 */
TimerHandle_t xTimerMDBNAK;

/**
 \brief Port MDB
 */
UART_MODULE MDBUART;

/**
 * \brief Montant maximum pouvant être contenu dans une clé.
 */
WORD wKeyAmountMax;

VMCConfig vmcConfig;

/**
 * \var semaphoreChange
 * \brief Indique la demande de change
 */
SemaphoreHandle_t hSemaphoreChange;

/**
 * \var hSemaphoreMDB
 * \brief handle du semaphore MDB.
 */
SemaphoreHandle_t hSemaphoreMDB;

/******************************************************************************/

/**
 * \brief Envoie une instruction MDB au périphérique.
 * \param[in] byAddress Adresse du périphérique.
 * \param[in] byCommand Commande.
 * \param[in] byLenParameters Longueur des paramètres.
 * \param[in] ptrParameters Pointeur sur le buffer des paramètres.
 * \param[out] ptrAnswer Pointeur sur le buffer qui contiendra la réponse le cas échéant.
 * \return La longeur de la réponse.
 */
BYTE byMDBSendCommand(const BYTE byAddress, const BYTE byCommand,
                      BYTE byLenParameters, void *ptrParameters, void *ptrAnswer);

/**
 * \brief Self-reset the device.
 * \param[in] byDeviceAddress Adresse du périphérique à reseter.
 */
BOOL isMDBReset(const BYTE byDeviceAddress);

/**
 * \brief Fonction utilisée pour obtenir des informations sur le périphérique.
 * \param[in] byDeviceAddress Adresse du périphérique.
 * \param[out] byResponse Pointeur sur le buffer qui contiendra la réponse.
 * \return la longueur de la réponse.
 */
BYTE byMDBPoll(const BYTE byDeviceAddress, BYTE *byResponse);

/**
 * \brief Envoi un ACK ou un NAK à partir de la VMC.
 * \param[in] byAcknowledge ACK ou NAK
 */
void vVMCAcknowledge(const BYTE byAcknowledge);

/**
 * \brief Fonction d'intialisation du port MDB.
 */
void InitMDB(const UART_MODULE uart);

BOOL isMDBSetupConfig(const BYTE byDeviceAddress, void *byStatus, const BYTE byLen);

WORD wDecimalDivider(BYTE byDecimal);

/******************************************************************************/

#endif	/* MDB_H */

