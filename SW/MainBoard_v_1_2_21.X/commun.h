/* 
 * File:   commun.h
 * Author: Administrateur
 *
 * Created on 30 novembre 2014, 10:33
 */

#ifndef MACHINE_H
    #define	MACHINE_H

    #ifdef	__cplusplus
extern "C"
{
    #endif

/**
 * \var byNumRefMachine
 * \brief Numéro de la machine de  référence.
 */
BYTE byNumRefMachine;

/**
 * \var byNumMachine
 * \brief Numéro de la machine en cours de sélection.
 */
BYTE byNumMachine;

/**
 * \var byIndexSelectedMachine
 * \brief Index dans la liste de la machine en cours de traitement.
 */
BYTE byIndexSelectedMachine;

/**
 * \var boFromHTTP
 * \brief Boolén indiquant si la demande vient d'un client HTTP.
 */
BOOL isFromHTTP;

/**
 * \var boFromHTTP
 * \Index de la machine en mode FTTP
 */
BYTE byIndexMachineHTPP;

/**
 * \var byManchineNumHTTP
 * \brief Numéro de la machine en cours sous HTTP
 */
BYTE byNumMachineHTTP;

/**
 * \var byHTTPNumMachine
 * \brief Copie du numéro de machine pour l'affichage dans le serveur.
 */
BYTE byHTTPNumMachine;

/**
 * \var wE2OperationPosRead
 * \brief Adresse eeprom à partir de laquelle il  faut lire l'opération.
 */
WORD wE2OperationPosRead;

/**
 * \var wE2OperationPos
 * \brief Adresse eeprom à partir de laquelle il faut écrire la dernière opéation
 */
WORD wE2OperationPos;

/**
 * \var wE2OperationPosBack
 * \brief Sauvegarde de l'adresse eeprom à partir de laquelle il faut écrire la dernière opéation
 */
WORD wE2OperationPosBack;


    #ifdef	__cplusplus
}
    #endif

#endif	/* MACHINE_H */

