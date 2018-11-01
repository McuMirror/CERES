
/** ****************************************************************************
 * \file            I2CE2PROML.h
 * \brief			Header de la gestion de la m�moire eeprom I2C.
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef I2CE2PROML_H
#define	I2CE2PROML_H

#include <plib.h>
#include "TCPIP Stack/delay.h"

/**
 * \defgroup EEPROM_I2C Gestion de la m�moire eeprom i2c
 * @{
 */

/*Macros**********************************************************************/
/**
 * \brief Identificateur eeprom i2c pour une �criture.
 */
#define EE_ADDR 0xA0

/**
 * \brief bit indiquant que l'eeprom doit �tre lue.
 */
#define EEREAD 0x01
/*End of macros***************************************************************/

/*Variables********************************************************************/
/**
 * \var I2CPort
 * \brief Module du port I2C.
 */
I2C_MODULE I2CPort;
/*End of variables*************************************************************/

/*Prototypes*******************************************************************/
/**
 * \param[in] module Module utilis� dans la communication du port I2C.
 * \param[in] ui32Frequence Frequence de fonctionne du bus des p�riph�riques.
 */
void InitI2CE2promL(const I2C_MODULE module, const UINT32 ui32Frequence);

/**
 * \brief Ecrit les donn�es contenu dans un buffer dans l'eeprom.
 * \param wAddress Adresse de d�but des donn�es dans l'eeprom.
 * \param data Buffer qui contient les donn�es � �crire dans la m�moire eeprom.
 * \param size Nombre d'octets � �crire dans l'eeprom
 * @return TRUE si les donn�es sont �crites correctement.
 */
BOOL I2CE2promLWriteBuffer(const WORD wAddress, void *data, const size_t size);

/**
 * \brief Ecrit un octet dans l'eeprom � l'adresse indiqu�e.
 * \param wAddress Adresse dans l'eeprom � laquelle doit �tre ecrit l'octet.
 * \param byData Octet � enregistrer dans l'eeprom.
 * @return
 */
BOOL I2CE2promLWriteByte(const WORD wAddress, BYTE byData);

/**
 * \brief Tansfert les donn�es lues dans l'eeprom dans un buffer.
 * \param wAddress Adresse de d�but des donn�es dans l'eeprom
 * \param data Buffer qui contiendra les donn�es lues.
 * \param size Nombre d'octet � lire
 * @return TRUE si les donn�es ont pu �tre lus.
 */
BOOL I2CE2promLReadBuffer(const WORD wAddress, void *data, const size_t size);
/*End of prototypes************************************************************/
/**@}*/
#endif	/* I2CE2PROML_H */

