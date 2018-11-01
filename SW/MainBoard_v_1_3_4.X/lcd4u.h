
/** ****************************************************************************
 * \file            lcd4u.h                                                 
 * \brief			Header de la gestion de l'afficheur
 * \date            2013.11.30                                                 
 * \author          Rachid AKKOUCHE                                            
 *******************************************************************************/
#ifndef __lcd4u_h
#define	__lcd4u_h
#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>
#include "TCPIP Stack/delay.h"

/**
 * \defgroup LCD Gestion de l'afficheur.
 * @{
 */
/*Macros***********************************************************************/
/**
 * \brief Nombre de caractères de l'afficheur.
 */
#define LCDNUMCHAR 40 //20

/**
 * \brief Port utilisé pour les datas de l'afficheur.
 */
#define LCD_PORT IOPORT_E

/**
 * \brief IO de la ligne RS du HD44780.
 */
#define RS BIT_1

/**
 * \brief Port et IO de la ligne RS
 */
#define LCD_RS LCD_PORT, RS

/**
 * \brief Active l'afficheur.
 */
#define LCD_ON              (1 << 2)

/**
 * \brief Commande de positionnement du curseur en haut à gauche.
 */
#define LCD_HOME            (1 << 1)

/**
 * \brief commande d'ecriture de l'adresse dans le contrôleur.
 */
#define LCD_SET_DDRAM_ADDR  (1 << 7)

/**
 * \brief Commande effacement de l'afficheur.
 */
#define LCD_CLEAR           (1 << 0)

/**
 * \brief LCD_DISPLAY_CONTROL
 */
#define LCD_DISPLAY_CONTROL (1 << 3)

/**
 * \brief Commande de clignotement du curseur.
 */
#define LCD_BLINKING        (1 << 0)

/**
 * \brief Commande d'affichage du curseur.
 */
#define LCD_CURSOR          (1 << 1)

/**
 * \brief Affiche un curseur clignotant.
 */
#define LCD_CURSOR_ON() LCD_Command(LCD_DISPLAY_CONTROL | LCD_ON | LCD_CURSOR | LCD_BLINKING);

/**
 * \brief Masque le curseur.
 */
#define LCD_CURSOR_OFF() LCD_Command(LCD_DISPLAY_CONTROL | LCD_ON);

/**
 * \brief Affiche ou non le curseur en fonction de la valeur de x
 */
#define LCD_CURSOR_SET(x) if(x){LCD_CURSOR_ON()} else {LCD_CURSOR_OFF()}


/**
 * \brief Positionne le curseur en haut à gauche de l'afficheur.
 */
#define LCDHome() LCD_Command(LCD_HOME); ClearWDT()//;DELAYMS(4)

/**
 * \brief Envoi un caractère sur l'afficheur
 * \details equivalent à la fonction overrided _mon_putc(byData)
 * byData contient le caractère à envoyer.
 */
#define LCD_Put(byData) _mon_putc(byData);

/*End of macros***************************************************************/

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
/*End of variables**************************************************************/

/*Prototypes*******************************************************************/

/**
 * \brief Envoie un caratère à l'afficheur
 * \details Override de la fonction _mon_putc
 * @param[in] cData caractère à afficher
 */
void _mon_putc(char cData);

/**
 * \brief Initialisation de l'afficheur
 * @param[in] byNumLignes Nombre de lignes de l'afficheur.
 */
void LCDInit(const BYTE byNumLignes);

/**
 * \brief Positionne le curseur
 * @param[in] byAddress Indique l'adresse du curseur dans l'afficheur.
 */
void setLCDAddressCounter(const BYTE byAddress);

/**
 * \brief Enregistre la valeur vers l'afficheur.
 * @param[in] byValue Valeur à envoyer dans l'afficheur.
 */
void LCDSetValue(const BYTE byValue);

/**
 * \brief Postionne le curseur de l'afficheur.
 * \param[in] X Colonne. Commence à 1.
 * \param[in] Y Ligne. Commence à 1.
 */
void LCDGotoXY(const BYTE X, const BYTE Y);

/**
 * \brief Efface la ligne
 * \param[in] line Ligne à effacer.
 */
void LCDClearLine(const BYTE line);

/**
 * \brief Récupère l'adresse actuelle du controleur d'afficheur
 * \details n'effectue pas de vérification sur le bit d'occupation
 * @return l'adresse actuelle du controleur.
 */
BYTE getLCDAddressCounter();

/**
 * \brief Lit le caractère de l'afficheur à l'adresse courante.
 * @return Le caractère lu.
 */
BYTE getLCDC();

/**
 * \brief Efface l'écran LCD
 */
void LCDClear(void);

/**
 * \brief Transmet une chaine à l'afficheur en simulant printf.
 * \param format Chaine de formatage
 * \param ... Elements à formater
 */
void vDisplayLCD(char *format, ...);

/**
 * \brief envoie une commande à l'afficheur
 * @param[in] byCmd
 */
void LCD_Command(const BYTE byCmd);
/*End of prototypes************************************************************/
/**@}*/
#endif	/* lcd4u_h */
