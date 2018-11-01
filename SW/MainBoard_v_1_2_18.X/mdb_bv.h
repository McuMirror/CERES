/* 
 * File:   mdb_bv.h
 * Author: RA
 *
 * Created on 21 janvier 2014, 20:01
 */

#ifndef MDB_BV_H
#define	MDB_BV_H

#include "MDB.h"

#define BVADDRESS 0X30

#define JUST_RESET_BV 0b00000110
#define BV_DISABLED 0b00001001

/**
 * \def MAXNUMBERCHANNELSBV
 * \brief Nombre de canaux pour le changer
 */
#define MAXNUMBERCHANNELSBV 16

typedef struct __attribute__((packed))
{
    BYTE byLevel;
    BYTE byCountryCode[2];
    WORD wScaleFactor;
    BYTE byDecimalPlace;
    WORD wStacker;
    BYTE bySecurity[2];
    BYTE byEscrow;
    BYTE byBillValue[MAXNUMBERCHANNELSBV];
}
BillValidatorConfig;

typedef struct __attribute__((packed))
{
    union
    {
        BYTE byBillEnable[2];
        WORD wBillEnable;
    };
    union
    {
        BYTE byBillEscrow[2];
        WORD wBillEscrow;
    };
}
BillType;

typedef enum
{
    OUT = 0,
    IN = 1,
} __attribute__((packed)) ESCROWDIR;

BYTE byStacker[2];

BillValidatorConfig billValidatorConfig;

/**
 * \brief Montant inséré dans le lecteur de billet
 */
long lAmountBV;

BOOL isBillValidatorReseted;

BOOL isSetMDBillType(BillType *billType);

BOOL isGetMDBStackerStatus(BYTE *wStacker);

/**
 * \fn isEnableBillValidator
 * \brief Active ou desactive le lecteur de  billets.
 * \param[in] isEnable Indique si le lecteur de  billets doit être activé ou non.
 * \param[in] billType Paramètrage d'acceptation des billets de la centrale.
 * \param[in] isEscrow Indique si l'escrow doit être activé.
 * \return FALSE si l'opération ne s'est pas déroulée correctement ou si le rendeur n'est pas initialisé.
 */
BOOL isEnableBillValidator(const BOOL isEnable, const BOOL isEscrow, BillType *billType);

#endif	/* MDB_BV_H */

