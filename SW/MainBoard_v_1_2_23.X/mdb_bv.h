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

/**
 * \def TIME_RESET_BV
 * \brief D�lai pour l'initialisation du lecteur de bille.
 */
#define TIME_RESET_BV (10 * SECONDE)

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

typedef struct __attribute__((packed))
{
    BYTE ManufacturerCode[3];
    BYTE SerialNumber[12];
    BYTE Revision[12];
    BYTE VersionSoft[2];
    //BYTE Options[4];
}
EXID;

typedef enum
{
    OUT = 0,
    IN = 1,
} __attribute__((packed)) ESCROWDIR;

BYTE byStacker[2];

BillValidatorConfig billValidatorConfig;

/**
 * \brief Montant ins�r� dans le lecteur de billet
 */
long lAmountBV;

BOOL isBillValidatorReseted;

/**
 * brief Indique que la phase d'initialisation du monnayeur est effectu�e.
 */
BOOL isBillValidatorInitialized;

/**
 * \brief Indique si le lecteur de billet a �t� poll�.
 */
BOOL isBVPolled;

EXID exId;

/**
 * @fn isGetMDBStackerStatus
 * @param wStacker variable contenant le nombre de biller et si le stacker est plein
 * @return true si l'op�ration s'est d�roul� correctement.
 */
BOOL isGetMDBStackerStatus(BYTE *wStacker);

/**
 * \fn isEnableBillValidator
 * \brief Active ou desactive le lecteur de  billets.
 * \param[in] isEnable Indique si le lecteur de  billets doit �tre activ� ou non.
 * \param[in] billType Param�trage d'acceptation des billets de la centrale.
 * \param[in] isEscrow Indique si l'escrow doit �tre activ�.
 * \return FALSE si l'op�ration ne s'est pas d�roul�e correctement ou si le rendeur n'est pas initialis�.
 */
BOOL isEnableBillValidator(const BOOL isEnable, const BOOL isEscrow, BillType *billType);

BOOL isGetExId(EXID *exId);

#endif	/* MDB_BV_H */
