
/** ****************************************************************************
 * \file            I2CE2PROML.h
 * \brief			Header de la gestion de la mémoire eeprom I2C.
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef I2CE2PROML_H
#define	I2CE2PROML_H

#include <plib.h>
#include "TCPIP Stack/delay.h"

/**
 * \defgroup EEPROM_I2C Gestion de la mémoire eeprom i2c
 * @{
 */

/*Macros**********************************************************************/
/**
 * \brief Identificateur eeprom i2c pour une écriture.
 */
#define EE_ADDR 0xA0

/**
 * \brief bit indiquant que l'eeprom doit être lue.
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
 * \param[in] module Module utilisé dans la communication du port I2C.
 * \param[in] ui32Frequence Frequence de fonctionne du bus des périphériques.
 */
void InitI2CE2promL(const I2C_MODULE module, const UINT32 ui32Frequence);

/**
 * \brief Ecrit les données contenu dans un buffer dans l'eeprom.
 * \param wAddress Adresse de début des données dans l'eeprom.
 * \param data Buffer qui contient les données à écrire dans la mémoire eeprom.
 * \param size Nombre d'octets à écrire dans l'eeprom
 * @return TRUE si les données sont écrites correctement.
 */
BOOL I2CE2promLWriteBuffer(const WORD wAddress, void *data, const size_t size);

/**
 * \brief Ecrit un octet dans l'eeprom à l'adresse indiquée.
 * \param wAddress Adresse dans l'eeprom à laquelle doit être ecrit l'octet.
 * \param byData Octet à enregistrer dans l'eeprom.
 * @return
 */
BOOL I2CE2promLWriteByte(const WORD wAddress, BYTE byData);

/**
 * \brief Tansfert les données lues dans l'eeprom dans un buffer.
 * \param wAddress Adresse de début des données dans l'eeprom
 * \param data Buffer qui contiendra les données lues.
 * \param size Nombre d'octet à lire
 * @return TRUE si les données ont pu être lus.
 */
BOOL I2CE2promLReadBuffer(const WORD wAddress, void *data, const size_t size);
/*End of prototypes************************************************************/
/**@}*/
#endif	/* I2CE2PROML_H */

