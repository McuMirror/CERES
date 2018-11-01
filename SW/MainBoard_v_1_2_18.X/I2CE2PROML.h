/* 
 * File:   I2CE2PROML.h
 * Author: RA
 *
 * Created on 15 janvier 2014, 04:35
 */

#ifndef I2CE2PROML_H
#define	I2CE2PROML_H

#include <plib.h>
#include "TCPIP Stack/delay.h"

/**
 * \def EE_ADDR
 * \brief Identificateur eeprom i2c pour une écriture.
 */
#define EE_ADDR 0xA0

/**
 * \def EEREAD
 * \brief bit indiquant que l'eeprom doit être lue.
 */
#define EEREAD 0x01

/**
 * \var I2CPort
 * \brief Module du port I2C.
 */
I2C_MODULE I2CPort;

/**
 * \fn InitI2CE2promL
 * @param[in] module Module utilisé dans la communication du port I2C.
 * @param[in] ui32Frequence Frequence de fonctionne du bus des périphériques.
 */
void InitI2CE2promL(const I2C_MODULE module, const UINT32 ui32Frequence);

/**
 * \fn I2CE2promLWriteBuffer
 * \brief Ecrit les données contenu dans un buffer dans l'eeprom.
 * @param wAddress Adresse de début des données dans l'eeprom.
 * @param data Buffer qui contient les données à écrire dans la mémoire eeprom.
 * @param size Nombre d'octets à écrire dans l'eeprom
 * @return TRUE si les données sont écrites correctement.
 */
BOOL I2CE2promLWriteBuffer(const WORD wAddress, void *data, const size_t size);

/**
 * \fn I2CE2promLWriteByte
 * \brief Ecrit un octet dans l'eeprom à l'adresse indiquée.
 * @param wAddress Adresse dans l'eeprom à laquelle doit être ecrit l'octet.
 * @param byData Octet à enregistrer dans l'eeprom.
 * @return
 */
BOOL I2CE2promLWriteByte(const WORD wAddress, BYTE byData);

/**
 * \fn I2CE2promLReadBuffer
 * \brief Tansfert les données lues dans l'eeprom dans un buffer.
 * @param wAddress Adresse de début des données dans l'eeprom
 * @param data Buffer qui contiendra les données lues.
 * @param size Nombre d'octet à lire
 * @return TRUE si les données ont pu être lus.
 */
BOOL I2CE2promLReadBuffer(const WORD wAddress, void *data, const size_t size);

/**
 * \fn isI2CE2promLReadByte
 * \brief Copie l'octet lu à l'adresse wAddress dans l'eeprom dans l'adresse pointée par le paramètre byData
 * @param wAddress Adresse de lecture.
 * @param byData Pointeur qui contient l'adresse de la variable dans laquelle sera transféré l'octet.
 * @return True si la lecture s'est effectuée correctement.
 */
BOOL isI2CE2promLReadByte(const WORD wAddress, BYTE *byData);

/**
 * \fn isSendByteToE2promL
 * \brief Ecrit un octet dans l'eeprom à l'adresse courante.
 * @param byData Octet à écrire.
 * @return True si l'opération s'est effectuée correctement.
 */
BOOL isSendByteToE2promL(BYTE byData);

/**
 * \fn SetE2promAddress
 * \brief Positionne l'adresse de l'eeprom.
 * @param wAddress Adresse dans la l'eeprom.
 * @return True si l'opération s'est effectuée.
 */
BOOL SetE2promAddress(WORD wAddress);

#endif	/* I2CE2PROML_H */

