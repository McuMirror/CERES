
/** ****************************************************************************
 * \file            UARTlib.h
 * \brief			Header de la gestion des port série
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/
#ifndef __UARTISRLIB_H
#define __UARTISRLIB_H

#include <plib.h>
/**
 * \defgroup URAT Gestion des ports série
 * @{
 */
/*Variables--------------------------------------------------------------------

/**
 * \var wTORequest
 * \brief Uitilisé pour indiquer une non réponse d'un satellite.
 */
WORD wTORequest;
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * @brief Initialisation du port série.
 * \param[in] UART Port utilisé sur le PIC.
 * \param[in] dwSYS_FREQ Fréquence du microprocesseur.
 * \param[in] dwBAUDRATE Vitesse de transmission.
 * \param[in] dataSize Taille des données.
 * \param[in] parity Parité.
 * \param[in] stop_bits Nombre de bits de stop.
 */
void OpenUART(const UART_MODULE UART, const DWORD dwSYS_FREQ,
              const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
              const UART_LINE_CONTROL_MODE parity,
              const UART_LINE_CONTROL_MODE stop_bits);

/**
 * @brief Envoi un nombre fixé d'octets sur le port série.
 * \param[in] UART Port série concerné.
 * \param[in] pBuffer Buffer contenant les octets.
 * \param[in] byLen Nombre d'octets à envoyer sur le port série.
 */
void UARTWriteBuffer(const UART_MODULE UART, const BYTE *pBuffer, BYTE byLen);

/**
 * \fn UARTGetByte
 * \brief Lit un caratcère sur le port série.
 * \param[in] UART Port série concerné.
 * @return Le caractère lu.
 */
BYTE UARTGetByte(const UART_MODULE UART);
/*EndPrototypes****************************************************************/
/**@}*/
#endif	/* UARTLIB_H */

