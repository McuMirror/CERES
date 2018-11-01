#include "lcd4u.h"

/*Constantes*******************************************************************/
/**
 * \var barr
 * \brief Barre de curseur sur l'afficheur
 */
const BYTE barr[] [8] = {
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C},
    {0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E},
    {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}
};

/**
 * \var euro
 * \brief Caractère ¤
 */
const BYTE euro[] = {0x07, 0x08, 0x1E, 0x08, 0x1E, 0x08, 0x07, 0x00};

/**
 * \var pound
 * \brief caractère £
 */
const BYTE pound[] = {0X0E, 0X11, 0X10, 0X08, 0X1C, 0X09, 0X1E, 0X00};

/******************************************************************************/

/*Macro************************************************************************/

/**
 * \def DB4
 * \brief IO utilisée pour le bit de donnée 4.
 */
#define DB4 BIT_4

/**
 * \def DB5
 * \brief IO utilisée pour le bit de donnée 5.
 */
#define DB5 BIT_5

/**
 * \def DB6
 * \brief IO utilisée pour le bit de donnée 6.
 */
#define DB6 BIT_6

/**
 * \def DB7
 * \brief IO utilisée pour le bit de donnée 7.
 */
#define DB7 BIT_7

/**
 * \def DATA_LINE
 * \brief IOs utilisées pour les données de l'afficheur.
 */
#define DATA_LINE DB7 | DB6 | DB5 | DB4

/**
 * \def LCD_DATA
 * \brief Port et entrée sortie des données de l'afficheur.
 */
#define LCD_DATA LCD_PORT, DATA_LINE

/**
 * \def RW
 * \brief IO de la ligne RW du HD44780.
 */
#define RW BIT_2

/**
 * \def EN
 * \brief IO de la ligne EN du HD44780
 */
#define EN BIT_3

/**
 * \def LCD_RW
 * \brief Port et IO de la ligne RW
 */
#define LCD_RW LCD_PORT, RW

/**
 * \def LCD_EN
 * \brief Port et IO de la ligne EN
 */
#define LCD_EN LCD_PORT, EN

/**
 * \def LCD_BUS
 * \brief BUS de l'afficheur
 */
#define LCD_BUS DATA_LINE | RS | RW | EN

/**
 * \def LCD_8BITS
 * \brief Commande de mode 8 bits
 */
#define LCD_8BITS LCD_4BITS | DB4

/**
 * \def LCD_CURSOR
 * \brief Commande concernant le curseur.
 */
#define LCD_FUNCTION        (1 << 5)
#define LCD_SET_CGRAM_ADDR  (1 << 6)
#define BUSY_FLAG           (1 << 7)

/**
 * \def LCD_RESET_PORT_DATA
 * \brief Positionne le bus de donnée à l'état bas.
 */
#define LCD_RESET_PORT_DATA() PORTClearBits(LCD_DATA)

/**
 * \def SetCGRamAddr
 * \brief Positionne l'adresse dans la mémoire graphique.
 * \param[in] addr Adresse dans la mémoire graphique.
 */
#define SetCGRamAddr(addr) LCD_Command(LCD_SET_CGRAM_ADDR | addr);

/**
 * \def EURO
 * \brief Numéro du caractère ¤
 */
#define EURO 7

/**
 * \def POUND
 * \brief Numéro du caractère £
 */
#define POUND 6
/*End of macros****************************************************************/

/*Variables********************************************************************/

/**
 * \var isLCDInitialized
 * \brief Indique si l'afficheur est présent et fonctionnel.
 */
BOOL isLCDInitialized;
/*End of variables*************************************************************/

/*Function*********************************************************************/

/*********************************************************************
 * Function:        void LCD_Clock(void)
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
 * Note:            Valide les données sur le  bus de data du controleur d'afficheur.
 ********************************************************************/
static void LCD_Clock(void)
{
    Delay10us(1);
    PORTSetBits(LCD_EN);
    Delay10us(1);
    PORTClearBits(LCD_EN);
}
//******************************************************************************

/*********************************************************************
 * Function:        void CreateChar(const BYTE Code, const BYTE *pBuffer)
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
static void CreateChar(const BYTE Code, const BYTE *pBuffer)
{
    BYTE byIndex;
    SetCGRamAddr(Code * 8);
    for(byIndex = 8; byIndex; byIndex--)
    {
        LCD_Put(*pBuffer++);
    }
}
//******************************************************************************

/*********************************************************************
 * Function:        BOOL LCD_IsBusy(void)
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
 * Note:            Vérifie si le contrôleur est disponibke.
 ********************************************************************/
BOOL LCD_IsBusy(void)
{
    if(isLCDInitialized)
    {
        return((getLCDAddressCounter() & BUSY_FLAG) > 0);
    }
    else
    {
        PORTClearBits(LCD_EN);
        PORTClearBits(LCD_RS);
        LCD_RESET_PORT_DATA();
        Delay10us(15);
    }
    return(FALSE);
}
//******************************************************************************

static void _LCDGotoXY(BYTE X, BYTE Y)
{
    while(LCD_IsBusy());
    LCD_Command(LCD_SET_DDRAM_ADDR | (--X + (--Y * 64)));
}

/*********************************************************************
 * Function:        BYTE getLCDAddressCounter(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          le compteur d'adresse.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            Lit le compteur d'adresse de la ram
 *									Le bit de poid fort indique si l'afficheur est occcupé par
 *									une opération interne.
 *
 ********************************************************************/
BYTE getLCDAddressCounter()
{
    BYTE byResult;

    PORTClearBits(LCD_RS); //RS à l'état bas.
    PORTSetBits(LCD_RW); //RW en lecture.
    PORTSetBits(LCD_EN); //Activé.
    Delay10us(1);
    PORTSetPinsDigitalIn(LCD_DATA);
    byResult = PORTReadBits(LCD_DATA); //Lecture de la partie haute de l'adresse
    PORTClearBits(LCD_EN); //Etat bas pour Enable
    Delay10us(1);
    PORTSetBits(LCD_EN); //Activé
    byResult += PORTReadBits(LCD_DATA) >> 4; //Lecture  de la partie basse de l'adresse.
    Delay10us(1);
    PORTClearBits(LCD_EN); //Etat bas pour Enable.
    PORTClearBits(LCD_RW); //Sort du mode lecture.
    LCD_RESET_PORT_DATA(); //Le port data à l'état bas
    PORTSetPinsDigitalOut(LCD_DATA);
    return byResult;
}
//******************************************************************************

/*********************************************************************
 * Function:        void LCDSetValue(const BYTE byValue)
 *
 * PreCondition:    Le contrôleur doit être libre. Utiliser LCD_IsBusy pour
 *									effectuer la vérification
 *
 * Input:           La valeur à transmettre au controleur de l'afficheur
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            Envoi une valeur à l'afficheur.
 ********************************************************************/
void LCDSetValue(const BYTE byValue)
{
    LCD_RESET_PORT_DATA();
    PORTSetBits(LCD_PORT, byValue & 0XF0);
    LCD_Clock();
    LCD_RESET_PORT_DATA();
    PORTSetBits(LCD_PORT, (byValue << 4) & 0XF0);
    LCD_Clock();
}
//******************************************************************************

void _mon_putc(char cData)
{
    while(LCD_IsBusy());
    PORTSetBits(LCD_RS);
    LCDSetValue(cData);
    while(LCD_IsBusy());
}
/******************************************************************************/

/*********************************************************************
 * Function:        void LCD_Command(const BYTE byCmd)
 *
 * PreCondition:    None
 *
 * Input:           La commande à transmettree à l'afficheur.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            Envoi une commande au controleur d'afficheur.
 ********************************************************************/
void LCD_Command(const BYTE byCmd)
{
    while(LCD_IsBusy());
    LCDSetValue(byCmd);
}

//******************************************************************************

/*********************************************************************
 * Function:        void LCDInit(void)
 *
 * PreCondition:    None
 *
 * Input:           byNumLignes Nombre de lignes de l'afficheur
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
void LCDInit(const BYTE byNumLignes)
{
    BYTE byIndex = 0;

    //Force toutes les lignes de commande à l'état bas.
    PORTSetPinsDigitalOut(LCD_PORT, LCD_BUS);
    PORTClearBits(LCD_PORT, LCD_BUS);
    
    //Positionne tout le bus en opendrain permettant ainsi de piloter l'afficheur en 5V
    ODCESET = LCD_BUS;
    
    //Stabilisation de l'alimentation
    //Wait time > 40ms
    DelayMs(150);

    //--------------------------------------------------------------------------
    //Fonction set
    PORTSetBits(LCD_PORT, DB5 | DB4);
    LCD_Clock();
    //-----------------------    
    //Wait time > 40us
    DelayMs(1);
    //--------------------------------------------------------------------------
    
    //Fonction set--------------------------------------------------
    //MSB bits    
    LCD_RESET_PORT_DATA();
    PORTSetBits(LCD_PORT, DB5);
    LCD_Clock();
    
    //LSB bits
    //Fonction 2 lignes
    LCD_RESET_PORT_DATA();
    //Si le nombre de ligne est > 1 on active le système 2 ligne sinon on choisit
    //les caractères precis.
    PORTSetBits(LCD_PORT, (byNumLignes > 1) ? DB7 : DB6 );
   
    LCD_Clock();
    //Wait time > 40 us    
    DelayMs(1);
    //--------------------------------------------------------------------------
    
    //Fonction set--------------------------------------------------
    //MSB bits    
    LCD_RESET_PORT_DATA();
    PORTSetBits(LCD_PORT, DB5);
    LCD_Clock();
    
    //LSB bits
    //Fonction 2 lignes
    LCD_RESET_PORT_DATA();
    //Si le nombre de ligne est > 1 on active le système 2 ligne sinon on choisit
    //les caractères precis.
    PORTSetBits(LCD_PORT, (byNumLignes > 1) ? DB7 : DB6 );
   
    LCD_Clock();
    
    //-----------------------------------
    //Wait time > 40 us    
    DelayMs(1);
    //--------------------------------------------------------------------------
    
    //Fonction display on/off control--------------------------------------------------
    //MSB bits    
    LCD_RESET_PORT_DATA();
    LCD_Clock();
    
    //LSB 
    PORTSetBits(LCD_PORT, DB7 | DB6 | DB5 | DB4); //Seul le bit 7 est positionné pour la fonction control de l'afficheur.
    //Display off, cursor off, blink off.
    LCD_Clock();
    
    //------------------------------------------
    //Wait time > 40 us    
    DelayMs(1);
    //--------------------------------------------------------------------------
    
    //Fonction clear display--------------------------------------------------
    //MSB bits    
    LCD_RESET_PORT_DATA();
    LCD_Clock();
    
    //LSB bits l'afficheur
    PORTSetBits(LCD_PORT, DB4);
    LCD_Clock();
    //Wait time > 40 us    
    DelayMs(1);
    //--------------------------------------------------------------------------
    
    //Fonction entry mode set--------------------------------------------------
    //MSB bits    
    LCD_RESET_PORT_DATA();
    LCD_Clock();
    
    //LSB bits Entry mode set
    PORTSetBits(LCD_PORT, DB6); //Seul le bit 6 est positionné pour pas de shift
    LCD_Clock();
    //Wait time > 40 us    
    DelayMs(1);
    LCD_RESET_PORT_DATA();
    //--------------------------------------------------------------------------

    isLCDInitialized = TRUE;
    //Attend au maximum 255 fois que le controleur soit libre.
    while(--byIndex && LCD_IsBusy())
    {
        Nop();
    }
    isLCDInitialized = (byIndex > 0);
    
    for(byIndex = 0; byIndex < 5; byIndex++)
    {
        CreateChar(byIndex + 1, barr[byIndex]);
    }
    CreateChar(EURO, euro);
    CreateChar(POUND, pound);
    //Clear display
    while(LCD_IsBusy());
    LCDSetValue(0x01);

    //Cursor OFF
    while(LCD_IsBusy());
    LCDSetValue(LCD_DISPLAY_CONTROL | LCD_ON);

    //Train d'impulsion sur OC2 à 10 KHZ duty 50% pour génerer la tension negative de l'afficheur.
    OpenOC2(OC_ON | OC_TIMER_MODE16 | OC_TIMER2_SRC | OC_CONTINUE_PULSE
            | OC_LOW_HIGH, 0X7C0, 0X7C0);
    OpenTimer2(T2_ON, 0X0F9F);
    xSemaphoreGive(semaphoreLCD = xSemaphoreCreateBinary());
}

//******************************************************************************

/*********************************************************************
 * Function:        void setLCDAddressCounter(void)
 *
 * PreCondition:    None
 *
 * Input:           Adresse pour le controleur
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            Fixe l'adresse courante du controleur
 ********************************************************************/
void setLCDAddressCounter(BYTE byAddress)
{
    xSemaphoreTake(semaphoreLCD, 10000);
    if(byAddress < 128)
    {
        LCD_Command(LCD_SET_DDRAM_ADDR | byAddress);
    }
    xSemaphoreGive(semaphoreLCD);
}

//******************************************************************************

void LCDClearLine(const BYTE line)
{
    BYTE byIndex;
    xSemaphoreTake(semaphoreLCD, 10000);
    _LCDGotoXY(1, line);
    for(byIndex = 1; byIndex <= LCDNUMCHAR; byIndex++)
    {
        LCD_Put(' ');
    }
    _LCDGotoXY(1, line);
    xSemaphoreGive(semaphoreLCD);
}

//******************************************************************************

BYTE getLCDC()
{
    BYTE byResult;
    xSemaphoreTake(semaphoreLCD, 10000);
    while(LCD_IsBusy());
    PORTSetBits(LCD_RS); //RS à l'état bas.
    PORTSetBits(LCD_RW); //RW en lecture.
    PORTSetBits(LCD_EN); //Activé.
    //vDelay1US(); //Temps de verrouillage de l'adresse.
    Delay10us(1);
    PORTSetPinsDigitalIn(LCD_DATA);
    byResult = PORTReadBits(LCD_DATA); //Lecture de la partie haute de l'adresse
    PORTClearBits(LCD_EN); //Etat bas pour Enable
    //vDelay1US(); //Délai.
    Delay10us(1);
    PORTSetBits(LCD_EN); //Activé
    byResult += PORTReadBits(LCD_DATA) >> 4; //Lecture  de la partie basse de l'adresse.
    //vDelay1US();
    Delay10us(1);
    PORTClearBits(LCD_EN); //Etat bas pour Enable.
    PORTClearBits(LCD_RW); //Sort du mode lecture.
    PORTClearBits(LCD_RS);
    LCD_RESET_PORT_DATA(); //Le port data à l'état bas
    PORTSetPinsDigitalOut(LCD_DATA);
    while(LCD_IsBusy());
    xSemaphoreGive(semaphoreLCD);
    return byResult;
}

/*********************************************************************
 * Function:        void LCDClear(void)
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
void LCDClear(void)
{
    LCD_Command(LCD_CLEAR);
    //ClearWDT();
    DelayMs(4);
    LCDGotoXY(1, 1);
}

/*********************************************************************
 * Function:        void vDisplayLCD(char *format, ...)
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
void vDisplayLCD(char *format, ...)
{
    va_list args;

    xSemaphoreTake(semaphoreLCD, 10000);
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    xSemaphoreGive(semaphoreLCD);        
}

/*********************************************************************
 * Function:        void LCDGotoXY(BYTE X, BYTE Y)
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
void LCDGotoXY(BYTE X, BYTE Y)
{
    xSemaphoreTake(semaphoreLCD, 10000);
    _LCDGotoXY(X, Y);
    xSemaphoreGive(semaphoreLCD);
}

/*End of functions*************************************************************/
