/*
 * File:   RAdefine.h
 * Author: RA
 *
 * Created on 14 janvier 2014, 11:56
 */

#ifndef RADEFINE_H
#define	RADEFINE_H

#include "FreeRTOS.h"
#include "semphr.h"
#include <plib.h>

#define SECONDE (1000 / portTICK_RATE_MS)
#define MILLISEC (1 / portTICK_RATE_MS)

#define BASEYEAR 2000

/**
 * \def STAR
 * \brief Résultat de la touche étoile du clavier.
 */
#define STAR 10

/**
 * \def SHARP
 * \brief Résultat de la touche dièse du clavier.
 */
#define SHARP 12

/**
 * \def WORD_SWAP(X)
 * \brief Inverse l'octet haut et l'octet bas dans un mot \b X
 */
#define WORD_SWAP(X) (((X << 8) & 0xFFFF) | ((X >> 8) & 0xFFFF))

#define KEYMENUCONFIGURATION    1
#define KEYMEBUAUDIT            2
#define KEYMENUHISTO            3
#define KEYMENUREFILLING        4
#define KEYFORWARD              0
#define KEYNEXT                 1
#define KEYTEMPORAIRE           0
#define KEYPERMANENT            1
#define KEYNO                   0
#define KEYYES                  1
#define KEYREMOVESATELLITE      4

#define KEYSATELLITEMANUAL      1
#define KEYSATELLITEMODIF       2
#define KEYONESATELLITEREMOVE   3
#define KEYPARAMETERS           1
#define KEYDEVICES              2
#define KEYSATELLITE            3
#define KEYDATETIME             4
#define KEYCENTRALCONFIG        1
#define KEYPERIPHERIQUES        2
#define KEYSATELLITES           3

/**
 * \enum ESCREEN
 * \brief Enumération des écrans.
 */
typedef enum
{
    SCREENBEGINMAINTENANCE, /*!< Ecran de confirmation de l'entrée en maintenance.*/
    SCREENMAINMAINTENANCE, /*!< Ecran de maintenance principal.*/
    SCREENCONFIGURATION, /*!< Ecran de choix de configuration.*/
    SCREENPERIPHERIQUE, /*!< Valeur intérmediaire permettant d'effectuer le calcul du périphérique à configurer.*/
    SCREENCHANGEGIVER, /*!< Ecran de paramétrage du rendeur.*/
    SCREENBILLVALIDATOR, /*!< Ecran de paramétrage du lecteur de billet.*/
    SCREENCASHLESS, /*!< Ecran de paramétrage du lecteur cashless.*/
    SCREENSATELLITE, /*!< Ecran de choix du paramétrage du satellite.*/
    SCREENDATETIME, /*!< Ecran d'ajustement de l'horloge*/
    SUBSATELLITE, /*!< Valeur intérmédiaire permettant le calcul de l'écran de la configuration des satellites.*/
    SCREENSATELLITEMANUAL, /*!< Ecran de déclaration manuel d'un satellite.*/
    SCREENSATELLTIEMODIF, /*!< Ecran modification des paramètres d'un satellite. */
    SCREENSATELLITEREMOVE, /*!< Ecran de supression d'un satellite.*/
    SCREENSATELLITEREMOVECONFIRM, /*!< Ecrand de confirmation de la suppression des modules.*/
    SCREENNUMMACHINE, /*!< Ecran de saisie du numéro de machine.*/
    SCREENMODIFNUMMACHINE, /*!< Ecran dans le cas d'une modificaiton des paramètres d'une machine.*/
    SCREENREFMACHINE, /*!< Ecran pour la saisie du numéro de la machine de référence.*/
    SCREENPRICECASH, /*!< Ecran de saisie du prix du service.*/
    SCREENPRICECASHLESS, /*!< Ecran de saisie du prix du service avec une clé.*/
    SCREENPRICECASH_HH, /*!< Ecran de saisie du prix du service en heure creuse.*/
    SCREENPRICECASHLESS_HH, /*!< Ecran de saisie du prix du service en heure creuse avec une clé.*/
    SCREENTIMETODSP, /*!< Ecran de saisie du temps théorique à afficher.*/
    SCREENPULSE, /*!< Ecran de saisie de la longeur de l'impulsion de commande en dixieme de seconde.*/
    SCREENDSPTIMEREMAINING, /*!< Ecran de saisie d'autorisation d'affichage du temps d'occupation resatant de la machine.*/
    SCREENOVERBUSY, /*!< Ecran de saisie du temps de suroccupation de la machine.*/
    SCREENBEGIN, /*!< Ecran de saisie de l'heure d'autorisation.*/
    SCREENEND, /*!< Ecran de saisie de l 'heure de fin d'autorisation.*/
    SCREENBEGINHH, /*!< Ecran de saisie du début des heures creuses.*/
    SCREENENDHH, /*!< Ecran de saisie du début des heures creuses.*/
    SCREENCUMUL, /*!< Ecran de saisie du cumul des services.*/
    SCREENNOMODULE, /*!< Ecran de saisie en cas d'absence de module.*/
    SCREENSATELLITEAUTO, /*!< Ecran de recherche auto d'un satellite.*/
    SCREENHISTORIQUE, /*!< Ecran menu historique.*/
    SCREENBUZZER, /*!< Premier ecran des paramètres, permettant l'activation du buzzer.*/
    SCREENESCROW, /*!< Ecran permettant l'activation des billets.*/
    SCREENEXACTCHANGE, /*!< Ecran de saisie du montant en dessous duquel on affiche la demande d'appoint.*/
    SCREENTOCUMUL, /*!< Ecran de saisie du time out du cumul.*/
    SCREENTO_KBD, /*!< Ecran de saisie du time out du clavier.*/
    SCREENTO_OVERPAY, /*!< Ecran de saisie du time out de l'overpay.*/
    SCREENMESSAGEDELAY, /*!< Ecran de saisie du délai d'affichage des messages.*/
    SCREENAUDIT, /*!< Ecran principal des audits.*/
    SCREENVENDCASH, /*!< Ecran d'affichage des ventes cash.*/
    SCREENVENDCASHLESS, /*!< Ecran d'affichage des ventes cashless.*/
    SCREENREVALUECAHSLESS, /*!< Ecran d'affichage du montant des recharges cashless.*/
    SCREENOVERPAY, /*!< Ecran d'affichage des trop perçus.*/
    SCREENAUDITREFILLING, /*!< Ecran d'audit du remplissage des tubes.*/
    SCREENVENDUSB, /*!< Ecran d'affichage des ventes USB.*/
    SCREENMACHINES, /*!< Ecran des résultats par machine.*/
    SCREENINCG, /*!< Ecran des pièces insérées par type.*/
    SCREENOUTCG, /*!< Ecran des pièces retournées par le rendeur.*/
    SCREENINBV, /*!< Ecran des billets insérés par le lecteur de billets.*/
    SCREENRAZAUDIT, /*!< Ecran de requête de remise à zéro de l'audit temporaire.*/
    SCREENFILLING, /*!< Ecran de remplissage.*/
    SCREENBUSYLEVEL, /*!< Ecran permettant la saisie du niveau de sensibilité de la détection de consommation.*/
    SCREENBILLACCEPTED, /*!<Ecran permettant la saisie de l'autorisation d'utiliser les billets pour payer le service.*/
    SCREENPOWER, /*!< Ecran permettant de piloté le relais d'alimentation générale du satellite.*/
    SCREENPWLOCALTECH, /*!<Ecran de saisie du mot de passe technique local.*/
    SCREENPWLOCALCOMPTA, /*!<Ecran de saisie du mot de passe audit local.*/
    SCREENPWHTTPTECH, /*!<Ecran de saisie du mode passe technique ethernet.*/
    SCREENPWHTTPCOMPTA, /*!<Ecran de saisie du mode passe compta ethernet.*/
    SCREENREQUESTPW, /*!<Ecran de saisie du mot passe.*/
} ESCREEN;

typedef uint16_t adc_result_t;

typedef union
{
    adc_result_t wBusyLevel;
    BYTE byBusyLevel[sizeof (adc_result_t)];
} uBusyLevel;

/*Variables********************************************************************/

/**
 * \var wEcran
 * \brief Ecran en cours en mode maintenance.
 */
ESCREEN wEcran;

#endif	/* RADEFINE_H */

