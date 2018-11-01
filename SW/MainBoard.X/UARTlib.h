/* 
 * File:   UARTLib.h
 * Author: RA
 *
 * Created on 18 janvier 2014, 13:12
 */
#ifndef __UARTISRLIB_H
    #define __UARTISRLIB_H

    #include <plib.h>

//*Prototypes*******************************************************************

/**
 * \fn InitIntTimer3
 * \brief Initialise l'interruption du timer 3
 * \details Le timer 3 est utilis� pour le TO des receptions s�ries.
 */
void InitIntTimer3(void);

/**
 * @brief Initialisation du port s�rie.
 * @param[in] UART Port utilis� sur le PIC.
 * @param[in] dwSYS_FREQ Fr�quence du microprocesseur.
 * @param[in] dwBAUDRATE Vitesse de transmission.
 * @param[in] dataSize Taille des donn�es.
 * @param[in] parity Parit�.
 * @param[in] stop_bits Nombre de bits de stop.
 */
void OpenUART(const UART_MODULE UART, const DWORD dwSYS_FREQ,
              const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
              const UART_LINE_CONTROL_MODE parity,
              const UART_LINE_CONTROL_MODE stop_bits);

/**
 * @brief Lit une chaine de caract�re � z�ro terminal sur le port s�rie.
 * @param[in] UART Port s�rie concern�.
 * @param[out] pBuffer Buffer de la chaine de caract�re.
 * @return Nombre de caract�res lus.
 */
BYTE UARTGetS(const UART_MODULE UART, BYTE *pBuffer);

/**
 * @brief Lit un nombre fix� d'octets.
 * @param[in] UART Port s�rie concern�.
 * @param[in] wLen Nombre d'octets � lire.
 * @param pBuffer Buffer contenant les octets lus.
 */
void UARTGetBuffer(const UART_MODULE UART, WORD wLen, BYTE *pBuffer);

/**
 * @brief Envoi un caract�re sur le port s�rie.
 * @param[in] UART Port s�rie concern�.
 * @param cData Caract�re � envoyer.
 */
void UARTWriteByte(const UART_MODULE UART, const BYTE cData);
/**
 * @brief Envoi une chaine de caract�re � z�ro terminal.
 * @param[in] UART Port s�rie concern�.
 * @param[in] pBuffer
 * @return le nombre de caract�res transmis.
 */
BYTE UARTWriteS(const UART_MODULE UART, const BYTE *pBuffer);

/**
 * @brief Envoi un nombre fix� d'octets sur le port s�rie.
 * @param[in] UART Port s�rie concern�.
 * @param[in] pBuffer Buffer contenant les octets.
 * @param[in] byLen Nombre d'octets � envoyer sur le port s�rie.
 */
void UARTWriteBuffer(const UART_MODULE UART, const BYTE *pBuffer, BYTE byLen);

/**
 * \fn UARTGetByte
 * \brief Lit un caratc�re sur le port s�rie.
 * @param[in] UART Port s�rie concern�.
 * @return Le caract�re lu.
 */
BYTE UARTGetByte(const UART_MODULE UART);

//*Variables--------------------------------------------------------------------

/**
 * \var wTORequest
 * \brief Uitilis� pour indiquer une non r�ponse d'un satellite.
 */
WORD wTORequest;

/******************************************************************************/

#endif	/* UARTLIB_H */

