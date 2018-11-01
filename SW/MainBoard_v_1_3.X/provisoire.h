
BOOL boMakeChange(long lAmount)
{
    long lInitialAmount;
    LCD_CURSOR_OFF();   //Pas de curseur.

    //Obtient le nombre d'unité de base en fonction du scale factor du changer.
    lAmount /= boChangerReseted ? changeGiverConfig.deviceConfig.byScaleFactor : 1;
    //Sauvegarde le nombre d'unité de base pour vérifier si le nombre d'unité de base distribué estt égale au nombre à distribuer.
    lInitialAmount = lAmount;

    if(boChangeAutorized && lAmount) //Vérifie si il y a un montant à distribuer.
    {
        BYTE byIndex;
        boChangeAutorized = FALSE;
        //Traitement pour un rendeur de niveau MDB 2
        if(changeGiverConfig.deviceConfig.byLevel < 3)
        {
            BYTE byIndex2 = 3;
            boGetMDBTubeStatus(&tubeStatus); //Récupère le niveau des tubes.
            while(--byIndex2 && lAmount)//Répéte 3 fois les opérations suivantes, à moins que la distribution soit terminée.
            {
                byIndex = 15; //On commence par le canal le plus élevé pour distribuer le minimum de pièces
                do
                {
                    if(changeGiverConfig.byCoinValue[byIndex] < 0xFF) //Vérifie si le canal est valable.
                    {
                        /*
                         * Si le nombre de pièces contenu dans le tube correspondant est supérieur au montant à distribuer,
                         * le nombre de pièces à distribuer sera égal au montant diviser par la valeur de la pièce du tube.
                         * Sinon toutes les pièces du tubes seront distribuées.
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
            //Envoie la commande de distribution d'un nombre d'unité de base en mode MDB 3.
            if(boAlternatePayout(lAmount))
            {
                //Création d'un tableau qui contiendra le nombre de pièces de chaque type distribué.
                BYTE byCoinsBuffer[MAXNUMBERCHANNELSCG + 1];
                //Efface la ligne 1.
                LCDClearLine(1);
                //Affiche rendu en cours.
                printf("%s", byTexte[RETURN]);
                do
                {
                    //S'asure que les autres opérations MDB sont terminées.
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
        //Par sécurité.
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
