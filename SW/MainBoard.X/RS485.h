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
 * \brief Port utilis� par l'io de direction du RS485
 */
IoPortId RS485port;

/**
 * \var RS485Io
 * brief IO utilis� pour la direction du 485.
 */
DWORD RS485Io;

/**
 * \var UART485
 * \brief Variable contenant le nom du module utilis�.
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
 * @param[in] UART Module UART utilis� pour la communication RS485.
 * @param[in] dwSYS_FREQ Fr�quence du syst�me.
 * @param[in] dwBAUDRATE Vitesse de communication.
 * @param[in] dataSize Nombre de bits de donn�es.
 * @param[in] parity Type de partit�.
 * @param[in] stop_bits Nombre de bit de stop.
 * @param[in] EnablePort Port de l'IO utilis� pour la direction de la transmission.
 * @param[in] dwEnableBit IO utilis� pour la direction.
 */
void InitRS485(const UART_MODULE UART, const DWORD dwSYS_FREQ,
               const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
               const UART_LINE_CONTROL_MODE parity,
               const UART_LINE_CONTROL_MODE stop_bits, const IoPortId EnablePort,
               DWORD dwEnableBit);

/**
 * \fn RS485GetS
 * \brief Lit une chaine de cartact�res sur le port RS485
 * @param pBuffer Buffer qui contiendra la chaine de cartact�res re�ue.
 * @return Le nombre de caract�re de la chaine.
 */
BYTE RS485GetS(BYTE pBuffer[]);

/**
 * \fn RS485GetBuffer
 * \brief Lit un nombre sp�cifi� d'octet.
 * @param[in] pBuffer Buffer qui contiendra les caract�res lus.
 * @param[in] wLen Nombre de caract�res � lire.
 * \return TRUE si le nombre de caract�res a �t� corretement lus sur le port.
 */
BOOL RS485GetBuffer(void *pBuffer, WORD wLen);

/**
 * \fn RS485WriteS
 * \brief Transmet une chaine de caract�res sur la ligne 485.
 * @param[in] pBuffer Buffer contenant la chaine de caract�re � transmettre.
 * @return Le nombre de byte r�ellement transmis.
 */
BYTE RS485WriteS(const BYTE *pBuffer);

/**
 * \brief Transmet un nombre d�fini d'octet sur la ligne 485.
 * @param[in] pBuffer Buffer contenant les octets � transmettre.
 * @param[in] byLen Nombre d'octet � transmettre.
 */
void RS485WriteBuffer(const void *pBuffer, const BYTE byLen);

/**
 * \fn RS485WriteByte
 * \brief Transmet un octet sur la ligne 485.
 * @param[in] cData Octet � tranmettre.
 */
void RS485WriteByte(const BYTE cData);

/**
 * \fn RS485GetByte
 * \brief Attend un caract�re sur la ligne 485.
 * @return Le caract�re lu.
 */
BYTE RS485GetByte(void);

#endif	/* RS485_H */

