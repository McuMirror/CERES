/*
 * File:   code.h
 * Author: Administrateur
 *
 * Created on 16 août 2014, 15:07
 */

#ifndef CODE_H
#define	CODE_H

  #include <plib.h>
  #include "I2CE2PROML.h"

/**
 * \def SIZECODE
 * \brief Nombre d'octet des codes.
 */
  #define SIZECODE 6

typedef BYTE CODE[SIZECODE];

CODE codeCredit;
CODE codeInter;

/**
 * \fn vCreateCode
 * \brief
 * @param wAddress
 * @param ptrCode
 */
void vCreateCode(const WORD wAddress, void *ptrCode);

#endif	/* CODE_H */

