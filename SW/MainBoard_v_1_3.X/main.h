/**
 * \file main.h
 * \author Rachid AKKOUCHE
 */

/*Change history
 *  Rev 0.9.0a      2014 04 23
 *                  Premi�re release fonctionnelle.
 *  Rev 0.9.1a      2014 09 22
 *                  USB
 *  Rev 0.9.2a      2014 09 25
 *                  1 - Affichage du num�ro de machine � l'affichage du prix.
 *                  2 - Correction du bug concernant le blocage au cours de l'achat avec cl�.
 *                  3 - Correction d'un bug d'affichage lors du retour d'une machine indisponible en pr�sence d'une cl�.
 *                  4 - Correction textes
 *                  5 - Le d�lai pour le trop-per�u est forc� au minimum � 1 seconde pour �viter une division  par 0.
 *                  6 - Modification de l'audit en fichier.
 *                  7 - Modification du syst�me USB pour g�rer plusieurs centrales sur une cl�.
 *                  8 - Am�lioration de l'historique et cr�ation de l'audit en fichier.
 *                  9 - Rendu entre chaque s�lection pour les machines cumulables.
 *                  10 - V�rification de la coh�rence de la date.
 * Rev 0.9.3a       2014 12 05
 *                  1 - Modification de la pr�sentation du temps sur pour le cumul et l'affichage du temps restant.
 * Rev 0.9.4a       2014 12 10
 *                  1 - Modification sur le temps de retour en mode.
 *                  2 - Modification du retour en mode utilisateur pour diminuer le temps de retour.
 *                  3 - Modification de l'historique. (Pour internet)
 *                  4 - Reset des machines en routes � la mise en route de la centrale.
 * Rev 0.9.5a       2014 12 14
 *                  1 - Correction du bug sur le retour de test.
 * Rev 0.9.6a       2014 12 15
 *                  1 - Modification de l'affichage lors du cumul des pi�ces.
 *                  2 - Correction du rendu lors du cumul.
 * Rev 0.9.7a       2014 12 16
 *                  1 - Suppression du curseur lors de la s�lection par internet.
 *                  2 - Correction des valeurs par d�faut pour les nouvelles machines.
 *                  3 - Suppression  du basculement d'�cran lors de l'affichage "S�lection machine" au retour de test.
 *                  4 - Correction des valeurs par d�faut des nouvelles machines.
 *                  5 - Correction Flip sortie de test.
 *                  6 - Correction du rendu pour les rendeurs MARS
 *                  7 - Modification de l'interruption du time out des r�ceptions s�ries dans le fichiers UARTLIB
 *                  8 - Ajout de l'affichage du temps accord� sur les machines sans cumul.
 * Rev 0.9.8a       2014 12 21
 *                  1 - Remise en place du buzzer.
 *                  2 - Modification des timing d'affichage.
 * Rev 0.9.9a       2015 03 20
 *                  1 - Modification internet
 * Rev 1.0.0b       2015 04 01
 *                  Premi�re version compl�te beta release
 * Rev 1.0.1b       2015 04 12
 *                  Retrait du cumul sur les achats par cl�s et t�l�-activation. Usage impossible.
 * Rev 1.0.2RC      Version release candidate
 *                  2015 04 27
 *                  1 -  Modification de la gestion de l'afficheur.
 *                  2 -  Ajout de la fonction rendu par internet.
 * Rev 1.0.3RC      2015 05 17
 *                  1 -  Correction bug affichage trop per�u.
 *                  2 -  Correction bug modification du T.O. du trop per�u par internet.
 * Rev 1.0.4RC      2015 06 20
 *                  1 -  Correction d'un bug sur le rendu sup�rieur � 2,55 Euro
 *                  2 -  Correction d'un bug sur la saisie des montants sur les pages internet
 *                  3 -  Correction d'une r�gression sur le TO du clavier.
 * Rev 1.1.0RC      2015 06 10
 *                  1 -  Correction de l'overflow des timers.
 *                  2 -  Nouvelle extension des timers
 *                  3 -  Gestion de la d�tection de la consommation par ADC
 *                  4 -  Pilotage d'un relais d'alimentation principale de l'alimentation. Ce relais peut �tre utilis�e �
 *                       d'autre fin.
 *                  5 -  Gestion de la d�tection de vide de produit.
 *                  6 -  D�tail du motif d'indisponibilit� du satellite.
 *                  7 -  Correction d'un bug sur le timing d'activation des machines par ethernet.
 * Rev 1.1.1RC      2015 06 23
 *                  Extension du tas du display flip.
 * Rev 1.1.2        2015 07 05
 *                  Correction du probl�me de watchdog
 * Rev 1.1.3        2015 08 21
 *                  1 -  Correction sur le d�lai du d�lai de cumul qui est fix� � 30 secondes si �gale � 0.
 *                  2 -  Les timers freertos ne peuvent plus �tre fix� � z�ro.
 * Rev 1.2.0        2015 08 22
 *                  1 -  Augmentation du TO du watchdog.
 *                  2 -  Mise en place des passwords pour acc�der aux param�trages et audits par la centrale.
 *                  3 -  Mise en place des passwords pour acc�der aux param�trages et audits par internet.
 *                  4 -  Suppression des canaux non utilis�s dans l'audit par internet.
 *                  5 -  Extension du nombre de ligne du tableau de l'historique sur internet.
 *                  6 -  Mise en place d'un param�tre permettant l'utilisation ou non des billets pour chaque machine.  
 *                  7 -  Correction de l'enregistrement de l'historique � l'activation de la machine.
 *                  8 -  Correction du texte de fin activation.                
 * Rev 1.2.1        2015 10 10
 *                  Modification texte dans l'affichage de l'historique internet.
 * Rev 1.2.2        2015 10 14
 *                  Modification des fusibles du watchdog dans le programme principale et dans le  isotloader.
 * Rev 1.2.3        2015 10 25
 *                  1 -  Correction d'un bug sur la validation des moyens de paiement lors de l'initialisation des satellites.
 *                  2 -  Correction d'un bug sur le poll MDB
 * Rev 1.2.4        2015 10 28
 *                  1 -  Augmentation de la taille du tas des t�ches.
 *                  2 -  D�sactivation de EnableWDT.
 *                  3 -  Augmentation du d�lai de time out pour les fonctions JavaScript.(javascripts.js)
 * Rev 1.2.5        2015 10 29
 *                  1 -  Modification des d�lais internet.                  
 *                  2 -  Suppression des param�tres par d�faut dans les appels newAjaxCommand.
 *                  3 -  Suppression des setTimeOut pour les commandes Ajax.
 *                  4 -  Correction d'un bug sur la liste des machines dans le param�trage par internet.
 * Rev 1.2.6        2015 11 05
 *                  1 -  Correction d'un bug de saisie des nombres sans les param�tres.
 *                  2 -  Affichage de nombre n�gatif sur le rendu dans l'historique internet.
 *                  3 -  Modification de la priorit� du battement de la led.
 *                  4 -  Synchronisation de la fonction newAjaxCommand de l'historique sur internet pour �viter les d�calages.
 *                  5 -  Sur l'historique les entr�es avec un mot de passe erron� sont indiqu�es.
 *                  6 -  Modification des priorit�s des t�ches pour �viter les probl�mes de trop per�u.
 * Rev 1.2.7        2015 11 11
 *                  1 -  Modification de la synchronisation des requ�tes Ajax pour les historiques et pour l'usage des machines.
 *                  2 -  Temps minimum d'overbusy fix� � 100ms
 *                  3 -  Rendu du montant introduit en cas de non activation de la machine.
 *                  4 -  Correction de l'affichage apr�s le time out du trop-per�u.
 *                  5 -  Correction de l'affichage sur la saisie des machines en pr�sence de trop per�u.
 *                  6 -  Correction d'un bug sur les time out en seconde lors de la modification des param�tres de la centrale par internet.
 * Rev 1.2.8        2015 11 25
 *                  1 -  Correction d'une r�gression qui double l'enregistrement dans l'historique de l'activation des machines.
 *                  2 -  Ajout du motif de la non-s�lection dans l'historique sur internet.
 *                  3 -  Ajout du motif de la non-activation dans l'historique sur internet.
 *                  4 -  Ajout de fonctions pour v�rification de l'activation des machines.
 * Rev 1.2.9        2015 12 07
 *                  1 -  Icone sur les urls.
 *                  2 -  Initialisation de la longueur de la saisie de la machine � chaque initialisation de la s�lection.
 *                  3 -  4 essais pour la r�ponse d'un module.
 *                  4 -  Modification du traitement du cumul. 
 *                  5 -  Modification de l'affichage des horaires sur les param�tres machines d� � un bug de chrome mobile.      
 * Rev 1.2.10       2015 12 20
 *                  1 -  Ajustement du tarif par internet.       
 *                  2 -  Ajout du montant � payer de la s�lection dans l'historique.
 *                  3 -  Suppression message time out newCommandAjax.
 *                  4 -  Correction r�gression sur les historiques internet.
 *                  5 -  Enregistrement du remplissage en cas d'interruption de Time out
 * Rev 1.2.11       2015 12 21
 *                  1 -  Modification de l'enregistrement du fichier historique.
 *                  2 -  Correction du bug de remplissage.
 * Rev 1.2.11b      2016 01 02
 *                  Inversion des param�tres par d�faut du TO cumul et TO keyisard.
 * Rev 1.2.11c      2016 02 22
 *                  Changement du timing de d�marrage et du d�lai entre les phases de rendu.
 * Rev 1.2.12       2016 03 03
 *                  1 -  Correction du bug sur la saisie des num�ros de machines.
 *                  2 -  Ajout du texte concernant l'absence du secteur sur le satellite
 *                       dans les historiques.
 * Rev 1.2.13       2016 03 13
 *                  1 -  Modification du mode de distribution, plus rapide et moins de pi�ces.
 *                  2 -  Correction de l'annulation
 *                  3 -  Suppression des portMax_delay
 * Rev 1.2.14       2016 04 08
 *                  Remise en place de la distribution lente.
 * Rev 1.2.16       2017 02 14
 *                  1 -  Correction du bug sur le scaling factor.
 *                  2 -  Modification des textes HTLM sur l'activation
 * Rev 1.2.17       2017 03 10
 *                  1 -  Correction du montant de la distribution par Internet
 *                       � la place de , du montant � distribuer
 *                  2 -  Correction du num�ro de version.
 * Rev 1.2.18       2017 03 29
 *                  1 -  Correction de la distribution par Internet
 *                  2 -  Correction de la valeur des rendus dans l'historique.
 * Rev 1.2.19       2017 03 29
 *                  1 -  Double reset pour les lecteur MEI.
 *                  2 -  Incr�mentation de l'index au cas de la r�ponse occup� du
 *                       lecteur cashless (RSP_BUSY)
 *                  3 -  Mise en place d'un TO pour la distribution
 *                  4 -  Correction de la v�rification de la distribution
 *                  5 -  Modification de la protection des commandes MDB.
 *                  6 -  Modification de la protection des polls MDB
 * Rev 1.2.20       2017 04 26
 *                  R�int�gration du bootloader
 *                  Proc�dure :
 *                   1 - Eteindre la centrale.
 *                   2 - Ins�rer la cl� USB nomm�e MDI et contenant un 
 *                       fichier MDIBOARD.HEX
 *                   3 - Maintenir le bouton de test appuy� pendant la mise 
 *                       sous tension de la centrale. Attendre que la led
 *                       clignote (15 secondes environ) et relacher le bouton.
 *                   4 - Attendre que la led clignote rapidement, puis la reprise
 *                       du clignotement normale.
 *                   5 - Eteindre la centrale.
 *                   6 - Retirer la cl� USB.
 *                   7 - Rallumer la centrale et v�rifier la centrale. 
 * Rev. 1.2.21      2017 04 27
 *                  Correction d'une r�gression sur la gestion des tubes par
 *                  internet.      
 * Rev. 1.2.22      2017 06 12
 *                  Mise en place d'un systeme watchdog             
 * Rev  1.2.23      2017 07 17
 *                  Watchdog sur le retrait total des modules.
 *                  Mise en place d'une s�curit� pour �viter un surremoursement.            
 *                  Correction sur le lecteur de billet MEI.  
 * Rev 1.2.24       2017 08 28
 *                  Doublage du temp de watchodg         
 * Rev. 1.3.00       2017 08 29
 *                  Bug 1.2.24 pas d'intenet, bouclage � la mise sous tension.
 *                  Division par 2 de la fr�quence de travail, permet de diminuer l'echaufement des composants et supprime le bouclage.
 *                  Modification de la priorit� de la t�che USB et Internet.
 *                  Beep au d�marrage.
 * Rev. 1.3.01      2017 08 31
 *                  Bug 1.3.00 pas de rendu
 *                  Modification de la priorit� du rendu.
 * 
 */
/*****************************************************************************/

#ifndef MAIN_H
#define	MAIN_H

#ifndef __L_DEBUG
static const char Version[] = "Rev 1.3.01";
#else
static const char Version[] = "Rev 1.3.01D";
#endif

#define Rev114

#include <plib.h>
#include <stddef.h>
#include <GenericTypeDefs.h>
#include <limits.h>
//#include "FreeRTOSConfig.h"
#include <FreeRtos.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>
#include "RAdefine.h"
#include "MDB.h"
#include "mdb_bv.h"
#include "mdb_cg.h"
#include "commun.h"
#include "mdb_cl.h"
#include "textes.h"
#include "parametres.h"
#include "lcd4u.h"
#include "I2CE2PROML.h"
#include "UARTLib.h"
#include "HexKeyboard.h"
#include "satellites.h"
#include "datetime.h"
#include "USB/usb.h"
#include "USB/usb_host_msd.h"
#include "USB/usb_host_msd_scsi.h"
#include "MDD File System/FSIO.h"
#include "TCPIP Stack/TCPIP.h"
#include "TCPIP Stack/Delay.h"
#include "global.h"
#include "code.h"
#include "exception.h"
#include "password.h"

/******************************************************************************/
// PIC32MX795F512L Configuration Bit Settings

// DEVCFG3
// USERID = No Setting
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = OFF             // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config FCANIO = OFF             // CAN I/O Pin Select (Default CAN I/O)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider (1x Divider)
#pragma config UPLLEN = ON              // USB PLL Enable (Enabled)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (HS osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enable, FSCM Enabled)
#pragma config WDTPS = PS65536          // Watchdog Timer Postscaler (1:1)

//Version 1.2.2
#pragma config FWDTEN = OFF             // Watchdog Timer Disable (WDT Enable (SWDTEN Bit Controls))
//-------------

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

/******************************************************************************/

/*Define***********************************************************************/

/**
 * \def DELAYRESET
 * \brief delai pour la prise en compte du clavier et MDB
 */
#define DELAYRESET 500

/**
 * \def POLLRS485
 * \brief Intervalle entre le d�but de chaque v�rification d'un satellite
 */
#define POLLRS485 (150 * MILLISEC)

/**
 * \def PULSE_RTOS
 * \brief Intervalle entre chaque inversion de la led.
 * Ce battement indique le fonctionnement du RTOS en mode utilisateur.
 */
#define PULSE_RTOS (1 * SECONDE)

/**
 * \def DELAY_CHK_KBD
 * \brief d�lai entre chaque v�rification du clavier
 */
#define DELAY_CHK_KBD (10 * MILLISEC)

/**
 * \def DISPLAYTIMEDELAY
 * \brief Delai entre chaque rafraichissement de l'heure affich�e.
 */
#define DISPLAYTIMEDELAY (500 * MILLISEC)

/**
 * \def PREDELAYFLIP
 * \brief D�lai avant que le flip ne soit op�rationnel.
 */
#define PREDELAYFLIP (1 * SECONDE)

/**
 * \def TOBUZZER
 * \brief D�lai de buzzer
 */
#define TOBUZZER (250 * MILLISEC)

/**
 * \def TODISPENSE
 * \brief D�lai de TO du rendu
 */
#define TODISPENSE (60 * SECONDE)

/**
 * \def CHECKUSB
 * \brief Delai entre chaque v�rification d'une pr�sence de cl� USB.
 */
#define CHECKUSB (100 * MILLISEC)

/**
 * \def BUZZER
 * \brief Port du buzzer
 */
#define BUZZER IOPORT_D, BIT_0

/**
 * \def ONBOARDBUTTON
 * \brief port du isuton sur la carte m�re.
 */
#define ONBOARDBUTTON IOPORT_B, BIT_4

/**
 * \def VP
 * \brief IO utilis� pour la v�rification de la pr�sence de tension.
 */
#define VP IOPORT_B, BIT_3

/**
 * \def ResetEEprom
 * \brief IO utilis� pour la remise � z�ro des donn�es dans l'eeprom.
 */
#define ResetEEprom IOPORT_B, BIT_6

/**
 * \def W1
 * \brief IO general purpose.
 */
#define W1 IOPORT_B, BIT_2

/**
 * \def RED
 * \brief port de la led rouge.
 */
#define RED IOPORT_C, BIT_1

/**
 * \def DEFAULTDELAYBUSY
 * \brief Delay d'occupation par d�faut.
 */
#define DEFAULTDELAYBUSY 6000ul

/**
 * \def DELAYOVERBUSYDEFAULT
 * \brief Temps par d�faut de la suroccupation d'un satellite.
 */
#define DELAYOVERBUSYDEFAULT 90000

/**
 * \def MDBLINE
 * \brief Port utilis� par la transmission MDB
 */
#define MDBLINE IOPORT_F, BIT_8 | BIT_2

/**
 * \def RS232_2
 * \brief port s�rie 2
 */
#define RS232_2 UART5

/**
 * \def RS485
 * \brief port 485
 */
#define RS485 UART2

/**
 * \def MDBPORT
 * \brief port s�rie MDB
 */
#define MDBPORT UART1

/**
 * \def LEDON(COLOR)
 *\brief Allume la led dont la couleur est d�finie en param�tre.
 */
#define LEDON(COLOR) PORTSetBits(COLOR)

/**
 * \def LEDOFF(COLOR)
 *\brief Eteint la led dont la couleur est d�finie en param�tre.
 */
#define LEDOFF(COLOR) PORTClearBits(COLOR)

/**
 * \def LEDTOGGLE(COLOR)
 *\brief Inverse l'�tat de la led dont la couleur est d�finie en param�tre.
 */
#define LEDTOGGLE(COLOR) PORTToggleBits(COLOR)

/**
 * \def BUZZER_ON()
 * \brief Active le buzzer.
 */
#define BUZZER_ON() PORTSetBits(BUZZER)

/**
 * \def BUZZER_OFF()
 * \brief Desactive le buzzer.
 */
#define BUZZER_OFF() PORTClearBits(BUZZER)

/**
 * \def BUZZER_SOUND(x)
 * \brief Active ou desactive le buzzer en fonction de\b x
 */
#define BUZZER_SOUND(x) (x ? BUZZER_ON() : BUZZER_OFF())

/**
 * \def DECIMALPOS
 * \brief Position de la d�cimale dans un nombre flottant.
 */
#define DECIMALPOSBYDEFAULT 2

/**
 * \def KEYNAME
 * \brief Nom de volume de la cl� USB
 * si le nom de volume de la cl� est diff�rent, celle-ci ne sera pas reconnue.
 */
#define KEYNAME "MDI"

/**
 * \def AUDITFILENAME
 * \brief Nom du fichier permettant ou non l'acc�s aux audits.
 */
#define AUDITFILENAME "AE"

/**
 * \def PARAMETREFILENAME
 * \brief Nom du fichier contenant l'autorisation d'entr�e dans le menu audit.
 */
#define PARAMETREFILENAME "PA"

/**
 * \def RAZFILENAME
 * \brief Nom du fichier contenant l'autorisation d'entr�e dans le menu audit.
 */
#define RAZFILENAME "RZ"

/**
 * \def REFILLINGFILENAME
 * \brief Nom du fichier contenant l'autorisation d'entr�e dans le menu audit.
 */
#define REFILLINGFILENAME "RF"

/**
 * \def HISTOFILENAME
 * \brief Nom du fichier contenant l'autorisation d'entr�e dans le menu audit.
 */
#define HISTOFILENAME "HE"

/**
 * \def REINICODEFILENAME
 * \brief Prefixe du nom du fichier contenant l'autorisation d'entr�e dans le menu audit.
 */
#define REINICODEFILENAME "IN"

/**
 * \def CREDITFILENAME
 * \brief Prefixe du nom du fichier contenant les cr�dits de la cl� USB.
 */
#define CREDITFILENAME "CR"

/**
 * \def SAVEAUDITENABLEFILENAME
 * \brief nom du fichier contenant l'autorisation d'effectuer une sauvegarde du fichier des audits.
 */
#define SAVEAUDITENABLEFILENAME "AF"

/**
 * \def SAVEHISTOENABLEFILENAME
 * \brief nom du fichier contenant l'autorisation d'effectuer une sauvegarde du fichier des audits.
 */
#define SAVEHISTOENABLEFILENAME "HF"

#define STACKHEARTBEATING 255
#define STACKDST 255
#define STACKMDB 2048
//#define STACKKBD 2048
#define STACKKBD 1024
#define STACKTREATKEY 1024
#define STACKUSB 1024
#define STACKDSPTIME 512
#define STACKFLIP 1024
#define STACKTEST 511
#define STACKCHANGE 2048

/**Enum�ration*****************************************************************/

/**
 * \enum ESENDER
 * \brief Enumeration des origines de l'utilisation d'une requ�te.
 */
typedef enum
{
    USER, /*!< La requ�te est effectu�e en mode user.*/
    MANUALMACHINE, /*!< La requ�te est effectu�e en parametrage manuel d'une nouvelle machine.*/
    MODIFMACHINES, /*!< La requ�te est effectu�e en modification d'une machine.*/
    REFMACHINE, /*! La requ�te est effectu�e pour obtenir la machine de r�f�rente.*/
    REMOVESATELLITE, /*! La requ�te est effectu�e pour supprimer une machine.*/
    //REMOVEALLSATTELITE, /*!< La requ�te est effectu�e pour supprimer toutes les machines.*/
    MAINMAINTENANCE, /*!< La requ�te est effectu�e � partir du menu principal de maintenance.*/
    HISTORIQUEMENU, /*!<* La requ�te est effectu�e � partir du menu historique.*/
} ESENDER;

/**
 * \enum EMODE
 * \brief Mode de fonctionnement du syst�me.
 */
typedef enum
{
    MODEUSER,
    MODEMAINTENANCE
} EMODE;

/**
 * \typedef EAUDIT
 * \brief enumeration des types d'audit.
 */
typedef enum
{
    TEMPORARY,
    PERMANENT,
} EAUDIT;

/**
 * \brief Device state on the USB
 */
typedef enum
{
    INITIALIZE,
    DETACH_STATE,
    APPLICATION_ERROR,
    APPLICATION_RUNNING,
} PROCESSIOSTATE;

/**Structure*******************************************************************/

/**Variables*******************************************************************/


/**
 * \var UsageMode
 * \brief Indique si le syst�me est en mode utilisateur ou en mode maintenance.
 */
static EMODE UsageMode = MODEUSER;

/**
 * \var semaphoreDST
 * \brief Informe le syst�me que l'heure doit �tre modifi�.
 */
SemaphoreHandle_t semaphoreDST;

/**
 * \var semaphoreTest
 * \brief Indique la demande d'entr�e en mode test.
 */
SemaphoreHandle_t semaphoreTest;

/**
 * \var queueKeyHit
 * \brief Queue contenant le num�ro de la touche utilis�e.
 */
QueueHandle_t queueKeyHit;

/**
 * \var isKeyPresent
 * \brief Indique la pr�sence d'une cl�.
 */
BOOL isKeyPresent;

/**
 * \var byCashPos
 * \brief Position du canal � visualiser dans les menus de maintenance
 */
BYTE byCashPos;

/**
 * \var lAmountToPay
 * \brief Montant � payer
 */
long lAmountToPay;

/**
 * \var lAmountToDisplay
 * \brief Montant � afficher.
 */
long lAmountToDisplay;

/**
 * \var lOldAmountInCashDispo
 * \brief Montant disponible pr�c�dent.
 * Utilis� par diff�rence pour d�tecter l'insertion de cash
 */
long lOldAmountInCashDispo;

/**
 * \var lAmountUSBDispo
 * \brief Montant disponible dans la cl� USB.
 */
long lAmountUSBDispo;

/**
 * \var lOldAmountUSBDispo
 * \brief Sauvegarde du montant disponible dans la cl� USB.
 */
long lOldAmountUSBDispo;

long lTimeRemaining;
/**
 * \var byPosNum
 * \brief Position du caract�re dans la cha�ne saisie.
 */
BYTE byPosNum;

/**
 * \var byBuffer
 * \brief buffer interm�diaire pour l'affichage.
 */
char byBuffer[64];

/**
 * \var byCreditFileName
 * \brief buffer contenant le nom du fichier de cr�dit.
 */
char byCreditFileName[13];

/**
 * \var eAudit
 * \brief Indique le type d'audit en cours.
 */
EAUDIT eAudit;

/**
 * \fn wPrice
 * \brief Prix int�rm�daire dans les saisies de prix.
 */
WORD wPrice;

/**
 * \var dwValue
 * \brief Variable temporaire contenant la valeur en cours de saisie.
 */
DWORD dwValue;

/**
 * \var byUnite
 * \brief Variable contenant le nombre d'unit�s d'un nombre.
 */
BYTE byUnite;

/**
 * \var byDizaine
 * \brief Variable contenant le nombre de dizaines d'un nombre.
 */
BYTE byDizaine;

/**
 * \var byCentaine
 * \brief Variable contenant le nombre de centaines d'un nombre.
 */
BYTE byCentaine;

/**
 * \var byMillier
 * \brief Variable contenant le nombre de milliers d'un nombre.
 */
BYTE byMillier;

/**
 * \var byDixMille
 * \brief Variable contenant le contenu du rang des dix milles.
 */
BYTE byDixMille;

/**
 * \var byCentMille
 * \brief Variable contenant le contenu du rang des cent mille.
 */
BYTE byCentMille;

/**
 * \var byMillion
 * \brief Variable contenant le contenu du rang des millions
 */
BYTE byMillion;

/**
 * \var byDixMillion
 * \brief Variable contenant le contenu du rang des dix millions.
 */
BYTE byDixMillion;

/**
 * \var byCentMillion
 * \brief Variable contenant le contenu du rang des cent millions.
 */
BYTE byCentMillion;

/**
 * \var byMilliard
 * \brief Variable contenant le contenu du rang des milliards
 */
BYTE byMilliard;

/**
 * \var ptrParameterMenu
 * \brief pointeur sur le param�tre � passer � l'�cran de maintenance.
 * Valeur, heure, d�lai...
 */
void *ptrParameterMenu;

/**
 * \var byHour
 * \brief Variable interm�daire stockant l'heure en cours de saisie.
 */
BYTE byHour;

/**
 * \var byMin
 * \brief Variable interm�diaire stockant les minute en cours de saisie.
 */
BYTE byMin;

BYTE byMDBCGBuffer[32] = {0};

/**
 * \var sender
 * \brief Variable permettant de conna�tre l'origine de la demande de selection d'une machine
 */
ESENDER sender;

/**
 * \var Today
 * \brief Variable contenant une date.
 */
rtccDate Today;

/**
 * \var byBeforeRetryCL
 * \brief Nombre de isucle avant de r�essayer d'initialiser le lecteur cashless
 */
int iBeforeRetryCL;

/**
 * \var byBeforeRetryCG
 * \brief Nombre de isucle avant de r�essayer d'initialiser le rendeur
 */
int iBeforeRetryCG;

/**
 * \var byBeforeRetryBV
 * \brief Nombre de isucle avant de r�essayer d'initialiser le lecteur de billet
 */
int iBeforeRetryBV;

/**
 * \var isDisplayTime
 * \brief Autorise l'affichage de l'heure.
 */
BOOL isDisplayTime;

/**
 * \var isFlip;
 * \brief Autorise l'�change entre la ligne 1 et la ligne 2;
 */
BOOL isFlip;

/**
 * \var isCancel
 * \brief Indique que la transaction a �t� annul�
 */
BOOL isCancel;

/**
 * \var isReturnMaintenance
 * \brief Indique si le programme doit afficher le menu de maintenance en cours.
 */
BOOL isReturnMaintenance;

BOOL isKBDEnable;

/**
 * \var isMediaCLFull
 * \brief Indique que la cl� cashless pr�sente est ne peut plus �tre recharg�e.
 */
BOOL isMediaCLFull;

/**
 * \var isRevalueRequested
 * \brief Indique qu'une demande de recharge de la cl� a �t� faite.
 */
BOOL isRevalueRequested;

/**
 * \var isDisplayRemaining
 * \brief Indique si le prochain affichage du montant dispo sera le restant.
 */
BOOL isDisplayRemaining;

/**
 * \var isTO_KBDEnable
 * \brief Flag indiquant que le timer du clavier est actif
 */
BOOL isTO_KBDEnable;

/**
 * \var isTOCumul
 * \brief Flag indiquant que le timer du cumul est actif
 */
BOOL isTOCumul;

/**
 * \var isToBeOFF
 * \brief Flag indiquant que la CPU doit passer en mode SLEEP.
 */
BOOL isToBeOFF;

/**
 * \var byBillNumber
 * \brief Num�ro du canal du dernier billet introduit.
 */
BYTE byBillNumber;

/**
 * \var isToEscrow
 * \brief Indique que la fonction vEscrowRequested doit �tre effectu�e.
 */
BOOL isToEscrow;

/**
 * \var isThumbDriveAttached
 * \brief Boolean indiquant si une cl� usb est connect�e.
 */
BOOL isThumbDriveAttached;

/**
 * \var isTestEnter
 * \brief boolean indiquant l'entree en test.
 */
BOOL isTestEnter;

/**
 * \var isAuditEnable
 * \brief Variable indiquant que l'audit est autoris�.
 */
BOOL isAuditEnable;

/**
 * \var isConfigEnable
 * \brief Variable indiquant que le param�trage de la centrale est autoris�
 */
BOOL isConfigEnable;

/**
 * \var isHistoEnable
 * \brief Variable indiquant que la lecture de l'historique est autoris�.
 */
BOOL isHistoEnable;

/**
 * \var isRAZEnable
 * \brief Variable indiquant que la remise � z�ro des audits est autoris�.
 */
BOOL isRAZEnable;

/**
 * \var isRefillingEnable
 * \brief Variable indiquant que le refilling est autoris�.
 */
BOOL isRefillingEnable;

/**
 * \var isFileCreditPresent
 * \brief Indique qu'une cl� USB est pr�sente qu'elle contient un fichier de cr�dit.
 */
BOOL isFileCreditPresent;

/**
 * \var isChangeInProgress
 * \brief Indique si le rendeur effectue une op�ration de change.
 */
BOOL isChangeInProgress;

/**
 * \var isFillingInProgress
 * \brief Indique si le remplissage du rendeur est en cours.
 */
BOOL isFillingInProgress;

/**
 * \var hTimerTOBuzzer
 * \brief Timer du buzzer.
 */
TimerHandle_t hTimerTOBuzzer;

/**
 * \var AppConfig
 * http
 * \brief Declare AppConfig structure and some other supporting stack variables
 */
APP_CONFIG AppConfig;

/**
 * \var searchRec
 * \brief Structure qui contiendra les param�tres du fichier recherch�.
 */
SearchRec searchRec;

/**
 * \var creditFile
 * \brief Pointeur sur la structure du fichier de cr�dits.
 */
FSFILE *creditFile;

/*
 * \var ProcessIOState
 * \brief Variable contenant le statut du p�riph�rique USB.
 */
PROCESSIOSTATE ProcessIOState;

static unsigned short wOriginalAppConfigChecksum; /*!< Checksum of the ROM defaults for AppConfig*/

/*--------------------*/

TaskHandle_t hHeartBeating;
TaskHandle_t hDST;
TaskHandle_t hMDB;
TaskHandle_t hKeyBoard;
TaskHandle_t hTreatKey;
TaskHandle_t hUSB;
TaskHandle_t hTimeDisplay;
TaskHandle_t hFlip;
TaskHandle_t hTest;
TaskHandle_t hChange;

BYTE byCheckStack[20];

/**
 * \var isUSBPolled
 * \brief Indique si le port USB a �t� poll�.
 */
BOOL isUSBPolled;

BOOL isDisplayPolled;

BOOL isFlipDisplayPolled;

/**Prototypes******************************************************************/

/**
 * \fn vLaunchMachine
 * \brief Effectue les op�rations correspondant au num�ro de machine.
 * \param[in] byNumSatellite Num�ro de la machine � activer.
 */
void vLaunchMachine(const BYTE byNumSatellite);

/**
 * \fn byMachineExist
 * \brief Recherche l'index dont le num�ro est pass� en param�tre.
 * @param[in] byMachine Num�ro de la machine dont on recherche l'index.
 * @return L'index dans la liste des machines si le num�ro de machine existe sinon MAXMACHINE.
 */
BYTE byMachineExist(const BYTE byMachine);

#ifdef __L_DEBUG

/**
 * \brief Fonction appel�e en cas d'echec d'allocation dans FreeRTOS.
 * \details vApplicationMallocFailedHook() will only be called if
 * configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
 * function that will get called if a call to pvPortMalloc() fails.
 * pvPortMalloc() is called internally by the kernel whenever a task, queue,
 * timer or semaphore is created.  It is also called by various parts of the
 * demo application.  If heap_1.c or heap_2.c are used, then the size of the
 * heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
 * FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
 * to query the size of free heap space that remains (although it does not
 * provide information on how the remaining heap might be fragmented).
 */
void vApplicationMallocFailedHook(void);

/******************************************************************************/
/**
 * \brief Fonction appel�e en cas de pile insuffisante lors de la cr�ation d'une t�che.
 * \detail Run time task stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook function is
    called if a task stack overflow is detected.  Note the system/interrupt
    stack is not checked.
 * @param pxTask Handle de la t�che.
 * @param pcTaskName Nom de la tache
 */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, signed char *pcTaskName);
#endif

#endif	/* MAIN_H */
