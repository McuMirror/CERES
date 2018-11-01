/**
 * \file main.c
 * \author Rachid AKKOUCHE
 * \date 30 Novembre 2013, 12:07
 */

#include "main.h"

/*Gestion des interruptions****************************************************/

void __ISR(_CHANGE_NOTICE_VECTOR/*, IPL7AUTO*/) ISRChangeNotice_Handler(void)
{
    if(!PORTReadBits(VP) || !PORTReadBits(W1))
    {
        DelayMs(350);
        isToBeOFF = TRUE;
    }
    else
    {
        SoftReset();
    }
    mCNClearIntFlag();
}

/******************************************************************************/

void __ISR(_RTCC_VECTOR/*, ipl3AUTO*/) ISRRtcc(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    INTClearFlag(INT_RTCC);
    xSemaphoreGiveFromISR(semaphoreDST, &xHigherPriorityTaskWoken);
}
/******************************************************************************/

/*Routines locales ************************************************************/

/*********************************************************************
 * Function:        void InitAppConfig(void)
 *
 * PreCondition:    MPFSInit() is already called.
 *
 * Input:           None
 *
 * Output:          Write/Read non-volatile config variables.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
// MAC Address Serialization using a MPLAB PM3 Programmer and
// Serialized Quick Turn Programming (SQTP).
// The advantage of using SQTP for programming the MAC Address is it
// allows you to auto-increment the MAC address without recompiling
// the code for each unit.  To use SQTP, the MAC address must be fixed
// at a specific location in program memory.  Uncomment these two pragmas
// that locate the MAC address at 0x1FFF0.  Syntax below is for MPLAB C
// Compiler for PIC18 MCUs. Syntax will vary for other compilers.
//#pragma romdata MACROM=0x1FFF0
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2,
                                           MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4,
                                           MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
//#pragma romdata

static void InitAppConfig(void)
{
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
    unsigned char vNeedToSaveDefaults = 0;
#endif
    while(TRUE)
    {
        // Start out zeroing all AppConfig bytes to ensure all fields are
        // deterministic for checksum generation
        memset((void*)&AppConfig, 0x00, sizeof(AppConfig));

        AppConfig.Flags.bIsDHCPEnabled = TRUE;
        AppConfig.Flags.bInConfigMode = TRUE;
        memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));

        AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2 << 8ul | MY_DEFAULT_IP_ADDR_BYTE3 << 16ul | MY_DEFAULT_IP_ADDR_BYTE4 << 24ul;
        AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
        AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2 << 8ul | MY_DEFAULT_MASK_BYTE3 << 16ul | MY_DEFAULT_MASK_BYTE4 << 24ul;
        AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
        AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2 << 8ul | MY_DEFAULT_GATE_BYTE3 << 16ul | MY_DEFAULT_GATE_BYTE4 << 24ul;
        AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2 << 8ul | MY_DEFAULT_PRIMARY_DNS_BYTE3 << 16ul | MY_DEFAULT_PRIMARY_DNS_BYTE4 << 24ul;
        AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2 << 8ul | MY_DEFAULT_SECONDARY_DNS_BYTE3 << 16ul | MY_DEFAULT_SECONDARY_DNS_BYTE4 << 24ul;

        // Load the default NetBIOS Host Name
        memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
        FormatNetBIOSName(AppConfig.NetBIOSName);

        // Compute the checksum of the AppConfig defaults as loaded from ROM
        wOriginalAppConfigChecksum = CalcIPChecksum((BYTE*) & AppConfig, sizeof(AppConfig));
        break;
    }
}

/******************************************************************************/

/*Programme principal *********************************************************/

int main(void)
{
    BYTE byIndex;

    /*Desactive le port JTAG*/
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    /*Configure le pic en  fonction de la fréquence*/
    SYSTEMConfigPerformance(configCPU_CLOCK_HZ);
    /*Active le systéme en mode interruption multiple*/
    INTEnableSystemMultiVectoredInt();

    /*Debut programme principal*/
    DisableWDT();
    InitI2CE2promL(I2C2, configPERIPHERAL_CLOCK_HZ);
    vInitialization();

    //Effacement de l'eeprom si nécessaire.
    if(!PORTReadBits(ResetEEprom))
    {
        //Reset l'eeprom
        vEraseEEprom();
    }

    //--------------
    //TODO A supprimer dans la version release.
    //  - Test du delay
    //    PORTSetBits(IOPORT_B, BIT_2);
    //    Delay10us(10);
    //    PORTSetPinsDigitalOut(IOPORT_B, BIT_2);
    //    while(TRUE)
    //    {
    //        PORTToggleBits(IOPORT_B, BIT_2);
    //        DelayMs(50);
    //    }

    vGetParametersAudits();
    /**************************************************************************/

    if(
       //Version 1.2.6
       xTaskCreate(vTaskBeatingHearth, "WTD", STACKHEARTBEATING, NULL, 3, hHeartBeating) &&
       //-----------------
       xTaskCreate(vTaskCheckDST, "DST", STACKDST, NULL, 1, hDST) &&
       xTaskCreate(vTaskPollMDB, "MDBCL", STACKMDB, NULL, 3, hMDB) &&
       xTaskCreate(vTaskCheckKeyBoard, "KEYBOARD", STACKKBD, NULL, 3, hKeyBoard) &&
       xTaskCreate(vTaskTreatKey, "KEYHIT", STACKTREATKEY, NULL, 3, hTreatKey) &&
       xTaskCreate(vTaskCheckUSB, "USB HOST", STACKUSB, NULL, 2, hUSB) &&
       xTaskCreate(vTaskDisplayTime, "DSP_TIME", STACKDSPTIME, NULL, 2, hTimeDisplay) &&
       xTaskCreate(vTaskFlipDisplay, "FLIP", STACKFLIP, NULL, 3, hFlip) &&
       xTaskCreate(vTaskTest, "TEST", STACKTEST, NULL, 1, hTest) &&
       xTaskCreate(vTaskDoChange, "CHANGE", STACKCHANGE, NULL, 3, hChange))
    {
        semaphoreDST = xSemaphoreCreateBinary();
        semaphoreTest = xSemaphoreCreateBinary();
        semaphoreChange = xSemaphoreCreateBinary();
        semaphoreMDB = xSemaphoreCreateMutex();
        queueKeyHit = xQueueCreate(1, sizeof(BYTE));

#ifdef __L_DEBUG
        vQueueAddToRegistry(semaphoreMDB, "SEMDB");
        vQueueAddToRegistry(semaphoreTest, "SETST");
        vQueueAddToRegistry(queueKeyHit, "QKEY");
#endif
        hTimerTOKBD = xTimerCreate("KEY_TO", (centralParameters.byKBDTO + 1) * SECONDE, pdFALSE,
                                   NULL, vTOKBD);
        hTimerTOOverpay = xTimerCreate("OVERPAY", (centralParameters.byOverPayTO + 1) * SECONDE,
                                       pdFALSE, NULL, vTOOverPay);
        hTimerTOCumul = xTimerCreate("CUMUL", (centralParameters.byCumulTO + 1) * SECONDE,
                                     pdFALSE, NULL, vTOCumul);
        hTimerKBDRepeat = xTimerCreate("RPT_KBD", lRepeatKBD + 1, pdFALSE, NULL, vTimerRepeat);
        hTimerFlip = xTimerCreate("FLIP", PREDELAYFLIP, pdFALSE, NULL, vTimerFlip);
        hTimerTOBuzzer = xTimerCreate("BUZZER", TOBUZZER, pdFALSE, NULL, vTOBuzzer);

        for(byIndex = 0; byIndex < MAXMACHINES; byIndex++)
        {
            ClrWdt();
            modules[byIndex].timerActivationMachine = xTimerCreate("PULSE", modules[byIndex].config.lPulseInMS,
                                                                   pdFALSE, &byIndex, vTimerMachineEndPulse);
#ifndef __L_DEBUG
            if((modules[byIndex].config.byNumero > 9) && (modules[byIndex].config.byNumero < 99) &&
               (wGetSatelliteFWVersion(modules[byIndex].config.byNumero) < 120))
            {
                boModifyMachineRelayState(modules[byIndex].config.byNumero, RELAY_OFF);
            }
#endif
        }

        IEC1bits.AD1IE = FALSE;
        IEC1CLR = 0X0002;

        xSemaphoreGive(semaphoreMDB);
        vSetHisto(0, 0, INITIALISATION, 0, SUCCESSFUL);
#ifndef __L_DEBUG
        EnableWDT();
#endif
        vTaskStartScheduler();
        for(;;);
    }
    return 0;
}

/******************************************************************************/

/*********************************************************************
 * Function:        void DisplayLine(BYTE *byData)
 *
 * PreCondition:    None
 *
 * Input:           byData pointeur sur la ligne à afficher
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void DisplayLine(BYTE *byData)
{
    BYTE byIndex = 0;
    do
    {
        while(LCD_IsBusy());
        PORTSetBits(LCD_RS);
        LCDSetValue(byData[byIndex]);
    }while(byData[++byIndex]);
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vInitalization(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vInitialization(void)
{
    wEcran = SCREENBEGINMAINTENANCE;
    lRepeatKBD = REPEATDELAYKBDBYDEFAULT;
    boFlip = boCancel = isFileCreditPresent = isTOCumul =
        boChangeAutorized = isTO_KBDEnable = boDisplayRemaining = isTO_KBDEnable =
        boToEscrow = boDisplayRemaining = boFromHTTP = isChangeInProgress =
        isToBeOFF = isFillingInProgress = FALSE;
    memset(byBuffer, 0, sizeof(byBuffer));
    memset(byCreditFileName, 0, sizeof(byCreditFileName));
    wTORequest = byPosNum = lOldAmountUSBDispo = lAmountToPay =
        lOldAmountInCashDispo = lAmountUSBDispo = lAmountInCashDispo = wPrice = 0;
    byDecimalPos = DECIMALPOSBYDEFAULT;
    byBillNumber = byIndexSelectedMachine = 0XFF;
    wCurrencyDivider = 100;
    memset(kbdButton, 0XFF, sizeof(kbdButton));

    vInit_IO();

    setbuf(stdout, NULL);
    LCDInit(2);
    //Affiche l'écran de présentation. Le scheduler n'est pas encore arrivé
    sprintf(byBuffer, "%s %s", byTexte[MDIVERSION], Version);

    DisplayLine(byBuffer);
    while(LCD_IsBusy());
    LCDSetValue(LCD_SET_DDRAM_ADDR | 0x40);
    sprintf(byBuffer, "%s *%02X%02X%02X%02X%02X%02X*", byTexte[CENTRALE],
            0XFC, EMAC1SA2 / 256, EMAC1SA1 % 256, EMAC1SA1 / 256,
            EMAC1SA0 % 256, EMAC1SA0 / 256);
    DisplayLine(byBuffer);


    InitRS485(RS485, configPERIPHERAL_CLOCK_HZ, 9600, UART_DATA_SIZE_8_BITS,
              UART_PARITY_NONE, UART_STOP_BITS_1, IOPORT_G, BIT_0);
    OpenUART(RS232_2, configPERIPHERAL_CLOCK_HZ, 9600, UART_DATA_SIZE_8_BITS,
             UART_PARITY_NONE, UART_STOP_BITS_1);
    InitMDB(MDBPORT);
    lAmountCL = lAmountBV = lAmountCG = lAmountInCashDispo = 0;
    //Annule toutes les authorisations.
    boLocalAccountantEnable = isHttpAccountantEnable = FALSE;
    RtccInit();
    while(RtccGetClkStat() != RTCC_CLK_ON);
    RtccGetTimeDate(&Now, &Today);

    //0.9.2a 2014 10 14 17:21
    //Vérification de la cohérence de la date.
    if(((Today.mday & 0x0F) > 9) || (((Today.mday >> 4) & 0xF) > 3) ||
       ((Today.mon & 0x0F) > 9) || (((Today.mon >> 4) & 0xF) > 1) ||
       ((Today.year & 0x0F) > 9) || (((Today.year >> 4) & 0xF) > 9) || (Today.wday > 6) ||
       ((Now.sec & 0x0F) > 9) || (((Now.sec >> 9) & 0xF) > 5) ||
       ((Now.min & 0x0F) > 9) || (((Now.min >> 4) & 0xF) > 5) ||
       ((Now.hour & 0x0F) > 9) || (((Now.hour >> 4) & 0xF) > 2))
    {
        Today.l = 0x15010100;
        Now.l = 0x00000100;
        RtccSetTimeDate(Now.l, Today.l);
    }
    /**********************/
    while(!RtccGetAlarmEnable())
    {
        RtccAlarmEnable();
    }
    RTCALRMbits.AMASK = 0b1001;
    INTSetVectorPriority(INT_RTCC_VECTOR, INT_PRIORITY_LEVEL_3); //Set the RTCC priority in the INT controller
    INTSetVectorSubPriority(INT_RTCC_VECTOR, INT_SUB_PRIORITY_LEVEL_1); //Set the RTCC sub-priority in the INT controller
    INTClearFlag(INT_RTCC);
    INTEnable(INT_RTCC, INT_ENABLED); //Enable the RTCC event interrupts in the INT controller.

    srand((Now.l = RtccGetTime()));

}
/******************************************************************************/

/*********************************************************************
 * Function:        void vInit_IO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vInit_IO(void)
{
    AD1CON1CLR = 0XFFFFFFF;
    AD1PCFGSET = 0XFFFFFFF;

    CM1CONbits.ON = FALSE;
    CM2CONbits.ON = FALSE;

    //Led
    PORTSetPinsDigitalOut(RED);
    LEDON(RED);

    //Bouton de test
    PORTSetBits(ONBOARDBUTTON);
    PORTSetBits(W1);
    PORTSetBits(VP);
    PORTSetPinsDigitalIn(ONBOARDBUTTON);
    PORTSetPinsDigitalIn(W1);
    PORTSetPinsDigitalIn(VP);

    //Jumper d'initialisation de l'eeprom.
    PORTSetBits(ResetEEprom);
    PORTSetPinsDigitalIn(ResetEEprom);

    vEnableCN();

    //Buzzer
    PORTSetPinsDigitalOut(BUZZER);
    PORTClearBits(BUZZER);

    //Clavier
    PORTSetBits(ROWPORT, LIGNES | COLONNES); //Positionne le port du clavier à l'etat haut.
    PORTSetPinsDigitalIn(COLUMNPORT, COLONNES); //Positionne les colonnes en entrées.
    PORTSetPinsDigitalOut(ROWPORT, LIGNES); //Positionne les lignes en sorties.

    //Reset du port MDB
    PORTSetPinsDigitalOut(MDBLINE);
    PORTClearBits(MDBLINE);
    DelayMs(500);
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vScreenHistorique(const BYTE byKeyHit)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vScreenHistorique(const BYTE byKeyHit)
{
    UOPERATION histoData;
    memset(byBuffer, 0, sizeof(byBuffer));
    //Si c'est la touche étoile, retour à l'ecran de maintenance.
    if(byKeyHit == STAR)
    {
        wEcran = SCREENMAINMAINTENANCE;
    }
    else
    {
        if(sender == MAINMAINTENANCE)
        {
            //Récupèration de l'adresse actuelle de l'historique
            wE2OperationPosRead = wE2OperationPos;
            sender = HISTORIQUEMENU;
        }
        else
        {
            switch(byKeyHit)
            {
                case KEYFORWARD:
                {
                    wE2OperationPosRead -= sizeof(UOPERATION);
                    if(wE2OperationPosRead < ADDRESS_HISTO)
                    {
                        wE2OperationPosRead = (0xFFFF - sizeof(histoData) + 1);
                        I2CE2promLReadBuffer(wE2OperationPosRead, &histoData, sizeof(UOPERATION));
                        if((histoData.Operation & 0XFF) == NONEOP)
                        {
                            wE2OperationPosRead = wE2OperationPos;
                        }
                    }
                }
                    break;
                case KEYNEXT:
                {
                    wE2OperationPosRead += sizeof(UOPERATION);
                    if(wE2OperationPosRead > wE2OperationPos)
                    {
                        wE2OperationPosRead = ADDRESS_HISTO;
                    }
                }
                    break;
                default:
                {
                    break;
                }
            }
        }
        I2CE2promLReadBuffer(wE2OperationPosRead, &histoData, sizeof(UOPERATION));
        sprintf(byBuffer, "%02X-%02X-%02X %02X:%02X:%02X %s", histoData.date.mday,
                histoData.date.mon, histoData.date.year, histoData.time.hour,
                histoData.time.min, histoData.time.sec, byTexte[UNKNOW_OP + histoData.Operation]);
        switch(histoData.Operation)
        {
            case LANCEMENT:
            {
                sprintf(&byBuffer[strlen(byBuffer)], " %u  %.*f\7", histoData.byMachine, byDecimalPos, (double)histoData.lAmount / wCurrencyDivider);
            }
                break;
            case INCG:
            case INBV:
            case OUCG:
            case OVERPAYOP:
            case FILLINGOP:
            {
                sprintf(&byBuffer[strlen(byBuffer)], " %.*f\7", byDecimalPos, (double)histoData.lAmount / wCurrencyDivider);
            }
                break;
            case PAYCASHLESS:
            case REVALUECASHLESS:
            case KEYPRESENT:
            case USBPAY:
            {
                sprintf(&byBuffer[strlen(byBuffer)], " %u  %.*f\7", histoData.lKeyNumber, byDecimalPos, (double)histoData.lAmount / wCurrencyDivider);
            }
                break;
            case USBKEYINSERTED:
            {
                if(histoData.lAmount)
                {
                    sprintf(&byBuffer[strlen(byBuffer)], " %u  %.*f\7", histoData.lKeyNumber, byDecimalPos, (double)histoData.lAmount / wCurrencyDivider);
                }
            }
                break;
            default:
            {
                break;
            }
        }
    }
    //Le buffer sera passé en paramètre à la fonction vMenuMaintenance.
    ptrParameterMenu = byBuffer;
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vConfirmSatelliteRemove(const BYTE byKey)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vConfirmSatelliteRemove(const BYTE byKey)
{
    switch(byKey)
    {
        case STAR:
        {
            wEcran = SCREENSATELLITE;
            break;
        }
        case SHARP:
        {
            if(sender == REMOVESATELLITE)
            {
                LCDClear();
                memset(bySatBuffer, 0, sizeof(bySatBuffer));
                if(!boModifyMachineNumber(modules[byIndexSelectedMachine].config.byNumero, 0XFF))
                {
                    vDisplayLCD("%s %u %s", byTexte[SATELLITE],
                                modules[byIndexSelectedMachine].config.byNumero, byTexte[NONEXISTENT]);
                    DelayMs(centralParameters.lDelayDisplay);
                    LCDGotoXY(1, 2);
                }
                vDisplayLCD(byTexte[REMOVED], modules[byIndexSelectedMachine].config.byNumero);
                memset(&modules[byIndexSelectedMachine], 0XFF, sizeof(SMACHINE_CONFIG));
                I2CE2promLWriteBuffer(ADDRESS_MACHINES_PARAMETERS + (byIndexSelectedMachine * sizeof(SMACHINE_CONFIG)),
                                      &modules[byIndexSelectedMachine], sizeof(SMACHINE_CONFIG));
                wEcran = SCREENSATELLITE;
                ptrParameterMenu = NULL;
                boReturnMaintenance = TRUE;
                byPosNum = 0;
                DelayMs(centralParameters.lDelayDisplay);
            }
            else
            {
                wEcran = SCREENSATELLITEAUTO;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskCheckKeyBoard(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskCheckKeyBoard(void *pvParameter)
{
    BYTE byKey = 0;
    //DelayMs(1000);
    vResetSelectMachine();
    TickType_t LastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        if(isToBeOFF)
        {
            vSleepMCU();
        }

        if((byKey = byGetKey()) && !((byKey == 11) && !byPosNum && (UsageMode == MODEUSER) && isKBDEnable))
        {
            xQueueSendToBack(queueKeyHit, &byKey, 0);
        }
        if(!PORTReadBits(ONBOARDBUTTON))
        {
            DelayMs(30);
            if(!PORTReadBits(ONBOARDBUTTON))
            {
                while(!PORTReadBits(ONBOARDBUTTON));
                if(UsageMode != MODEUSER)
                {
                    //vReset();
                    vReturnFromTest();
                }
                else
                {
                    vSetHisto(0, 0, TEST_START, 0, SUCCESSFUL);
                    isAuditEnable = isConfigEnable = isHistoEnable = isRAZEnable = isRefillingEnable = TRUE;
                    xSemaphoreGive(semaphoreTest);
                }
            }
            isTO_KBDEnable = TRUE;
            xTimerStart(hTimerTOKBD, 10);
        }
        vTaskDelayUntil(&LastWakeTime, DELAY_CHK_KBD);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskTreatKey(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskTreatKey(void *pvParameter)
{
    BYTE byKeyHit;

    for(;;)
    {
        xQueueReceive(queueKeyHit, &byKeyHit, portMAX_DELAY);
        vStartBuzzer(centralParameters.boBuzzer, TOBUZZER);
        isTO_KBDEnable = TRUE;
        isTOCumul = FALSE;
        xTimerStart(hTimerTOKBD, 1000);
        xTimerStop(hTimerTOCumul, 1000);
        if(byKeyHit == 11)
        {
            byKeyHit = 0;
        }
        if(UsageMode == MODEMAINTENANCE)
            // <editor-fold defaultstate="collapsed" desc="MODEMAINTENANCE">
        {
            switch(wEcran)
            {
                case SCREENBEGINMAINTENANCE:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            //vReset();
                            vReturnFromTest();
                            break;
                        }
                        case SHARP:
                        {
                            //wEcran = SCREENMAINMAINTENANCE;
                            wEcran = SCREENREQUESTPW;
                            dwValue = 0;
                            boReturnMaintenance = TRUE;
                            ptrParameterMenu = &dwValue;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case SCREENMAINMAINTENANCE:
                {
                    vScreenMainMaintenance(byKeyHit);
                    break;
                }
                case SCREENCONFIGURATION:
                {
                    vScreenConfiguration(byKeyHit);
                    break;
                }
                case SCREENPERIPHERIQUE:
                {
                    vConfigDevices(byKeyHit);
                    break;
                }
                case SCREENBILLVALIDATOR:
                case SCREENCHANGEGIVER:
                {
                    vScreenCashDevice(byKeyHit);
                    break;
                }
                case SCREENCASHLESS:
                {
                    vScreenCashLess(byKeyHit);
                    break;
                }
                case SCREENSATELLITE:
                {
                    vScreenSatellite(byKeyHit);
                    break;
                }
                case SCREENNOMODULE:
                {
                    wEcran = SCREENSATELLITE;
                    boReturnMaintenance = TRUE;
                    ptrParameterMenu = NULL;
                    break;
                }
                case SCREENDATETIME:
                {
                    vScreenDateTime(byKeyHit);
                    break;
                }
                case SCREENMODIFNUMMACHINE:
                {
                    sender = MODIFMACHINES;
                    vSelectMachine(byKeyHit);
                    break;
                }
                case SCREENNUMMACHINE:
                {
                    sender = MANUALMACHINE;
                    vSelectMachine(byKeyHit);
                    break;
                }
                case SCREENREFMACHINE:
                {
                    sender = REFMACHINE;
                    vSelectMachine(byKeyHit);
                    break;
                }
                case SCREENSATELLITEREMOVE:
                {
                    sender = REMOVESATELLITE;
                    vSelectMachine(byKeyHit);
                    break;
                }
                case SCREENPRICECASH:
                case SCREENPRICECASHLESS:
                case SCREENPRICECASH_HH:
                case SCREENPRICECASHLESS_HH:
                case SCREENEXACTCHANGE:
                {
                    vSetPrice(byKeyHit);
                    break;
                }
                case SCREENPULSE:
                case SCREENOVERBUSY:
                case SCREENTO_KBD:
                case SCREENTOCUMUL:
                case SCREENTO_OVERPAY:
                case SCREENMESSAGEDELAY:
                case SCREENTIMETODSP:
                case SCREENBUSYLEVEL:
                case SCREENPWLOCALTECH:
                case SCREENPWLOCALCOMPTA:
                case SCREENPWHTTPTECH:
                case SCREENPWHTTPCOMPTA:
                case SCREENREQUESTPW:
                {
                    vSetDelay(byKeyHit);
                    break;
                }
                case SCREENBEGIN:
                case SCREENEND:
                case SCREENBEGINHH:
                case SCREENENDHH:
                {
                    vSetTime(byKeyHit);
                    break;
                }
                case SCREENDSPTIMEREMAINING:
                {
                    vScreenDspTimeRemaining(byKeyHit);
                    break;
                }
                case SCREENCUMUL:
                {
                    vScreenCumul(byKeyHit);
                    break;
                }
                case SCREENPOWER:
                {
                    vScreenPower(byKeyHit);
                    break;
                }
                case SCREENBILLACCEPTED:
                {
                    vScreenBillAccepted(byKeyHit);
                    break;
                }
                case SCREENSATELLITEREMOVECONFIRM:
                {
                    vConfirmSatelliteRemove(byKeyHit);
                    break;
                }
                case SCREENBUZZER:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            wEcran = SCREENCONFIGURATION;
                            break;
                        }
                        case KEYNO:
                        case KEYYES:
                        {
                            vDisplayEnableChoice(byTexte[SOUND], (centralParameters.boBuzzer = (BOOL)byKeyHit));
                            DelayMs(centralParameters.lDelayDisplay);
                        }
                            /* fall through */
                        case SHARP:
                        {
                            wEcran = SCREENESCROW;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case SCREENESCROW:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            wEcran = SCREENBUZZER;
                            break;
                        }
                        case KEYNO:
                        case KEYYES:
                        {
                            vDisplayEnableChoice(byTexte[ESCROWBILL], (centralParameters.boEscrow = (BOOL)byKeyHit));
                            DelayMs(centralParameters.lDelayDisplay);
                        }
                            /* fall through */
                        case SHARP:
                        {
                            wEcran = SCREENEXACTCHANGE;
                            dwValue = wPrice = centralParameters.wAmountExactChange;
                            ptrParameterMenu = &dwValue;
                            boReturnMaintenance = TRUE;
                            byPosNum = 0;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case SCREENAUDIT:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            wEcran = SCREENMAINMAINTENANCE;
                            break;
                        }
                        case KEYTEMPORAIRE:
                        case KEYPERMANENT:
                        {
                            eAudit = byKeyHit;
                            wEcran++;
                            dwValue = (eAudit == TEMPORARY) ? auditData.data.dwVendCash : auditDataPermanent.data.dwVendCash;
                            ptrParameterMenu = &dwValue;
                            boReturnMaintenance = TRUE;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case SCREENVENDCASH:
                case SCREENVENDCASHLESS:
                case SCREENREVALUECAHSLESS:
                case SCREENOVERPAY:
                case SCREENAUDITREFILLING:
                case SCREENVENDUSB:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            switch(wEcran)
                            {
                                case SCREENVENDCASHLESS:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwVendCash : auditDataPermanent.data.dwVendCash;
                                    break;
                                }
                                case SCREENREVALUECAHSLESS:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwVendCL : auditDataPermanent.data.dwVendCL;
                                    break;
                                }
                                case SCREENOVERPAY:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwRefilling : auditDataPermanent.data.dwRevalueCL;
                                    break;
                                }
                                case SCREENAUDITREFILLING:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwVendUSB : auditDataPermanent.data.dwOverPay;
                                    break;
                                }
                                case SCREENVENDUSB:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwRevalueCL : auditDataPermanent.data.dwRefilling;
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                            wEcran--;
                            break;
                        }
                        case SHARP:
                        {
                            switch(wEcran)
                            {
                                case SCREENVENDCASH:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwVendCL : auditDataPermanent.data.dwVendCL;
                                    break;
                                }
                                case SCREENVENDCASHLESS:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwRevalueCL : auditDataPermanent.data.dwRevalueCL;
                                    break;
                                }
                                case SCREENREVALUECAHSLESS:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwOverPay : auditDataPermanent.data.dwOverPay;
                                    break;
                                }
                                case SCREENOVERPAY:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwRefilling : auditDataPermanent.data.dwRefilling;
                                    break;
                                }
                                case SCREENAUDITREFILLING:
                                {
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwVendUSB : auditDataPermanent.data.dwVendUSB;
                                    break;
                                }
                                case SCREENVENDUSB:
                                {
                                    byIndexSelectedMachine = 0X0;
                                    dwValue = 0;
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                            wEcran++;
                            ptrParameterMenu = &dwValue;
                            boReturnMaintenance = TRUE;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case SCREENMACHINES:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            while((--byIndexSelectedMachine < MAXMACHINES) && (modules[byIndexSelectedMachine].config.byNumero > 100));
                            if(byIndexSelectedMachine >= MAXMACHINES)
                            {
                                wEcran--;
                                dwValue = (eAudit == TEMPORARY) ? auditData.data.dwOverPay : auditDataPermanent.data.dwOverPay;
                            }
                            break;
                        }
                        case SHARP:
                        {
                            byIndexSelectedMachine++;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    boReturnMaintenance = TRUE;
                    break;
                }
                case SCREENINCG:
                case SCREENOUTCG:
                case SCREENINBV:
                {
                    switch(byKeyHit)
                    {
                        case STAR:
                        {
                            if(byCashPos)
                            {
                                byCashPos--;
                            }
                            else
                            {
                                wEcran--;
                                //Récupère l'index de la dernière machine.
                                byIndexSelectedMachine = MAXMACHINES;
                                while((--byIndexSelectedMachine < MAXMACHINES) && modules[byIndexSelectedMachine].config.byNumero > 99);
                                //Récupère l'index du dernier canal utile du rendeur.
                                byCashPos = MAXCASHCHANNELS;
                                while(--byCashPos && ((changeGiverConfig.byCoinValue[byCashPos] == 0XFF) ||
                                                      (changeGiverConfig.byCoinValue[byCashPos] == 0x00)));
                                if(byIndexSelectedMachine == 0XFF)
                                {
                                    wEcran--;
                                    dwValue = (eAudit == TEMPORARY) ? auditData.data.dwOverPay : auditDataPermanent.data.dwOverPay;
                                }
                            }
                            break;
                        }
                        case SHARP:
                        {
                            ((wEcran == SCREENINBV) && (eAudit == PERMANENT) && byCashPos >= MAXNUMBERCHANNELSBV) ?
                                wEcran = SCREENMAINMAINTENANCE :
                                byCashPos < MAXCASHCHANNELS ? byCashPos++ : wEcran++;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    boReturnMaintenance = TRUE;
                    break;
                }
                case SCREENRAZAUDIT:
                {
                    switch(byKeyHit)
                    {
                        case SHARP:
                        {
                            boRAZAudit();
                        }
                            /* fall trough */
                        case STAR:
                        {
                            wEcran = SCREENAUDIT;
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    break;
                }
                case SCREENHISTORIQUE:
                {
                    vScreenHistorique(byKeyHit);
                    break;
                }
                case SCREENFILLING:
                {
                    if(byKeyHit == STAR)
                    {
                        //Sauvegarde des audits.
                        auditData.data.dwRefilling += lAmountCG;
                        auditDataPermanent.data.dwRefilling += lAmountCG;
                        I2CE2promLWriteBuffer(ADDRESS_DWREFILLING, &auditData.data.dwRefilling, sizeof(auditData.data.dwRefilling));
                        I2CE2promLWriteBuffer(ADDRESS_DWREFILLING_PERMANENT, &auditDataPermanent.data.dwRefilling, sizeof(auditDataPermanent.data.dwRefilling));
                        //Sauvegarde de l'historique.
                        vSetHisto(0, 0, FILLINGOP, lAmountCG, SUCCESSFUL);
                        isFillingInProgress = FALSE;
                        //Provoquera le retour à l'écran du menu principal.
                        wEcran = SCREENMAINMAINTENANCE;
                        boEnableChanger(FALSE, &centralParameters.coinType);
                        DelayMs(10);
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
        }// </editor-fold>
        else
        {
            vSelectMachine(byKeyHit);
        }
        byKeyHit = 0;
        if(boReturnMaintenance)
        {
            vMaintenanceMenu(ptrParameterMenu);
        }
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskPollMDB(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/

void vTaskPollMDB(void *pvParameter)
{
    DWORD wAmountSubstract = 0;
    BYTE byMDBCLBuffer[32] = {0};
    BYTE byMDBBVBuffer[32] = {0};
    BYTE byIndex = 0, byLen = 0;
    byBeforeRetryBV = byBeforeRetryCG = byBeforeRetryCL = 0;
    boVendRequested = FALSE;
#ifndef __L_DEBUG
    DelayMs(1000);
#endif
    vEnableCashDevice(FALSE, 0XFF);
    TickType_t LastWakeTime = xTaskGetTickCount();
    for(;;)
    {

        xSemaphoreTake(semaphoreMDB, 15000);
                if(!boCashLessReseted)
                {
                    if(!byBeforeRetryCL--)
                    {
                        DelayMs(500);
                        byBeforeRetryCL = MDBRETRY + 2; //ajoute 2 pour provoquer 1 décalage.
                        boCashLessReseted = boMDBReset(centralParameters.byCLAddress);
                    }
                }
                else
                {
                    if((byLen = byMDBPoll(centralParameters.byCLAddress, byMDBCLBuffer)) > 1)
                    {
                        byIndex = 0;
                        while(byIndex < (byLen - 1))
                        {
                            switch(byMDBCLBuffer[byIndex])
                            {
                                case RSP_JUST_RESET: //00 Si le cashless un reset vient d'être effectuée,
                                {
                                    byIndex++;
                                    boCashLessReseted = boMDBSetupCLConfig(centralParameters.byCLAddress,
                                                                           &vmcConfig); //Configuration de la VMC
        
                                    break;
                                }
                                case RSP_READER_CONFIG_DATA: //01 Réponse à la configuration de la VMC
                                {
                                    byIndex += 8;
                                    memmove(&readerConfig, &byMDBCLBuffer[1], sizeof(READERConfig)); //Récupération de la configuration du cashless.
                                    wCurrencyDivider = wDecimalDivider(byDecimalPos = readerConfig.deviceConfig.byDecimalPlace);
                                    boCashLessReseted = FALSE;
                                    wmcMaxMinPrices.wMax = 0XFFFF;
                                    wmcMaxMinPrices.wMin = 0X0000;
                                    if(boMDBSetupMaxMinPrice(centralParameters.byCLAddress, &wmcMaxMinPrices))
                                    {
                                        boCashLessReseted = boMDBCLEnable(centralParameters.byCLAddress); //Fixe les prix maximum et minimum et active le lecteur.
                                    }
                                    break;
                                }
                                case RSP_DISPLAY_REQUEST: //02 Demande d'affichage. Non traité par ce software
                                {
                                    byIndex += (byLen - 1);
                                    break;
                                }
                                case RSP_BEGIN_SESSION: //03 Début d'une transaction, une sélection peut-être effectuée.
                                {
                                    byIndex += 10;
                                    boKeyPresent = TRUE; //Indique que la clé est présent sur le support.
                                    boChangeAutorized = FALSE;
                                    boRevalueRequested = FALSE;
                                    lAmountCL = byMDBCLBuffer[1] * 256 + byMDBCLBuffer[2]; //Calcul du montant de la clé sur le support
                                    dwMediaID = byMDBCLBuffer[3] * 0x1000000 +
                                        byMDBCLBuffer[4] * 0x10000 +
                                        byMDBCLBuffer[5] * 0x100 +
                                        byMDBCLBuffer[6]; //Calcul de l'identifiant unique de la clé
                                    boCashLessReseted = boMDBLimitRevalueRequest(centralParameters.byCLAddress); //Demande la limite de rechargement.
                                    //Le reste des opérations s'effectue lors de la réponse à la requête de limit.
                                    break;
                                }
                                case RSP_SESSION_CANCEL_REQUEST: //04 Demande de fin de transaction
                                {
                                    byIndex++;
                                    lAmountCL = 0;
                                    boKeyPresent = FALSE;
                                    boCashLessReseted = boMDBSessionComplete(centralParameters.byCLAddress);
                                    break;
                                }
                                case RSP_VEND_APPROVED: //05 Vente acceptée
                                {
                                    byIndex += 3;
                                    wAmountSubstract = byMDBCLBuffer[1]*256 + byMDBCLBuffer[2];
                                    lAmountToDisplay = (lAmountCL -= wAmountSubstract);
                                    if(boMDBVendSuccess(centralParameters.byCLAddress))
                                    {
                                        DelayMs(centralParameters.lDelayDisplay);
                                        vLaunchMachine(byNumMachine);
                                        auditData.data.dwVendCL += wAmountSubstract;
                                        auditDataPermanent.data.dwVendCL += wAmountSubstract;
                                        I2CE2promLWriteBuffer(ADDRESS_DWCASHLESSVEND, &auditData.data.dwVendCL, sizeof(auditData.data.dwVendCL));
                                        I2CE2promLWriteBuffer(ADDRESS_DWCASHLESSVEND_PERMANENT,
                                                              &auditDataPermanent.data.dwVendCL,
                                                              sizeof(auditDataPermanent.data.dwVendCL));
                                        //Enregistrement de la vente effectuée avec la clé dans l'historique.
                                        vSetHisto(dwMediaID, 0, PAYCASHLESS, wAmountSubstract, SUCCESSFUL);
                                        if((byIndexSelectedMachine >= MAXMACHINES))// || !modules[byIndexSelectedMachine].config.boCumulEnable)
                                        {
                                            vResetSelectMachine();
                                        }
                                    }
                                    boVendRequested = FALSE;
                                    break;
                                }
                                case RSP_VEND_DENIED: //06 Vente refusée
                                {
                                    byIndex++;
                                    LCDClear();
                                    vDisplayLCD("%s", byTexte[SALEFAILURE]);
                                    vSetHisto(dwMediaID, 0, PAYCASHLESS, 0, FAIL);
                                    DelayMs(centralParameters.lDelayDisplay);
                                    vResetSelectMachine();
                                    boVendRequested = FALSE;
                                    break;
                                }
                                case RSP_END_SESSION://07 Fin de transaction
                                {
                                    byIndex++;
                                    boKeyPresent = FALSE;
                                    vEnableCashDevice(FALSE, 0XFF);
                                    lAmountCL = 0;
                                    wKeyAmountMax = 0;
                                    vResetSelectMachine();
                                    break;
                                }
                                case RSP_CANCELLED: //08 Vente annulée
                                {
                                    byIndex++;
                                    break;
                                }
                                case RSP_PERIPHERAL_ID: //09 Identification du périphérique
                                {
                                    byIndex += sizeof(PeripheralID);
                                    memmove(&peripheralID, byMDBCLBuffer, sizeof(PeripheralID));
                                    break;
                                }
                                case RSP_MALFUNCTION_ERROR: //10 Disfonctionnement
                                {
                                    byIndex += 2;
                                    boCashLessReseted = FALSE;
                                    break;
                                }
                                case RSP_CMD_OUT_OF_SEQUENCE: //11
                                {
                                    byIndex += 2;
                                    boCashLessReseted = FALSE;
                                    break;
                                }
                                case RSP_BUSY: //12 lecteur occupé
                                {
                                    break;
                                }
                                case RSP_REVALUE_APPROVED: //13 Rechargement accepté
                                {
                                    byIndex++;
                                    boRevalueRequested = FALSE;
                                    byLCDAddressCounter = getLCDAddress();
                                    vDisplayAmount(lAmountToDisplay = (lAmountCL += lAmountInCashDispo), byTexte[INKEY], TRUE);
                                    auditData.data.dwRevalueCL += lAmountInCashDispo;
                                    I2CE2promLWriteBuffer(ADDRESS_DWCASHLESSREVALUE, &auditData.data.dwRevalueCL, sizeof(auditData.data.dwRevalueCL));
                                    auditDataPermanent.data.dwRevalueCL += lAmountInCashDispo;
                                    I2CE2promLWriteBuffer(ADDRESS_DWCASHLESSREVALUE_PERMANENT,
                                                          &auditDataPermanent.data.dwRevalueCL,
                                                          sizeof(auditDataPermanent.data.dwRevalueCL));
                                    //Enregistrement du rechargement de la clé dans l'historique.
                                    vSetHisto(dwMediaID, 0, REVALUECASHLESS, lAmountToDisplay, SUCCESSFUL);
                                    lAmountInCashDispo = lAmountCG = lAmountBV = 0;
                                    //Respositonnenment du curseur.
                                    setLCDAddressCounter(byLCDAddressCounter);
                                    LCD_CURSOR_ON();
                                    break;
                                }
                                case RSP_REVALUE_DENIED://14 Rechargement refusé
                                {
                                    byIndex++;
                                    boRevalueRequested = FALSE;
                                    vSetHisto(dwMediaID, 0, REVALUECASHLESS, lAmountInCashDispo, FAIL);
                                    break;
                                }
                                case RSP_REVALUE_LIMIT_AMOUNT://15 Recharge maximum
                                {
                                    byIndex += 3;
                                    wKeyAmountMax = byMDBCLBuffer[1] * 256 + byMDBCLBuffer[2]; //Calcul du montant maximal pouvant être enregistré dans la clé.
                                    vSetHisto(dwMediaID, 0, KEYPRESENT, lAmountCL, SUCCESSFUL);
                                    boMediaCLFull = vIsMediaFull();
                                    if(byNumMachine < 10)
                                    {
                                        vResetSelectMachine();
                                    }
                                    break;
                                }
                                default:
                                {
                                    byIndex++;
                                    break;
                                }
                            }
                        }
                        //REV 1.2.3
                        byIndex = 0;
                    }
                    boCashLessReseted = ((byLen > 0) && (byLen < 32));
                }
        
        DelayMs(10);
        if(!boChangerReseted)
        {
            if(!byBeforeRetryCG--)
            {
                byBeforeRetryCG = MDBRETRY;
                boChangerReseted = boMDBReset(CGADDRESS);
            }
        }
        else
        {
            if((byLen = byMDBPoll(CGADDRESS, byMDBCGBuffer)))
            {
                for(byIndex = 0; byIndex < byLen - 1; byIndex++)
                {
                    if(byMDBCGBuffer[byIndex] & 0b01000000)
                    {
                        if(!(byMDBCGBuffer[byIndex] & 0b00100000))
                        {
                            lAmountCG += changeGiverConfig.byCoinValue[byMDBCGBuffer[byIndex] & 0x0F] *
                                changeGiverConfig.deviceConfig.byScaleFactor;
                            //Vérifie si le mode remplissage est en cours.
                            if(wEcran == SCREENFILLING)
                            {
                                //Récupère l'index du canal de la pièce acceptée.
                                byCashPos = byMDBCGBuffer[byIndex] & 0x0F;
                                //Et le transfert comme paramètre au menu de remplissage.
                                vMaintenanceMenu(&byCashPos);
                            }
                            else
                            {
                                lAmountInCashDispo += changeGiverConfig.byCoinValue[byMDBCGBuffer[byIndex] & 0x0F] *
                                    changeGiverConfig.deviceConfig.byScaleFactor;
                                boFlip = FALSE;
                                if(!boKeyPresent)
                                {
                                    LCDClearLine(2);
                                }
                            }
                            ++auditData.data.wNumberChannelCGIn[byMDBCGBuffer[byIndex] & 0x0F];
                            I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCIN + (sizeof(WORD) * (byMDBCGBuffer[byIndex] & 0x0F)),
                                                  &auditData.data.wNumberChannelCGIn[byMDBCGBuffer[byIndex] & 0x0F], sizeof(WORD));
                            ++auditDataPermanent.data.wNumberChannelCGIn[byMDBCGBuffer[byIndex] & 0x0F];
                            I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCIN_PERMANENT + (sizeof(WORD) * (byMDBCGBuffer[byIndex] & 0x0F)),
                                                  &auditDataPermanent.data.wNumberChannelCGIn[byMDBCGBuffer[byIndex] & 0x0F],
                                                  sizeof(WORD));
                            //Enregistrement de la pièce enregistrée dans l'historique.
                            vSetHisto(0, 0, INCG, changeGiverConfig.byCoinValue[byMDBCGBuffer[byIndex] & 0x0F] *
                                      changeGiverConfig.deviceConfig.byScaleFactor, SUCCESSFUL);
                            boChangeAutorized = TRUE;
                        }
                        else
                        {
                            vSetHisto(0, 0, REFUSED, changeGiverConfig.byCoinValue[byMDBCGBuffer[byIndex] & 0x0F] *
                                      changeGiverConfig.deviceConfig.byScaleFactor, FAIL);
                        }
                        byIndex++;
                    }
                    else
                    {
                        switch(byMDBCGBuffer[byIndex])
                        {
                            case ESCROW_REQUEST:
                            {
                                boToEscrow = TRUE;
                                break;
                            }
                            case CHANGERPAYOUTBUS:
                            {
                                break;
                            }
                            case CHANGERNOCREDIT:
                            {
                                break;
                            }
                            case CHANGETUBESENSORHS:
                            {
                                break;
                            }
                            case CHANGERDOUBLECOINS:
                            {
                                break;
                            }
                            case CHANGERUNPLUGGED:
                            {
                                break;
                            }
                            case CHANGERTUBEJAM:
                            {
                                break;
                            }
                            case CHANGERROMERROR:
                            {
                                break;
                            }
                            case CHANGERROUTEERROR:
                            {
                                break;
                            }
                            case CHANGERBUSY:
                            {
                                break;
                            }
                            case JUST_RESET_CG:
                            {
                                boChangerReseted = FALSE;
                                if(boMDBSetupConfig(CGADDRESS, &changeGiverConfig, sizeof(ChangeGiverConfig)))
                                {
                                    if(changeGiverConfig.deviceConfig.byLevel > 2)
                                    {
                                        memset(&changerId, 0, sizeof(changerId));
                                        boChangerReseted = boGetMDBChangerID(&changerId) && boEnableFeature();
                                    }
                                    if(boGetMDBTubeStatus(&tubeStatus))
                                    {
                                        boChangerReseted = boEnableChanger(FALSE, &centralParameters.coinType);
                                        wCurrencyDivider = wDecimalDivider(byDecimalPos = changeGiverConfig.deviceConfig.byDecimalPlace);
                                    }
                                }
                                break;
                            }
                            case COINJAM:
                            {
                                break;
                            }
                            case COINREMOVAL:
                            {
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                }
                //Rev 1.2.3
                byIndex = 0;
            }
            boChangerReseted = ((byLen > 0) && (byLen < 32));
        }

        DelayMs(10);
        if(!boBillValidatorReseted)
        {
            if(!byBeforeRetryBV--)
            {
                byBeforeRetryBV = MDBRETRY + 1; //Ajout 1 pour provoquer un décalage
                boBillValidatorReseted = boMDBReset(BVADDRESS);
            }
        }
        else
        {
            if((byLen = byMDBPoll(BVADDRESS, byMDBBVBuffer)))
            {
                for(byIndex = 0; byIndex < byLen - 1; byIndex++)
                {
                    if(byMDBBVBuffer[byIndex] & 0b10000000)
                    {
                        if(!(byMDBBVBuffer[byIndex] & 0b01100000))
                        {
                            isTO_KBDEnable = TRUE;
                            xTimerStart(hTimerTOKBD, 10);
                            byBillNumber = byMDBBVBuffer[byIndex] & 0X0F;
                            lAmountBV += billValidatorConfig.byBillValue[byBillNumber] *
                                billValidatorConfig.wScaleFactor;
                            lAmountInCashDispo += billValidatorConfig.byBillValue[byBillNumber] *
                                billValidatorConfig.wScaleFactor;
                            boFlip = FALSE;
                            LCDClear();
                            ++auditData.data.wNumberChannelBV[byBillNumber];
                            I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELBV + (sizeof(WORD) * byBillNumber),
                                                  &auditData.data.wNumberChannelBV[byBillNumber], sizeof(WORD));
                            ++auditDataPermanent.data.wNumberChannelBV[byBillNumber];
                            I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELBV_PERMANENT + (sizeof(WORD) * byBillNumber),
                                                  &auditDataPermanent.data.wNumberChannelBV[byBillNumber], sizeof(WORD));
                            //Enregitrement du billet inséré dans l'historique.
                            vSetHisto(0, 0, INBV, billValidatorConfig.byBillValue[byBillNumber] *
                                      billValidatorConfig.wScaleFactor, SUCCESSFUL);
                            if(!centralParameters.boEscrow)
                            {
                                byBillNumber = 0XFF;
                            }
                            boChangeAutorized = TRUE;
                        }
                        byIndex++;
                    }
                    else
                    {
                        switch(byMDBBVBuffer[byIndex])
                        {
                            case JUST_RESET_BV:
                            {
                                if((boBillValidatorReseted = boMDBSetupConfig(BVADDRESS, &billValidatorConfig,
                                                                              sizeof(BillValidatorConfig))))
                                {
                                    billValidatorConfig.wScaleFactor = WORD_SWAP(billValidatorConfig.wScaleFactor);
                                    wCurrencyDivider = wDecimalDivider(byDecimalPos = billValidatorConfig.byDecimalPlace);
                                    boBillValidatorReseted = boGetMDBStackerStatus(byStacker);
                                }
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                }
                byIndex = 0;
            }
            boBillValidatorReseted = ((byLen > 0) && (byLen < 32));
        }
        DelayMs(10);
        xSemaphoreGive(semaphoreMDB);
        if(boToEscrow)
        {
            vEscrowRequested();
        }
        if(!byIndex) //Avant de tester le montant s'assure que toute la longueur du message retourner par un périphérique est traiter.
        {
            vCheckCashAmount();
        }
        vTaskDelayUntil(&LastWakeTime, MDBPOLLINMS);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskBeatingHeath(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskBeatingHearth(void *pvParameter)
{
    TickType_t LastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        ClearWDT();
        if(UsageMode == MODEUSER)
        {
            LEDTOGGLE(RED);
        }
        vTaskDelayUntil(&LastWakeTime, PULSE_RTOS);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskCheckUSB(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskCheckUSB(void *pvParameter)
{
    TickInit();
    MPFSInit();
    InitAppConfig();
    StackInit();
    portTickType xLastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        USBTasks();
        vProcessUSB();
        StackTask();
        StackApplications();
        vTaskDelayUntil(&xLastWakeTime, CHECKUSB);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskDisplayTime(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskDisplayTime(void *pvParameter)
{
    TickType_t LastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        if(boDisplayTime)
        {
            Now.l = RtccGetTime();
            if((byIndexSelectedMachine < MAXMACHINES) && modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining &&
               modules[byIndexSelectedMachine].config.boCumulEnable)
            {
                if((lTimeRemaining = (modules[byIndexSelectedMachine].lEndActivation - lConvertTimetoMS(&Now))) < 0)
                {
                    lTimeRemaining = 0;
                }
                LCDGotoXY(30, 1);
                lTimeRemaining ? vDisplayTimeInfo(lTimeRemaining) : vDisplayLCD("%s", "   ");
            }
            else
            {

                LCDGotoXY(36, 1);
                vDisplayLCD("%02X%c%02X", Now.hour, (Now.sec % 2) ? ':' : ' ', Now.min);
                //                LCD_CURSOR_ON();
            }
            setLCDAddressCounter(byLCDAddressCounter);
        }
        vTaskDelayUntil(&LastWakeTime, DISPLAYTIMEDELAY);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskFlipDisplay(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskFlipDisplay(void *pvParameter)
{
    BYTE byIndex;
    BYTE byX, byY;
    TickType_t LastWakeTime = xTaskGetTickCount();
    for(;;)
    {
        if(boFlip)
        {
            vTaskSuspendAll();
            LastWakeTime = xTaskGetTickCount();
            for(byIndex = 0; byIndex < LCDNUMCHAR; byIndex++)
            {
                setLCDAddressCounter(byIndex);
                byX = getLCDC();
                setLCDAddressCounter(byIndex + 0x40);
                byY = getLCDC();
                if(byX != byY)
                {
                    setLCDAddressCounter(byIndex);
                    vDisplayLCD("%c", byY);
                    setLCDAddressCounter(byIndex + 0x40);
                    vDisplayLCD("%c", byX);
                }
            }
            xTaskResumeAll();
        }
        vTaskDelayUntil(&LastWakeTime, DELAY_FLIP);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskChange(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskDoChange(void *pvParameter)
{
    //    TickType_t LastWakeTime = xTaskGetTickCount();
    //    long lInitialAmount, lAmount;
    //    BYTE byIndex;
    //    BYTE byToBeDispensed;
    //    BYTE byLenAnswer;
    //
    //    BOOL boDispensed;
    //    for(;;)
    //    {
    //        xSemaphoreTake(semaphoreChange, portMAX_DELAY);
    //        xSemaphoreTake(semaphoreMDB, 5000);
    //        LCD_CURSOR_OFF(); //Pas de curseur.
    //        //Obtient le nombre d'unité de base en fonction du scale factor du changer.
    //        //Sauvegarde le nombre d'unité de base pour vérifier si le nombre d'unité de base distribué estt égale au nombre à distribuer.
    //        //        lInitialAmount = lAmount = lAmountInCashDispo / (boChangerReseted ? changeGiverConfig.deviceConfig.byScaleFactor : 1);
    //        lAmount = 0;
    //        if(boChangeAutorized && lAmountInCashDispo && boGetMDBTubeStatus(&tubeStatus)) //Vérifie si il y a un montant à distribuer.
    //        {
    //            boDispensed = TRUE;
    //            boChangeAutorized = FALSE;
    //            isChangeInProgress = TRUE;
    //            //Traitement pour un rendeur de niveau MDB 2
    //
    //            //Efface la ligne 1.
    //            LCDClearLine(1);
    //            //Affiche rendu en cours.
    //            vDisplayLCD("%s", byTexte[RETURN]);
    //            //Envoie la commande de distribution d'un nombre d'unité de base en mode MDB 3.
    //
    //            byIndex = MAXNUMBERCHANNELSCG;
    //            while(lAmountInCashDispo && --byIndex)
    //            {
    //                do
    //                {
    //                    if(changeGiverConfig.byCoinValue[byIndex] && (changeGiverConfig.byCoinValue[byIndex] < 255) &&
    //                       tubeStatus.byLevel[byIndex])
    //                    {
    //                        if((byToBeDispensed = (lAmountInCashDispo / changeGiverConfig.byCoinValue[byIndex])))
    //                        {
    //                            if(byToBeDispensed > 15)
    //                            {
    //                                byToBeDispensed = 15;
    //                            }
    //                            if(byToBeDispensed > tubeStatus.byLevel[byIndex])
    //                            {
    //                                byToBeDispensed = tubeStatus.byLevel[byIndex];
    //                            }
    //                            if(byToBeDispensed && (boDispenseMDBChanger(byIndex, byToBeDispensed)))
    //                            {
    //                                tubeStatus.byLevel[byIndex] -= byToBeDispensed;
    //                                lAmount += (byToBeDispensed * changeGiverConfig.byCoinValue[byIndex]);
    //                                lAmountInCashDispo -= (byToBeDispensed * changeGiverConfig.byCoinValue[byIndex]);
    //                                auditData.data.wNumberChannelCGOut[byIndex] += byToBeDispensed;
    //                                auditDataPermanent.data.wNumberChannelCGOut[byIndex] += byToBeDispensed;
    //                                I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCOUT + (sizeof(WORD) * byIndex),
    //                                                      &auditData.data.wNumberChannelCGOut[byIndex],
    //                                                      sizeof(WORD));
    //                                I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT + (sizeof(WORD) * byIndex),
    //                                                      &auditDataPermanent.data.wNumberChannelCGOut[byIndex],
    //                                                      sizeof(WORD));
    //                            }
    //                            if(lAmount)
    //                            {
    //                                LCDClear();
    //                                vDisplayAmount(lAmount, byTexte[RETURNED], TRUE);
    //                            }
    //                        }
    //                    }
    //                    else
    //                    {
    //                        byToBeDispensed = 0;
    //                    }
    //                }while(byToBeDispensed = 0);
    //            }
    //            if(lAmount)
    //            {
    //                do
    //                {
    //                    memset(&byMDBCGBuffer, 0xFF, sizeof(byMDBCGBuffer));
    //                    DelayMs(100);
    //                }while(!byMDBPoll(CGADDRESS, byMDBCGBuffer) ||
    //                       (byMDBCGBuffer[0] == CHANGERPAYOUTBUS));
    //            }
    //        }
    //        vDisplayAmount(lAmount, byTexte[RETURNED], TRUE);
    //        vSetHisto(0, 0, OUCG, lAmount, lAmountInCashDispo ? FAIL : SUCCESSFUL);
    //        //DelayMs(centralParameters.lDelayDisplay);
    //
    //        if(lAmountInCashDispo)
    //        {
    //            xTimerStart(hTimerTOOverpay, 1000);
    //        }
    //        isChangeInProgress = FALSE;
    //        xSemaphoreGive(semaphoreMDB);
    //        if(boFromHTTP)
    //        {
    //
    //            boChangeAutorized = FALSE;
    //            boFromHTTP = FALSE;
    //            DelayMs(centralParameters.lDelayDisplay);
    //            vResetSelectMachine();
    //        }
    //        //    vTaskDelayUntil(&LastWakeTime, DELAYCHECKCHANGE);
    //    }

    //TickType_t LastWakeTime = xTaskGetTickCount();
    long lInitialAmount, lAmount;
    BYTE byIndex, byToBeDispensed;
    BOOL boDispensed;
    for(;;)
    {
        xSemaphoreTake(semaphoreChange, portMAX_DELAY);
        xSemaphoreTake(semaphoreMDB, 1000);
        LCD_CURSOR_OFF(); //Pas de curseur.
        //Obtient le nombre d'unité de base en fonction du scale factor du changer.
        //Sauvegarde le nombre d'unité de base pour vérifier si le nombre d'unité de base distribué estt égale au nombre à distribuer.
        lInitialAmount = lAmount = lAmountInCashDispo / (boChangerReseted ? changeGiverConfig.deviceConfig.byScaleFactor : 1);

        if(boChangeAutorized && lAmount) //Vérifie si il y a un montant à distribuer.
        {
            boDispensed = TRUE;
            boChangeAutorized = FALSE;
            isChangeInProgress = TRUE;
            //Traitement pour un rendeur de niveau MDB 2
            if(changeGiverConfig.deviceConfig.byLevel > 2)
            {
                //Efface la ligne 1.
                LCDClearLine(1);
                //Affiche rendu en cours.
                vDisplayLCD("%s", byTexte[RETURN]);
                //Envoie la commande de distribution d'un nombre d'unité de base en mode MDB 3.

                while(lAmount && boDispensed)
                {
                    byToBeDispensed = (lAmount > 250) ? 250 : lAmount;
                    boDispensed = FALSE;
                    if(boAlternatePayout(byToBeDispensed))
                    {
                        //Création d'un tableau qui contiendra le nombre de pièces de chaque type distribué.
                        do
                        {
                            //S'asure que les autres opérations MDB sont terminées.
                            DelayMs(MDBPOLLINMS);
                            ClearWDT();
                        }while(!boPayoutStatus(byCoinsBuffer));

                        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
                        {
                            if((changeGiverConfig.byCoinValue[byIndex] < 0xFF) && byCoinsBuffer[byIndex])
                            {
                                auditData.data.wNumberChannelCGOut[byIndex] += byCoinsBuffer[byIndex];
                                I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCOUT + (sizeof(WORD) * byIndex),
                                                      &auditData.data.wNumberChannelCGOut[byIndex],
                                                      sizeof(WORD));
                                auditDataPermanent.data.wNumberChannelCGOut[byIndex] += byCoinsBuffer[byIndex];
                                I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCOUT_PERMANENT + (sizeof(WORD) * byIndex),
                                                      &auditDataPermanent.data.wNumberChannelCGOut[byIndex],
                                                      sizeof(WORD));
                                lAmount -= (byCoinsBuffer[byIndex] * changeGiverConfig.byCoinValue[byIndex]);
                                if((byCoinsBuffer[byIndex] * changeGiverConfig.byCoinValue[byIndex]) > 0)
                                {
                                    boDispensed = TRUE;
                                }
                            }
                        }
                    }
                   // DelayMs(500);
                }
            }
            if(lAmountInCashDispo)
            {
                lAmountInCashDispo -= (lInitialAmount - lAmount) * changeGiverConfig.deviceConfig.byScaleFactor;
            }
            //Par sécurité.
            if(lAmountInCashDispo < 0)
            {
                lAmountInCashDispo = 0;
            }
            vDisplayAmount(lInitialAmount - lAmount, byTexte[RETURNED], TRUE);
            vSetHisto(0, 0, OUCG, lInitialAmount - lAmount, lAmountInCashDispo ? FAIL : SUCCESSFUL);
            //DelayMs(centralParameters.lDelayDisplay);
        }
        if(lAmountInCashDispo)
        {
            xTimerStart(hTimerTOOverpay, 1000);
        }
        xSemaphoreGive(semaphoreMDB);
        isChangeInProgress = FALSE;
        if(boFromHTTP)
        {
            boChangeAutorized = FALSE;
            boFromHTTP = FALSE;
            DelayMs(centralParameters.lDelayDisplay);
            vResetSelectMachine();
        }
        //        vTaskDelayUntil(&LastWakeTime, DELAYCHECKCHANGE);    
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskTest(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskTest(void *pvParameter)
{
    for(;;)
    {
        xSemaphoreTake(semaphoreTest, portMAX_DELAY);
        boDisplayTime = FALSE;
        boFlip = FALSE;
        LEDON(RED);
        LCD_CURSOR_OFF();
        DelayMs(200);
        LCDClear();
        vDisplayLCD("%s: ", byTexte[TEST_START_OP]);
        sprintf(byBuffer, "%s %s", byTexte[EXIT], byTexte[CONTINUE]);
        vDisplayLCD("%20s", byBuffer);
        UsageMode = MODEMAINTENANCE;
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTaskCheckDST(void *pvParameter)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTaskCheckDST(void *pvParameter)
{
    rtccDate date;
    for(;;)
    {
        xSemaphoreTake(semaphoreDST, portMAX_DELAY);
        Today.l = RtccGetDate();
        Now.l = RtccGetTime();
        if(Today.mon == 0x10)
        {
            Now.hour--;
            date = getDSTDate(((Today.year >> 4) * 10) + (Today.year & 0X0F) + 2001, SUMMER);
        }
        else
        {

            Now.hour++;
            date = getDSTDate(((Today.year >> 4) * 10) + (Today.year & 0X0F) + 2001, WINTER);
        }
        RtccSetTime(Now.l);
        RtccSetAlarmTimeDate(0x02000000, date.l);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vDisplayAmount(DWORD dwAmount, const char *byText, const BOOL boDelay)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vDisplayAmount(DWORD dwAmount, const char *byText, const BOOL boDelay)
{
    boFlip = FALSE;
    boDisplayTime = FALSE;
    LCD_CURSOR_OFF();

    sprintf(byBuffer, "%s %.*f\7", byText, byDecimalPos, (double)dwAmount / wCurrencyDivider);
    vTaskSuspendAll();
    ((lAmountInCashDispo || boKeyPresent || thumbDriveAttached) && (byNumMachine < 10) &&
     (strcmp(byText, byTexte[RETURNED]) != 0)) ? LCDGotoXY(23, 1) : LCDClearLine(1);
    vDisplayLCD("%*s", boKeyPresent || thumbDriveAttached ? -17 : -20, byBuffer);
    if(strcmp(byText, byTexte[RETURNED]) && !boKeyPresent && !thumbDriveAttached &&
       !lAmountInCashDispo && !modules[byIndexSelectedMachine].config.boCumulEnable &&
       !modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining &&
       !modules[byIndexSelectedMachine].config.lTimeToDisplay)
    {
        boDisplayTime = FALSE;
        LCDGotoXY(22, 1);
        vDisplayLCD("%19s", byTexte[CANCEL]);
    }
    if(boKeyPresent)
    {
        LCDClearLine(2);
        boMediaCLFull ? vWarning(byTexte[MAXI]) : vDisplayLCD("%s%9lu", byTexte[MEDIA_ID], dwMediaID); //Affiche l'identiant de la clé.
    }
    xTaskResumeAll();
    if(!boKeyPresent && !modules[byIndexSelectedMachine].config.lTimeToDisplay && boDelay)
    {

        DelayMs(centralParameters.lDelayDisplay);
    }
}
/******************************************************************************/

/*********************************************************************
 * Function:        void vTimerMachineEndPulse(const TimerHandle_t pxTimer)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vTimerMachineEndPulse(const TimerHandle_t pxTimer)
{
    BYTE byIndex;
    BYTE byLoop = 3;
    for(byIndex = 0; byIndex < MAXMACHINES; byIndex++)
    {
        if(modules[byIndex].timerActivationMachine == pxTimer)
        {
            modules[byIndex].lEndActivation = 0;
            do
            {
                boModifyMachineRelayState(modules[byIndex].config.byNumero, RELAY_OFF);
                DelayMs(10);
            }while(--byLoop && (getMachineRelayState(modules[byIndex].config.byNumero) == RELAY_ON));
            vSetHisto(0, modules[byIndex].config.byNumero, PULSE_END, 0, SUCCESSFUL);
            break;
        }
    }
}

/******************************************************************************/

void vMaintenanceMenu(void *vParameter)
{
    rtccTime time;
    BYTE byIndex;
    LCDClear();
    LCD_CURSOR_OFF();

    boFlip = FALSE;
    xTimerStop(hTimerFlip, 1000);
    switch(wEcran)
    {
        case SCREENSATELLITEREMOVECONFIRM:
        {
            vDisplayLCD("%s", byTexte[CONFIRM]);
            LCDGotoXY(20, 1);
            vDisplayLCD("%s %s", byTexte[NO], byTexte[YES]);
            break;
        }
        case SCREENMAINMAINTENANCE:
        {
            vDisplayLCD("%-20s%-20s", isConfigEnable ? byTexte[CONFIGURATION] : "", isAuditEnable && boLocalAccountantEnable ? byTexte[AUDIT] : "");
            LCDGotoXY(1, 2);
            vDisplayLCD("%s %s%s %s", isHistoEnable ? byTexte[HISTORIQUE] : "", isRefillingEnable ? "(4)" : "", isRefillingEnable ? byTexte[FILLING] : "", byTexte[EXIT]);
            break;
        }
        case SCREENCONFIGURATION:
        {
            vDisplayLCD("%s %s", byTexte[PARAMETERS], byTexte[DEVICES]);
            LCDGotoXY(1, 2);
            vDisplayLCD("%s %s %s", byTexte[SATELLITE], byTexte[DATETIME], byTexte[EXIT]);
            break;
        }
        case SCREENPERIPHERIQUE:
        {
            byCashPos = 0;
            vDisplayLCD("%-20s%-20s%-20s%-20s", boChangerReseted ? byTexte[CHANGEGIVER] : "",
                        boBillValidatorReseted ? byTexte[BILLVALIDATOR] : "",
                        byTexte[CASHLESS], byTexte[EXIT]);
            break;
        }
        case SCREENCHANGEGIVER:
        {
            vDisplayCashEnable(*(BYTE*)vParameter, (BOOL)(centralParameters.coinType.wCoinEnable & (1 << *(BYTE*)vParameter)));
            break;
        }
        case SCREENBILLVALIDATOR:
        {
            vDisplayCashEnable(*(BYTE*)vParameter, (BOOL)(centralParameters.billType.wBillEnable & (1 << *(BYTE*)vParameter)));
            break;
        }
        case SCREENCASHLESS:
        {
            vDisplayLCD("(%u)%s%X%c  ", 1, byTexte[ADDRESSMDB], CASHLESS1,
                        centralParameters.byCLAddress == CASHLESS1 ? 127 : 32);
            vDisplayLCD("(%u)%s%X%c", 2, byTexte[ADDRESSMDB], CASHLESS2,
                        centralParameters.byCLAddress == CASHLESS2 ? 127 : 32);
            LCDGotoXY(1, 2);
            vDisplayLCD("%-20s", byTexte[EXIT]);
            break;
        }
        case SCREENSATELLITE:
        {
            vDisplayLCD("%-20s%-20s", byTexte[NEWMACHINEMANUAL], byTexte[MODIFICATIONMACHINE]);
            LCDGotoXY(1, 2);
            vDisplayLCD("%s %s %s", byTexte[REMOVEMACHINE], byTexte[RETRAITAUTO],
                        byTexte[EXIT]);
            break;
        }
        case SCREENDATETIME:
        {
            RtccGetTimeDate(&Now, &Today);
            byPosNum = 0;
            vDisplayLCD("%s %02X:%02X:%02X %s %02X-%02X-%u%02X", byTexte[HEURE],
                        Now.hour, Now.min, Now.sec, byTexte[DATE], Today.mday,
                        Today.mon, 20, Today.year);
            LCDGotoXY(strlen(byTexte[HEURE]) + 2, 1);
            break;
        }
        case SCREENSATELLITEAUTO:
        {
            BYTE byNumResetMachine = 0XFF;
            LCDClear();
            vDisplayLCD("%s", byTexte[SEARCH]);
            for(byIndexSelectedMachine = 0; byIndexSelectedMachine < MAXMACHINES; byIndexSelectedMachine++)
            {
                if(modules[byIndexSelectedMachine].config.byNumero != byNumResetMachine)
                {
                    if(boSimplePoll(modules[byIndexSelectedMachine].config.byNumero))
                    {
                        LCDClearLine(1);
                        if(!boModifyMachineNumber(modules[byIndexSelectedMachine].config.byNumero, byNumResetMachine))
                        {
                            vDisplayLCD("%s %u %s", byTexte[SATELLITE],
                                        modules[byIndexSelectedMachine].config.byNumero, byTexte[MACHINEMISSING]);
                            DelayMs(centralParameters.lDelayDisplay);
                        }
                        vDisplayLCD(byTexte[REMOVED], modules[byIndexSelectedMachine].config.byNumero);
                        DelayMs(centralParameters.lDelayDisplay);
                    }
                    LCDClearLine(1);
                    vDisplayLCD("%s", byTexte[SEARCH]);
                }
                memset(&modules[byIndexSelectedMachine], 0XFF, sizeof(SMACHINE_CONFIG));
                I2CE2promLWriteBuffer(ADDRESS_MACHINES_PARAMETERS + (byIndexSelectedMachine * sizeof(SMACHINE_CONFIG)),
                                      &modules[byIndexSelectedMachine], sizeof(SMACHINE_CONFIG));
            }
            LCDClear();
            for(byIndex = 99; byIndex > 9; byIndex--)
            {
                //Contrôle tous les satellites possibles et confirme la reinitialisation
                LCDGotoXY(1, 1);
                vDisplayLCD("%s %s %u", byTexte[CHECK], byTexte[SATELLITE2], byIndex);
                if(boModifyMachineNumber(byIndex, byNumResetMachine))
                {
                    LCDGotoXY(1, 2);
                    vDisplayLCD(byTexte[MACHINEREMOVED], byIndex);
                }
                isTO_KBDEnable = TRUE;
                xTimerStart(hTimerTOKBD, 10);
            }
            wEcran = SCREENSATELLITE;
            vScreenLeave();
            break;
        }
        case SCREENREFMACHINE:
        {
            vDisplayLCD("%40s", byTexte[PASS]);
            LCDHome();
            vDisplayLCD("%s ", byTexte[REFERENCE]);
            byPosNum = 0;
            break;
        }
        case SCREENSATELLITEREMOVE:
        case SCREENSATELLITEMANUAL:
        case SCREENSATELLTIEMODIF:
        {
            vDisplayLCD("%s ", byTexte[NUMERO]);
            if(wEcran == SCREENSATELLITEMANUAL)
            {
                LCDClear();
                vDisplayLCD("%s", byTexte[SEARCH]);
                if(boSimplePoll(0XFF))
                {
                    byNumMachine = 9; //Initialise la recherche de la première machine libre.
                    do
                    {
                        byIndexSelectedMachine = byMachineExist(++byNumMachine);
                    }while((byIndexSelectedMachine < MAXMACHINES) && (byNumMachine < 100));
                    LCDClear();
                    if(byNumMachine == 100)
                    {
                        vDisplayLCD("%s", byTexte[TOOMANYMACHINE]);
                        wEcran = SCREENSATELLITE;
                    }
                    else
                    {
                        vDisplayLCD("%s ", byTexte[NUMERO]);
                        byLCDAddressCounter = getLCDAddress();
                        vDisplayLCD("%u", byNumMachine);
                        setLCDAddressCounter(byLCDAddressCounter);
                    }
                }
                else
                {
                    wEcran = SCREENNOMODULE;
                    vScreenLeave();
                }
            }
            if(wEcran != SCREENSATELLITEREMOVE && wEcran != SCREENNOMODULE)
            {
                wEcran = (wEcran == SCREENSATELLITEMANUAL) ? SCREENNUMMACHINE : SCREENMODIFNUMMACHINE;
            }
            byPosNum = 0;
            break;
        }
        case SCREENPRICECASHLESS:
        case SCREENPRICECASH:
        case SCREENPRICECASH_HH:
        case SCREENPRICECASHLESS_HH:
        case SCREENEXACTCHANGE:
        {
            byPosNum = 0;
            switch(wEcran)
            {
                case SCREENPRICECASH:
                {
                    vDisplayLCD("%s ", byTexte[PRICECASH]);
                    break;
                }
                case SCREENPRICECASHLESS:
                {
                    vDisplayLCD("%s ", byTexte[PRICECASHLESS]);
                    break;
                }
                case SCREENPRICECASH_HH:
                {
                    vDisplayLCD("%s ", byTexte[PRICECASH_HH]);
                    break;
                }
                case SCREENPRICECASHLESS_HH:
                {
                    vDisplayLCD("%s ", byTexte[PRICECASHLESS_HH]);
                    break;
                }
                case SCREENEXACTCHANGE:
                {
                    vDisplayLCD("%s ", byTexte[EXACTCHANGEAMOUNT]);
                    break;
                }
                default:
                {
                    break;
                }
            }
            byLCDAddressCounter = getLCDAddress();
            vDisplayLCD("%05.*f\7", byDecimalPos, (double)*(WORD*)vParameter / wCurrencyDivider);
            setLCDAddressCounter(byLCDAddressCounter);
            break;
        }
        case SCREENREQUESTPW:
        case SCREENPULSE:
        case SCREENOVERBUSY:
        case SCREENTO_KBD:
        case SCREENTOCUMUL:
        case SCREENTO_OVERPAY:
        case SCREENMESSAGEDELAY:
        case SCREENTIMETODSP:
        case SCREENBUSYLEVEL:
        case SCREENPWLOCALTECH:
        case SCREENPWLOCALCOMPTA:
        case SCREENPWHTTPTECH:
        case SCREENPWHTTPCOMPTA:
        {
            byPosNum = 0;
            switch(wEcran)
            {
                case SCREENPWLOCALTECH:
                {
                    vDisplayLCD("%s", byTexte[PWLOCALTECH]);
                    break;
                }
                case SCREENPWLOCALCOMPTA:
                {
                    vDisplayLCD("%s", byTexte[PWLOCALCOMPTA]);
                    break;
                }
                case SCREENPWHTTPTECH:
                {
                    vDisplayLCD("%s", byTexte[PWHTTPTECH]);
                    break;
                }
                case SCREENPWHTTPCOMPTA:
                {
                    vDisplayLCD("%s", byTexte[PWHTPPCOMPTA]);
                    break;
                }
                case SCREENPULSE:
                {
                    vDisplayLCD("%s ", byTexte[PULSEDELAY]);
                    break;
                }
                case SCREENOVERBUSY:
                {
                    vDisplayLCD("%s ", byTexte[OVERBUSY]);
                    break;
                }
                case SCREENTO_KBD:
                {
                    vDisplayLCD("%s %s ", byTexte[KBDTO], byTexte[INSECONDES]);
                    break;
                }
                case SCREENTOCUMUL:
                {
                    vDisplayLCD("%s %s ", byTexte[CUMULTO], byTexte[INSECONDES]);
                    break;
                }
                case SCREENTO_OVERPAY:
                {
                    vDisplayLCD("%s %s ", byTexte[OVERPAYTO], byTexte[INSECONDES]);
                    break;
                }
                case SCREENMESSAGEDELAY:
                {
                    vDisplayLCD("%s ", byTexte[MESSAGETO]);
                    break;
                }
                case SCREENTIMETODSP:
                {
                    vDisplayLCD("%s ", byTexte[TIMETODISPLAY]);
                    break;
                }
                case SCREENBUSYLEVEL:
                {
                    vDisplayLCD("%s", byTexte[BUSYSENSIBILITY]);
                    break;
                }
                case SCREENREQUESTPW:
                {
                    vDisplayLCD(("%s", byTexte[REQUESTPW]));
                    break;
                }
                default:
                {
                    break;
                }
            }
            byLCDAddressCounter = getLCDAddress();
            vDisplayLCD("%-10lu", *(DWORD*)vParameter);
            setLCDAddressCounter(byLCDAddressCounter);
            break;
        }
        case SCREENBEGIN:
        case SCREENEND:
        case SCREENBEGINHH:
        case SCREENENDHH:
        {
            byPosNum = 0;
            time = *(rtccTime*)vParameter;
            switch(wEcran)
            {
                case SCREENBEGIN:
                {
                    vDisplayLCD("%s ", byTexte[TIMESTART]);
                    break;
                }
                case SCREENEND:
                {
                    vDisplayLCD("%s ", byTexte[TIMEEND]);
                    break;
                }
                case SCREENBEGINHH:
                {
                    vDisplayLCD("%s ", byTexte[HHSTART]);
                    break;
                }
                case SCREENENDHH:
                {
                    vDisplayLCD("%s ", byTexte[HHEND]);
                    break;
                }
                default:
                {
                    break;
                }
            }
            byHour = time.hour;
            byMin = time.min;
            byLCDAddressCounter = getLCDAddress();
            vDisplayLCD("%02Xh%02X", byHour, byMin);
            setLCDAddressCounter(byLCDAddressCounter);
            byPosNum = 0;
            break;
        }
        case SCREENDSPTIMEREMAINING:
        case SCREENCUMUL:
        case SCREENPOWER:
        case SCREENBILLACCEPTED:
        {
            switch(wEcran)
            {
                case SCREENDSPTIMEREMAINING:
                {
                    vDisplayLCD("%s%8s%c", byTexte[DSPTIMEREMAINING], byTexte[DISABLE], !*(BYTE*)vParameter ? 127 : 32);
                    break;
                }
                case SCREENCUMUL:
                {
                    vDisplayLCD("%s%8s%c", byTexte[CUMUL], byTexte[DISABLE], !*(BYTE*)vParameter ? 127 : 32);
                    break;
                }
                case SCREENPOWER:
                {
                    vDisplayLCD("%s%8s%c", byTexte[MAINPOWER], byTexte[DISABLE], !*(BYTE*)vParameter ? 127 : 32);
                    break;
                }
                case SCREENBILLACCEPTED:
                {
                    vDisplayLCD("%s%8s%c", byTexte[BILLACCEPTED], byTexte[DISABLE], !*(BYTE*)vParameter ? 127 : 32);
                    break;
                }
                default:
                {
                    break;
                }
            }
            vDisplayLCD("%8s%c", byTexte[ENABLE], *(BYTE*)vParameter ? 127 : 32);
            LCDGotoXY(1, 2);
            vDisplayLCD("(*)%-17s(#)%-17s", byTexte[BACK], byTexte[(wEcran == SCREENPOWER) ? SAVE : NEXT]);
            break;
        }
        case SCREENBUZZER:
        {
            vDisplayEnableChoice(byTexte[SOUND], centralParameters.boBuzzer);
            break;
        }
        case SCREENESCROW:
        {
            vDisplayEnableChoice(byTexte[ESCROWBILL], centralParameters.boEscrow);
            break;
        }
        case SCREENAUDIT:
        {
            vDisplayLCD("%-20s%-20s", byTexte[TEMPORARYTEXT], byTexte[PERMANENTTEXT]);
            LCDGotoXY(1, 2);
            vDisplayLCD("%s", byTexte[EXIT]);
            break;
        }
        case SCREENVENDCASH:
        case SCREENVENDCASHLESS:
        case SCREENREVALUECAHSLESS:
        case SCREENOVERPAY:
        case SCREENAUDITREFILLING:
        case SCREENVENDUSB:
        {
            vDisplayLCD("%c - ", eAudit == PERMANENT ? 'P' : 'T');
            switch(wEcran)
            {
                case SCREENVENDCASH:
                {
                    byIndex = CASHTEXT;
                    break;
                }
                case SCREENVENDCASHLESS:
                {
                    byIndex = CASHLESSTEXT;
                    break;
                }
                case SCREENREVALUECAHSLESS:
                {
                    byIndex = REVALUECASHLESSTEXT;
                    break;
                }
                case SCREENOVERPAY:
                {
                    byIndex = OVERPAYTEXTE;
                    break;
                }
                case SCREENAUDITREFILLING:
                {
                    byIndex = FILLING;
                    break;
                }
                case SCREENVENDUSB:
                {
                    byIndex = VENDUSBTEXT;
                    break;
                }
                default:
                {
                    break;
                }
            }
            vDisplayLCD("%s: %.*f\7", byTexte[byIndex], byDecimalPos, (double)(*(DWORD*)vParameter) / wCurrencyDivider);
            LCDGotoXY(1, 2);
            vDisplayLCD("(*)%-17s(#)%-17s", byTexte[BACK], byTexte[NEXT]);
            break;
        }
        case SCREENMACHINES:
        case SCREENINCG:
        case SCREENOUTCG:
        case SCREENINBV:
        {
            if((byIndexSelectedMachine > MAXMACHINES) && (wEcran == SCREENMACHINES))
            {
                wEcran = SCREENAUDITREFILLING;
                byIndexSelectedMachine = 0;
                xQueueSendToBack(queueKeyHit, &byIndex, 0);
            }
            else
            {
                vDisplayLCD("%c - ", eAudit == PERMANENT ? 'P' : 'T');
                switch(wEcran)
                {
                    case SCREENMACHINES:
                    {
                        while((byIndexSelectedMachine < MAXMACHINES) && (modules[byIndexSelectedMachine].config.byNumero > 100))
                        {
                            byIndexSelectedMachine++;
                        }
                        if(byIndexSelectedMachine < MAXMACHINES)
                        {
                            vDisplayLCD("%s %u: %u", byTexte[SERVICE], modules[byIndexSelectedMachine].config.byNumero,
                                        (eAudit == TEMPORARY) ? auditData.data.wNumberServices[byIndexSelectedMachine] :
                                        auditDataPermanent.data.wNumberServices[byIndexSelectedMachine]);
                        }
                        break;
                    }
                    case SCREENINCG:
                    case SCREENOUTCG:
                    {
                        while((byCashPos < MAXNUMBERCHANNELSCG) && ((changeGiverConfig.byCoinValue[byCashPos] == 0XFF) ||
                                                                    (changeGiverConfig.byCoinValue[byCashPos] == 0X00)))
                        {
                            byCashPos++;
                        }
                        if(byCashPos < MAXNUMBERCHANNELSCG)
                        {
                            if(wEcran == SCREENINCG)
                            {
                                vDisplayLCD(byTexte[COININ], byDecimalPos,
                                            (double)(changeGiverConfig.byCoinValue[byCashPos] * changeGiverConfig.deviceConfig.byScaleFactor) /
                                            wCurrencyDivider, (eAudit == TEMPORARY) ? auditData.data.wNumberChannelCGIn[byCashPos] :
                                            auditDataPermanent.data.wNumberChannelCGIn[byCashPos]);
                            }
                            else
                            {
                                vDisplayLCD(byTexte[COINOUT], byDecimalPos,
                                            (double)(changeGiverConfig.byCoinValue[byCashPos] * changeGiverConfig.deviceConfig.byScaleFactor) /
                                            wCurrencyDivider, (eAudit == TEMPORARY) ? auditData.data.wNumberChannelCGOut[byCashPos] :
                                            auditDataPermanent.data.wNumberChannelCGOut[byCashPos]);
                            }
                        }
                        break;
                    }
                    case SCREENINBV:
                    {
                        while((byCashPos < MAXNUMBERCHANNELSBV) && ((billValidatorConfig.byBillValue[byCashPos] == 0XFF) ||
                                                                    (billValidatorConfig.byBillValue[byCashPos] == 0X00)))
                        {
                            byCashPos++;
                        }
                        if(byCashPos < MAXNUMBERCHANNELSBV)
                        {
                            vDisplayLCD(byTexte[BILLIN], byDecimalPos,
                                        (double)(billValidatorConfig.byBillValue[byCashPos] * billValidatorConfig.wScaleFactor) /
                                        wCurrencyDivider, (eAudit == TEMPORARY) ? auditData.data.wNumberChannelBV[byCashPos] :
                                        auditDataPermanent.data.wNumberChannelBV[byCashPos]);
                        }
                        break;
                    }
                    case SCREENCUMUL:
                    {
                        vDisplayLCD("%s%8s%c", byTexte[(wEcran == SCREENBILLACCEPTED) ? CUMUL : DSPTIMEREMAINING], byTexte[DISABLE], !*(BYTE*)vParameter ? 127 : 32);
                        vDisplayLCD("%8s%c", byTexte[ENABLE], *(BYTE*)vParameter ? 127 : 32);
                        LCDGotoXY(1, 2);
                        vDisplayLCD("(*)%-17s(#)%-17s", byTexte[BACK], byTexte[NEXT]);
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
            if((byCashPos < MAXCASHCHANNELS) && (byIndexSelectedMachine < MAXMACHINES))
            {
                LCDGotoXY(1, 2);
                vDisplayLCD("(*)%-17s(#)%-17s", byTexte[BACK], byTexte[NEXT]);
            }
            else
            {
                byCashPos = 0;
                byIndexSelectedMachine = 0;
                ((!isRAZEnable || (eAudit == PERMANENT)) && (wEcran == SCREENINBV)) ? wEcran = SCREENAUDIT : wEcran++;
                byIndex = 0XFF;
                xQueueSendToBack(queueKeyHit, &byIndex, 0);
            }
            break;
        }
        case SCREENRAZAUDIT:
        {
            vDisplayLCD("%s %s %s", byTexte[RAZAUDIT], byTexte[NO], byTexte[YES]);
            break;
        }
        case SCREENHISTORIQUE:
        {
            vDisplayLCD("%s", (BYTE*)vParameter);
            LCDGotoXY(1, 2);
            vDisplayLCD("(0)%s  (1)%s  %s", byTexte[BACK], byTexte[NEXT], byTexte[EXIT]);
            byIndex = 0XFF; //Empêche le délai pour l'affichage;
            break;
        }
        case SCREENFILLING:
        {
            xTimerStart(hTimerTOKBD, 1000);
            isFillingInProgress = TRUE;
            if(*(BYTE*)vParameter == 0XFF)
            {
                lAmountCG = 0;
                boEnableChanger(TRUE, &centralParameters.coinType);
                DelayMs(10);
            }
            vDisplayLCD("%s %.*f\7 %s %.*f\7", byTexte[COIN], byDecimalPos, *(BYTE*)vParameter > 0X0F ? 0 :
                        (double)(changeGiverConfig.byCoinValue[*(BYTE*)vParameter] * changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider,
                        byTexte[TOTAL], byDecimalPos, (double)lAmountCG / wCurrencyDivider);
            LCDGotoXY(1, 2);
            vDisplayLCD("%s %s", byTexte[INSERTCOIN], byTexte[EXIT]);
            break;
        }

    }

    LCD_CURSOR_SET(wEcran == SCREENDATETIME ||
                   wEcran == SCREENPRICECASH ||
                   wEcran == SCREENPRICECASHLESS ||
                   wEcran == SCREENPRICECASH_HH ||
                   wEcran == SCREENNUMMACHINE ||
                   wEcran == SCREENPRICECASHLESS_HH ||
                   wEcran == SCREENEXACTCHANGE ||
                   wEcran == SCREENPULSE ||
                   wEcran == SCREENOVERBUSY ||
                   wEcran == SCREENTO_KBD ||
                   wEcran == SCREENTOCUMUL ||
                   wEcran == SCREENTO_OVERPAY ||
                   wEcran == SCREENMESSAGEDELAY ||
                   wEcran == SCREENBEGIN ||
                   wEcran == SCREENEND ||
                   wEcran == SCREENBEGINHH ||
                   wEcran == SCREENENDHH ||
                   wEcran == SCREENMODIFNUMMACHINE ||
                   wEcran == SCREENSATELLITEREMOVE ||
                   wEcran == SCREENREFMACHINE ||
                   wEcran == SCREENTIMETODSP ||
                   wEcran == SCREENBUSYLEVEL ||
                   wEcran == SCREENPWLOCALTECH ||
                   wEcran == SCREENPWLOCALCOMPTA ||
                   wEcran == SCREENPWHTTPTECH ||
                   wEcran == SCREENPWHTTPCOMPTA ||
                   wEcran == SCREENREQUESTPW);

    if(!(wEcran == SCREENSATELLITEREMOVE ||
         wEcran == SCREENDATETIME ||
         wEcran == SCREENSATELLITEAUTO ||
         wEcran == SCREENNUMMACHINE ||
         wEcran == SCREENMODIFNUMMACHINE ||
         wEcran == SCREENREFMACHINE ||
         wEcran == SCREENPRICECASHLESS ||
         wEcran == SCREENPRICECASH_HH ||
         wEcran == SCREENPRICECASHLESS_HH ||
         wEcran == SCREENEXACTCHANGE ||
         wEcran == SCREENPULSE ||
         wEcran == SCREENDSPTIMEREMAINING ||
         wEcran == SCREENOVERBUSY ||
         wEcran == SCREENTO_KBD ||
         wEcran == SCREENTOCUMUL ||
         wEcran == SCREENTO_OVERPAY ||
         wEcran == SCREENMESSAGEDELAY ||
         wEcran == SCREENBEGIN ||
         wEcran == SCREENEND ||
         wEcran == SCREENBEGINHH ||
         wEcran == SCREENENDHH ||
         wEcran == SCREENSATELLITEREMOVECONFIRM ||
         wEcran == SCREENRAZAUDIT ||
         wEcran == SCREENPRICECASH ||
         wEcran == SCREENTIMETODSP ||
         wEcran == SCREENBUSYLEVEL ||
         wEcran == SCREENPWLOCALTECH ||
         wEcran == SCREENPWLOCALCOMPTA ||
         wEcran == SCREENPWHTTPTECH ||
         wEcran == SCREENPWHTTPCOMPTA ||
         wEcran == SCREENREQUESTPW))
    {

        xTimerStart(hTimerFlip, 1000);
    }
}

/******************************************************************************/

void vDisplayEnableChoice(const char *byTexteToDisplay, const BOOL boEnable)
{

    LCDClear();
    vDisplayLCD("%s %s%c %s%c", byTexteToDisplay, byTexte[DISABLE], boEnable ? 32 : 127, byTexte[ENABLE], boEnable ? 127 : 32);
    LCDGotoXY(1, 2);
    vDisplayLCD("(*)%-17s(#)%-17s", byTexte[BACK], byTexte[NEXT]);
}

/******************************************************************************/

void vReset(void)
{
    SoftReset();
    EnableWDT();
    INTDisableInterrupts();

    while(TRUE);
}

/******************************************************************************/

void vGetParametersAudits(void)
{
    BYTE byIndex;

    I2CE2promLReadBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));

    if(centralParameters.byTemoin != 0X55)
    {
        centralParameters.byTemoin = 0X55;
        memset(&auditData, 0X00, sizeof(AUDITDATA));
        memset(&auditDataPermanent, 0x00, sizeof(AUDITDATA));
        if(I2CE2promLWriteBuffer(ADDRESS_DEBUT_AUDIT, &auditData, 128))
        {
            I2CE2promLWriteBuffer(ADDRESS_DEBUT_AUDIT + 128, &auditData.byAuditData[128], 128);
        }
        if(I2CE2promLWriteBuffer(ADDRESS_DEBUT_AUDIT_PERMANENT, &auditDataPermanent, 128))
        {
            I2CE2promLWriteBuffer(ADDRESS_DEBUT_AUDIT_PERMANENT + 128, &auditDataPermanent.byAuditData[128], 128);
        }

        centralParameters.boBuzzer = TRUE;
        centralParameters.boEscrow = FALSE;
        centralParameters.byCLAddress = 0X10;
        memset(&centralParameters.coinType, 0XFF, sizeof(centralParameters.coinType));
        memset(&centralParameters.billType, 0XFF, sizeof(centralParameters.billType));
        centralParameters.byKBDTO = KBDTOBYDEFAUT;
        centralParameters.byOverPayTO = OVERPAYTODEFAUT;
        centralParameters.byCumulTO = DEFAULTTOCUMUL;
        centralParameters.lDelayDisplay = DELAYDISPLAYDEFAULT;
        centralParameters.wAmountExactChange = DEFAUTAMOUNTEXACTCHANGE;
        centralParameters.passWords.localTechnician = 16383;
        centralParameters.passWords.localAccountant = 32767;
        centralParameters.passWords.httpTechnician = 16383;
        centralParameters.passWords.httpAccountant = 32767;
        I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));
        I2CE2promLReadBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));
    }
    if(centralParameters.byCumulTO == 0)
    {
        centralParameters.byCumulTO = DEFAULTTOCUMUL;
        I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));
    }
    //I2CE2promLReadBuffer(ADDRESS_DWCASHLESSVEND, &auditData.data.dwVendCL, 4);
    if(I2CE2promLReadBuffer(ADDRESS_DEBUT_AUDIT, auditData.byAuditData, 128))
    {
        I2CE2promLReadBuffer(ADDRESS_DEBUT_AUDIT + 128, &auditData.byAuditData[128], 128);
    }
    if(I2CE2promLReadBuffer(ADDRESS_DEBUT_AUDIT_PERMANENT, auditDataPermanent.byAuditData, 128))
    {
        I2CE2promLReadBuffer(ADDRESS_DEBUT_AUDIT_PERMANENT + 128, &auditDataPermanent.byAuditData[128], 128);
    }
    I2CE2promLReadBuffer(ADDRESS_HISTOEE_POINTER, &wE2OperationPos, sizeof(wE2OperationPos));
    for(byIndex = 0; byIndex < MAXMACHINES; byIndex++)
    {

        ClrWdt();
        I2CE2promLReadBuffer(ADDRESS_MACHINES_PARAMETERS + (byIndex * sizeof(SMACHINE_CONFIG)),
                             &modules[byIndex].config, sizeof(SMACHINE_CONFIG));
    }
}

/******************************************************************************/

void vTOCumul(TimerHandle_t pxTimer)
{

    isTOCumul = FALSE;
    vTOReached();
}

/******************************************************************************/

void vTOKBD(TimerHandle_t pxTimer)
{
    isTO_KBDEnable = FALSE;
    if(UsageMode == MODEMAINTENANCE)
    {

        vReturnFromTest();
    }
    vTOReached();
}

/******************************************************************************/

void vTOReached(void)
{
    if(!isTO_KBDEnable && !isTOCumul) //Vérifie qu'un autre timer n'est pas en cours.
    {
        xSemaphoreTake(semaphoreMDB, 5000);
        vEnableCashDevice(FALSE, 0XFF);
        xSemaphoreGive(semaphoreMDB);
        byIndexSelectedMachine = 0XFF;
        byNumMachine = 0;
        vResetSelectMachine();
    }
}

/******************************************************************************/

void vTimerFlip(TimerHandle_t pxTimer)
{

    boFlip = TRUE;
}

/******************************************************************************/

void vTOBuzzer()
{

    BUZZER_OFF();
}

/******************************************************************************/

/*********************************************************************
 * Function:        BYTE byCheckMachine(const BYTE byNumber)
 *
 * PreCondition:    None
 *
 * Input:           byNumber Numéro de la machine à vérifier.
 *
 * Output:          None
 *
 * Return:	    0 si la machine est disponible, sinon l'index du message à
 *		    afficher sur l'état du module.
 *
 * Side Effects:    None
 *
 * Overview:        Lit l'heure actuelle de la centrale
 *		    Vérifie si un satellite a le numéro de machine passé en
 *		    paramètre et si l'heure de sélection est autorisée.
 *		    Si non le résultat du test sera 0XFF et le numéro
 *		    du message retourné sera le résultat du test.
 *		    Si le résultat du test précédent est 0, on continue.
 *		    On habilite les système de paiement.
 *		    On accorde un délai à l'affichage du numéro de machine.
 *		    Et ensuite on affiche le prix demandé.
 *		    Le cas écheant on affiche le temps à cumuler.
 *
 * Note:            None
 ********************************************************************/
BYTE byCheckMachine(const BYTE byNumber)
{
    BYTE byResult = 0;
    Now.l = RtccGetTime();
    byResult = isMachineAvailable(&Now, byNumber);

    if(!byResult)
    {
        xSemaphoreTake(semaphoreMDB, 5000);
        vEnableCashDevice(TRUE, byIndexSelectedMachine);
        xSemaphoreGive(semaphoreMDB);
        if(sender != USER)
        {
            DelayMs(centralParameters.lDelayDisplay);
        }
        sprintf(byBuffer, "%s %u: ", byTexte[NUMMACHINE], byNumber); //, boKeyPresent ? byTexte[AMOUNT] : "");
        vDisplayAmount((lAmountToPay = lGetAmountToPay(byNumber)), byBuffer, TRUE);

        if(modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining)
        {
            vDisplayLCD("%c", '+');
            vDisplayTimeInfo(modules[byIndexSelectedMachine].config.lPulseInMS);
            boDisplayTime = modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining &&
                modules[byIndexSelectedMachine].config.boCumulEnable;
        }
        else
        {
            if(modules[byIndexSelectedMachine].config.lTimeToDisplay)
            {
                LCDGotoXY(25, 1);
                vDisplayTimeInfo(modules[byIndexSelectedMachine].config.lTimeToDisplay * 1000);
            }
        }
        lOldAmountInCashDispo = LONG_MAX;
    }
    else
    {

        byNumMachine = 0;
    }
    return byResult;
}

/******************************************************************************/

void vSetHisto(const DWORD dwNumMedia, const BYTE byNumMachine, const EHISTOOP histoOperation,
               const WORD wAmount, const ERESULT result)
{
    UOPERATION histoData;
    histoData.Operation = histoOperation & 0XFF;
    histoData.lKeyNumber = dwNumMedia;
    histoData.date.l = RtccGetDate();
    histoData.time.l = RtccGetTime();
    histoData.byMachine = byNumMachine;
    histoData.lAmount = wAmount;
    histoData.result = result & 0xFF;
    //Definit la nouvelle adresse à partir de laquelle va commencer le nouvel enregistrement.
    wE2OperationPos += sizeof(UOPERATION);
    //Vérifie que la capacité de l'eeprom n'est pas dépassée, si c'est le cas
    //effectue la rotation en fixant l'adresse au début de la sauvegarde de l'historique.
    if(wE2OperationPos < ADDRESS_HISTO)
    {

        wE2OperationPos = ADDRESS_HISTO;
    }
    //Enregistre l'opération dans l'historique.
    I2CE2promLWriteBuffer(ADDRESS_HISTOEE_POINTER, &wE2OperationPos, sizeof(wE2OperationPos));
    //Enregistre l'adresse actuelle de l'historique dans l'eeprom en cas d'extinction de la centrale.
    I2CE2promLWriteBuffer(wE2OperationPos, &histoData, sizeof(UOPERATION));
}

/******************************************************************************/

void vResetSelectMachine(void)
{
    byPosNum = 0;
    isKBDEnable = TRUE;
    DelayMs(100);
    if(isFillingInProgress && (lAmountCG > 0))
    {
        isFillingInProgress = FALSE;
        vSetHisto(0, 0, FILLINGOP, lAmountCG, SUCCESSFUL);
    };
    if(!isChangeInProgress)
    {
        byNumMachine = 0;
        isTO_KBDEnable = FALSE;
        byIndexSelectedMachine = 0xFF;
        lAmountToPay = 0;
        xTimerStop(hTimerTOKBD, 1000);
        xTimerStop(hTimerFlip, 1000);
        //DelayMs(50);
        LCDClear();
        vDisplayLCD("%s ", byTexte[SELECTION_MACHINE]);
        byLCDAddressCounter = getLCDAddress();
        if(boKeyPresent || isFileCreditPresent)
        {
            vDisplayAmount(boKeyPresent ? lAmountCL : lAmountUSBDispo, byTexte[boKeyPresent ? INKEY : CREDITINUSB], TRUE);
        }
        else
        {
            if(lAmountInCashDispo)
            {
                boDisplayTime = FALSE;
                if(centralParameters.byOverPayTO)
                {
                    xTimerStart(hTimerTOOverpay, 1000);
                    vDisplayAmount(lAmountInCashDispo, byTexte[DISPO], TRUE);
                }
                else
                {

                    vTOOverPay(NULL);
                }
            }
        }
        setLCDAddressCounter(byLCDAddressCounter);
        LCD_CURSOR_SET(!boFromHTTP);
        boCancel = boFlip = FALSE;
        boDisplayTime = (!boKeyPresent && !thumbDriveAttached && !lAmountInCashDispo);
    }
    //DisableWDT();
}

/******************************************************************************/

BOOL isExactChange(const long lAmountToCheck)
{
    BOOL boExact = TRUE;
    DelayMs(10);
    xSemaphoreTake(semaphoreMDB, 5000);
    if(boGetMDBTubeStatus(&tubeStatus))
    {
        BYTE byIndex;
        long lAmountInTube = 0;
        xSemaphoreGive(semaphoreMDB);
        for(byIndex = 0; byIndex < MAXCASHCHANNELS; byIndex++)
        {
            if(changeGiverConfig.byCoinValue[byIndex] < 0xFF)
            {
                lAmountInTube += changeGiverConfig.byCoinValue[byIndex] * changeGiverConfig.deviceConfig.byScaleFactor * tubeStatus.byLevel[byIndex];
            }
        }
        if((boExact = (lAmountInTube <= lAmountToCheck)) && boChangerReseted)
        {
            vWarning(byTexte[EXACTCHANGE]);
        }
    }
    else
    {

        xSemaphoreGive(semaphoreMDB);
    }
    return boExact;
}

/******************************************************************************/

BYTE isMachineAvailable(rtccTime * time, const BYTE byNumMachine)
{
    long lTime = lConvertTimetoMS(time);
    if((byIndexSelectedMachine = byMachineExist(byNumMachine)) >= MAXMACHINES)
    {
        return NONEXISTENT;
    }

    //Vérifie la communication avec le satelleite et la présence secteur.
    if(!boSimplePoll(modules[byIndexSelectedMachine].config.byNumero))
    {
        return MACHINEMISSING;
    }

#ifndef __L_DEBUG
    if(!isMainPresent(modules[byIndexSelectedMachine].config.byNumero))
    {
        return MAINMISSING;
    }
#endif

    //Vérifie la plage horaire.
    if(!(((modules[byIndexSelectedMachine].config.utBeginSelect.l <= modules[byIndexSelectedMachine].config.utEndSelect.l) &&
          (time->l >= modules[byIndexSelectedMachine].config.utBeginSelect.l) && (time->l <= modules[byIndexSelectedMachine].config.utEndSelect.l)) ||
         ((modules[byIndexSelectedMachine].config.utBeginSelect.l > modules[byIndexSelectedMachine].config.utEndSelect.l) &&
          (time->l <= modules[byIndexSelectedMachine].config.utBeginSelect.l) && (time->l >= modules[byIndexSelectedMachine].config.utEndSelect.l))))
    {
        return OVERTIME;
    }

    //Vérifie le niveau de la machine.
    if(boGetMachineFull(modules[byIndexSelectedMachine].config.byNumero) == EMPTY)
    {
        return TEXTEMPTY;
    }

    //Verifie si le cumul est autorisé. Si le cumul est autorisé les test des
    //délais d'occupation et d'activation ne sont effecutés.
    if(!modules[byIndexSelectedMachine].config.boCumulEnable)
    {
        if(getMachineState(modules[byIndexSelectedMachine].config.byNumero) == MACHINE_BUSY)
        {
            return OCCUPIED;
        }
        //Verifie l'activation et le temps restant.
        if(modules[byIndexSelectedMachine].lEndActivation && lTime < modules[byIndexSelectedMachine].lEndActivation)
        {
            //remainingTime = convertLongToTime(modules[byIndexSelectedSatellite].lEndActivation - lTime);
            //lRemainingTime = modules[byIndexSelectedSatellite].lEndActivation - lTime;
            if(modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining)
            {
                LCDClear();
                vDisplayLCD("%s %s ", byTexte[OCCUPIED], byTexte[REMAININGTIME]);
                vDisplayTimeInfo(modules[byIndexSelectedMachine].lEndActivation - lTime);
            }
            else
            {
                //vDisplayLCD("%s", byTexte[MACHINEMISSING]);

                return OCCUPIED;
            }
            xSemaphoreTake(semaphoreMDB, 5000);
            DelayMs(centralParameters.lDelayDisplay);
            xSemaphoreGive(semaphoreMDB);
            return UCHAR_MAX;
        }
    }
    return 0;
}

/******************************************************************************/

/*********************************************************************
 * Function:        vLaunchMachine (const BYTE byNumSatellite)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void vLaunchMachine(const BYTE byNumSatellite)
{
    ERESULT SuccessActivation = FAIL;
    BOOL boHistoSet = FALSE;
    BYTE byIndexSatellite = byMachineExist(byNumSatellite);
    Now.l = RtccGetTime(); //Récupère l'heure actuelle.
    vStartBuzzer(centralParameters.boBuzzer, TOBUZZER * 3);

    if(((wGetSatelliteFWVersion(byNumSatellite) >= 120) && boExModifyMachineRelayState(byNumSatellite, modules[byIndexSatellite].config.lPulseInMS)) ||
       boModifyMachineRelayState(byNumSatellite, RELAY_ON)) //Active le relay du satellite.
    {
        //Un délai de 3 ms pour être sûr que le relais a le temps d'être activé.
        DelayMs(3);
        //Version 1.2.8
        SuccessActivation = (ERESULT)(getMachineRelayState(byNumSatellite) == RELAY_ON);
        vSetHisto(SuccessActivation ? 0 : 101, byNumSatellite, LANCEMENT, lAmountToPay, SuccessActivation);
        boHistoSet = TRUE;
        if(SuccessActivation == SUCCESSFUL) //verfie si le relay du satellite est actionné
        {
            //-----------------
            long lTimeRemaining = modules[byIndexSatellite].lEndActivation > lConvertTimetoMS(&Now) ?
                modules[byIndexSatellite].lEndActivation - lConvertTimetoMS(&Now) : 0;
            //On lance le timer pour l'activation.
            xTimerChangePeriod(modules[byIndexSatellite].timerActivationMachine,
                               lTimeRemaining + modules[byIndexSatellite].config.lPulseInMS, 100);
            //On enregistre l'heure en milliseconde de fin d'activation qui est l'heure actuelle + le temps restant + le temps d'acitvation enregistré en paramètre.
            modules[byIndexSatellite].lEndActivation = lConvertTimetoMS(&Now) +
                lTimeRemaining + modules[byIndexSatellite].config.lPulseInMS;
            LCD_CURSOR_OFF();
            LCDClear();
            if(!lTimeRemaining)
            {
                vDisplayLCD(byTexte[INPROGRESS], byNumSatellite); //Affiche l'activation de la machine.
                if(!boFromHTTP)
                {
                    DelayMs(centralParameters.lDelayDisplay * 2);
                }
            }
            if(!boFromHTTP)
            {
                //Enregistrement des audits des services.
                ++auditData.data.wNumberServices[byIndexSatellite];
                I2CE2promLWriteBuffer(ADDRESS_WNUMBERSERVICES + (sizeof(WORD) * byIndexSatellite),
                                      &auditData.data.wNumberServices[byIndexSatellite], sizeof(WORD));
                ++auditDataPermanent.data.wNumberServices[byIndexSatellite];
                I2CE2promLWriteBuffer(ADDRESS_WNUMBERSERVICES_PERMANENT + (sizeof(WORD) * byIndexSatellite),
                                      &auditDataPermanent.data.wNumberServices[byIndexSatellite], sizeof(WORD));
            }
            if(!lTimeRemaining)
            {
                DelayMs(centralParameters.lDelayDisplay);
            }
        }
        if(!boFromHTTP)
        {
            if(boBillValidatorReseted)
            {
                boRouteBill(IN);
            }
            if(!boKeyPresent) //Si la clé n'est pas préseente.
            {
                if(!thumbDriveAttached)
                {
                    if(SuccessActivation)
                    {
                        lOldAmountInCashDispo = lAmountInCashDispo -= lAmountToPay; //Retire le montant du service au montant disposnible et effectue une copie de celui-ci
                        //Enregistre les audits.
                        auditData.data.dwVendCash += lAmountToPay;
                        auditDataPermanent.data.dwVendCash += lAmountToPay;
                        I2CE2promLWriteBuffer(ADDRESS_DWCASHVEND, &auditData.data.dwVendCash, sizeof(DWORD));
                        I2CE2promLWriteBuffer(ADDRESS_DWCASHVEND_PERMANENT, &auditDataPermanent.data.dwVendCash,
                                              sizeof(DWORD));
                    }
                    if(lAmountInCashDispo)
                    {
                        xSemaphoreGive(semaphoreChange); //Autorise le rendu.
                        DelayMs(centralParameters.lDelayDisplay);
                    }
                }
                else
                {
                    auditData.data.dwVendUSB += lAmountToPay;
                    auditDataPermanent.data.dwVendUSB += lAmountToPay;
                    I2CE2promLWriteBuffer(ADDRESS_DWVENDUSB, &auditData.data.dwVendUSB, sizeof(DWORD));
                    I2CE2promLWriteBuffer(ADDRESS_DWVENDUSB_PERMANENT, &auditDataPermanent.data.dwVendUSB,
                                          sizeof(DWORD));
                }
            }
        }
        lOldAmountInCashDispo = LONG_MAX;
    }
    //Version 1.2.8
    if(!boHistoSet)
    {
        LCDClear();
        vDisplayLCD(byTexte[UNACTIVED], byNumSatellite); //Affiche l'activation de la machine.
        vSetHisto(100, byNumSatellite, LANCEMENT, lAmountToPay, SuccessActivation);
        DelayMs(centralParameters.lDelayDisplay);
        if(lAmountInCashDispo)
        {
            xSemaphoreGive(semaphoreChange); //Autorise le rendu.
        }
        DelayMs(centralParameters.lDelayDisplay);
    };

    while(isChangeInProgress);
    if(lAmountInCashDispo)
    {
        xTimerStart(hTimerTOOverpay, 1000);
    }
    if(byIndexSatellite <= MAXMACHINES && modules[byIndexSatellite].config.boCumulEnable && !boKeyPresent && !boFromHTTP)
    {
        //Donne la priorité au TO du cumul en annulant les actions du TO du clavier.
        isTO_KBDEnable = FALSE;
        xTimerStop(hTimerTOKBD, 100);
        isTOCumul = TRUE;
        xTimerStart(hTimerTOCumul, 100);
        byCheckMachine(byNumSatellite);
        vDisplayLCD("%s", byTexte[TOADD]);
    }
    else
    {
        if(!boFromHTTP)
        {

            DelayMs(centralParameters.lDelayDisplay);
        }
        //       while(isChangeInProgress);
        vResetSelectMachine();
    }
    //-------------------
    boFromHTTP = FALSE;
}

/******************************************************************************/

void vCheckCashAmount(void)
{
    if(UsageMode == MODEUSER)
    {
        if(thumbDriveAttached)
        {
            if((lAmountUSBDispo > 0) && (lOldAmountUSBDispo != lAmountUSBDispo))
            {
                lOldAmountUSBDispo = lAmountUSBDispo;
                vResetSelectMachine();
            }
            if((byPosNum > 1) &&
               !byCheckMachine(modules[byIndexSelectedMachine].config.byNumero) &&
               ((lAmountToPay = lGetAmountToPay(modules[byIndexSelectedMachine].config.byNumero)) < lAmountUSBDispo) &&
               vSetUSBAmountOrEnable(byCreditFileName, ADDRESS_DATE_CREDIT_USB, (lAmountUSBDispo - lAmountToPay)))
            {
                isKBDEnable = FALSE;
                lAmountUSBDispo -= lAmountToPay;
                vSetHisto(0, 0, USBPAY, lAmountToPay, SUCCESSFUL);
                vLaunchMachine(byNumMachine);
                lAmountToPay = 0;
                byIndexSelectedMachine = 0XFF;
                byNumMachine = 0;
            }
        }
        else
        {
            if(!boKeyPresent && lOldAmountInCashDispo != lAmountInCashDispo)
            {
                //Donne la priorité au TO du cumul en annulant les actions du TO du clavier.
                isTO_KBDEnable = FALSE;
                xTimerStop(hTimerTOKBD, 100);
                isTOCumul = TRUE;
                xTimerStart(hTimerTOCumul, 100);

                if((lOldAmountInCashDispo = lAmountInCashDispo))
                {
                    if(boDisplayRemaining)
                    {
                        byLCDAddressCounter = getLCDAddress();
                        vDisplayAmount(lAmountInCashDispo, byTexte[CASHREMAINING], FALSE);
                        setLCDAddressCounter(byLCDAddressCounter);
                        if(byIndexSelectedMachine > 99)
                        {
                            LCD_CURSOR_ON();
                        }
                    }
                    else
                    {
                        vDisplayAmount(lAmountInCashDispo, byTexte[INTRODUCED], FALSE);
                    }
                    if(lAmountInCashDispo && (lAmountInCashDispo < lAmountToPay))
                    {
                        LCDGotoXY(22, 1);
                        vDisplayLCD("%19s", byTexte[CANCEL]);
                    }
                }
                if(lAmountInCashDispo >= lAmountToPay) //Le montant introduit en cash est-il supérieur au montant à payer
                { //oui =>
                    xSemaphoreTake(semaphoreMDB, 5000); //Empêche les autres activitées MDB.
                    vEnableCashDevice(FALSE, 0XFF);
                    xSemaphoreGive(semaphoreMDB); //Autorise les activité MDB.
                    // DelayMs(350);
                    // Remise à zéro du compteurs des paiement en espèces.
                    lAmountBV = lAmountCG = 0; //Annulation des compteurs du changer et du lecteur de billets.
                    //                    DelayMs(centralParameters.lDelayDisplay); //Laisse le montant introduit affiché quelques secondes
                    if(lAmountToPay && !boCancel)
                    {
                        vLaunchMachine(byNumMachine);
                        boDisplayRemaining = TRUE;
                    }
                    else
                    {
                        byIndexSelectedMachine = 0xFF;
                        byNumMachine = 0;
                    }
                }
                else
                {
                    boDisplayRemaining = FALSE;
                }
            }
            if(boKeyPresent && (lAmountInCashDispo > 0) && ((lAmountInCashDispo + lAmountCL) < wKeyAmountMax) && !boRevalueRequested)
            {
                boRevalueRequested = TRUE;
                boMDBRevalueRequest(centralParameters.byCLAddress, &lAmountInCashDispo);
            }
            if(boKeyPresent && wKeyAmountMax && (byPosNum > 1))
            {
                byPosNum = 0;
                lAmountToPay = lGetAmountToPay(modules[byIndexSelectedMachine].config.byNumero);
                LCD_CURSOR_OFF();
                DelayMs(10);
                if(lAmountToPay && (lAmountToPay <= lAmountCL))
                {
                    BYTE byLAnswer;

                    while(boVendRequested);
                    xSemaphoreTake(semaphoreMDB, 5000);
                    byMDBPoll(centralParameters.byCLAddress, &byLAnswer);
                    xSemaphoreGive(semaphoreMDB);
                    DelayMs(200);
                    xSemaphoreTake(semaphoreMDB, 5000);
                    vDisplayAmount(lAmountToPay, byTexte[AMOUNT], TRUE); //byTexte[boKeyPresent ? AMOUNT: TOPAY]);
                    boMDBVendRequest(centralParameters.byCLAddress, &lAmountToPay);
                    DelayMs(100);
                    xSemaphoreGive(semaphoreMDB);
                }
                else
                {

                    DelayMs(centralParameters.lDelayDisplay); //Laisse le temps de lire le prix nécessaire.
                    vDisplayAmount(lAmountCL, byTexte[INKEY], TRUE); //byTexte[boKeyPresent ? AMOUNT: TOPAY]);
                    vResetSelectMachine();
                }
            }
        }
    }
}

/******************************************************************************/

void vWarning(char * byMessage)
{

    LCDClearLine(2);
    vDisplayLCD("%-20s", byMessage);
    xTimerStart(hTimerFlip, 1000);
}

/******************************************************************************/

BOOL vIsMediaFull(void)
{

    vEnableCashDevice(lAmountCL < wKeyAmountMax, 100);
    DelayMs(50);
    return lAmountCL >= wKeyAmountMax;
}

/******************************************************************************/

void vSetDateTime(const rtccDate date, const rtccTime time)
{
    rtccDate DSTdate;
    LCD_CURSOR_OFF();
    LCDClear();
    vDisplayLCD("%s", byTexte[REGISTRED]);
    RtccSetTimeDate(time.l, date.l);
    DSTdate = getDSTDate(((date.year >> 4) * 10) + (date.year & 0X0F) + 2000, SUMMER);
    if(DSTdate.l <= date.l)
    {

        DSTdate = getDSTDate(((date.year >> 4) * 10) + (date.year & 0X0F) + 2000, WINTER);
    }
    DSTdate.wday = RtccWeekDay(((DSTdate.year >> 4) * 10) + (DSTdate.year & 0x0F) + 2000,
                               ((DSTdate.mon >> 4) * 10) + (DSTdate.mon & 0X0F),
                               ((DSTdate.mday >> 4) * 10) + (DSTdate.mday & 0X0F));
    RtccSetAlarmTimeDate(0x02000000, DSTdate.l);
    DelayMs(centralParameters.lDelayDisplay);
    wEcran = SCREENCONFIGURATION;
    vMaintenanceMenu(NULL);
}

/******************************************************************************/

void vConfigDevices(BYTE byKey)
{
    boReturnMaintenance = TRUE;
    ptrParameterMenu = NULL;
    if(byKey == STAR)
    {
        wEcran = SCREENCONFIGURATION;
    }
    else
    {
        wEcran = byKey + SCREENPERIPHERIQUE;
        switch(wEcran)
        {
            case SCREENCHANGEGIVER:
            {
                if(boChangerReseted)
                {
                    centralParameters.coinType.wCoinEnable = WORD_SWAP(centralParameters.coinType.wCoinEnable);
                    ptrParameterMenu = &byCashPos;
                }
                else
                {
                    wEcran = SCREENPERIPHERIQUE;
                }
                break;
            }
            case SCREENBILLVALIDATOR:
            {
                if(boBillValidatorReseted)
                {
                    centralParameters.billType.wBillEnable = WORD_SWAP(centralParameters.billType.wBillEnable);
                    ptrParameterMenu = &byCashPos;
                }
                else
                {
                    wEcran = SCREENPERIPHERIQUE;
                }
                break;
            }
            case SCREENCASHLESS:
            {
                break;
            }
            default:
            {

                wEcran = SCREENPERIPHERIQUE;
                break;
            }
        }
    }
    byCashPos = 0;
}

/******************************************************************************/

void vScreenMainMaintenance(const BYTE byKey)
{
    boReturnMaintenance = TRUE;
    switch(byKey)
    {
        case STAR:
        {
            vReturnFromTest();
            //vReset();
            break;
        }
        case KEYMENUCONFIGURATION:
        {
            if(isConfigEnable)
            {
                wEcran = SCREENCONFIGURATION;
            }
            break;
        }
        case KEYMEBUAUDIT:
        {
            if(isAuditEnable && boLocalAccountantEnable)
            {
                wEcran = SCREENAUDIT;
            }
            break;
        }
        case KEYMENUHISTO:
        {
            if(isHistoEnable)
            {
                sender = MAINMAINTENANCE;
                vScreenHistorique(0xFF);
                wEcran = SCREENHISTORIQUE;
            }
            break;
        }
        case KEYMENUREFILLING:
        {
            if(isRefillingEnable)
            {
                wEcran = SCREENFILLING;
                byCashPos = 0XFF;
                ptrParameterMenu = &byCashPos;
                lAmountCG = 0x00;
            }
            break;
        }
        default:
        {

            break;
        }
    }
}

/******************************************************************************/

void vScreenCashDevice(BYTE byKey)
{
    switch(byKey)
    {
        case 0:
        case 1:
        {
            if(wEcran == SCREENCHANGEGIVER)
            {
                centralParameters.coinType.wCoinEnable = byKey == 1 ? centralParameters.coinType.wCoinEnable | (1 << byCashPos) : centralParameters.coinType.wCoinEnable & ~(1 << byCashPos);
            }
            else
            {
                centralParameters.billType.wBillEnable = byKey == 1 ? centralParameters.billType.wBillEnable | (1 << byCashPos) : centralParameters.billType.wBillEnable & ~(1 << byCashPos);
            }
            boFlip = FALSE;
            vDisplayCashEnable(byCashPos, (byKey == 1));
            DelayMs(centralParameters.lDelayDisplay);
            break;
        }
        case STAR:
        {
            LCDClear();
            boFlip = FALSE;
            if(wEcran == SCREENCHANGEGIVER)
            {
                if(boChangerReseted)
                {
                    centralParameters.coinType.wCoinEnable = WORD_SWAP(centralParameters.coinType.wCoinEnable);
                    I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));
                    vDisplayLCD("%s", byTexte[REGISTRED]);
                }
            }
            else
            {
                if(boBillValidatorReseted)
                {
                    centralParameters.billType.wBillEnable = WORD_SWAP(centralParameters.billType.wBillEnable);
                    I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));
                    vDisplayLCD("%s", byTexte[REGISTRED]);
                }
            }
            DelayMs(centralParameters.lDelayDisplay);
            break;
        }
        default:
        {
            break;
        }
    }
    if((byKey < 2) || (byKey > 9))
    {
        if(wEcran == SCREENCHANGEGIVER)
        {
            do
            {
                if(++byCashPos == MAXCASHCHANNELS)
                {
                    byCashPos = 0;
                }
                if(changeGiverConfig.byCoinValue[byCashPos] == 0xFF ||
                   changeGiverConfig.byCoinValue[byCashPos] == 0x00)
                {
                    centralParameters.coinType.wCoinEnable = centralParameters.coinType.wCoinEnable & ~(1 << byCashPos);
                }
            }while(changeGiverConfig.byCoinValue[byCashPos] == 0xFF ||
                   changeGiverConfig.byCoinValue[byCashPos] == 0x00);
        }
        else
        {
            do
            {
                if(++byCashPos == MAXCASHCHANNELS)
                {
                    byCashPos = 0;
                }
                if(billValidatorConfig.byBillValue[byCashPos] == 0xFF ||
                   billValidatorConfig.byBillValue[byCashPos] == 0x00)
                {
                    centralParameters.billType.wBillEnable = centralParameters.billType.wBillEnable & ~(1 << byCashPos);
                }
            }while(billValidatorConfig.byBillValue[byCashPos] == 0xFF ||
                   billValidatorConfig.byBillValue[byCashPos] == 0x00);
        }
    }
    if(byKey == STAR)
    {

        wEcran = SCREENPERIPHERIQUE;
    }
    ptrParameterMenu = &byCashPos;
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vScreenCashLess(BYTE byKey)
{
    switch(byKey)
    {
        case 1:
        {
            centralParameters.byCLAddress = CASHLESS1;
            break;
        }
        case 2:
        {
            centralParameters.byCLAddress = CASHLESS2;
            break;
        }
        case STAR:
        {
            I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(centralParameters));
            wEcran = SCREENPERIPHERIQUE;
            LCDClear();
            boFlip = FALSE;
            vDisplayLCD("%s", byTexte[REGISTRED]);
            DelayMs(centralParameters.lDelayDisplay);
            break;
        }
        default:
        {

            break;
        }
    }
    ptrParameterMenu = NULL;
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vScreenSatellite(BYTE byKey)
{
    switch(byKey)
    {
        case STAR:
        {
            wEcran = SCREENCONFIGURATION;
            break;
        }
        case KEYREMOVESATELLITE:
        {
            sender = REMOVEALLSATTELITE;
        }
            /* fall through */
        case KEYSATELLITEMANUAL:
        case KEYSATELLITEMODIF:
        case KEYONESATELLITEREMOVE:
        {
            wEcran = SUBSATELLITE + byKey;
            break;
        }
        default:
        {

            break;
        }
    }
    ptrParameterMenu = NULL;
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vScreenDateTime(BYTE byKey)
{
    boReturnMaintenance = FALSE;
    switch(byKey)
    {
        case STAR:
            // <editor-fold defaultstate="collapsed" desc="Touche annulation">
        {
            if(!byPosNum)
            {
                LCD_CURSOR_OFF();
                wEcran = SCREENCONFIGURATION;
                boReturnMaintenance = TRUE;
            }
            else
            {
                byPosNum--;
                setLCDAddressCounter(getLCDAddress() - 1 -
                                     (byPosNum % 2) -
                                     (strlen(byTexte[DATE]) + 1) *
                                     ((BYTE)(byPosNum == 5)) -
                                     (2 * (BYTE)(byPosNum == 9)));
            }
            break;
        }
            // </editor-fold>
        case SHARP:
            // <editor-fold defaultstate="collapsed" desc="Touche acceptation">
        {
            if(byPosNum)
            {
                byKey = (byGetCharUnderCursor() & 0X0F);
            }
            else
            {
                byPosNum = 11;
            }
        }
            /* fall through */
            // </editor-fold>
        default:
            // <editor-fold defaultstate="collapsed" desc="Touches numériques">
        {
            switch(byPosNum)
            {
                case 0:
                {
                    if(byKey < 3)
                    {
                        Now.hour = (byKey << 4);
                        vDisplayLCD("%u", byKey);
                        byPosNum++;
                    }
                    break;
                }
                case 1:
                {
                    if((byKey < 4) || ((Now.hour >> 4) < 2))
                    {
                        Now.hour += byKey;
                        vDisplayLCD("%u:", byKey);
                        byPosNum++;
                    }
                    break;
                }
                case 2:
                case 4:
                {
                    if(byKey < 7)
                    {
                        (byPosNum == 2) ? (Now.min = (byKey << 4)) : (Now.sec = (byKey << 4));
                        vDisplayLCD("%u", byKey);
                        byPosNum++;
                    }
                    break;
                }
                case 3:
                case 5:
                {
                    (byPosNum == 3) ? (Now.min += byKey) : (Now.sec += byKey);
                    vDisplayLCD("%u", byKey);
                    (byPosNum == 3) ? vDisplayLCD("%c", ':') :
                        setLCDAddressCounter(strlen(byTexte[HEURE]) + strlen(byTexte[DATE]) + 11);
                    byPosNum++;
                    break;
                }
                case 6:
                {
                    if(byKey < 4)
                    {
                        Today.mday = byKey << 4;
                        vDisplayLCD("%u", byKey);
                        byPosNum++;
                    }
                    break;
                }
                case 7:
                {
                    Today.mday += byKey;
                    vDisplayLCD("%u-", byKey);
                    byPosNum++;
                    break;
                }
                case 8:
                {
                    if(byKey < 2)
                    {
                        Today.mon = byKey << 4;
                        vDisplayLCD("%u", byKey);
                        byPosNum++;
                    }
                    break;
                }
                case 9:
                {
                    if(!Today.mon || byKey < 3)
                    {
                        Today.mon += byKey;
                        vDisplayLCD("%u%s", byKey, "-20");
                        byPosNum++;
                    }
                    break;
                }
                case 10:
                {
                    Today.year = byKey << 4;
                    vDisplayLCD("%u", byKey);
                    byPosNum++;
                    break;
                }
                case 11:
                {
                    if(byKey < 10)
                    {
                        Today.year += byKey;
                        vDisplayLCD("%u", byKey);
                    }
                    vSetDateTime(Today, Now);
                    break;
                }
                default:
                {

                    break;
                }
            }
            break;
        }
            // </editor-fold>
    }
}

/******************************************************************************/

void vScreenConfiguration(BYTE byKey)
{
    boReturnMaintenance = TRUE;
    switch(byKey)
    {
        case STAR:
        {
            wEcran = SCREENMAINMAINTENANCE;
            break;
        }
        case KEYCENTRALCONFIG:
        {
            wEcran = SCREENBUZZER;
            break;
        }
        case KEYPERIPHERIQUES:
        {
            wEcran = SCREENPERIPHERIQUE;
            break;
        }
        case KEYSATELLITES:
        {
            wEcran = SCREENSATELLITE;
            break;
        }
        case KEYDATETIME:
        {
            wEcran = SCREENDATETIME;
            break;
        }
        default:
        {

            break;
        }
    }
}

/******************************************************************************/

void vScreenDspTimeRemaining(BYTE byKey)
{
    ptrParameterMenu = NULL;
    switch(byKey)
    {
        case STAR:
        {
            dwValue = modules[byIndexSelectedMachine].config.lPulseInMS < UINT_MAX ? modules[byIndexSelectedMachine].config.lPulseInMS : 0;
            wEcran = SCREENPULSE;
            ptrParameterMenu = &dwValue;
            break;
        }
        case 1:
        case 0:
        {
            modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining = (BOOL)byKey;
        }
            //Pas de break pour effectuer une validation.
        case SHARP:
        {
            dwValue = modules[byIndexSelectedMachine].config.lTimeToDisplay < UINT_MAX ? modules[byIndexSelectedMachine].config.lTimeToDisplay : 0;
            wEcran = SCREENTIMETODSP;
            ptrParameterMenu = &dwValue;
            break;
        }
        default:
        {

            break;
        }
    }
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vScreenCumul(BYTE byKey)
{
    ptrParameterMenu = NULL;
    switch(byKey)
    {
        case STAR:
        {
            dwValue = modules[byIndexSelectedMachine].config.utEndHH.l < UINT_MAX ? modules[byIndexSelectedMachine].config.utEndHH.l : 0;
            wEcran = SCREENENDHH;
            ptrParameterMenu = &dwValue;
            break;
        }
        case 1:
        case 0:
        {
            modules[byIndexSelectedMachine].config.boCumulEnable = (BOOL)byKey;
        } //Pas de break pour effectuer une validation.
        case SHARP:
        {
            LCDClear();
            if(modules[byIndexSelectedMachine].config.boCumulEnable != 1)
            {
                modules[byIndexSelectedMachine].config.boCumulEnable = 0;
            }
            dwValue = modules[byIndexSelectedMachine].config.BusyLevel.wBusyLevel < UINT16_MAX ? modules[byIndexSelectedMachine].config.BusyLevel.wBusyLevel : 1000;
            wEcran = SCREENBUSYLEVEL;
            ptrParameterMenu = &dwValue;
            break;
        }
        default:
        {

            break;
        }
    }
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vScreenBillAccepted(BYTE byKey)
{
    ptrParameterMenu = NULL;
    switch(byKey)
    {
        case STAR:
        {
            dwValue = modules[byIndexSelectedMachine].config.BusyLevel.wBusyLevel < UINT16_MAX ? modules[byIndexSelectedMachine].config.BusyLevel.wBusyLevel : 1000;
            wEcran = SCREENBUSYLEVEL;
            ptrParameterMenu = &dwValue;
            break;
        }
        case 1:
        case 0:
        {
            modules[byIndexSelectedMachine].config.boBillAccepted = (BOOL)byKey;
        } //Pas de break pour effectuer une validation.
        case SHARP:
        {
            LCDClear();
            //Rev 1.2.3 
            if(modules[byIndexSelectedMachine].config.boBillAccepted)
            {
                modules[byIndexSelectedMachine].config.boBillAccepted = 1;
            }
            dwValue = modules[byIndexSelectedMachine].config.boMachinePowered < 2 ? modules[byIndexSelectedMachine].config.boMachinePowered : TRUE;
            wEcran = SCREENPOWER;
            ptrParameterMenu = &dwValue;
            break;
        }
        default:
        {

            break;
        }
    }
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vScreenPower(BYTE byKey)
{
    ptrParameterMenu = NULL;
    switch(byKey)
    {
        case STAR:
        {
            dwValue = modules[byIndexSelectedMachine].config.boBillAccepted < 2 ? modules[byIndexSelectedMachine].config.boBillAccepted : TRUE;
            wEcran = SCREENBILLACCEPTED;
            ptrParameterMenu = &dwValue;
            break;
        }
        case 1:
        case 0:
        {
            modules[byIndexSelectedMachine].config.boMachinePowered = (BOOL)byKey;
        } //Pas de break pour effectuer une validation.
        case SHARP:
        {
            LCDClear();
            //Rev 1.2.3 
            if(modules[byIndexSelectedMachine].config.boMachinePowered)
            {
                modules[byIndexSelectedMachine].config.boMachinePowered = 1;
            }
            vRecordMachineData();
            break;
        }
        default:
        {

            break;
        }
    }
    boReturnMaintenance = TRUE;
}

/******************************************************************************/

void vSelectMachine(BYTE byKeyHit)
{
    BYTE byKey = byKeyHit;
    BYTE byIndex, byBackNumMachine, byError = 0;
    boReturnMaintenance = FALSE;
    ptrParameterMenu = NULL;
    xTimerStart(hTimerTOKBD, 1000);
    switch(byKey)
    {
        case STAR:
            // <editor-fold defaultstate="collapsed" desc="Touche annulation">
        {
            switch(sender)
            {
                case USER:
                {
                    xSemaphoreTake(semaphoreMDB, 5000);
                    vEnableCashDevice(FALSE, 0XFF);
                    xSemaphoreGive(semaphoreMDB);
                    if(byPosNum > 1)
                    {
                        boToEscrow = TRUE;
                    }
                    else
                    {
                        byIndexSelectedMachine = 0xFF;
                        byNumMachine = 0;
                        vResetSelectMachine();
                    }
                    break;
                }
                case REFMACHINE:
                {
                    if(byPosNum)
                    {
                        wEcran = SCREENREFMACHINE;
                    }
                    else
                    {
                        //Recherche du nouveau numéro de machine dans la liste pour l'effacer.
                        if((byIndex = byMachineExist(byNumMachine)) < MAXMACHINES)
                        {
                            modules[byIndex].config.byNumero = 0xFF;
                        }
                        wEcran = SCREENSATELLITEMANUAL;
                    }
                    boReturnMaintenance = TRUE;
                    break;
                }
                case REMOVESATELLITE:
                case MODIFMACHINES:
                case MANUALMACHINE:
                {
                    if(byPosNum)
                    {
                        switch(sender)
                        {
                            case MANUALMACHINE:
                            {
                                wEcran = SCREENSATELLITEMANUAL;
                                break;
                            }
                            case MODIFMACHINES:
                            {
                                wEcran = SCREENSATELLTIEMODIF;
                                break;
                            }
                            case REMOVESATELLITE:
                            {
                                wEcran = SCREENSATELLITEREMOVE;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                    else
                    {
                        wEcran = SCREENSATELLITE;
                    }
                    boReturnMaintenance = TRUE;
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
            // </editor-fold>
        case SHARP:
            // <editor-fold defaultstate="collapsed" desc="Touche acceptation">
        {
            if(sender == REFMACHINE)
            {
                memset(&modules[byIndexSelectedMachine].config.wCashPrice, 0xFF,
                       sizeof(SMACHINE_CONFIG) - 1);
                dwValue = (wPrice = (modules[byIndexSelectedMachine].config.wCashPrice < 10000) ? modules[byIndexSelectedMachine].config.wCashPrice : 400);
                wEcran = SCREENPRICECASH;
                ptrParameterMenu = &dwValue;
                boReturnMaintenance = TRUE;
            }
            if(sender == MANUALMACHINE && byPosNum == 1)
            {
                byKey = byGetCharUnderCursor() & 0X0F;
            }
            break;
        }
        default:
        {
            break;
        }
    }
    //            // </editor-fold>
    if(((byKey < 10) || (byKey == 12 && sender == MANUALMACHINE)) && (byPosNum < 2))
    {
        boDisplayTime = FALSE;
        if(byKey == 12 && sender == MANUALMACHINE && !byPosNum)
        {
            byPosNum = 1;
            byKey = byGetCharUnderCursor() & 0X0F;
        }
        else
        {
            byNumMachine = byPosNum ? byNumMachine + byKey : byKey * 10;
        }
        vDisplayLCD("%u", byKey);
        if(byPosNum++)
        {
            LCD_CURSOR_OFF();
            LCDClear();
            vDisplayLCD("%s %u  ", byTexte[SELECTED], byNumMachine);
            if(sender != USER)
            {
                DelayMs(centralParameters.lDelayDisplay);
            }
            switch(sender)
            {
                case USER:
                {
                    byBackNumMachine = byNumMachine;
                    vSetHisto((byIndex = byCheckMachine(byNumMachine)), byBackNumMachine, SELECTION, lAmountToPay, byIndex > 0 ? FAIL : SUCCESSFUL);
                    if(byIndex)
                    {
                        if(byIndex != 0XFF)
                        {
                            vSelectMachineError(byTexte[byIndex]);
                        }
                        vResetSelectMachine();
                    }
                    else
                    {
                        if(!boKeyPresent && !thumbDriveAttached)
                        {
                            boExactChange = !lAmountInCashDispo && byPosNum && boChangerReseted && isExactChange(centralParameters.wAmountExactChange);
                        }
                    }
                    break;
                }
                case MANUALMACHINE:
                {
                    byIndexSelectedMachine = 0;
                    while(modules[byIndexSelectedMachine].config.byNumero != 0XFF && byIndexSelectedMachine++ < MAXMACHINES);
                    if(byIndexSelectedMachine == MAXMACHINES || (byMachineExist(byNumMachine) < MAXMACHINES))
                    {
                        vSelectMachineError(byTexte[byIndexSelectedMachine == MAXMACHINES ? TOOMANYMACHINE : MACHINEEXIST]);
                        wEcran = SCREENSATELLITEMANUAL;
                        boReturnMaintenance = TRUE;
                    }
                    else
                    {
                        modules[byIndexSelectedMachine].config.byNumero = byNumMachine;
                        byPosNum = 0;
                        wEcran = SCREENREFMACHINE;
                        boReturnMaintenance = TRUE;
                    }
                    break;
                }
                case MODIFMACHINES:
                {
                    byIndexSelectedMachine = byMachineExist(byNumMachine);
                    if(byIndexSelectedMachine >= MAXMACHINES)
                    {
                        vDisplayLCD("%s", byTexte[MACHINEMISSING]);
                        DelayMs(centralParameters.lDelayDisplay);
                        wEcran = SCREENSATELLITE; // SCREENSATELLITEMANUAL;
                        boReturnMaintenance = TRUE;
                    }
                    else
                    {
                        dwValue = wPrice = modules[byIndexSelectedMachine].config.wCashPrice;
                        wEcran = SCREENPRICECASH;
                        ptrParameterMenu = &dwValue;
                        boReturnMaintenance = TRUE;
                        byPosNum = 0;
                    }
                    break;
                }
                case REFMACHINE:
                {
                    BYTE byIndexRefMachine;

                    // Copie du numéro de machine choisie comme numéro de machine de référence et recherche de l'index de cette machine
                    byIndexRefMachine = byMachineExist(byNumRefMachine = byNumMachine);
                    if(byIndexRefMachine == byIndexSelectedMachine || byIndexRefMachine == MAXMACHINES)
                    {
                        vSelectMachineError(byTexte[MACHINEMISSING]);
                        boReturnMaintenance = TRUE;
                    }
                    else
                    {
                        memcpy(&modules[byIndexSelectedMachine].config.wCashPrice, &modules[byIndexRefMachine].config.wCashPrice, (sizeof(SMACHINE_CONFIG) - sizeof(BYTE)));
                        dwValue = (wPrice = modules[byIndexSelectedMachine].config.wCashPrice < 10000 ? modules[byIndexSelectedMachine].config.wCashPrice : 9999);
                        wEcran = SCREENPRICECASH;
                        ptrParameterMenu = &dwValue;
                        boReturnMaintenance = TRUE;
                        byPosNum = 0;
                    }
                    break;
                }
                case REMOVESATELLITE:
                {
                    byIndexSelectedMachine = byMachineExist(byNumMachine);
                    if(byIndexSelectedMachine >= MAXMACHINES)
                    {
                        vDisplayLCD("%s", byTexte[MACHINEMISSING]);
                        wEcran = SCREENSATELLITE;
                        DelayMs(centralParameters.lDelayDisplay);
                    }
                    else
                    {
                        wEcran = SCREENSATELLITEREMOVECONFIRM;
                    }
                    ptrParameterMenu = NULL;
                    boReturnMaintenance = TRUE;
                    byPosNum = 0;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        else
        {

            byLCDAddressCounter = getLCDAddress();
            LCDGotoXY(23, 1);
            vDisplayLCD("%18s", byTexte[CORRECT]);
            setLCDAddressCounter(byLCDAddressCounter);
        }
        // </editor-fold>
    }
}

/******************************************************************************/

void vSelectMachineError(char *byMessage)
{

    byIndexSelectedMachine = 0xFF;
    byNumMachine = 0;
    vDisplayLCD("%s", byMessage);
    vStartBuzzer(centralParameters.boBuzzer, TOBUZZER * 6);
    DelayMs(centralParameters.lDelayDisplay);
}

/******************************************************************************/

void vSetPrice(BYTE byKey)
{
    boReturnMaintenance = FALSE;
    ptrParameterMenu = NULL;
    vGetDigitNumber((DWORD)wPrice, &byMilliard, &byCentMillion, &byDixMillion,
                    &byMillion, &byCentMille, &byDixMille, &byMillier,
                    &byCentaine, &byDizaine, &byUnite);
    switch(byKey)
    {
        case STAR:
            // <editor-fold defaultstate="collapsed" desc="Touche annulation">
        {
            if(!byPosNum--)
            {
                switch(wEcran)
                {
                    case SCREENPRICECASH:
                    {
                        switch(sender)
                        {
                            case REFMACHINE:
                            {
                                wEcran = SCREENREFMACHINE;
                                break;
                            }
                            case REMOVESATELLITE:
                            {
                                wEcran = SCREENSATELLITEREMOVE;
                                break;
                            }
                            case MODIFMACHINES:
                            {
                                wEcran = SCREENSATELLTIEMODIF;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                        break;
                    }
                    case SCREENPRICECASHLESS:
                    {
                        wEcran = SCREENPRICECASH;
                        dwValue = wPrice = modules[byIndexSelectedMachine].config.wCashPrice < 10000 ? modules[byIndexSelectedMachine].config.wCashPrice : 9999;
                        ptrParameterMenu = &dwValue;
                        break;
                    }
                    case SCREENPRICECASH_HH:
                    {
                        wEcran = SCREENPRICECASHLESS;
                        dwValue = wPrice = modules[byIndexSelectedMachine].config.wCashLessPrice < 10000 ? modules[byIndexSelectedMachine].config.wCashLessPrice : 9999;
                        ptrParameterMenu = &dwValue;
                        break;
                    }
                    case SCREENPRICECASHLESS_HH:
                    {
                        wEcran = SCREENPRICECASH_HH;
                        dwValue = wPrice = modules[byIndexSelectedMachine].config.wCashPriceHH < 10000 ? modules[byIndexSelectedMachine].config.wCashPriceHH : 9999;
                        ptrParameterMenu = &dwValue;
                        break;
                    }
                    case SCREENEXACTCHANGE:
                    {
                        wEcran = SCREENESCROW;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                byPosNum = 0;
                boReturnMaintenance = TRUE;
            }
            else
            {
                setLCDAddressCounter(getLCDAddress() - (byPosNum == 1 ? 2 : 1));
            }
            break;
        }
            // </editor-fold>
        case SHARP:
            // <editor-fold defaultstate="collapsed" desc="Touche validation">
        {
            if(!byPosNum) //Au début de la saisie
            {
                byPosNum = 3; //Enregistrement dans la structure et passage à l'écran suivant.
                byKey = byUnite;
            }
            else//En cours de saisie
            {
                //Calcul de la valeur virtuelle byKey
                switch(byPosNum)
                {
                    case 1://Centaines
                    {
                        byKey = byCentaine;
                        break;
                    }
                    case 2://Dizaine
                    {
                        byKey = byDizaine;
                        break;
                    }
                    case 3://Unités
                    {
                        byKey = byUnite;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
        default:
        {
            break;
        }
            // </editor-fold>
    }
    if(byKey != 10 && ++byPosNum < 5)
        // <editor-fold defaultstate="collapsed" desc="Touche numériques">
    {
        if(byKey != 12)
        {
            vDisplayLCD("%u", byKey);
        }
        switch(byPosNum)
        {
            case 1:
            {
                wPrice = wPrice - byMillier * 1000 + byKey * 1000;
                break;
            }
            case 2:
            {
                wPrice = wPrice - byCentaine * 100 + byKey * 100;
                vDisplayLCD("%c", '.');
                break;
            }
            case 3:
            {
                wPrice = wPrice - byDizaine * 10 + byKey * 10;
                break;
            }
            case 4:
            {
                wPrice = wPrice + byKey - byUnite;
                switch(wEcran)
                {
                        //Enregistrement du prix en espèces.
                    case SCREENPRICECASH:
                    {
                        modules[byIndexSelectedMachine].config.wCashPrice = wPrice;
                        //Le prochain écran affichera le prix en cashless
                        dwValue = (wPrice = modules[byIndexSelectedMachine].config.wCashLessPrice < 10000 ? modules[byIndexSelectedMachine].config.wCashLessPrice : 400);
                        wEcran = SCREENPRICECASHLESS;
                        break;
                    }
                        //Enregistrement du prix cashless.
                    case SCREENPRICECASHLESS:
                    {
                        //si le prix en cashless n'est pas renseigné alors le prix sera le même que le prix en espèces.
                        modules[byIndexSelectedMachine].config.wCashLessPrice = wPrice < 9999 ? wPrice : modules[byIndexSelectedMachine].config.wCashPrice;
                        //Le prochain écran affichira le prix en espèces dans les heures creuses.
                        dwValue = (wPrice = modules[byIndexSelectedMachine].config.wCashPriceHH < 10000 ? modules[byIndexSelectedMachine].config.wCashPriceHH : 400);
                        wEcran = SCREENPRICECASH_HH;
                        break;
                    }
                        //Enregistrement du prix en espèces durant les heures creuses.
                    case SCREENPRICECASH_HH:
                    {
                        //si le prix en heure creuse n'est pas renseigné alors le prix sera le même que le prix en espèces.
                        modules[byIndexSelectedMachine].config.wCashPriceHH = wPrice < 9999 ? wPrice : modules[byIndexSelectedMachine].config.wCashPrice;
                        //Le prochain écran affiche le prix cashless en heure creuse.
                        dwValue = (wPrice = modules[byIndexSelectedMachine].config.wCashLessPriceHH < 10000 ? modules[byIndexSelectedMachine].config.wCashLessPriceHH : 400);
                        wEcran = SCREENPRICECASHLESS_HH;
                        break;
                    }
                        //Enregistrement du prix cashless en heures creuses.
                    case SCREENPRICECASHLESS_HH:
                    {
                        //Si le prix n'est pas renseigné alors le prix sera le même que le prix en cashless.
                        modules[byIndexSelectedMachine].config.wCashLessPriceHH = wPrice < 9999 ? wPrice : modules[byIndexSelectedMachine].config.wCashLessPrice;
                        dwValue = (modules[byIndexSelectedMachine].config.lPulseInMS < 0) ? 2000 : modules[byIndexSelectedMachine].config.lPulseInMS;
                        wEcran = SCREENPULSE;
                        break;
                    }
                    case SCREENEXACTCHANGE:
                    {
                        centralParameters.wAmountExactChange = wPrice;
                        dwValue = centralParameters.byCumulTO;
                        wEcran = SCREENTOCUMUL;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                ptrParameterMenu = &dwValue;
                boReturnMaintenance = TRUE;
                byPosNum = 0;
                break;
            }
            default:
            {

                break;
            }
        }
        // </editor-fold>
    }
}

/******************************************************************************/

BYTE byMachineExist(const BYTE byMachine)
{
    BYTE byIndex = 0;

    while((modules[byIndex].config.byNumero != byMachine) && (++byIndex <= MAXMACHINES));
    if(byIndex < MAXMACHINES)
    {

        return byIndex;
    }
    return UCHAR_MAX;
}

/******************************************************************************/

long lGetAmountToPay(const BYTE byNumMachine)
{
    BYTE byIndexSelectedSatellite = byMachineExist(byNumMachine);
    BOOL boHappyHour = ((modules[byIndexSelectedSatellite].config.utBeginHH.l < modules[byIndexSelectedSatellite].config.utEndHH.l) &&
                        (Now.l >= modules[byIndexSelectedSatellite].config.utBeginHH.l) && (Now.l <= modules[byIndexSelectedSatellite].config.utEndHH.l)) ||
        ((modules[byIndexSelectedSatellite].config.utBeginHH.l > modules[byIndexSelectedSatellite].config.utEndHH.l) &&
         (Now.l <= modules[byIndexSelectedSatellite].config.utBeginHH.l) && (Now.l >= modules[byIndexSelectedSatellite].config.utEndHH.l));
    if(boKeyPresent)
    {

        return boHappyHour ? modules[byIndexSelectedSatellite].config.wCashLessPriceHH : modules[byIndexSelectedSatellite].config.wCashLessPrice;
    }
    return boHappyHour ? modules[byIndexSelectedSatellite].config.wCashPriceHH : modules[byIndexSelectedSatellite].config.wCashPrice;
}

/******************************************************************************/

void vScreenLeave(void)
{

    BYTE byKey = 0;
    LCDClear();
    vDisplayLCD("%s", byTexte[wEcran == SCREENSATELLITE ? COMPLETED : NOMODULE]);
    ptrParameterMenu = NULL;
    boReturnMaintenance = TRUE;
    byPosNum = 0;
    DelayMs(centralParameters.lDelayDisplay);
    xQueueSendToBack(queueKeyHit, &byKey, 0);
}

/******************************************************************************/

long lConvertTimetoMS(const rtccTime * time)
{

    return((time->sec & 0X0F) + ((time->sec >> 4) * 10) +
           ((time->min & 0X0F) * 60) + ((time->min >> 4) * 600)+
           ((time->hour & 0X0F)*3600) + ((time->hour >> 4) * 36000)) * 1000;
}

/******************************************************************************/

rtccTime convertLongToTime(long lMilliSeconde)
{
    rtccTime time;
    if(lMilliSeconde > 0)
    {
        BYTE byData;
        lMilliSeconde /= 1000;
        byData = lMilliSeconde % 60;
        time.sec = (byData % 10) + ((byData / 10) << 4);
        lMilliSeconde /= 60;
        byData = lMilliSeconde % 60;
        time.min = (byData % 10) + ((byData / 10) << 4);
        lMilliSeconde /= 60;
        time.hour = (lMilliSeconde % 10) + ((lMilliSeconde / 10) << 4);
    }
    else
    {

        time.l = 0;
    }
    return time;
}

/******************************************************************************/

void vSetDelay(BYTE byKey)
{
    boReturnMaintenance = FALSE;
    ptrParameterMenu = NULL;
    switch(byKey)
    {
        case STAR:
        {
            // <editor-fold defaultstate="collapsed" desc="Touche d'annulation">
            if(!byPosNum)
            {
                boReturnMaintenance = TRUE;
                switch(wEcran)
                {
                    case SCREENTOCUMUL:
                    {
                        dwValue = centralParameters.wAmountExactChange;
                        wEcran = SCREENEXACTCHANGE;
                        break;
                    }
                    case SCREENTO_KBD:
                    {
                        dwValue = centralParameters.byCumulTO;
                        wEcran = SCREENTOCUMUL;
                        break;
                    }
                    case SCREENTO_OVERPAY:
                    {
                        dwValue = centralParameters.byKBDTO;
                        wEcran = SCREENTO_KBD;
                        break;
                    }
                    case SCREENTIMETODSP:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining;
                        wEcran = SCREENDSPTIMEREMAINING;
                        break;
                    }
                    case SCREENPULSE:
                    {
                        dwValue = wPrice = modules[byIndexSelectedMachine].config.wCashLessPriceHH;
                        wEcran = SCREENPRICECASHLESS_HH;
                        break;
                    }
                    case SCREENBUSYLEVEL:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.boCumulEnable;
                        wEcran = SCREENCUMUL;
                        break;
                    }
                    case SCREENOVERBUSY:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.lTimeToDisplay;
                        wEcran = SCREENTIMETODSP;
                        break;
                    }
                    case SCREENMESSAGEDELAY:
                    {
                        dwValue = centralParameters.byOverPayTO;
                        wEcran = SCREENTO_OVERPAY;
                        break;
                    }
                    case SCREENPWLOCALTECH:
                    {
                        dwValue = centralParameters.lDelayDisplay;
                        wEcran = SCREENMESSAGEDELAY;
                        break;
                    }
                    case SCREENPWLOCALCOMPTA:
                    {
                        dwValue = centralParameters.passWords.localTechnician;
                        wEcran = SCREENPWLOCALTECH;
                        break;
                    }
                    case SCREENPWHTTPTECH:
                    {
                        if(boLocalAccountantEnable)
                        {
                            dwValue = centralParameters.passWords.localAccountant;
                            wEcran = SCREENPWLOCALCOMPTA;
                        }
                        else
                        {
                            dwValue = centralParameters.passWords.localTechnician;
                            wEcran = SCREENPWLOCALTECH;
                        }
                        break;
                    }
                    case SCREENPWHTTPCOMPTA:
                    {
                        dwValue = centralParameters.passWords.httpTechnician;
                        wEcran = SCREENPWHTTPTECH;
                        break;
                    }
                    case SCREENREQUESTPW:
                    {
                        boReturnMaintenance = FALSE;
                        vReturnFromTest();
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                ptrParameterMenu = &dwValue;
            }
            else
            {
                setLCDAddressCounter(getLCDAddress() - 1);
                if(dwValue > 9)
                {
                    dwValue /= 10;
                    vDisplayLCD("%c", ' ');
                }
                else
                {
                    vDisplayLCD("%u", (unsigned int)dwValue);
                }
                setLCDAddressCounter(getLCDAddress() - 1);
                byPosNum--;
            }
            break;
        }
            // </editor-fold>
        case SHARP:
            // <editor-fold defaultstate="collapsed" desc="Touche acceptation">
        {
            boReturnMaintenance = TRUE;
            switch(wEcran)
            {
                case SCREENTOCUMUL:
                {
                    centralParameters.byCumulTO = dwValue;
                    dwValue = centralParameters.byKBDTO;
                    wEcran = SCREENTO_KBD;
                    break;
                }
                case SCREENTO_KBD:
                {
                    centralParameters.byKBDTO = dwValue;
                    dwValue = centralParameters.byOverPayTO;
                    wEcran = SCREENTO_OVERPAY;
                    break;
                }
                case SCREENPULSE:
                {
                    modules[byIndexSelectedMachine].config.lPulseInMS = dwValue;
                    dwValue = modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining < UINT_MAX ? modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining :
                        (modules[byIndexSelectedMachine].config.boDisplayedTimeRemaining = FALSE);
                    wEcran = SCREENDSPTIMEREMAINING;
                    break;
                }
                case SCREENTIMETODSP:
                {
                    modules[byIndexSelectedMachine].config.lTimeToDisplay = dwValue;
                    dwValue = modules[byIndexSelectedMachine].config.lOverBusy < UINT_MAX ? modules[byIndexSelectedMachine].config.lOverBusy : DELAYOVERBUSYDEFAULT;
                    wEcran = SCREENOVERBUSY;
                    break;
                }
                case SCREENOVERBUSY:
                {
                    modules[byIndexSelectedMachine].config.lOverBusy = (dwValue < 100) ? 100 : dwValue;
                    dwValue = modules[byIndexSelectedMachine].config.utBeginSelect.l < UINT_MAX ? modules[byIndexSelectedMachine].config.utBeginSelect.l : 0;
                    wEcran = SCREENBEGIN;
                    break;
                }
                case SCREENBUSYLEVEL:
                {
                    modules[byIndexSelectedMachine].config.BusyLevel.wBusyLevel = (adc_result_t)dwValue;
                    dwValue = modules[byIndexSelectedMachine].config.boBillAccepted < 2 ? modules[byIndexSelectedMachine].config.boBillAccepted : TRUE;
                    wEcran = SCREENBILLACCEPTED;
                    break;
                }
                case SCREENTO_OVERPAY:
                {
                    centralParameters.byOverPayTO = dwValue;
                    dwValue = centralParameters.lDelayDisplay;
                    wEcran = SCREENMESSAGEDELAY;
                    break;
                }
                case SCREENMESSAGEDELAY:
                {
                    centralParameters.lDelayDisplay = dwValue;
                    dwValue = centralParameters.passWords.localTechnician;
                    wEcran = SCREENPWLOCALTECH;
                    break;
                }
                case SCREENPWLOCALTECH:
                {
                    centralParameters.passWords.localTechnician = dwValue;
                    if(boLocalAccountantEnable)
                    {
                        dwValue = centralParameters.passWords.localAccountant;
                        wEcran = SCREENPWLOCALCOMPTA;
                    }
                    else
                    {
                        dwValue = centralParameters.passWords.httpTechnician;
                        wEcran = SCREENPWHTTPTECH;
                    }
                    break;
                }
                case SCREENPWLOCALCOMPTA:
                {
                    centralParameters.passWords.localAccountant = dwValue;
                    dwValue = centralParameters.passWords.httpTechnician;
                    wEcran = SCREENPWHTTPTECH;
                    break;
                }
                case SCREENPWHTTPTECH:
                {
                    centralParameters.passWords.httpTechnician = dwValue;
                    if(boLocalAccountantEnable)
                    {
                        dwValue = centralParameters.passWords.httpAccountant;
                        wEcran = SCREENPWHTTPCOMPTA;
                    }
                    else
                    {
                        I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(CENTRAL_PARAMETERS));
                        LCDClear();
                        vDisplayLCD("%s", byTexte[REGISTRED]);
                        wEcran = SCREENCONFIGURATION;
                        DelayMs(centralParameters.lDelayDisplay);
                    }
                    break;
                }
                case SCREENPWHTTPCOMPTA:
                {
                    centralParameters.passWords.httpAccountant = dwValue;
                    wEcran = SCREENCONFIGURATION;
                    I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(CENTRAL_PARAMETERS));
                    LCDClear();
                    vDisplayLCD("%s", byTexte[REGISTRED]);
                    DelayMs(centralParameters.lDelayDisplay);
                    break;
                }
                case SCREENREQUESTPW:
                {
                    boReturnMaintenance = FALSE;
                    if(dwValue == centralParameters.passWords.localTechnician)
                    {
                        boReturnMaintenance = TRUE;
                    }
                    if((dwValue == centralParameters.passWords.localAccountant) ||
                       (dwValue == 17484))
                    {
                        boLocalAccountantEnable = boReturnMaintenance = TRUE;
                    }
                    wEcran = SCREENMAINMAINTENANCE;
                    vSetHisto(boReturnMaintenance ? 0 : dwValue, 0, PASSWORDENTRANCE, 0, boReturnMaintenance);
                    if(!boReturnMaintenance)
                    {
                        vReturnFromTest();
                    }
                    break;
                }
                default:
                {
                    break;
                }
            }
            ptrParameterMenu = &dwValue;
            byPosNum = 0;
            break;
        }
            // </editor-fold>
        default:
            // <editor-fold defaultstate="collapsed" desc="Touches numériques">
        {
            if(!byPosNum++)
            {
                (wEcran == SCREENREQUESTPW) ? vDisplayLCD("%c", '*') :
                    vDisplayLCD("%-10u", byKey);

                dwValue = byKey;
                setLCDAddressCounter(byLCDAddressCounter + 1);
            }
            else
            {
                if(((wEcran != SCREENTO_KBD) && (wEcran != SCREENTOCUMUL) && (wEcran != SCREENTO_OVERPAY)) || (dwValue * 10 + byKey < 256))
                {
                    (wEcran == SCREENREQUESTPW) ? vDisplayLCD("%c", '*') :
                        vDisplayLCD("%u", byKey);
                    dwValue = dwValue * 10 + byKey;
                }
                    //Version 1.2.6
                else
                {

                    byPosNum--;
                }
            }
            //------------------
            break;
        }
            // </editor-fold>
    }
    // </editor-fold>
}

/******************************************************************************/

void vSetTime(BYTE byKey)
{
    boReturnMaintenance = FALSE;
    switch(byKey)
    {
        case STAR:
            // <editor-fold defaultstate="collapsed" desc="Touche annulation">
        {
            if(!byPosNum)
            {
                //Retour à l'écran précédent.
                switch(wEcran)
                {
                    case SCREENBEGIN:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.lOverBusy;
                        wEcran = SCREENOVERBUSY;
                        break;
                    }
                    case SCREENEND:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.utBeginSelect.l;
                        wEcran = SCREENBEGIN;
                        break;
                    }
                    case SCREENBEGINHH:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.utEndSelect.l;
                        wEcran = SCREENEND;
                        break;
                    }
                    case SCREENENDHH:
                    {
                        dwValue = modules[byIndexSelectedMachine].config.utBeginHH.l;
                        wEcran = SCREENBEGINHH;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                ptrParameterMenu = &dwValue;
                boReturnMaintenance = TRUE;
            }
            else
            {
                byPosNum--;
                setLCDAddressCounter(getLCDAddress() - (byPosNum == 1 ? 2 : 1));
            }
            break;
        }
            // </editor-fold>
        case SHARP:
            // <editor-fold defaultstate="collapsed" desc="Touche validation">
        {
            byKey = byGetCharUnderCursor() & 0X0F;
            if(!byPosNum)
            {
                byPosNum = 3;
                byKey = 0;
            }
        }
            // </editor-fold>
    }
    if(byKey < 10)
        // <editor-fold defaultstate="collapsed" desc="Touches numériques">
    {
        switch(byPosNum)
        {
            case 0:
            {
                if(byKey < 3)
                {
                    byHour = byKey << 4;
                    vDisplayLCD("%u", byKey);
                    ++byPosNum;
                }
                break;
            }
            case 1:
            {
                byHour += byKey;
                vDisplayLCD("%uH", byKey);
                ++byPosNum;
                break;
            }
            case 2:
            {
                if(byKey < 7)
                {
                    byMin = byKey << 4;
                    vDisplayLCD("%u", byKey);
                    ++byPosNum;
                }
                break;
            }
            case 3:
            {
                byMin += byKey;
                switch(wEcran)
                {
                    case SCREENBEGIN:
                    {
                        modules[byIndexSelectedMachine].config.utBeginSelect.hour = byHour;
                        modules[byIndexSelectedMachine].config.utBeginSelect.min = byMin;
                        modules[byIndexSelectedMachine].config.utBeginSelect.sec = 0;
                        modules[byIndexSelectedMachine].config.utBeginSelect.rsvd = 0;
                        dwValue = modules[byIndexSelectedMachine].config.utEndSelect.l < UINT_MAX ? modules[byIndexSelectedMachine].config.utEndSelect.l : 0;
                        wEcran = SCREENEND;
                        break;
                    }
                    case SCREENEND:
                    {
                        modules[byIndexSelectedMachine].config.utEndSelect.hour = byHour;
                        modules[byIndexSelectedMachine].config.utEndSelect.min = byMin;
                        modules[byIndexSelectedMachine].config.utEndSelect.sec = 0;
                        modules[byIndexSelectedMachine].config.utEndSelect.rsvd = 0;
                        dwValue = modules[byIndexSelectedMachine].config.utBeginHH.l < UINT_MAX ? modules[byIndexSelectedMachine].config.utBeginHH.l : 0;
                        wEcran = SCREENBEGINHH;
                        break;
                    }
                    case SCREENBEGINHH:
                    {
                        modules[byIndexSelectedMachine].config.utBeginHH.hour = byHour;
                        modules[byIndexSelectedMachine].config.utBeginHH.min = byMin;
                        modules[byIndexSelectedMachine].config.utBeginHH.sec = 0;
                        modules[byIndexSelectedMachine].config.utBeginHH.rsvd = 0;
                        dwValue = modules[byIndexSelectedMachine].config.utEndHH.l < UINT_MAX ? modules[byIndexSelectedMachine].config.utEndHH.l : 0;
                        wEcran = SCREENENDHH;
                        break;
                    }
                    case SCREENENDHH:
                    {
                        modules[byIndexSelectedMachine].config.utEndHH.hour = byHour;
                        modules[byIndexSelectedMachine].config.utEndHH.min = byMin;
                        modules[byIndexSelectedMachine].config.utEndHH.sec = 0;
                        modules[byIndexSelectedMachine].config.utEndHH.rsvd = 0;
                        dwValue = ((modules[byIndexSelectedMachine].config.boCumulEnable == 0) || (modules[byIndexSelectedMachine].config.boCumulEnable == 1)) ? modules[byIndexSelectedMachine].config.boCumulEnable : 0;
                        wEcran = SCREENCUMUL;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                ptrParameterMenu = &dwValue;
                boReturnMaintenance = TRUE;
                break;
            }
            default:
            {

                break;
            }
        }
    }
    // </editor-fold>
}

/******************************************************************************/

void vGetDigitNumber(DWORD dwNumber,
                     BYTE *byBillion, BYTE *byHundredMillion, BYTE *byTenMillion,
                     BYTE *byMillions, BYTE *byHundredThousand, BYTE *byTenThousand,
                     BYTE *byThousand, BYTE *byHundred, BYTE *byDecade, BYTE * byUnit)
{

    *byBillion = dwNumber / 1000000000;
    dwNumber %= 1000000000;
    *byHundredMillion = dwNumber / 100000000ul;
    dwNumber %= 100000000ul;
    *byTenMillion = dwNumber / 10000000ul;
    dwNumber %= 10000000ul;
    *byMillions = dwNumber / 1000000ul;
    dwNumber %= 1000000ul;
    *byHundredThousand = dwNumber / 100000ul;
    dwNumber %= 100000ul;
    *byTenThousand = dwNumber / 10000ul;
    dwNumber %= 10000ul;
    *byThousand = dwNumber / 1000ul;
    dwNumber %= 1000ul;
    *byHundred = dwNumber / 100ul;
    dwNumber %= 100ul;
    *byDecade = dwNumber / 10ul;
    *byUnit = dwNumber % 10ul;
}

/******************************************************************************/

void vDisplayCashEnable(BYTE byIndex, BOOL boEnable)
{

    LCDClear();
    vDisplayLCD("%s %6.*f\7%8s%c", byTexte[wEcran == SCREENCHANGEGIVER ? COIN : BILL],
                byDecimalPos, (wEcran == SCREENCHANGEGIVER ?
                               (double)(changeGiverConfig.byCoinValue[byIndex] * changeGiverConfig.deviceConfig.byScaleFactor) :
                               (double)(billValidatorConfig.byBillValue[byIndex] * billValidatorConfig.wScaleFactor)) /
                wCurrencyDivider, byTexte[DISABLE], !boEnable ? 127 : 32);
    vDisplayLCD("%8s%c", byTexte[ENABLE], boEnable ? 127 : 32);
    LCDGotoXY(1, 2);
    vDisplayLCD("%-17s(#)%-17s", byTexte[EXIT], byTexte[NEXT]);
}

/******************************************************************************/

BYTE byGetCharUnderCursor(void)
{

    BYTE byResult;
    setLCDAddressCounter(getLCDAddress());
    byResult = getLCDC();
    setLCDAddressCounter(getLCDAddress() - 1);
    return byResult;
}

/******************************************************************************/

void vSleepMCU(void)
{

    ClearWDT();
    DisableWDT();

    U1MODECLR = 0XFFFF;
    U2MODECLR = 0XFFFF;
    U3MODECLR = 0XFFFF;
    U4MODECLR = 0XFFFF;
    U5MODECLR = 0XFFFF;
    U6MODECLR = 0XFFFF;

    AD1CON1CLR = 0XFFFF;
    AD1CON2CLR = 0XFFFF;
    AD1CON3CLR = 0XFFFF;

    CM1CONCLR = 0XFFFF;
    CM2CONCLR = 0XFFFF;

    CVRCONCLR = 0XFFFF;

    mPMPClose();
    PMCONCLR = 0XFFFF;

    CloseCapture1();
    CloseCapture2();
    CloseCapture3();
    CloseCapture4();
    CloseCapture5();
    IC1CONCLR = 0XFFFF;
    IC2CONCLR = 0XFFFF;
    IC3CONCLR = 0XFFFF;
    IC4CONCLR = 0XFFFF;
    IC5CONCLR = 0XFFFF;

    CloseOC1();
    CloseOC2();
    CloseOC3();
    CloseOC4();
    CloseOC5();
    OC1CONCLR = 0XFFFF;
    OC2CONCLR = 0XFFFF;
    OC3CONCLR = 0XFFFF;
    OC4CONCLR = 0XFFFF;
    OC5CONCLR = 0XFFFF;

    SpiChnClose(SPI_CHANNEL1);
    SpiChnClose(SPI_CHANNEL2);
    SpiChnClose(SPI_CHANNEL3);
    SpiChnClose(SPI_CHANNEL4);
    SPI1CONCLR = 0XFFFF;
    SPI2CONCLR = 0XFFFF;
    SPI3CONCLR = 0XFFFF;
    SPI4CONCLR = 0XFFFF;

    I2CEnable(I2C1, FALSE);
    I2CEnable(I2C2, FALSE);
    I2CEnable(I2C3, FALSE);
    I2CEnable(I2C4, FALSE);
    I2CEnable(I2C5, FALSE);
    I2C1CONCLR = 0XFFFF;
    I2C2CONCLR = 0XFFFF;
    I2C3CONCLR = 0XFFFF;
    I2C4CONCLR = 0XFFFF;
    I2C5CONCLR = 0XFFFF;

    RTCCONbits.ON = TRUE;
    RTCCONbits.RTCCLKON = TRUE;

    DMACONCLR = 0XFFFF;

    U1PWRCbits.USBPWR = FALSE; // disable USB power
    U1PWRCbits.USUSPEND = TRUE; // put USB in suspend mode
    //disable entire usb module
    U1CONbits.USBEN = FALSE;

    C1CONCLR = 0XFFF;
    C2CONCLR = 0XFFF;

    // disable the JTAG Port
    DDPCONbits.JTAGEN = FALSE; // disable JTAG port

    ETHCON1CLR = 0XFFFF;
    ETHCON2CLR = 0XFFFF;

    PORTSetBits(IOPORT_A, 0XFFFFFFFF);
    PORTSetBits(IOPORT_B, 0XFFFFFFFF);
    PORTSetBits(IOPORT_C, 0XFFFFFFFF);
    PORTSetBits(IOPORT_D, 0XFFFFFFFF);
    PORTSetBits(IOPORT_E, 0XFFFFFFFF);
    PORTSetBits(IOPORT_F, 0XFFFFFFFF);
    PORTSetBits(IOPORT_G, 0XFFFFFFFF);

    PORTSetPinsDigitalIn(IOPORT_A, 0XFFFFFFFF);
    PORTSetPinsDigitalIn(IOPORT_B, 0XFFFFFFFF);
    PORTSetPinsDigitalIn(IOPORT_C, 0XFFFFFFFF);
    PORTSetPinsDigitalIn(IOPORT_D, 0XFFFFFFFF);
    PORTSetPinsDigitalIn(IOPORT_E, 0XFFFFFFFF);
    PORTSetPinsDigitalIn(IOPORT_F, 0XFFFFFFFF);
    PORTSetPinsDigitalIn(IOPORT_G, 0XFFFFFFFF);

    DisableIntT1;
    DisableIntT2;
    DisableIntT3;
    DisableIntT4;
    DisableIntT5;

    IEC0CLR = 0XFFFF;

    vEnableCN();

    OSCConfig(OSC_SOSC, 0, 0, 0);
    mOSCSetPBDIV(OSC_PB_DIV_1);
    Nop();
    OSCCONSET = 0x10; // Device will enter SLEEP mode
    PowerSaveSleep();
    Nop();
    Nop();
    SoftReset();

    //Redémarrage de la carte
    Nop();
    Nop();
    Nop();
    Nop();

    OSCConfig(OSC_POSC_PLL, OSC_PLL_MULT_20, OSC_PLL_POST_1, 0);
    DelayMs(100);
    vReset();
}

/******************************************************************************/

void vEraseEEprom(void)
{
    LCDClear();
    vDisplayLCD("%s", "Effacement de l'eeprom.");
    WORD wIndex;
    byLCDAddressCounter = getLCDAddress();
    //Les quatre derniers octets ne seront pas effacés.
    for(wIndex = 0; wIndex < 65530; wIndex++)
    {
        ClearWDT();
        I2CE2promLWriteByte(wIndex, 0XFF);
        if(!(wIndex % 23))
        {
            LCDGotoXY(1, 2);
            vDisplayLCD("Patientez environ %u minutes (0X%04X)", 1 + ((59999 - wIndex) / 10000), wIndex);
        }
    }
    LCDClear();
    vDisplayLCD("%s", "EEprom effacee");
    LCDGotoXY(1, 2);
    vDisplayLCD("%s", "Retirez le cavalier...");
    while(!PORTReadBits(ResetEEprom))
    {

        ClearWDT();
    }
}

/******************************************************************************/

void vEnableCashDevice(const BOOL boEnable, const BYTE byIndexMachine)
{
    if(boChangerReseted)
    {
        boEnableChanger(boEnable, &centralParameters.coinType);
        DelayMs(10);
    }
    if(boBillValidatorReseted)
    {

        boEnableBillValidator(boEnable && ((byIndexMachine == 100) || modules[byIndexMachine].config.boBillAccepted),
                              centralParameters.boEscrow && billValidatorConfig.byEscrow,
                              &centralParameters.billType);
        DelayMs(10);
    }
}

/******************************************************************************/

void vTOOverPay(TimerHandle_t pxTimer)
{
    auditData.data.dwOverPay += lAmountInCashDispo;
    auditDataPermanent.data.dwOverPay += lAmountInCashDispo;
    I2CE2promLWriteBuffer(ADDRESS_DWOVERPAY, &auditData.data.dwOverPay, sizeof(auditData.data.dwOverPay));
    I2CE2promLWriteBuffer(ADDRESS_DWOVERPAY_PERMANENT, &auditDataPermanent.data.dwOverPay, sizeof(auditDataPermanent.data.dwOverPay));
    if(lAmountInCashDispo)
    {

        vSetHisto(0, 0, OVERPAYOP, lAmountInCashDispo, SUCCESSFUL);
    }
    lAmountInCashDispo = 0;
    vResetSelectMachine();
}

/******************************************************************************/

void vEscrowRequested(void)
{
    boCancel = TRUE;
    boToEscrow = FALSE;
    vEnableCashDevice(FALSE, 0XFF);
    if(lAmountInCashDispo)
    {
        isChangeInProgress = TRUE;
        xSemaphoreGive(semaphoreChange);
        while(isChangeInProgress);
        if(centralParameters.boEscrow)
        {
            boRouteBill(OUT);
        }
        lAmountCG = lAmountBV = 0;
        if(lAmountInCashDispo)
        {

            xTimerStart(hTimerTOOverpay, 1000);
        }
    }
    byIndexSelectedMachine = 0xFF;
    byNumMachine = 0;
    vResetSelectMachine();
}

/******************************************************************************/

void vDisplayTimeInfo(DWORD dwTimeInMS)
{
    BYTE byHeure, byMinute, bySeconde = 0;
    DWORD dwDisplayTimer = dwTimeInMS / 1000;
    //    WORD wDisplayTime = modules[byIndexSelectedMachine].config.wDisplayedTime;
    byLCDAddressCounter = getLCDAddress();
    byHeure = dwDisplayTimer / 3600;
    dwDisplayTimer %= 3600;
    byMinute = dwDisplayTimer / 60;
    bySeconde = dwDisplayTimer % 60;
    memset(byBuffer, 0, sizeof(byBuffer));
    //sprintf(byBuffer, "%s", "+");
    if(byHeure)
    {
        sprintf(&byBuffer[strlen(byBuffer)], "%uh ", byHeure);
    }
    if(byHeure || byMinute)
    {
        sprintf(&byBuffer[strlen(byBuffer)], byHeure ? "%02um " : "%umin. ", byMinute);
    }
    if(bySeconde)
    {

        sprintf(&byBuffer[strlen(byBuffer)], "%02us", bySeconde);
    }

    vDisplayLCD("%-10s", byBuffer);
}

/******************************************************************************/

BOOL boRouteBill(const ESCROWDIR escrowDirection)
{
    BYTE byAcknowledge;
    BYTE byDir = (BYTE)escrowDirection;
    BOOL boResult = FALSE;
    DelayMs(10);
    xSemaphoreTake(semaphoreMDB, 1000); //portMAX_DELAY);
    if((byBillNumber != 0XFF) && (byMDBSendCommand(BVADDRESS, CMD_ESCROW, sizeof(BYTE),
                                                   &byDir, &byAcknowledge) == 1) && (byAcknowledge == ACK))
    {

        LCDClear();
        vDisplayLCD("%s", byTexte[TAKEBILL]);
        lAmountInCashDispo -= (billValidatorConfig.byBillValue[byBillNumber] *
                               billValidatorConfig.wScaleFactor);
        --auditData.data.wNumberChannelBV[byBillNumber];
        I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELBV + (sizeof(WORD) * byBillNumber),
                              &auditData.data.wNumberChannelBV[byBillNumber], sizeof(WORD));
        --auditDataPermanent.data.wNumberChannelBV[byBillNumber];
        I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELBV_PERMANENT + (sizeof(WORD) * byBillNumber),
                              &auditDataPermanent.data.wNumberChannelBV[byBillNumber], sizeof(WORD));
        //Enregitrement du billet retoruné dans l'historique.
        vSetHisto(0, 0, OUTBV, billValidatorConfig.byBillValue[byBillNumber] *
                  billValidatorConfig.wScaleFactor, SUCCESSFUL);
        DelayMs(centralParameters.lDelayDisplay);
        boResult = TRUE;
    }
    xSemaphoreGive(semaphoreMDB);
    byBillNumber = 0XFF;
    return boResult;
}

/******************************************************************************/

BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_CONFIGURED:
        {
            CDCInitEP();
            break;
        }
        case EVENT_EP0_REQUEST:
        {
            USBCheckCDCRequest();
            break;
        }
        default:
        {

            break;
        }
    }
    return TRUE;
}

/******************************************************************************/

void vProcessUSB(void)
{
    long lEnable, lIndex;
    BOOL boMaintenance = FALSE;
    if(USBHostMSDSCSIMediaDetect())
    {
        if(!thumbDriveAttached)
        {
            thumbDriveAttached = TRUE; // Thumb drive connected
            if(FSInit() && (FindFirst(KEYNAME, ATTR_VOLUME, &searchRec) == 0))
            {
                //Recherche d'un fichier de credit
                sprintf(byBuffer, "%s%02X%02X%02X.%s", CREDITFILENAME, EMAC1SA1 / 256, EMAC1SA0 % 256, EMAC1SA0 / 256, KEYNAME);
                if(FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0)
                {
                    memmove(byCreditFileName, byBuffer, sizeof(byCreditFileName));
                    lOldAmountUSBDispo = LONG_MAX; //pour provoquer un affichage du montant.
                    lAmountUSBDispo = lGetUSBAmountOrEnable(searchRec.filename, ADDRESS_DATE_CREDIT_USB);
                    DelayMs(100);
                    isFileCreditPresent = TRUE;
                    vSetHisto(0, 0, USBKEYINSERTED, lAmountUSBDispo, SUCCESSFUL);
                }
                else
                {
                    //recherche d'un fichier d'initialisation
                    vSetHisto(0, 0, USBKEYINSERTED, 0, SUCCESSFUL);
                    isFileCreditPresent = FALSE;
                    memmove(byBuffer, REINICODEFILENAME, 2);
                    if(FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0)
                    {
                        FSremove(byBuffer);
                        //0.9.2a 2017 09 27
                        for(lIndex = 0; lIndex < ADDRESS_END_CODE - ADDRESS_DEBUT_CODE; lIndex++)
                        {
                            I2CE2promLWriteByte(ADDRESS_DEBUT_CODE + lIndex, 0XFF);
                        }
                        vSetHisto(0, 0, USBREINITCODE, 0, SUCCESSFUL);
                        boDisplayTime = FALSE;
                        LCD_CURSOR_OFF();
                        LCDClear();
                        vDisplayLCD("%s %s", byTexte[USB_INITIALIZED], byTexte[KTOBERETIRED]);
                    }
                    else
                    {
                        //recherche d'un fichier autorisant la sauvegarde sur fichier des audits.

                        memmove(byBuffer, SAVEAUDITENABLEFILENAME, 2);
                        lEnable = isAuditEnable = isConfigEnable = isRAZEnable = isRefillingEnable = isHistoEnable = FALSE;

                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_SAVE_AUDIT) >> 24) & 0XAA) == 0XAA))
                        {
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_SAVE_AUDIT, lEnable);
                            vSaveAudit();
                            vSetHisto(0, 0, USBSAVEAUDIT, 0, SUCCESSFUL);
                        }
                        memmove(byBuffer, SAVEHISTOENABLEFILENAME, 2);
                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_SAVE_HISTO) >> 24) & 0XAA) == 0XAA))
                        {
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_SAVE_HISTO, lEnable);
                            vSetHisto(0, 0, USBSAVEHISTO, 0, SUCCESSFUL);
                            vSaveHisto();
                        }
                        memmove(byBuffer, AUDITFILENAME, 2);
                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_AUDIT_USB) >> 24) & 0XAA) == 0XAA))
                        {
                            isAuditEnable = TRUE;
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_AUDIT_USB, lEnable);
                            boMaintenance = TRUE;
                        }
                        memmove(byBuffer, PARAMETREFILENAME, 2);
                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_PARAMETRES_USB) >> 24) & 0XAA) == 0XAA))
                        {
                            isConfigEnable = TRUE;
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_PARAMETRES_USB, lEnable);
                            boMaintenance = TRUE;
                        }
                        memmove(byBuffer, RAZFILENAME, 2);
                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_RAZ_USB) >> 24) & 0XAA) == 0XAA))
                        {
                            isRAZEnable = TRUE;
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_RAZ_USB, lEnable);
                            boMaintenance = TRUE;
                        }
                        memmove(byBuffer, REFILLINGFILENAME, 2);
                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_REFFILLING_USB) >> 24) & 0XAA) == 0XAA))
                        {
                            isRefillingEnable = TRUE;
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_REFFILLING_USB, lEnable);
                            boMaintenance = TRUE;
                        }
                        memmove(byBuffer, HISTOFILENAME, 2);
                        if((FindFirst(byBuffer, ATTR_MASK, &searchRec) == 0) && (((lGetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_HISTO_USB) >> 24) & 0XAA) == 0XAA))
                        {
                            isHistoEnable = TRUE;
                            lEnable = (0XAA << 24) + ((rand() & 0x00FFFFFF));
                            vSetUSBAmountOrEnable(byBuffer, ADDRESS_DATE_HISTO_USB, lEnable);
                            boMaintenance = TRUE;
                        }
                        if(boMaintenance)
                        {
                            xSemaphoreGive(semaphoreTest);
                        }
                    }
                }
            }
            else
            {
                switch(FSerror())
                {
                    case CE_UNSUPPORTED_FS:
                    {
                        LCDClearLine(2);
                        vDisplayLCD("%s", "FS not supported");
                        break;
                    }
                    case CE_UNSUPPORTED_SECTOR_SIZE:
                    {
                        LCDClearLine(2);
                        vDisplayLCD("%s", "Sector size err.");
                        break;
                    }
                    default:
                    {
                        LCDClearLine(2);
                        vDisplayLCD("%s : %h", "FSInit Erreur", FSerror());
                        break;
                    }
                }
            }
        }
    }
    else
    {
        switch(ProcessIOState)
        {
            case INITIALIZE: // Starts here after reset or detach
            {
                ProcessIOState = DETACH_STATE;
                break;
            }
            case APPLICATION_ERROR: // Hold here until detached
            {
                LCDClearLine(2);
                vDisplayLCD("%s", "** App Erreur **");
                break;
            }
            default:
            {

                ProcessIOState = INITIALIZE;
                break;
            }
        }
    }
} //end ProcessIO

/******************************************************************************/

void vSaveAudit(void)
{
    BYTE byIndex;
    BYTE bylBuffer[32];
    FSFILE *auditFile;

    sprintf(bylBuffer, "%s_%02X%02X%02X%02X%02X%02X.csv", byTexte[SAVEAUDITFILENAME], 0XFC, EMAC1SA2 / 256, EMAC1SA1 % 256,
            EMAC1SA1 / 256, EMAC1SA0 % 256, EMAC1SA0 / 256);
    if(auditFile = FSfopen(bylBuffer, FS_APPENDPLUS))
    {
        RtccGetTimeDate(&Now, &Today);
        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s; %s; %s;%s;%02X-%02X-%02X;%02XH%02X", byTexte[HEADERAUDIT],
                byTexte[HEADERNUMBER], byTexte[HEADERVALUE], byTexte[HEADERAMOUNT],
                Today.mday, Today.mon, Today.year, Now.hour, Now.min);
        FSfwrite(bylBuffer, strlen(bylBuffer) + 4, 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;;;;%s\r\n", byTexte[TEMPORARYTEXT], byTexte[PERMANENTTEXT]);
        FSfwrite(bylBuffer, strlen(byBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[CASHTEXT], "", "", byDecimalPos, (double)auditData.data.dwVendCash / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[CASHLESSTEXT], "", "", byDecimalPos, (double)auditData.data.dwVendCL / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[REVALUECASHLESSTEXT], "", "", byDecimalPos, (double)auditData.data.dwRevalueCL / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[VENDUSBTEXT], "", "", byDecimalPos, (double)auditData.data.dwVendUSB / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[FILLING], "", "", byDecimalPos, (double)auditData.data.dwRefilling / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[OVERPAYTEXTE], "", "", byDecimalPos, (double)auditData.data.dwOverPay / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        for(byIndex = 0; byIndex < MAXMACHINES; byIndex++)
        {
            if(modules[byIndex].config.byNumero < 100 && modules[byIndex].config.byNumero > 9)
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "%s %u; %u\r\n ", byTexte[SATELLITE2], modules[byIndex].config.byNumero, auditData.data.wNumberServices[byIndex]);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }

        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
        {
            if((changeGiverConfig.byCoinValue[byIndex] > 0) && (changeGiverConfig.byCoinValue[byIndex] < 255))
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "CG IN - %s %u; %u; %.*f; %.*f\r\n ", byTexte[AUDITCHANNEL],
                        byIndex + 1, auditData.data.wNumberChannelCGIn[byIndex],
                        byDecimalPos, (double)(changeGiverConfig.byCoinValue[byIndex] *
                                               changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider, byDecimalPos,
                        (double)(auditData.data.wNumberChannelCGIn[byIndex] *
                                 changeGiverConfig.deviceConfig.byScaleFactor *
                                 changeGiverConfig.byCoinValue[byIndex]) / wCurrencyDivider);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }

        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
        {
            if((changeGiverConfig.byCoinValue[byIndex] > 0) && (changeGiverConfig.byCoinValue[byIndex] < 255))
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "CG OUT - %s %u; %u; %.*f; %.*f\r\n ", byTexte[AUDITCHANNEL],
                        byIndex + 1, auditData.data.wNumberChannelCGOut[byIndex],
                        byDecimalPos, (double)(changeGiverConfig.byCoinValue[byIndex] *
                                               changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider,
                        byDecimalPos, (double)(auditData.data.wNumberChannelCGOut[byIndex] *
                                               changeGiverConfig.byCoinValue[byIndex] *
                                               changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }

        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSBV; byIndex++)
        {
            if((billValidatorConfig.byBillValue[byIndex] > 0) && (billValidatorConfig.byBillValue[byIndex] < 255))
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "BV IN - %s %u; %u; %.*f; %.*f\r\n ", byTexte[AUDITCHANNEL], byIndex + 1, auditData.data.wNumberChannelBV[byIndex],
                        byDecimalPos, (double)(billValidatorConfig.byBillValue[byIndex] *
                                               billValidatorConfig.wScaleFactor) / wCurrencyDivider, byDecimalPos,
                        (double)(auditData.data.wNumberChannelBV[byIndex] *
                                 billValidatorConfig.byBillValue[byIndex] * billValidatorConfig.wScaleFactor) / wCurrencyDivider);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "\r\n%s\r\n", byTexte[PERMANENTTEXT]);
        FSfwrite(bylBuffer, strlen(byBuffer) + 5, 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[CASHTEXT], "", "", byDecimalPos, (double)auditDataPermanent.data.dwVendCash / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[CASHLESSTEXT], "", "", byDecimalPos, (double)auditDataPermanent.data.dwVendCL / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[REVALUECASHLESSTEXT], "", "", byDecimalPos, (double)auditDataPermanent.data.dwRevalueCL / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[VENDUSBTEXT], "", "", byDecimalPos, (double)auditDataPermanent.data.dwVendUSB / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[FILLING], "", "", byDecimalPos, (double)auditDataPermanent.data.dwRefilling / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%.*f\r\n", byTexte[OVERPAYTEXTE], "", "", byDecimalPos, (double)auditDataPermanent.data.dwOverPay / wCurrencyDivider);
        FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);

        for(byIndex = 0; byIndex < MAXMACHINES; byIndex++)
        {
            if(modules[byIndex].config.byNumero < 100 && modules[byIndex].config.byNumero > 9)
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "%s %u; %u\r\n ", byTexte[SATELLITE2], modules[byIndex].config.byNumero, auditDataPermanent.data.wNumberServices[byIndex]);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }

        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
        {
            if((changeGiverConfig.byCoinValue[byIndex] > 0) && (changeGiverConfig.byCoinValue[byIndex] < 255))
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "CG IN - %s %u; %u; %.*f; %.*f\r\n ", byTexte[AUDITCHANNEL],
                        byIndex + 1, auditDataPermanent.data.wNumberChannelCGIn[byIndex],
                        byDecimalPos, (double)(changeGiverConfig.byCoinValue[byIndex] *
                                               changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider, byDecimalPos,
                        (double)(auditDataPermanent.data.wNumberChannelCGIn[byIndex] *
                                 changeGiverConfig.deviceConfig.byScaleFactor *
                                 changeGiverConfig.byCoinValue[byIndex]) / wCurrencyDivider);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }

        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
        {
            if((changeGiverConfig.byCoinValue[byIndex] > 0) && (changeGiverConfig.byCoinValue[byIndex] < 255))
            {
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "CG OUT - %s %u; %u; %.*f; %.*f\r\n ", byTexte[AUDITCHANNEL],
                        byIndex + 1, auditDataPermanent.data.wNumberChannelCGOut[byIndex],
                        byDecimalPos, (double)(changeGiverConfig.byCoinValue[byIndex] *
                                               changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider,
                        byDecimalPos, (double)(auditDataPermanent.data.wNumberChannelCGOut[byIndex] *
                                               changeGiverConfig.byCoinValue[byIndex] *
                                               changeGiverConfig.deviceConfig.byScaleFactor) / wCurrencyDivider);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }
        for(byIndex = 0; byIndex < MAXNUMBERCHANNELSBV; byIndex++)
        {
            if((billValidatorConfig.byBillValue[byIndex] > 0) && (billValidatorConfig.byBillValue[byIndex] < 255))
            {

                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "BV IN - %s %u; %u; %.*f; %.*f\r\n ", byTexte[AUDITCHANNEL], byIndex + 1, auditDataPermanent.data.wNumberChannelBV[byIndex],
                        byDecimalPos, (double)(billValidatorConfig.byBillValue[byIndex] *
                                               billValidatorConfig.wScaleFactor) / wCurrencyDivider, byDecimalPos,
                        (double)(auditDataPermanent.data.wNumberChannelBV[byIndex] *
                                 billValidatorConfig.byBillValue[byIndex] * billValidatorConfig.wScaleFactor) / wCurrencyDivider);
                FSfwrite(bylBuffer, strlen(bylBuffer), 1, auditFile);
            }
        }
        FSfwrite("\r\n", 2, 1, auditFile);
        boRAZAudit();
        FSfclose(auditFile);
        LCDClear();
        LCD_CURSOR_OFF();
        boDisplayTime = FALSE;
        vDisplayLCD("%s", byTexte[AUDITSAVED]);
        DelayMs(centralParameters.lDelayDisplay);
    }
}

/******************************************************************************/

void vSaveHisto(void)
{
    FSFILE *histoFile;
    UOPERATION histoData;
    BYTE bylBuffer[72] = {0};
    sprintf(bylBuffer, "%s_%02X%02X%02X%02X%02X%02X.csv", byTexte[SAVEHISTOFILENAME], 0XFC, EMAC1SA2 / 256, EMAC1SA1 % 256,
            EMAC1SA1 / 256, EMAC1SA0 % 256, EMAC1SA0 / 256);
    if(histoFile = FSfopen(bylBuffer, FS_WRITE))
    {
        wE2OperationPosRead = wE2OperationPos;
        RtccGetTimeDate(&Now, &Today);
        memset(bylBuffer, 0x00, sizeof(bylBuffer));
        sprintf(bylBuffer, "%s;%s;%s;%s;%s;%s;%s;%02X-%02X-%02X;%02X:%02X;\0",
                byTexte[DATE], byTexte[HEURE], byTexte[OP], byTexte[HEADERAMOUNT],
                byTexte[NUMERO], byTexte[INFOSUP], byTexte[RESULT_OP],
                Today.mday, Today.mon, Today.year, Now.hour, Now.min);
        FSfwrite(bylBuffer, strlen(bylBuffer) + 2, 1, histoFile);
        do
        {
            if(wE2OperationPosRead < ADDRESS_HISTO)
            {
                wE2OperationPosRead = (0XFFF - sizeof(UOPERATION)) + 1;
            }
            I2CE2promLReadBuffer(wE2OperationPosRead, &histoData, sizeof(UOPERATION));
            memset(bylBuffer, 0x00, sizeof(bylBuffer));
            if((histoData.Operation & 0XFF) == NONEOP)
            {
                wE2OperationPosRead = wE2OperationPos;
            }
            else
            {
                wE2OperationPosRead -= sizeof(UOPERATION);
                memset(bylBuffer, 0x00, sizeof(bylBuffer));
                sprintf(bylBuffer, "\r\n%02X-%02X-%02X;%02X:%02X:%02X;%s;%*f;%u;%d;%s",
                        histoData.date.mday, histoData.date.mon, histoData.date.year,
                        histoData.time.hour, histoData.time.min, histoData.time.sec,
                        byTexte[UNKNOW_OP + histoData.Operation], byDecimalPos, (double)histoData.lAmount / wCurrencyDivider,
                        histoData.byMachine, histoData.lKeyNumber, histoData.result == FAIL ? byTexte[FAIL_OP] : byTexte[SUCCESSFUL_OP]);
                FSfwrite(bylBuffer, strlen(bylBuffer) + 2, 1, histoFile);
            }
        }while(wE2OperationPosRead - wE2OperationPos);
        FSfwrite("\r\n", 0x02, 1, histoFile);
        FSfclose(histoFile);
        LCDClear();
        LCD_CURSOR_OFF();
        boDisplayTime = FALSE;
        vDisplayLCD("%s", byTexte[HISTOSAVED]);
        DelayMs(centralParameters.lDelayDisplay + 2000);
    }
}

/******************************************************************************/

long lGetUSBAmountOrEnable(char *fileName, const WORD wEEAddress)
{
    BYTE byData[4] = {0};
    long lResult = 0;
    if((creditFile = FSfopen(fileName, FS_READ)) && (boCheckSN()))
    {
        if(boCodeCheck(wEEAddress))
        {
            if(FSfread(byData, 1, sizeof(byData), creditFile) == sizeof(byData))
            {
                lResult = byData[0] + (byData[1] * 0x100) + (byData[2] * 0x10000) +
                    (byData[3] * 0x1000000);
            }
        }
    }
    if(creditFile)
    {

        FSfclose(creditFile);
        creditFile = NULL;
    }
    return lResult;
}

/******************************************************************************/

BOOL vSetUSBAmountOrEnable(char *fileName, const WORD wEEAddress, const long lAmount)
{
    CODE CodeSN;

    if(thumbDriveAttached && (creditFile = FSfopen(fileName, FS_READ)) &&
       boCheckSN() && boCodeCheck(wEEAddress) && !FSfclose(creditFile) && !FSremove(fileName) &&
       (creditFile = FSfopen(fileName, FS_WRITEPLUS)))
    {

        vSetRndGap();
        CodeSN[0] = codeInter[0];
        CodeSN[1] = codeInter[1] ^(EMAC1SA2 / 256);
        CodeSN[2] = codeInter[2] ^(EMAC1SA1 % 256);
        CodeSN[3] = codeInter[3] ^(EMAC1SA1 / 256);
        CodeSN[4] = codeInter[4] ^(EMAC1SA0 % 256);
        CodeSN[5] = codeInter[5] ^(EMAC1SA0 / 256);
        FSfwrite(CodeSN, SIZECODE, 1, creditFile);
        vSetRndGap();
        vCreateCode(wEEAddress, &codeCredit);
        FSfwrite(codeCredit, SIZECODE, 1, creditFile);
        vSetRndGap();
        FSfwrite(&lAmount, sizeof(lAmount), 1, creditFile);
        vSetRndGap();
        FSfclose(creditFile);
        return TRUE;
    }
    return FALSE;
}

/******************************************************************************/

void vSetRndGap()
{
    BYTE *byData;
    BYTE byIndex;
    BYTE byRnd = (rand() % 166) + 4;
    BYTE byRnd2 = byRnd - 3;
    byRnd += 0X55;
    if(FSfwrite(&byRnd, 1, 1, creditFile))
    {
        if((byData = pvPortMalloc(byRnd)))
        {
            for(byIndex = 0; byIndex < byRnd; byIndex++)
            {

                byData[byIndex] = rand();
                FSfwrite(&byData[byIndex], 1, 1, creditFile);
            }
            memmove(codeInter, &byData[byRnd2], SIZECODE);
            vPortFree(byData);
        }
    }
}

/******************************************************************************/

BOOL boCheckSN()
{

    BYTE byData[6];
    BYTE byCode2[6] = {0};
    return(FSfread(byData, 1, 1, creditFile) == 1) && !FSfseek(creditFile, byData[0] - 0x57, SEEK_SET) &&
        (FSfread(byCode2, 1, 6, creditFile) == 6) && !FSfseek(creditFile, byData[0] + 1, SEEK_SET) &&
        (FSfread(byData, 1, 6, creditFile) == 6) &&
        ((byData[1] ^ byCode2[1]) == (EMAC1SA2 / 256)) && ((byData[2] ^ byCode2[2]) == (EMAC1SA1 % 256)) &&
        ((byData[3] ^ byCode2[3]) == (EMAC1SA1 / 256)) && ((byData[4] ^ byCode2[4]) == (EMAC1SA0 % 256)) &&
        ((byData[5] ^ byCode2[5]) == (EMAC1SA0 / 256));
}

/******************************************************************************/

BOOL boCodeCheck(WORD wEEAddress)
{

    BYTE byData[6] = {0};
    BYTE byDateTime[6] = {0};
    return I2CE2promLReadBuffer(wEEAddress, byDateTime, SIZECODE) &&
        (FSfread(byData, 1, 1, creditFile) == 1) && !FSfseek(creditFile, byData[0], SEEK_CUR) &&
        (FSfread(byData, 1, 6, creditFile) == 6) &&
        ((byData[1] ^ (EMAC1SA2 / 256)) == byDateTime[5]) && ((byData[2] ^ (EMAC1SA1 % 256)) == byDateTime[1]) &&
        ((byData[3] ^ (EMAC1SA1 / 256)) == byDateTime[4]) && ((byData[4] ^ (EMAC1SA0 % 256)) == byDateTime[0]) &&
        ((byData[5] ^ (EMAC1SA0 / 256)) == byDateTime[3]) && (FSfread(byData, 1, 1, creditFile) == 1) &&
        !FSfseek(creditFile, byData[0], SEEK_CUR);
}

/******************************************************************************/

void vEnableCN(void)
{
    //Interruption sur le changement de niveau d'une entrée.

    mCNClearIntFlag();
    mCNOpen(CN_ON | CN_IDLE_CON, CN5_ENABLE | CN4_ENABLE, CN5_PULLUP_ENABLE | CN4_PULLUP_ENABLE);
    ConfigIntCN(CHANGE_INT_ON | CHANGE_INT_PRI_1);
    EnableCN5;
    EnableCN4;
}

/******************************************************************************/

BOOL USB_ApplicationEventHandler(BYTE address, USB_EVENT event, void *data,
                                 DWORD size)
{
    // Handle specific events.
    isFileCreditPresent = FALSE;
    boFlip = FALSE;

    switch((INT)event)
    {
        case EVENT_VBUS_REQUEST_POWER:
            // We'll let anything attach.
        {
            return TRUE;
        }
        case EVENT_VBUS_RELEASE_POWER:
        {
            if(thumbDriveAttached)
            {
                thumbDriveAttached = FALSE;
                if(creditFile)
                {
                    FSfclose(creditFile);
                    creditFile = NULL;
                }
                if(UsageMode == MODEMAINTENANCE)
                {
                    vReturnFromTest();
                    //vReset();
                }
                byNumMachine = 0;
                byIndexSelectedMachine = 0xFF;
                boDisplayTime = TRUE;
                DelayMs(1000);
                vResetSelectMachine();
                vSetHisto(0, 0, USB_LEFT, 0, SUCCESSFUL);
            }
            ProcessIOState = INITIALIZE;
            return TRUE;
        }
        case EVENT_HUB_ATTACH:
        {
            LCDClear();
            vDisplayLCD("%s", "** USB Erreur **");
            LCDClearLine(2);
            vDisplayLCD("%s", "HUB IMPOSSIBLE! ");
            return TRUE;
        }
        case EVENT_UNSUPPORTED_DEVICE:
        {
            LCDClear();
            vDisplayLCD("%s", "** USB Erreur **");
            LCDClearLine(2);
            vDisplayLCD("%s", "PERIPH. REFUSE!");
            return TRUE;
        }
        case EVENT_CANNOT_ENUMERATE:
        {
            LCDClear();
            vDisplayLCD("%s", "** USB Erreur **");
            LCDClearLine(2);
            vDisplayLCD("%s", "Cannot Enumerate");
            break;
        }
        case EVENT_CLIENT_INIT_ERROR:
        {
            LCDClear();
            vDisplayLCD("%s", "** USB Erreur **");
            LCDClearLine(2);
            vDisplayLCD("%s", "Client Init Err.");
            return TRUE;
        }
        case EVENT_OUT_OF_MEMORY:
        {
            LCDClear();
            vDisplayLCD("%s", "** USB Erreur **");
            LCDClearLine(2);
            vDisplayLCD("%s", "Out of Heap Mem.");
            return TRUE;
        }

        case EVENT_UNSPECIFIED_ERROR: // This should never be generated.
        {
            LCDClear();
            vDisplayLCD("%s", "** USB Erreur **");
            LCDClearLine(2);
            vDisplayLCD("%s", " Not Specified! ");
            return TRUE;
        }
        case EVENT_DETACH:
        case EVENT_SUSPEND:
        case EVENT_RESUME:
        case EVENT_BUS_ERROR:
        {
            return TRUE;
        }
        default:
        {

            break;
        }
    }

    return FALSE;
} // USB_ApplicationEventHandler

/******************************************************************************/

BOOL boRAZAudit()
{
    BOOL boResult = TRUE;
    memset(&auditData, 0x00, sizeof(auditData));
    LCDClear();
    if(I2CE2promLWriteBuffer(ADDRESS_DEBUT_AUDIT, auditData.byAuditData, 128) &&
       (I2CE2promLWriteBuffer(ADDRESS_DEBUT_AUDIT + 128, &auditData.byAuditData[128], 128)))
    {
        vDisplayLCD("%s", byTexte[RAZOK]);
    }
    else
    {

        vDisplayLCD("%s", byTexte[RAZNOK]);
        boResult = FALSE;
    }
    vSetHisto(0, 0, RAZAUDITOP, 0, boResult ? SUCCESSFUL : FAIL);
    DelayMs(centralParameters.lDelayDisplay);
    return boResult;
}

/******************************************************************************/

void vReturnFromTest(void)
{
    //Supprime les autorisations d'accès au paramètrage.

    boLocalAccountantEnable = FALSE;
    boReturnMaintenance = FALSE;
    UsageMode = MODEUSER;
    wEcran = SCREENBEGINMAINTENANCE;
    sender = USER;
    vSetHisto(0, 0, TEST_LEFT, 0, SUCCESSFUL);
    vResetSelectMachine();
}

/******************************************************************************/

void vStartBuzzer(BOOL boActive, int iBuzzerLen)
{
    if(boActive)
    {

        BUZZER_ON();
        xTimerChangePeriod(hTimerTOBuzzer, iBuzzerLen, 1000);
    }
}

/******************************************************************************/

/*********************************************************************
 * Function:        BYTE getLCDAddress(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          L'adresse actuelle dans le controleur d'afficheur
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            Renvoi l'adresse actuelle du controleur d'afficheur
 *									Effectue une vérification sur le bit d'occupation.
 ********************************************************************/
BYTE getLCDAddress(void)
{

    while(LCD_IsBusy());
    return getLCDAddressCounter();
}

/******************************************************************************/

void vRecordMachineData()
{
    memset(bySatBuffer, 0, sizeof(bySatBuffer));
    if(boModifyMachineNumber(sender == MODIFMACHINES ? byNumMachine : 0XFF,
                             modules[byIndexSelectedMachine].config.byNumero))
    {
        boFlip = FALSE;
        vDisplayLCD(byTexte[MACHINEREGISTERED], modules[byIndexSelectedMachine].config.byNumero);
        if(modules[byIndexSelectedMachine].config.utEndSelect.l == 0)
        {
            modules[byIndexSelectedMachine].config.utEndSelect.l = 0X23595900; //23h59m59s
        }
        I2CE2promLWriteBuffer(ADDRESS_MACHINES_PARAMETERS + (byIndexSelectedMachine * sizeof(SMACHINE_CONFIG)),
                              &modules[byIndexSelectedMachine].config, sizeof(SMACHINE_CONFIG));
        boSetSensibility(modules[byIndexSelectedMachine].config.byNumero,
                         modules[byIndexSelectedMachine].config.BusyLevel.wBusyLevel);
        vSetMainPowerRelayState(modules[byIndexSelectedMachine].config.byNumero, !(ESTATE)modules[byIndexSelectedMachine].config.boMachinePowered);
        boSetOverBusyDelay(modules[byIndexSelectedMachine].config.byNumero, modules[byIndexSelectedMachine].config.lOverBusy);
    }
    else
    {

        vDisplayLCD(" %s", byTexte[FAILEDRECORD]);
        memset(&modules[byIndexSelectedMachine].config, 0X00, sizeof(SMACHINE_CONFIG));
        modules[byIndexSelectedMachine].config.byNumero = 0XFF;
    }
    DelayMs(centralParameters.lDelayDisplay);
    wEcran = SCREENSATELLITE;
}

/******************************************************************************/
#ifdef __L_DEBUG

void vApplicationMallocFailedHook(void)
{
    /* vApplicationMallocFailedHook(void) will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc(void) fails.
    pvPortMalloc(void) is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc(void) is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize(void) API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    LEDOFF(RED);
    LCDClearLine(1);
    vDisplayLCD("%s", "Malloc failed!");

    for(;;);
}

/******************************************************************************/


void vApplicationStackOverflowHook(TaskHandle_t pxTask, signed char *pcTaskName)
{
    (void)pcTaskName;
    (void)pxTask;
    taskDISABLE_INTERRUPTS();
    LCDClearLine(1);
    vDisplayLCD("%s %s", pcTaskName, "Stack overflow!");

    for(;;);
}
#endif

/******************************************************************************/
#ifdef __L_DEBUG

/*-----------------------------------------------------------*/

void vAssertCalled(const char * pcFile, unsigned long ulLine)
{
    volatile unsigned long ul = 0;

    (void)pcFile;
    (void)ulLine;

    __asm volatile( "di");
    {
        /* Set ul to a non-zero value using the debugger to step out of this
        function. */
        while(ul == 0)
        {
            portNOP();
        }
    }
    __asm volatile( "ei");
}
#endif
