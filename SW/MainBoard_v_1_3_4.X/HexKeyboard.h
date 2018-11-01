
/** ****************************************************************************
 * \file            HexKeyboard.h                                                 
 * \brief			Header de la gestion du clavier
 * \details         Les lignes de ports des lignes doivent �tre adjacentes.
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/

#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include <plib.h>
#include "RAdefine.h"
#include "FreeRTOS.h"
#include "timers.h"

/**
 * \defgroup CLAVIER Gestion du clavier
 * @{
 */

/**Definition******************************************************************/

/**
 * \brief Nombre de touches sur le clavier.
 * Commenter la ligne suivante pour un clavier 16 touches.
 */
#define KEYS_12

/**
 * \brief Port utilis� par les lignes.
 */
#define ROWPORT IOPORT_B

/**
 * \brief IO de la ligne 1
 */
#define LIGNE_1 BIT_8

/**
 * \brief IO de la ligne 2
 */
#define LIGNE_2 BIT_9

/**
 * \brief IO de la ligne 3
 */
#define LIGNE_3 BIT_10

/**
 * \brief IO de la ligne 4
 */
#define LIGNE_4 BIT_11

/**
 * \brief Nombre de lignes du clavier.
 */
#define NUMLIGNES 4

/**
 * \brief ensemble des IOs pour les lignes.
 */
#define LIGNES  LIGNE_1 | LIGNE_2 | LIGNE_3 | LIGNE_4

/**
 * \brief Num�ro sur le port de la premi�re ligne.
 */
#define LINESSHIFT 8

/**
 * \brief Port utilis� par les colonnes.
 */
#define COLUMNPORT IOPORT_B

/**
 * \brief IO de la colonne 1.
 */
#define COLONNE_1 BIT_12

/**
 * \brief IO de la colonne 2.
 */
#define COLONNE_2 BIT_13

/**
 * \brief IO de la colonne 3.
 */
#define COLONNE_3 BIT_14
#ifndef KEYS_12

/**
 * \brief IO de la colonne 4.
 */
#define COLONNE_4 BIT_15

/**
 * \brief ensemble des IOs pour les colonnes.
 */
#define COLONNES COLONNE_1 | COLONNE_2 | COLONNE_3 | COLONNE_4

/**
 * \brief Nombre de colonnes du clavier.
 */
#define NUMCOLONNES 4
#else
/**
 * \brief ensemble des IOs pour les lignes.
 */
#define COLONNES COLONNE_1 | COLONNE_2 | COLONNE_3// | COLONNE_4

/**
 * \brief Nombre de colonnes du clavier.
 */
#define NUMCOLONNES 3
#endif

/**
 * \brief Num�ro sur le port de la premi�re colonne.
 */
#define COLUMNSHIFT 12

/**
 * \brief Nombre de boutons du clavier.
 */
#define NUMBUTTONS (NUMLIGNES * NUMCOLONNES)

/**
 * \brief Delai par d�faut de r�p�tition du clavier.
 */
#define REPEATDELAYKBDBYDEFAULT (1100)

/*Enum�rations*****************************************************************/

enum
{
    LO, /*!< Etat bas.*/
    HI, /*!< Etat haut.*/
};

/*Variables********************************************************************/

/**
 * \var isKBDPolled
 * \brief Variable indiquant si le clavier a �t� v�rifi�.
 */
BOOL isKBDPolled;

/**
 * \var lRepeatKBD
 * \brief contient la valeur par d�faut de la r�p�tition.
 */
long lRepeatKBD;

/**
 * \brief Tableau de structure contenant les informations d'�tat concernant une  touche du clavier.
 */
struct __attribute__((packed))
{
    BOOL byLevel : 1; /*!< Etat du bouton.*/
    BOOL isTreated : 1; /*!< Indique si un bouton a �t� consid�r�.*/
    BOOL isNotUsed : 1; /*!< */
}kbdButton[NUMBUTTONS];

/**
 * \var hTimerKBDRepeat;
 * \brief Handle du timer de d�lai d'attente avant de r�p�ter une touche du clavier.
 */
TimerHandle_t hTimerKBDRepeat;


/**
 * \var hTimerFlip
 * \brief Handle du timer g�rant le flip.
 */
TimerHandle_t hTimerFlip;

/**
 * \var byKeyHitBack
 * \brief Copie du num�ro de la touche actionn�e.
 */
BYTE byKeyHitBack;

/*Prototypes*******************************************************************/

/**
 * \brief Verifie le clavier et renvoie le num�ro de la derni�re touche utilis�e.
 * \return Le num�ro de la derni�re touche utilis�e.
 */
BYTE byGetKey(void);

/**
 * \brief Fonction qui execute les op�rations de r�p�titions du clavier.
 */
void vTimerRepeat(TimerHandle_t pxTimer);

/**@}*/

#endif	/* KEYBOARD_H */

