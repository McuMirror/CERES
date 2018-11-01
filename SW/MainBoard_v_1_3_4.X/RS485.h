
/** ****************************************************************************
 * \file            RS485.h                                                 
 * \brief			Header de la gestion des parametres du port RS485
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/

#ifndef RS485_H
#define	RS485_H

#include "UARTLib.h"
#include "FreeRTOS.h"
#include "RAdefine.h"

/**
 * \defgroup RS485 Gestion du port RS485
 * @{
 */

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
/*End of macros****************************************************************/

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
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/
/**
 * \fn InitRS485
 * \brief Initialisation du port RS485
 * \param[in] UART Module UART utilis� pour la communication RS485.
 * \param[in] dwSYS_FREQ Fr�quence du syst�me.
 * \param[in] dwBAUDRATE Vitesse de communication.
 * \param[in] dataSize Nombre de bits de donn�es.
 * \param[in] parity Type de partit�.
 * \param[in] stop_bits Nombre de bit de stop.
 * \param[in] EnablePort Port de l'IO utilis� pour la direction de la transmission.
 * \param[in] dwEnableBit IO utilis� pour la direction.
 */
void InitRS485(const UART_MODULE UART, const DWORD dwSYS_FREQ,
               const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
               const UART_LINE_CONTROL_MODE parity,
               const UART_LINE_CONTROL_MODE stop_bits, const IoPortId EnablePort,
               DWORD dwEnableBit);

/**
 * \fn RS485GetBuffer
 * \brief Lit un nombre sp�cifi� d'octet.
 * \param[in] pBuffer Buffer qui contiendra les caract�res lus.
 * \param[in] wLen Nombre de caract�res � lire.
 * \return TRUE si le nombre de caract�res a �t� corretement lus sur le port.
 */
BOOL RS485GetBuffer(void *pBuffer, WORD wLen);

/**
 * \brief Transmet un nombre d�fini d'octet sur la ligne 485.
 * \param[in] pBuffer Buffer contenant les octets � transmettre.
 * \param[in] byLen Nombre d'octet � transmettre.
 */
void RS485WriteBuffer(const void *pBuffer, const BYTE byLen);
/*End of prototypes************************************************************/
/**@}*/
#endif	/* RS485_H */

