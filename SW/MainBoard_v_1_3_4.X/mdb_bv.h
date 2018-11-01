
/** ****************************************************************************
 * \file            mdb_bv.h                                                 
 * \brief			Header de la gestion du lecteur de billets
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef MDB_BV_H
#define	MDB_BV_H

#include "MDB.h"

/**
 * \defgroup BV Gestion du lecteur de billets
 * \ingroup MDB
 * @{
 */

/*Define***********************************************************************/

/**
 * \def BVADDRESS
 * \brief Adresse du lecteur de billets 
 */
#define BVADDRESS 0X30

/**
 * \def JUST_RESET_BV
 * \brief Flag indiquant qu'un reset vient d'être effectué
 */
#define JUST_RESET_BV 0b00000110

/**
 * \def BV_DISABLED
 * \brief Flag permettant de désactiver le lecteur de billet.
 */
#define BV_DISABLED 0b00001001


/**
 * \def MAXNUMBERCHANNELSBV
 * \brief Nombre de canaux pour le lecteur de  billet
 */
#define MAXNUMBERCHANNELSBV 16

/**
 * \def TIME_RESET_BV
 * \brief Délai pour l'initialisation du lecteur de bille.
 */
#define TIME_RESET_BV (10 * SECONDE)

/*End defines******************************************************************/

/*typedef *********************************************************************/

/**
 * \brief Structure contenant les éléments de la configuration du lecteur de
 * billets
 * \details
 * SETUP 31H 27 bytes: Z1 - Z27
 * Z1 = Bill Validator Feature Level - 1 byte
 *      Indicates current feature level of the bill validator. Currently defined
 *      levels are:
 *          Level 1 - does not support option bits (Z1 = 01h)
 *          Level 2 - supports option bits (Z1 = 02h)
 * 
 * Z2 - Z3 = Country / Currency Code - 2 bytes
 *          The packed BCD country / currency code of the bill validator can be
 *          sent in two different forms depending on the value of the left most
 *          BCD digit.
 *          If the left most digit is a 0, the International Telephone Code is used
 *          to indicate the country that the validator is set-up for. For example,
 *          the USA code is 00 01H (Z2 = 00 and Z3 = 01).
 *          If the left most digit is a 1, the latest version of the ISO 4217 numeric
 *          currency code is used (see Appendix A1). For example, the code for
 *          the US dollar is 18 40H (Z2 = 18 and Z3 = 40) and for the Euro is
 *          1978 (Z2 = 19 and Z3 = 78).
 *          All new designs after July, 2000 must use the ISO 4217 numeric
 *          currency codes as listed in Appendix A1.
 *      
 * Z4 - Z5 = Bill Scaling Factor - 2 bytes
 *          All accepted bill values must be evenly divisible by this number. For
 *          example, this could be set to 0064H for the USA.
 * 
 * Z6 = Decimal Places - 1 byte
 *          Indicates the number of decimal places on a credit display. For
 *          example, this could be set to 02H for the USA.
 * 
 * Z7 - Z8 = Stacker Capacity - 2 bytes
 *          Indicates the number of bills that the stacker will hold. For example,
 *          400 bill capacity = 0190H.
 * 
 * Z9 - Z10 = Bill Security Levels - 2 bytes
 *          Indicates the security level for bill types 0 to 15. Since not all
 *          validators support multiple security levels, validators that do not have
 *          this feature must report a ?high? security level.
 * 
 * Z11 = Escrow/No Escrow - 1 byte
 *      Indicates the escrow capability of the bill validator. If Z11 = 00H, the
 *      bill validator does not have escrow capability. If Z11 = FFH, the bill
 *      validator has escrow capability.
 * 
 * Z12 - Z27 = Bill Type Credit - 16 bytes
 *          Indicates the value of the bill types 0 to 15. Values must be sent in
 *          ascending order. This number is the bill's monetary value divided by
 *          the bill scaling factor. Unused bill types are sent as 00H. Unsent bill
 *          types are assumed to be zero. FFH bills are assumed to be vend
 *          tokens.
 */
typedef struct __attribute__((packed))
{
    BYTE byLevel; /*!<Niveau MDB du lecteur de billet*/
    BYTE byCountryCode[2]; /*!<Code pays*/
    WORD wScaleFactor; /*!<Facteur multiplicateur, permettant de determiner la valeur d'un billet.*/
    BYTE byDecimalPlace; /*!<Position de la virgule.*/
    WORD wStacker; /*!<Capacité du stacker.*/
    BYTE bySecurity[2]; /*!<Niveau de discrimination des billets. 1 bit par canal.*/
    BYTE byEscrow; /*!<Indique si l'escrow est possible sur ce lecteur.*/
    BYTE byBillValue[MAXNUMBERCHANNELSBV]; /*!<Valeur de chaque billet.*/
}
BILLVALIDATORSETUP;

/**
 * \def BILLTYPE
 * \brief structure contenant les billets autorisés et les billets en escrow
 * BILL TYPE 34H 4 bytes: Y1 - Y4
 * Y1 - Y2 = Bill Enable - 2 bytes
 *          Indicates what type of bills are accepted.
 *          b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0
 *          Y1                                                   Y2
 *          Bill types are 0 to 15. A bit is set to indicate acceptance of bill type.
 * <B>NOTE:</B> Sending 0000H disables the bill validator.
 * Y3 - Y4 = Bill Escrow Enable:
 *          b15 b14 b13 b12 b11 b10 b9 b8 | b7 b6 b5 b4 b3 b2 b1 b0
 *          Y3                                                   Y4
 *          Bill types are 0 to 15. A bit is set to indicate enable of escrow for a
 *          bill type.
 * 
 * <B>NOTE:</B> On power-up or reset all bill acceptance and escrow are disabled.
 */
typedef struct __attribute__((packed)) BILLTYPE
{

    union __attribute__((packed))
    {
        WORD wBillEnable; /*!<Mot contenant les validations des billets. Chaque bit correspond à 1 canal*/
        BYTE byBillEnable[2]; /*!<Tableau contenant la validation des billets.*/
    };

    union __attribute__((packed))
    {
        BYTE byBillEscrow[2]; /*!<Tableau contenant l'escrow des billets.*/
    };
}
BILLTYPE;

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
}
ESCROWDIR;

/*End of typedef***************************************************************/
BYTE byStacker[3];

BILLVALIDATORSETUP billValidatorSetup;

/**
 * \brief Montant inséré dans le lecteur de billet
 */
long lAmountBV;

BOOL isBillValidatorReseted;

/**
 * brief Indique que la phase d'initialisation du monnayeur est effectuée.
 */
BOOL isBillValidatorInitialized;

/**
 * \var isBVPolled
 * \brief Flag indiquant si le lecteur de billet a été pollé.
 * \details Permettra de reseter la carte si le lecteur n'est pas pollé.
 */
BOOL isBVPolled;

EXID exId;

/**
 * @fn isGetMDBStackerStatus
 * \param stacker pointeur sur une variable contenant le nombre de biller et si le stacker est plein
 * @return true si l'opération s'est déroulé correctement.
 */
BOOL isGetMDBStackerStatus(BYTE *stacker);

/**
 * \brief Active ou desactive le lecteur de  billets.
 * \param[in] isEnable Indique si le lecteur de  billets doit être activé ou non.
 * \param[in] billType Paramètrage d'acceptation des billets de la centrale.
 * \param[in] isEscrow Indique si l'escrow doit être activé.
 * \return FALSE si l'opération ne s'est pas déroulée correctement ou si le rendeur n'est pas initialisé.
 */
BOOL isEnableBillValidator(const BOOL isEnable, const BOOL isEscrow, BILLTYPE *billType);

BOOL isGetExId(EXID *exId);

/**@}*/
#endif	/* MDB_BV_H */

