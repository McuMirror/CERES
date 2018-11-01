
BOOL boMakeChange(long lAmount)
{
    long lInitialAmount;
    LCD_CURSOR_OFF();   //Pas de curseur.

    //Obtient le nombre d'unit� de base en fonction du scale factor du changer.
    lAmount /= boChangerReseted ? changeGiverConfig.deviceConfig.byScaleFactor : 1;
    //Sauvegarde le nombre d'unit� de base pour v�rifier si le nombre d'unit� de base distribu� estt �gale au nombre � distribuer.
    lInitialAmount = lAmount;

    if(boChangeAutorized && lAmount) //V�rifie si il y a un montant � distribuer.
    {
        BYTE byIndex;
        boChangeAutorized = FALSE;
        //Traitement pour un rendeur de niveau MDB 2
        if(changeGiverConfig.deviceConfig.byLevel < 3)
        {
            BYTE byIndex2 = 3;
            boGetMDBTubeStatus(&tubeStatus); //R�cup�re le niveau des tubes.
            while(--byIndex2 && lAmount)//R�p�te 3 fois les op�rations suivantes, � moins que la distribution soit termin�e.
            {
                byIndex = 15; //On commence par le canal le plus �lev� pour distribuer le minimum de pi�ces
                do
                {
                    if(changeGiverConfig.byCoinValue[byIndex] < 0xFF) //V�rifie si le canal est valable.
                    {
                        /*
                         * Si le nombre de pi�ces contenu dans le tube correspondant est sup�rieur au montant � distribuer,
                         * le nombre de pi�ces � distribuer sera �gal au montant diviser par la valeur de la pi�ce du tube.
                         * Sinon toutes les pi�ces du tubes seront distribu�es.
                         */
                        BYTE byNumToDispense;
                        if((lAmount / changeGiverConfig.byCoinValue[byIndex]) <
                           tubeStatus.byTubeLevel[byIndex])
                        {
                            byNumToDispense = (BYTE)(lAmount /
                                                     changeGiverConfig.byCoinValue[byIndex]);
                        }
                        else
                        {
                            byNumToDispense = tubeStatus.byTubeLevel[byIndex];
                        };
                        if(byNumToDispense)
                        {
                            if(boDispenseMDBChanger(byIndex, byNumToDispense))
                            {
                                auditData.data.wNumberChannelCGOut[byIndex] += byNumToDispense;
                                I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCOUT + (sizeof(WORD) * byIndex),
                                                      &auditData.data.wNumberChannelCGOut[byIndex],
                                                      sizeof(WORD));
                                auditDataPermanent.data.wNumberChannelCGOut[byIndex] += byNumToDispense;
                                I2CE2promLWriteBuffer(ADDRESS_WNUMBERCHANNELGCIN_PERMANENT + (sizeof(WORD) * byIndex),
                                                      &auditDataPermanent.data.wNumberChannelCGOut[byIndex],
                                                      sizeof(WORD));
                                lAmount -= (byNumToDispense * changeGiverConfig.byCoinValue[byIndex]);
                                DelayMs(200 * byNumToDispense);
                            };
                        };
                    };
                }
                while(byIndex-- && (lAmount > 0));
            };
        }
        else
        {
            //Envoie la commande de distribution d'un nombre d'unit� de base en mode MDB 3.
            if(boAlternatePayout(lAmount))
            {
                //Cr�ation d'un tableau qui contiendra le nombre de pi�ces de chaque type distribu�.
                BYTE byCoinsBuffer[MAXNUMBERCHANNELSCG + 1];
                //Efface la ligne 1.
                LCDClearLine(1);
                //Affiche rendu en cours.
                printf("%s", byTexte[RETURN]);
                do
                {
                    //S'asure que les autres op�rations MDB sont termin�es.
                    DelayMs(MDBPOLLINMS);
                    ClearWDT();
                }
                while(!boPayoutStatus(byCoinsBuffer));
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
                    };
                };
            };
        };
        lAmountInCashDispo -= (lInitialAmount - lAmount) * changeGiverConfig.deviceConfig.byScaleFactor;
        //Par s�curit�.
        if(lAmountInCashDispo < 0)
        {
            lAmountInCashDispo = 0;
        };
        vDisplayAmount(lInitialAmount - lAmount, byTexte[RETURNED]);
        vSetHisto(0, 0, OUCG, lInitialAmount - lAmount, lInitialAmount == lAmount ? SUCCESSFUL : FAIL);
        DelayMs(centralParameters.lDelayDisplay);
        xTimerStart(hTimerTOOverpay, portMAX_DELAY);
        return(lInitialAmount != lAmount);
    };
    return FALSE;
}
