/**
 * File:   RS485.h
 * Author: RA
 *
 * Created on 19 janvier 2014, 18:25
 */

#ifndef RS485_H
#define	RS485_H
#include <plib.h>
#include "UARTLib.h"
#include "satellites.h"
#include "FreeRTOS.h"
#include "RAdefine.h"

//**Variables*******************************************************************
/**
 * \var RS485port
 * \brief Port utilisé par l'io de direction du RS485
 */
IoPortId RS485port;

/**
 * \var RS485Io
 * brief IO utilisé pour la direction du 485.
 */
DWORD RS485Io;

/**
 * \var UART485
 * \brief Variable contenant le nom du module utilisé.
 */
UART_MODULE UART485;

//*Macros***********************************************************************

/**
 * \def SETREAD
 * \brief Positionne le port RS485 en mode lecture.
 */
#define SETREAD() PORTClearBits(RS485port, RS485Io)

/**
 * \def SETWRITE
 * \brief Positionne le port RS485 en mode ecriture.
 */
#define SETWRITE() PORTSetBits(RS485port, RS485Io)

//*Prototypes*******************************************************************
/**
 * \fn InitRS485
 * \brief Initialisation du port RS485
 * @param[in] UART Module UART utilisé pour la communication RS485.
 * @param[in] dwSYS_FREQ Fréquence du système.
 * @param[in] dwBAUDRATE Vitesse de communication.
 * @param[in] dataSize Nombre de bits de données.
 * @param[in] parity Type de partité.
 * @param[in] stop_bits Nombre de bit de stop.
 * @param[in] EnablePort Port de l'IO utilisé pour la direction de la transmission.
 * @param[in] dwEnableBit IO utilisé pour la direction.
 */
void InitRS485(const UART_MODULE UART, const DWORD dwSYS_FREQ,
               const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
               const UART_LINE_CONTROL_MODE parity,
               const UART_LINE_CONTROL_MODE stop_bits, const IoPortId EnablePort,
               DWORD dwEnableBit);

/**
 * \fn RS485GetBuffer
 * \brief Lit un nombre spécifié d'octet.
 * @param[in] pBuffer Buffer qui contiendra les caractères lus.
 * @param[in] wLen Nombre de caractères à lire.
 * \return TRUE si le nombre de caractères a été corretement lus sur le port.
 */
BOOL RS485GetBuffer(void *pBuffer, WORD wLen);

/**
 * \brief Transmet un nombre défini d'octet sur la ligne 485.
 * @param[in] pBuffer Buffer contenant les octets à transmettre.
 * @param[in] byLen Nombre d'octet à transmettre.
 */
void RS485WriteBuffer(const void *pBuffer, const BYTE byLen);

#endif	/* RS485_H */

