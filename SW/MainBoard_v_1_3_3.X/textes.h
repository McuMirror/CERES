/* 
 * File:   textes.h
 * Author: RA
 *
 * Created on 21 janvier 2014, 10:50
 */

#ifndef TEXTES_H
#define	TEXTES_H
//#define UPPERCASE

#ifdef UPPERCASE
char *byTexte[] = {
                   "SELECTION MACHINE:", //SELECTION_MACHINE, 0
                   "PIECE:", //COIN, 1
                   "BILLET:", //BILL, 2
                   "(#)CONTINUER", //CONTINUE, 3
                   "(*)SORTIR", //EXIT, 4
                   "(1)CONFIGURATION", //CONFIGURATION, 5
                   "(2)AUDIT", //AUDIT, 6
                   "(3)HISTORIQUE", //HISTORIQUE, 7
                   "(1)RENDEUR", //CHANGEGIVER, 8
                   "(2)LECTEUR BILLETS", //BILLVALIDATOR, 9
                   "(3)CASHLESS", //CASHLESS, 10
                   "(0)NON", //DISABLE, 11
                   "(1)OUI", //ENABLE, 12
                   "SUIVANT", //NEXT, 13
                   "PRIX:", //PRICE, 14
                   "(*)CORRECTION", //CORRECT, 15
                   "(*)POUR ANNULER", //CANCEL, 16
                   "DISPO CLEF:", //INKEY, 17
                   "DISPO.:", //DISPO, 18
                   "RENDU:", //RETURNED, 19
                   "FAITES L'APPOINT", //EXACTCHANGE, 20
                   "CLE ID:", //MEDIA_ID, 21
                   "MAXIMUM ATTEINT!", //MAXI, 22
                   "ADRESSE: 0X", //ADDRESSMDB, 23
                   "ECHEC DE VENTE.", //SALEFAILURE, 24
                   "MONTANT:", //AMOUNT, 25
                   "MACHINE", //NUMMACHINE, 26
                   "INTRODUIT:", //INTRODUCED, 27
                   "(4)DATE HEURE", //DATETIME, 28
                   "HEURE", //HEURE, 29
                   "DATE", //DATE, 30
                   "(3)MACHINES", //SATELLITE, 31
                   "(1)RETRAIT AUTO", //RETRAITAUTO, 32
                   "(2)NOUVELLE MACH.", //NEWMACHINEMANUAL, 33
                   "(3)MODIFICATION", //MODIFICATIONMACHINE, 34
                   "(4)SUPPRESION", //REMOVEMACHINE, 35
                   "RECHERCHE...", //SEARCH, 36
                   "NUMERO MACHINE:", //NUMERO,37
                   "MACHINE REFERENTE:", //REFERENCE, 38
                   "(#)PASSER", //PASS, 39
                   "MACHINE EXISTANTE!", //MACHINEEXIST, 40
                   "TROP DE MACHINES!", //TOOMANYMACHINE, 41
                   "INDISPONIBLE", //MACHINEMISSING, 42
                   "PRIX BASE EN ESPECES:", //PRICECASH, 43
                   "PRIX AVEC CLEF:", //PRICECASHLESS, 44
                   "PRIX EN HEURES CREUSES:", //PRICECASH_HH, 45
                   "PRIX CLEF HEURES CREUSES:", //PRICECASHLESS_HH, 46
                   "MACHINE %U EN ROUTE...", //INPROGRESS, 47
                   "IMPULSION COMMANDE EN MS:", //PULSEDELAY, 48
                   "AFFICHE TEMPS RESTANT:", //DSPTIMEREMAINING, 49
                   "DELAI SUROCCUPATION EN MS:", //OVERBUSY, 50
                   "HEURE MISE EN ROUTE:", //TIMESTART, 51
                   "HEURE FIN:", //TIMEEND, 52
                   "HEURE DEBUT HEURES CREUSES:", //HHSTART, 53
                   "HEURE FIN HEURES CREUSES:", //HHEND, 54
                   "CUMUL AUTORISE:", //CUMUL,55
                   "SATELLITE %U EFFACE!", //MACHINEREMOVED,56
                   "PARAMETRES MACHINE %U ENREGISTRES!", //MACHINEREGISTERED, 57
                   "ENREGISTRER", //SAVE, 58
                   "PRECEDENT", //BACK, 59
                   "(1)PARAMETRES", //PARAMETERS,60
                   "PAS DE NOUVEAU MODULE", //NOMODULE, 61
                   "TERMINE", //COMPLETED, 62
                   "HORS PLAGE HORAIRE", //OVERTIME, 63
                   "TEMPS RESTANT:", //REMAININGTIME, 64
                   "OCCUPEE", //OCCUPIED, 65
                   "ETES-VOUS SUR?", //CONFIRM, 66
                   "(*)NON", //NO, 67
                   "(#)OUI", //YES, 68
                   "PARAMETRES MACHINE %U EFFACES!", //REMOVED, 69
                   "ENREGISTRE!", //REGISTRED, 70
                   "SATELLITE", //SATELLITE2, 71
                   "RENDU EN COURS...", //RETURN, 72
                   "(2) PERIPHERIQUES", //DEVICES, 73
                   "BUZZER:", //SOUND, 74
                   "ESCROW BILLETS:", //ESCROWBILL, 75
                   "MONTANT EXACT CHANGE:", //EXACTCHANGEAMOUNT, 76
                   "DELAI CLAVIER", //KBDTO, 77
                   "DELAI CUMUL", //CUMULTO, 78
                   "DELAI TROP PERCU", //OVERPAYTO, 79
                   "EN SECONDES:", //INSECONDES, 80
                   "DELAI MESSAGES EN MS:", //MESSAGETO, 81
                   "(0)TEMPORAIRE", //TEMPORARYTEXT, 82
                   "(1)PERMANENT", //PERMANENTTEXT, 83
                   "VENTES EN ESPECES", //CASHTEXT, 84
                   "VENTE CASHLESS", //CASHLESSTEXT, 85
                   "RECHARGE CASHLESS", //REVALUECASHLESSTEXT,86
                   "TROP PERCU", //OVERPAYTEXTE,87
                   "NBR. UTILISATIONS MACHINE", //SERVICE,88
                   "PIECES %.*F\7 INTRODUITES: %U", //COININ, 89
                   "PIECES %.*F\7 RENDUES: %U", //COINOUT, 90
                   "BILLETS %.*F\7 INTRODUITS: %U", //BILLIN, 91
                   "RAZ AUDITS? ", //RAZAUDIT,,92
                   "RAZ EFFECTUE!", //RAZOK, 93
                   "ECHEC RAZ AUDITS", //RAZNOK, 94
                   "VERIFICATION", //CHECK, 95
                   "INCONNUE", //UNKNOW_OP,96
                   "MISE EN ROUTE", //INITIALISATION_OP,97
                   "MAINTENANCE", //TEST_START_OP,98
                   "START", //SELECTION_OP,99
                   "IN:", //INCG_OP,100
                   "RET.:", //OUCG_OP,101
                   "IN:", //INBV_OP,102
                   "OUT:", //OUTBV_OP,103
                   "P. CLEF", //PAYCASHLESS_OP,104
                   "R. CLEF", //REVALUECASHLESSL_OP,105
                   "CLEF", //KEYPRESENT_OP,106
                   "ANN. OVERPAY", //CANCELOVERPAY, 107
                   "REMPLISSAGE", //FILLING, 108
                   "USB INS.", //USBPRESENT, 109
                   "P. USB", //PAYUSB_OP,110
                   "SAVE AUDIT", //SAVEAUDIT_OP,111
                   "INIT USB", //INITCODE_OP,112
                   "RAZ AUDITS", //RAZAUDIT_OP, 113
                   "SAVE HISTO", //SAVEHISTO_OP, 114
                   "MACHINE SELECT. ", //SELECTED, 115
                   "REJETEE", //REJECTED, 116
                   "SORTIE TEST", //TEST_EXIT,117
                   "RETRAIT USB", //TAKE_USB, 118
                   "FIN PAIEMENT", //ENDPULSE, 119
                   "SAISIE PASSWORD", //PASSWORDENTER, 120
                   "TOTAL:", //TOTAL, 121
                   "INSEREZ PIECE OU ", //INSERTCOIN, 122
                   "TEMPS A AFFICHER", //TIMEINFOTO, 123
                   "POUR", //FOR, 124
                   "SUP.", //ADDITIONAL, 125
                   "RESTE:", //CASHREMAINING, 126
                   "ECHEC ENREGISTREMENT MACHINE:", //FAILEDRECORD, 127
                   "REPRENEZ LE BILLET", //TAKEBILL, 128
                   "CLEF USB INVALIDE", //ERRORUSBKEY, 129
                   "DISPO USB:", //CREDITINUSB, 130
                   "VENTE USB", //VENDUSBTEXT, 131
                   "CODES USB REINITIALISES.", //USB_INITIALIZED, 132
                   "AUDIT_", //SAVEAUDITFILENAME, 133
                   "HISTO_", //SAVEHISTOFILENAME, 134
                   "AUDIT", //HEADERAUDIT, 135
                   "NOMBRE", //HEADERNUMBER, 136
                   "VALEUR", //HEADERVALUE, 137
                   "MONTANT", //HEADERAMOUNT, 138
                   "CANAL", //AUDITCHANNEL, 139
                   "AUDIT ENREGISTRE!", //AUDITSAVED, 140
                   "HISTORIQUE ENREGISTRE!", //HISTOSAVED, 141
                   "REUSSI", //SUCCESSFUL_OP, 142
                   "ECHEC", //FAIL_OP, 143
                   "OPERATION", //OP, 144
                   "RESULTAT", //RESULTOP, 145
                   "TEMPS A AFFICHER EN SECONDES:", //TIMETODISPLAY, 146
                   "RETIREZ CLEF.", //KTOBERETIRED, 147
                   "POUR AJOUT.", //TOADD, 148
                   "CENTRALE", //CENTRALE, 149
                   "M.D.I. - VERSION", //MDIVERSION, 150
                   "INEXISTANTE", //NONEXISTENT, 151
                   "VIDE", //TEXTEMPTY, 152
                   "SECTEUR PRESENT : ", //MAINPOWER, 153
                   "SENSIBILITE CONSOMMATION : ", //BUSYSENSIBILITY, 154
                   "PASSWORD LOCAL TECHNICIEN : ", //PWLOCALTECH, 155
                   "PASSWORD LOCAL SUPERVISOR : ", //PWLOCALCOMPTA, 156
                   "PASSWORD HTTP TECHNICIEN : ", //PWHTTPTECH, 157
                   "PASSWORD HTTP SUPERVISOR : ", //PWHTPPCOMPTA, 158
                   "CODE D'ACCES : ", //REQUESTPW, 159
                   "BILLETS ACCEPTES : ", //BILLACCEPTED, 160
                   "MACHINE %U NON ACTIVEE!", //UNACTIVED, 161
                   "INFO SUP.", //INFOSUP
                   "SECTEUR INDISPO.", MAINMISSING
};
#else
char *byTexte[] = {
                   "Selection machine:", //SELECTION_MACHINE, 0
                   "Piece:", //COIN, 1
                   "Billet:", //BILL, 2
                   "(#)Continuer", //CONTINUE, 3
                   "(*)Sortir", //EXIT, 4
                   "(1)Configuration", //CONFIGURATION, 5
                   "(2)Audit", //AUDIT, 6
                   "(3)Historique", //HISTORIQUE, 7
                   "(1)Rendeur", //CHANGEGIVER, 8
                   "(2)Lecteur billets", //BILLVALIDATOR, 9
                   "(3)Cashless", //CASHLESS, 10
                   "(0)NON", //DISABLE, 11
                   "(1)OUI", //ENABLE, 12
                   "Suivant", //NEXT, 13
                   "Prix:", //PRICE, 14
                   "(*)correction", //CORRECT, 15
                   "(*)pour annuler", //CANCEL, 16
                   "Dispo clef:", //INKEY, 17
                   "Dispo.:", //DISPO, 18
                   "Rendu:", //RETURNED, 19
                   "Faites l'appoint                       ", //EXACTCHANGE, 20
                   "Cle ID:", //MEDIA_ID, 21
                   "Maximum atteint!", //MAXI, 22
                   "Adresse: 0X", //ADDRESSMDB, 23
                   "Echec de vente.", //SALEFAILURE, 24
                   "Montant:", //AMOUNT, 25
                   "Machine", //NUMMACHINE, 26
                   "Introduit:", //INTRODUCED, 27
                   "(4)Date heure", //DATETIME, 28
                   "Heure", //HEURE, 29
                   "Date", //DATE, 30
                   "(3)Machines", //SATELLITE, 31
                   "(1)Nouvelle mach.", //NEWMACHINEMANUAL, 33
                   "(2)Modification", //MODIFICATIONMACHINE, 34
                   "(3)Suppresion", //REMOVEMACHINE, 35
                   "(4)Retrait auto", //RETRAITAUTO, 32
                   "Recherche...", //SEARCH, 36
                   "Numero machine:", //NUMERO,37
                   "Machine referente:", //REFERENCE, 38
                   "(#)Passer", //PASS, 39
                   "Machine existante!", //MACHINEEXIST, 40
                   "Trop de machines!", //TOOMANYMACHINE, 41
                   "Indisponible", //MACHINEMISSING, 42
                   "Prix base en especes:", //PRICECASH, 43
                   "Prix avec clef:", //PRICECASHLESS, 44
                   "Prix en heures creuses:", //PRICECASH_HH, 45
                   "Prix clef heures creuses:", //PRICECASHLESS_HH, 46
                   "Machine %u en route...", //INPROGRESS, 47
                   "Impulsion commande en ms:", //PULSEDELAY, 48
                   "Affiche temps restant:", //DSPTIMEREMAINING, 49
                   "Delai suroccupation en ms:", //OVERBUSY, 50
                   "Heure mise en route:", //TIMESTART, 51
                   "Heure fin:", //TIMEEND, 52
                   "Heure debut heures creuses:", //HHSTART, 53
                   "Heure fin heures creuses:", //HHEND, 54
                   "Cumul autorise:", //CUMUL,55
                   "Satellite %u efface!", //MACHINEREMOVED,56
                   "Parametres machine %u enregistres!", //MACHINEREGISTERED, 57
                   "Enregistrer", //SAVE, 58
                   "Precedent", //BACK, 59
                   "(1)Parametres", //PARAMETERS,60
                   "Pas de nouveau module", //NOMODULE, 61
                   "Termine", //COMPLETED, 62
                   "Hors plage horaire", //OVERTIME, 63
                   "temps restant:", //REMAININGTIME, 64
                   "Occupee", //OCCUPIED, 65
                   "Etes-vous sur?", //CONFIRM, 66
                   "(*)NON", //NO, 67
                   "(#)OUI", //YES, 68
                   "Parametres machine %u effaces!", //REMOVED, 69
                   "Enregistre!", //REGISTRED, 70
                   "Satellite", //SATELLITE2, 71
                   "Rendu en cours...", //RETURN, 72
                   "(2) Peripheriques", //DEVICES, 73
                   "Buzzer:", //SOUND, 74
                   "Escrow billets:", //ESCROWBILL, 75
                   "Montant exact change:", //EXACTCHANGEAMOUNT, 76
                   "Delai clavier", //KBDTO, 77
                   "Delai cumul", //CUMULTO, 78
                   "Delai trop percu", //OVERPAYTO, 79
                   "en secondes:", //INSECONDES, 80
                   "Delai messages en ms:", //MESSAGETO, 81
                   "(0)Temporaire", //TEMPORARYTEXT, 82
                   "(1)Permanent", //PERMANENTTEXT, 83
                   "Ventes en especes", //CASHTEXT, 84
                   "Vente cashless", //CASHLESSTEXT, 85
                   "Recharge cashless", //REVALUECASHLESSTEXT,86
                   "Trop percu", //OVERPAYTEXTE,87
                   "Nbr. utilisations machine", //SERVICE,88
                   "Pieces %.*f\7 introduites: %u", //COININ, 89
                   "Pieces %.*f\7 rendues: %u", //COINOUT, 90
                   "Billets %.*f\7 introduits: %u", //BILLIN, 91
                   "RAZ audits? ", //RAZAUDIT,,92
                   "RAZ effectue!", //RAZOK, 93
                   "Echec RAZ audits", //RAZNOK, 94
                   "Verification", //CHECK, 95
                   "Inconnue", //UNKNOW_OP,96
                   "Mise en route", //INITIALISATION_OP,97
                   "Maintenance", //TEST_START_OP,98
                   "Start", //SELECTION_OP,99
                   "In:", //INCG_OP,100
                   "Ret.:", //OUCG_OP,101
                   "In:", //INBV_OP,102
                   "Out:", //OUTBV_OP,103
                   "P. clef", //PAYCASHLESS_OP,104
                   "R. clef", //REVALUECASHLESSL_OP,105
                   "Clef", //KEYPRESENT_OP,106
                   "Ann. overpay", //CANCELOVERPAY, 107
                   "Remplissage", //FILLING, 108
                   "USB ins.", //USBPRESENT, 109
                   "P. USB", //PAYUSB_OP,110
                   "Save audit", //SAVEAUDIT_OP,111
                   "Init USB", //INITCODE_OP,112
                   "Raz audits", //RAZAUDIT_OP, 113
                   "Save histo", //SAVEHISTO_OP, 114
                   "Machine select. ", //SELECTED, 115
                   "Rejetee", //REJECTED, 116
                   "Sortie test", //TEST_EXIT,117
                   "Retrait USB", //TAKE_USB, 118
                   "Fin paiement", //ENDPULSE, 119
                   "Saisie password", //PASSWORDENTER, 120
                   "Total:", //TOTAL, 121
                   "Inserez piece ou ", //INSERTCOIN, 122
                   "Temps a afficher", //TIMEINFOTO, 123
                   "pour", //FOR, 124
                   "sup.", //ADDITIONAL, 125
                   "Reste:", //CASHREMAINING, 126
                   "Echec enregistrement machine:", //FAILEDRECORD, 127
                   "Reprenez le billet", //TAKEBILL, 128
                   "Clef USB invalide", //ERRORUSBKEY, 129
                   "Dispo USB:", //CREDITINUSB, 130
                   "Vente USB", //VENDUSBTEXT, 131
                   "Codes USB reinitialises.", //USB_INITIALIZED, 132
                   "AUDIT_", //SAVEAUDITFILENAME, 133
                   "HISTO_", //SAVEHISTOFILENAME, 134
                   "Audit", //HEADERAUDIT, 135
                   "Nombre", //HEADERNUMBER, 136
                   "Valeur", //HEADERVALUE, 137
                   "Montant", //HEADERAMOUNT, 138
                   "Canal", //AUDITCHANNEL, 139
                   "Audit enregistre!", //AUDITSAVED, 140
                   "Historique enregistre!", //HISTOSAVED, 141
                   "Reussi", //SUCCESSFUL_OP, 142
                   "Echec", //FAIL_OP, 143
                   "Operation", //OP, 144
                   "Resultat", //RESULTOP, 145
                   "Temps a afficher en secondes:", //TIMETODISPLAY, 146
                   "Retirez clef.", //KTOBERETIRED, 147
                   "pour ajout.", //TOADD, 148
                   "CENTRALE", //CENTRALE, 149
                   "M.D.I. - Version", //MDIVERSION, 150
                   "Inexistante", //NONEXISTENT, 151
                   "Vide", //TEXTEMPTY, 152
                   "Secteur present : ", //MAINPOWER, 153
                   "Sensibilite consommation : ", //BUSYSENSIBILITY, 154
                   "Password local technicien : ", //PWLOCALTECH, 155
                   "Password local supervisor : ", //PWLOCALCOMPTA, 156
                   "Password http technicien : ", //PWHTTPTECH, 157
                   "Password http supervisor : ", //PWHTPPCOMPTA, 158
                   "Code d'acces : ", //REQUESTPW, 159
                   "Billets acceptes : ", //BILLACCEPTED, 160
                   "Machine %u non activee!", //UNACTIVED, 161
                   "Info sup.", //INFOSUP
                   "Secteur indispo.", //MAINMISSING
};
#endif

enum
{
    SELECTION_MACHINE, //0
    COIN, //1
    BILL, //2
    CONTINUE, //3
    EXIT, //4
    CONFIGURATION, //5
    AUDIT, //6
    HISTORIQUE, //7
    CHANGEGIVER, //8
    BILLVALIDATOR, //9
    CASHLESS, //10
    DISABLE, //11
    ENABLE, //12
    NEXT, //13
    PRICE, //14
    CORRECT, //15
    CANCEL, //16
    INKEY, //17
    DISPO, //18
    RETURNED, //19
    EXACTCHANGE, //20
    MEDIA_ID, //21
    MAXI, //22
    ADDRESSMDB, //23
    SALEFAILURE, //24
    AMOUNT, //25
    NUMMACHINE, //26
    INTRODUCED, //27
    DATETIME, //28
    HEURE, //29
    DATE, //30
    SATELLITE, //31
    NEWMACHINEMANUAL, //32
    MODIFICATIONMACHINE, //33
    REMOVEMACHINE, //34
    RETRAITAUTO, //35
    SEARCH, //36
    NUMERO, //37
    REFERENCE, //38
    PASS, //39
    MACHINEEXIST, //40
    TOOMANYMACHINE, //41
    MACHINEMISSING, //42
    PRICECASH, //43
    PRICECASHLESS, //44
    PRICECASH_HH, //45
    PRICECASHLESS_HH, //46
    INPROGRESS, //47
    PULSEDELAY, //48
    DSPTIMEREMAINING, //49
    OVERBUSY, //50
    TIMESTART, //51
    TIMEEND, //52
    HHSTART, //53
    HHEND, //54
    CUMUL, //55
    MACHINEREMOVED, //56
    MACHINEREGISTERED, //57
    SAVE, //58
    BACK, //59
    PARAMETERS, //60
    NOMODULE, //61
    COMPLETED, //62
    OVERTIME, //63
    REMAININGTIME, //64
    OCCUPIED, //65
    CONFIRM, //66
    NO, //67
    YES, //68
    REMOVED, //69
    REGISTRED, //70
    SATELLITE2, //71
    RETURN, //72
    DEVICES, //73
    SOUND, //74
    ESCROWBILL, //75
    EXACTCHANGEAMOUNT, //76
    KBDTO, //77
    CUMULTO, //78
    OVERPAYTO, //79
    INSECONDES, //80
    MESSAGETO, //81
    TEMPORARYTEXT, //82
    PERMANENTTEXT, //83
    CASHTEXT, //84
    CASHLESSTEXT, //85
    REVALUECASHLESSTEXT, //86
    OVERPAYTEXTE, //87
    SERVICE, //88
    COININ, //89
    COINOUT, //90
    BILLIN, //91
    RAZAUDIT, //92
    RAZOK, //93
    RAZNOK, //94
    CHECK, //95
    UNKNOW_OP, //96
    INITIALISATION_OP, //97
    TEST_START_OP, //98
    SELECTION_OP, //99
    INCG_OP, //100
    OUCG_OP, //101
    INBV_OP, //102
    OUTBV_OP, //103
    PAYCASHLESS_OP, //104
    REVALUECASHLESSL_OP, //105
    KEYPRESENT_OP, //106
    CANCELOVERPAY, //107
    FILLING, //108
    USBPRESENT, //109
    PAYUSB_OP, //110
    SAVEAUDIT_OP, //111
    INITCODE_OP, //112
    RAZAUDIT_OP, //113
    SAVEHISTO_OP, //114
    SELECTED, //115
    REJECTED, //116
    TEST_EXIT, //117
    TAKE_USB, //118
    ENDPULSE, //119
    PASSWORDENTER, //120
    TOTAL, //121
    INSERTCOIN, //122
    TIMEINFOTO, //123
    FOR, //124
    ADDITIONAL, //125
    CASHREMAINING, //126
    FAILEDRECORD, //127
    TAKEBILL, //128
    ERRORUSBKEY, //129
    CREDITINUSB, //130
    VENDUSBTEXT, //131
    USB_INITIALIZED, //132
    SAVEAUDITFILENAME, //133
    SAVEHISTOFILENAME, //134
    HEADERAUDIT, //135
    HEADERNUMBER, //136
    HEADERVALUE, //137
    HEADERAMOUNT, //138
    AUDITCHANNEL, //139
    AUDITSAVED, //140
    HISTOSAVED, //141
    SUCCESSFUL_OP, //142
    FAIL_OP, //143
    OP, //144
    RESULT_OP, //145
    TIMETODISPLAY, //146
    KTOBERETIRED, //147
    TOADD, //148
    CENTRALE, //149
    MDIVERSION, //150
    NONEXISTENT, //151
    TEXTEMPTY, //152
    MAINPOWER, //153
    BUSYSENSIBILITY, //154
    PWLOCALTECH, //155
    PWLOCALCOMPTA, //156
    PWHTTPTECH, //157
    PWHTPPCOMPTA, //158
    REQUESTPW, //159
    BILLACCEPTED, //160
    UNACTIVED, //161
    INFOSUP, //162
    MAINMISSING, //163

} __attribute__((packed)) ETEXTE;

#endif	/* TEXTES_H */

