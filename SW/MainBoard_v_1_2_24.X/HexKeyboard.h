/* 
 * File:   keyboard.h
 * Author: RA
 *
 * Created on 13 janvier 2014, 05:44
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include <plib.h>
#include "RAdefine.h"
#include "FreeRTOS.h"
#include "timers.h"


/**Definition******************************************************************/
/*Clavier*/
//    Les lignes de ports des lignes doivent être adjacentes.
//Commenter la ligne suivante pour un clavier 16 touches.

/**
 * \def KEYS_12
 * \brief Nombre de touches sur le clavier.
 */
#define KEYS_12

/**
 * \def ROWPORT
 * \brief Port utilisé par les lignes.
 */
#define ROWPORT IOPORT_B

/**
 * \def LIGNE_1
 * \brief IO de la ligne 1
 */
#define LIGNE_1 BIT_8

/**
 * \def LIGNE_2
 * \brief IO de la ligne 2
 */
#define LIGNE_2 BIT_9

/**
 * \def LIGNE_3
 * \brief IO de la ligne 3
 */
#define LIGNE_3 BIT_10

/**
 * \def LIGNE_4
 * \brief IO de la ligne 4
 */
#define LIGNE_4 BIT_11

/**
 * \def NUMLIGNES
 * \brief Nombre de lignes du clavier.
 */
#define NUMLIGNES 4

/**
 * \def LIGNES
 * \brief ensemble des IOs pour les lignes.
 */
#define LIGNES  LIGNE_1 | LIGNE_2 | LIGNE_3 | LIGNE_4

/**
 * \def KEYS_12
 * \brief Numéro sur le port de la première ligne.
 */
#define LINESSHIFT 8

/**
 * \def COLUMNPORT
 * \brief Port utilisé par les colonnes.
 */
#define COLUMNPORT IOPORT_B

/**
 * \def COLONNE_1
 * \brief IO de la colonne 1.
 */
#define COLONNE_1 BIT_12

/**
 * \def COLONNE_2
 * \brief IO de la colonne 2.
 */
#define COLONNE_2 BIT_13

/**
 * \def COLONNE_3
 * \brief IO de la colonne 3.
 */
#define COLONNE_3 BIT_14
#ifndef KEYS_12

/**
 * \def COLONNE_4
 * \brief IO de la colonne 4.
 */
#define COLONNE_4 BIT_15

/**
 * \def LIGNES
 * \brief ensemble des IOs pour les colonnes.
 */
#define COLONNES COLONNE_1 | COLONNE_2 | COLONNE_3 | COLONNE_4

/**
 * \def NUMCOLONNES
 * \brief Nombre de colonnes du clavier.
 */
#define NUMCOLONNES 4
#else
/**
 * \def LIGNES
 * \brief ensemble des IOs pour les lignes.
 */
#define COLONNES COLONNE_1 | COLONNE_2 | COLONNE_3// | COLONNE_4

/**
 * \def NUMCOLONNES
 * \brief Nombre de colonnes du clavier.
 */
#define NUMCOLONNES 3
#endif

/**
 * \def COLUMNSHIFT
 * \brief Numéro sur le port de la première colonne.
 */
#define COLUMNSHIFT 12

/**
 * \def NUMBUTTONS
 * \brief Nombre de boutons du clavier.
 */
#define NUMBUTTONS (NUMLIGNES * NUMCOLONNES)

/**
 * \def REPEATDELAYKBDBYDEFAULT
 * \brief Delai par défaut de répétition du clavier.
 */
#define REPEATDELAYKBDBYDEFAULT (1100)

/*Enumérations*****************************************************************/

enum 
{
    LO, /*!< Etat bas.*/
    HI, /*!< Etat haut.*/
};

/*Variables********************************************************************/

/**
 * \var isKBDPolled
 * \brief Variable indiquant si le clavier a été vérifié.
 */
BOOL isKBDpOLLED;

/**
 * \var lRepeatKBD
 * \brief contient la valeur par défaut de la répétition.
 */
long lRepeatKBD;

/**
 * \var kbdButton
 * \brief Tableau de structure contenant les informations d'état concernant une  touche du clavier.
 */
struct __attribute__((packed))
{
    BOOL byLevel: 1; /*!< Etat du bouton.*/
    BOOL isTreated: 1; /*!< Indique si un bouton a été considéré.*/
    BOOL isNotUsed: 1; /*!< */
} kbdButton[NUMBUTTONS];

/**
 * \var hTimerKBDRepeat;
 * \brief Handle du timer de délai d'attente avant de répéter une touche du clavier.
 */
TimerHandle_t hTimerKBDRepeat;


/**
 * \var hTimerFlip
 * \brief Handle du timer gérant le flip.
 */
TimerHandle_t hTimerFlip;

/**
 * \var byKeyHitBack
 * \brief Copie du numéro de la touche actionnée.
 */
BYTE byKeyHitBack;

/*Prototypes*******************************************************************/

/**
 * \fn byGetKey
 * \brief Verifie le clavier et renvoie le numéro de la dernière touche utilisée.
 * \return Le numéro de la dernière touche utilisée.
 */
BYTE byGetKey(void);

/**
 * \fn vTimerRepeat
 * \brief Fonction qui execute les opérations de répétitions du clavier.
 */
void vTimerRepeat(TimerHandle_t pxTimer);

#endif	/* KEYBOARD_H */

