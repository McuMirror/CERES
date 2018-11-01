
/** ****************************************************************************
 * \file            UARTlib.h
 * \brief			Header de la gestion des port s�rie
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 ******************************************************************************/
#ifndef __UARTISRLIB_H
#define __UARTISRLIB_H

#include <plib.h>
/**
 * \defgroup URAT Gestion des ports s�rie
 * @{
 */
/*Variables--------------------------------------------------------------------

/**
 * \var wTORequest
 * \brief Uitilis� pour indiquer une non r�ponse d'un satellite.
 */
WORD wTORequest;
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/

/**
 * @brief Initialisation du port s�rie.
 * \param[in] UART Port utilis� sur le PIC.
 * \param[in] dwSYS_FREQ Fr�quence du microprocesseur.
 * \param[in] dwBAUDRATE Vitesse de transmission.
 * \param[in] dataSize Taille des donn�es.
 * \param[in] parity Parit�.
 * \param[in] stop_bits Nombre de bits de stop.
 */
void OpenUART(const UART_MODULE UART, const DWORD dwSYS_FREQ,
              const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
              const UART_LINE_CONTROL_MODE parity,
              const UART_LINE_CONTROL_MODE stop_bits);

/**
 * @brief Envoi un nombre fix� d'octets sur le port s�rie.
 * \param[in] UART Port s�rie concern�.
 * \param[in] pBuffer Buffer contenant les octets.
 * \param[in] byLen Nombre d'octets � envoyer sur le port s�rie.
 */
void UARTWriteBuffer(const UART_MODULE UART, const BYTE *pBuffer, BYTE byLen);

/**
 * \fn UARTGetByte
 * \brief Lit un caratc�re sur le port s�rie.
 * \param[in] UART Port s�rie concern�.
 * @return Le caract�re lu.
 */
BYTE UARTGetByte(const UART_MODULE UART);
/*EndPrototypes****************************************************************/
/**@}*/
#endif	/* UARTLIB_H */

