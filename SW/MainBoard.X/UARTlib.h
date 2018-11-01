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
 * \details Le timer 3 est utilisé pour le TO des receptions séries.
 */
void InitIntTimer3(void);

/**
 * @brief Initialisation du port série.
 * @param[in] UART Port utilisé sur le PIC.
 * @param[in] dwSYS_FREQ Fréquence du microprocesseur.
 * @param[in] dwBAUDRATE Vitesse de transmission.
 * @param[in] dataSize Taille des données.
 * @param[in] parity Parité.
 * @param[in] stop_bits Nombre de bits de stop.
 */
void OpenUART(const UART_MODULE UART, const DWORD dwSYS_FREQ,
              const DWORD dwBAUDRATE, const UART_LINE_CONTROL_MODE dataSize,
              const UART_LINE_CONTROL_MODE parity,
              const UART_LINE_CONTROL_MODE stop_bits);

/**
 * @brief Lit une chaine de caractère à zéro terminal sur le port série.
 * @param[in] UART Port série concerné.
 * @param[out] pBuffer Buffer de la chaine de caractère.
 * @return Nombre de caractères lus.
 */
BYTE UARTGetS(const UART_MODULE UART, BYTE *pBuffer);

/**
 * @brief Lit un nombre fixé d'octets.
 * @param[in] UART Port série concerné.
 * @param[in] wLen Nombre d'octets à lire.
 * @param pBuffer Buffer contenant les octets lus.
 */
void UARTGetBuffer(const UART_MODULE UART, WORD wLen, BYTE *pBuffer);

/**
 * @brief Envoi un caractère sur le port série.
 * @param[in] UART Port série concerné.
 * @param cData Caractère à envoyer.
 */
void UARTWriteByte(const UART_MODULE UART, const BYTE cData);
/**
 * @brief Envoi une chaine de caractère à zéro terminal.
 * @param[in] UART Port série concerné.
 * @param[in] pBuffer
 * @return le nombre de caractères transmis.
 */
BYTE UARTWriteS(const UART_MODULE UART, const BYTE *pBuffer);

/**
 * @brief Envoi un nombre fixé d'octets sur le port série.
 * @param[in] UART Port série concerné.
 * @param[in] pBuffer Buffer contenant les octets.
 * @param[in] byLen Nombre d'octets à envoyer sur le port série.
 */
void UARTWriteBuffer(const UART_MODULE UART, const BYTE *pBuffer, BYTE byLen);

/**
 * \fn UARTGetByte
 * \brief Lit un caratcère sur le port série.
 * @param[in] UART Port série concerné.
 * @return Le caractère lu.
 */
BYTE UARTGetByte(const UART_MODULE UART);

//*Variables--------------------------------------------------------------------

/**
 * \var wTORequest
 * \brief Uitilisé pour indiquer une non réponse d'un satellite.
 */
WORD wTORequest;

/******************************************************************************/

#endif	/* UARTLIB_H */

