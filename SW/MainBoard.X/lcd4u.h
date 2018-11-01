
#ifndef __lcd4u_h
  #define	__lcd4u_h
  #include "FreeRTOS.h"
  #include "semphr.h"
  #include "TCPIP Stack/delay.h"

/*Macros***********************************************************************/

/**
 * \def LCDNUMCHAR
 * \brief Nombre de caractères de l'afficheur.
 */
  #define LCDNUMCHAR 40 //20

/**
 * \def LCD_PORT
 * \brief Port utilisé pour les datas de l'afficheur.
 */
  #define LCD_PORT IOPORT_E

/**
 * \def RS
 * \brief IO de la ligne RS du HD44780.
 */
  #define RS BIT_1

/**
 * \def LCD_RS
 * \brief Port et IO de la ligne RS
 */
  #define LCD_RS LCD_PORT, RS

/**
 * \def LCD_ON
 * \brief Active l'afficheur.
 */
  #define LCD_ON              (1 << 2)

/**
 * \def LCD_HOME
 * \brief Commande de positionnement du curseur en haut à gauche.
 */
  #define LCD_HOME            (1 << 1)

/**
 * \def LCD_SET_DDRAM_ADDR
 * \brief commande d'ecriture de l'adresse dans le contrôleur.
 */
  #define LCD_SET_DDRAM_ADDR  (1 << 7)

/**
 * \def LCD_CLEAR
 * \brief Commande effacement de l'afficheur.
 */
  #define LCD_CLEAR           (1 << 0)

/**
 * \brief LCD_DISPLAY_CONTROL
 */
  #define LCD_DISPLAY_CONTROL (1 << 3)

/**
 * \def LCD_BLINKING
 * \brief Commande de clignotement du curseur.
 */
  #define LCD_BLINKING        (1 << 0)

/***/
  #define LCD_CURSOR          (1 << 1)

/**
 * \def LCD_CURSOR_ON
 * \brief Affiche un curseur clignotant.
 */
  #define LCD_CURSOR_ON() LCD_Command(LCD_DISPLAY_CONTROL | LCD_ON | LCD_CURSOR | LCD_BLINKING);

/**
 * \def LCD_CURSOR_OFF
 * \brief Masque le curseur.
 */
  #define LCD_CURSOR_OFF() LCD_Command(LCD_DISPLAY_CONTROL | LCD_ON);

/**
 * \def LCD_CURSOR_SET
 * \brief Affiche ou non le curseur en fonction de la valeur de x
 */
  #define LCD_CURSOR_SET(x) if(x){LCD_CURSOR_ON()} else {LCD_CURSOR_OFF()}


/**
 * \def LCDHome()
 * \brief Positionne le curseur en haut à gauche de l'afficheur.
 */
  #define LCDHome() LCD_Command(LCD_HOME); ClearWDT()//;DELAYMS(4)

/******************************************************************************/

/*Variables********************************************************************/

/**
 * \var byLCDAddressCounter
 * \brief Variable qui contiendra la position du curseur.
 */
BYTE byLCDAddressCounter;

/**
 * \var semaphoreLCD
 * \brief semaphore autorisant l'envoi de caractère vers l'afficheur.
 */
SemaphoreHandle_t semaphoreLCD;

/******************************************************************************/

/*Prototypes*******************************************************************/

/**
 *\fn LCDSetValue
 * \brief Envoie la valeur vers l'afficheur.
 * @param byValue
 */
void LCDSetValue(BYTE byValue);

/**
 * \fn LCDGotoXY
 * \brief Postionne le curseur de l'afficheur.
 * @param X Colonne. Commence à 1.
 * @param Y Ligne. Commence à 1.
 */
void LCDGotoXY(BYTE X, BYTE Y);

/**
 * \fn LCDClearLine
 * \brief Remplit la ligne de caractères espace.
 * @param line Ligne à effacer.
 */
void LCDClearLine(const BYTE line);

/**
 * \fn getLCDAddressCounter
 * \brief Récpère l'adresse actuelle du controleur d'afficheur
 * \détail n'effectue pas de vérification sur le bit d'occupation
 * @return l'adresse actuelle du controleur.
 */
BYTE getLCDAddressCounter();

/**
 * \fn getLCDC
 * \brief Lit le caractère de l'afficheur à l'adresse courante.
 * @return Le caractère lu.
 */
BYTE getLCDC();

/**
 * \fn LCDClear
 * \brief Efface l'écran LCD
 */
void LCDClear(void);

/**
 * vDisplayLCD
 * @param format Chaine de formatage
 * @param ... Elements à formater
 */
void vDisplayLCD(char *format, ...);

#endif	/* lcd4u_h */
