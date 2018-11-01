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
 * \brief Identificateur eeprom i2c pour une �criture.
 */
#define EE_ADDR 0xA0

/**
 * \def EEREAD
 * \brief bit indiquant que l'eeprom doit �tre lue.
 */
#define EEREAD 0x01

/**
 * \var I2CPort
 * \brief Module du port I2C.
 */
I2C_MODULE I2CPort;

/**
 * \fn InitI2CE2promL
 * @param[in] module Module utilis� dans la communication du port I2C.
 * @param[in] ui32Frequence Frequence de fonctionne du bus des p�riph�riques.
 */
void InitI2CE2promL(const I2C_MODULE module, const UINT32 ui32Frequence);

/**
 * \fn I2CE2promLWriteBuffer
 * \brief Ecrit les donn�es contenu dans un buffer dans l'eeprom.
 * @param wAddress Adresse de d�but des donn�es dans l'eeprom.
 * @param data Buffer qui contient les donn�es � �crire dans la m�moire eeprom.
 * @param size Nombre d'octets � �crire dans l'eeprom
 * @return TRUE si les donn�es sont �crites correctement.
 */
BOOL I2CE2promLWriteBuffer(const WORD wAddress, void *data, const size_t size);

/**
 * \fn I2CE2promLWriteByte
 * \brief Ecrit un octet dans l'eeprom � l'adresse indiqu�e.
 * @param wAddress Adresse dans l'eeprom � laquelle doit �tre ecrit l'octet.
 * @param byData Octet � enregistrer dans l'eeprom.
 * @return
 */
BOOL I2CE2promLWriteByte(const WORD wAddress, BYTE byData);

/**
 * \fn I2CE2promLReadBuffer
 * \brief Tansfert les donn�es lues dans l'eeprom dans un buffer.
 * @param wAddress Adresse de d�but des donn�es dans l'eeprom
 * @param data Buffer qui contiendra les donn�es lues.
 * @param size Nombre d'octet � lire
 * @return TRUE si les donn�es ont pu �tre lus.
 */
BOOL I2CE2promLReadBuffer(const WORD wAddress, void *data, const size_t size);

#endif	/* I2CE2PROML_H */

