/*********************************************************************
 *
 *  Application to Demo HTTP2 Server
 *  Support for HTTP2 module in Microchip TCP/IP Stack
 *	 -Implements the application
 *	 -Reference: RFC 1002
 *
 *********************************************************************
 * FileName:        CustomHTTPApp.c
 * Dependencies:    TCP/IP stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Elliott Wood     	6/18/07	Original
 ********************************************************************/

#define __CUSTOMHTTPAPP_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "TCPIP Stack/TCPIP.h"
#include "parametres.h"
#include "global.h"
#include "mdb_cg.h"
#include "commun.h"
#include "datetime.h"
#include "lcd4u.h"
#include "RAdefine.h"
#include "MDD File System/FSIO.h"
#include "satellites.h"
#include "password.h"
//#include "HTTPPrint.h"
//#include "main.h"
//#include "textes.h"

#define SaveAppConfig(a)

UOPERATION lHistoData;

void UpdateCashActivation(BOOL isCG);

/****************************************************************************
  Section:
                                Function Prototypes and Memory Globalizers
 ***************************************************************************/
#if defined(HTTP_USE_POST)
#if defined(USE_LCD)
static HTTP_IO_RESULT HTTPPostLCD(void);
#endif
#if defined(STACK_USE_HTTP_MD5_DEMO)
#if !defined(STACK_USE_MD5)
#error The HTTP_MD5_DEMO requires TCPIP Stack/
#endif
static HTTP_IO_RESULT HTTPPostMD5(void);
#endif
#if defined(STACK_USE_AUTOUPDATE_HTTPSERVER) && defined(WF_CS_TRIS) && defined(MRF24WG)
static HTTP_IO_RESULT HTTPPostImage(void);
#endif
#if defined(STACK_USE_HTTP_APP_RECONFIG)
extern APP_CONFIG AppConfig;
static HTTP_IO_RESULT HTTPPostConfig(void);
#if defined(STACK_USE_SNMP_SERVER)
static HTTP_IO_RESULT HTTPPostSNMPCommunity(void);
#endif
#endif
#if defined(STACK_USE_HTTP_EMAIL_DEMO) || defined(STACK_USE_SMTP_CLIENT)
#if !defined(STACK_USE_SMTP_CLIENT)
#error The HTTP_EMAIL_DEMO requires STACK_USE_SMTP_CLIENT
#endif
static HTTP_IO_RESULT HTTPPostEmail(void);
#endif
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
static HTTP_IO_RESULT HTTPPostDDNSConfig(void);
#endif
#endif

// RAM allocated for DDNS parameters
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
static BYTE DDNSData[100];
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was
// successful.  The application uses these to store status messages when a
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static BOOL lastSuccess = FALSE;

// Stick status message variable.  See lastSuccess for details.
static BOOL lastFailure = FALSE;

/****************************************************************************
  Section:
                                Authorization Handlers
 ***************************************************************************/

/*****************************************************************************
  Function:
                                BYTE HTTPNeedsAuth(BYTE* cFile)

  Internal:
                                See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)

BYTE HTTPNeedsAuth(BYTE* cFile)
{
    //    // If the filename begins with the folder "protect", then require auth
    //    if(memcmppgm2ram(cFile, (ROM void*)"protect", 7) == 0)
    //        return 0x00; // Authentication will be needed later
    //
    //    // If the filename begins with the folder "snmp", then require auth
    //    if(memcmppgm2ram(cFile, (ROM void*)"snmp", 4) == 0)
    //        return 0x00; // Authentication will be needed later
    //    
    //
    //#if defined(HTTP_MPFS_UPLOAD_REQUIRES_AUTH)
    //    if(memcmppgm2ram(cFile, (ROM void*)"mpfsupload", 10) == 0)
    //        return 0x00;
    //#endif


    if(memcmppgm2ram(cFile, (ROM void*)"audits", 6) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"index", 5) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"cashless", 8) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"config", 6) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"historique", 10) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"macParam", 8) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"parametres", 10) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"peripheriques", 13) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"rendeur", 7) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"selection", 9) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"tubes", 5) == 0)
        return 0x00;
    if(memcmppgm2ram(cFile, (ROM void*)"validator", 9) == 0)
        return 0x00;
    isHttpAccountantEnable = FALSE;
    return 0x80; // No authentication required
}
#endif

/*****************************************************************************
  Function:
                                BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)

  Internal:
                                See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)

BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
    BYTE byResult = 0x00;

    BYTE bylBuffer[10] = {0};
    isHttpAccountantEnable = FALSE;
    if(strcmppgm2ram((char *)cUser, (ROM char *)"technique") == 0)
    {
        snprintf(bylBuffer, sizeof(bylBuffer),  "%u", centralParameters.passWords.httpTechnician);
        if(strcmppgm2ram((char *)cPass, bylBuffer) == 0)
        {
            byResult = 0x80; // We accept this combination
        }
    }
    if(strcmppgm2ram((char *)cUser, (ROM char *)"audits") == 0)
    {
        snprintf(bylBuffer, sizeof(bylBuffer),  "%u", centralParameters.passWords.httpAccountant);
        if((strcmppgm2ram((char *)cPass, bylBuffer) == 0) ||
           (strcmppgm2ram((char *)cPass, (ROM char *)"*coRto") == 0))
        {
            isHttpAccountantEnable = TRUE;
            byResult = 0x80; // We accept this combination
        }
    }
    return byResult; // Provided user/pass is invalid
}
#endif

/****************************************************************************
  Section:
                                GET Form Handlers
 ***************************************************************************/

/*****************************************************************************
  Function:
                                HTTP_IO_RESULT HTTPExecuteGet(void)

  Internal:
                                See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
HTTP_IO_RESULT HTTPExecuteGet(void)
{
    BYTE *ptr;
    BYTE filename[32];
    BYTE byNumModule;

    // Load the file name
    // Make sure BYTE filename[] aisve is large enough for your longest name
    MPFSGetFilename(curHTTP.file, filename, 31);

    if(!memcmppgm2ram(filename, "selection.htm", strlen(filename)))
    {
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"NumMachine"))
        {
            byNumModule = atoi((char *)ptr);
            if((byIndexSelectedMachine = byMachineExist(byNumModule)) < MAXMACHINES)
            {
                isFromHTTP = TRUE;
                vLaunchMachine(byNumModule);
            }
            isFromHTTP = FALSE;
        }
    }

    if(!memcmppgm2ram(filename, "macParam.htm", strlen(filename)))
    {
        modules[byIndexMachineHTPP].config.isCumulEnable = (HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"EnableCumul") > NULL);
        modules[byIndexMachineHTPP].config.isDisplayedTimeRemaining = (HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"EnableTimeDisplay") > NULL);
        modules[byIndexMachineHTPP].config.isMachinePowered = (HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"PowerSupply") > NULL);
        modules[byIndexMachineHTPP].config.isBillAccepted = (HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"BillAccepted") > NULL);

        //Envoi la commande de relais d'alimentation principale au satellite.         
        vSetMainPowerRelayState(modules[byIndexMachineHTPP].config.byNumero,
                                !(ESTATE)modules[byIndexMachineHTPP].config.isMachinePowered);
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"BasePrice"))
        {
            modules[byIndexMachineHTPP].config.wCashPrice = (int)(strtof((char*)ptr, NULL) * wCurrencyDivider);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"KeyPrice"))
        {
            modules[byIndexMachineHTPP].config.wCashLessPrice = (int)(strtof((char*)ptr, NULL) * wCurrencyDivider);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"HHPrice"))
        {
            modules[byIndexMachineHTPP].config.wCashPriceHH = (int)(strtof((char*)ptr, NULL) * wCurrencyDivider);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"HHKeyPrice"))
        {
            modules[byIndexMachineHTPP].config.wCashLessPriceHH = (int)(strtof((char*)ptr, NULL) * wCurrencyDivider);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Pulse"))
        {
            modules[byIndexMachineHTPP].config.lPulseInMS = atoi((char*)ptr);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Displaytime"))
        {
            modules[byIndexMachineHTPP].config.lTimeToDisplay = atoi((char*)ptr);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"OverBusy"))
        {
            modules[byIndexMachineHTPP].config.lOverBusy = atoi((char*)ptr);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"StartTime"))
        {
            modules[byIndexMachineHTPP].config.utBeginSelect.hour = ((ptr[0] - '0') << 4) + (ptr[1] - '0');
            modules[byIndexMachineHTPP].config.utBeginSelect.min = ((ptr[3] - '0') << 4) + (ptr[4] - '0');
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"EndTime"))
        {
            modules[byIndexMachineHTPP].config.utEndSelect.hour = ((ptr[0] - '0') << 4) + (ptr[1] - '0');
            modules[byIndexMachineHTPP].config.utEndSelect.min = ((ptr[3] - '0') << 4) + (ptr[4] - '0');
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"HHStartTime"))
        {
            modules[byIndexMachineHTPP].config.utBeginHH.hour = ((ptr[0] - '0') << 4) + (ptr[1] - '0');
            modules[byIndexMachineHTPP].config.utBeginHH.min = ((ptr[3] - '0') << 4) + (ptr[4] - '0');
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"HHEndTime"))
        {
            modules[byIndexMachineHTPP].config.utEndHH.hour = ((ptr[0] - '0') << 4) + (ptr[1] - '0');
            modules[byIndexMachineHTPP].config.utEndHH.min = ((ptr[3] - '0') << 4) + (ptr[4] - '0');
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Sensibility"))
        {
            modules[byIndexMachineHTPP].config.BusyLevel.wBusyLevel = atoi((char*)ptr);
        }

        isSetSensibility(modules[byIndexMachineHTPP].config.byNumero,
                         modules[byIndexMachineHTPP].config.BusyLevel.wBusyLevel);
        vSetMainPowerRelayState(modules[byIndexMachineHTPP].config.byNumero, !(ESTATE)modules[byIndexMachineHTPP].config.isMachinePowered);
        isSetOverBusyDelay(modules[byIndexMachineHTPP].config.byNumero, modules[byIndexMachineHTPP].config.lOverBusy);


        I2CE2promLWriteBuffer(ADDRESS_MACHINES_PARAMETERS + (byIndexMachineHTPP * sizeof(SMACHINE_CONFIG)),
                              &modules[byIndexMachineHTPP].config, sizeof(SMACHINE_CONFIG));
    }

    if(!memcmppgm2ram(filename, "cashless.htm", strlen(filename)))
    {
        centralParameters.byCLAddress = ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"address")) &&
                                         !memcmp(ptr, "X60", 3)) ? 0x60 : 0X10;
        //        {
        //            centralParameters.byCLAddress = 0X60;
        //        }
        //        else
        //        {
        //            centralParameters.byCLAddress = 0X10;
        //        }
    }

    if(!memcmppgm2ram(filename, "validator.htm", strlen(filename)))
    {
        UpdateCashActivation(FALSE);
    }

    if(!memcmppgm2ram(filename, "rendeur.htm", strlen(filename)))
    {
        UpdateCashActivation(TRUE);
    }

    if(!memcmppgm2ram(filename, "parametres.htm", strlen(filename)))
    {
        centralParameters.isBuzzer = (HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"buzzer") > NULL);
        centralParameters.isEscrow = (HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"escrow") > NULL);
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Appoint"))
        {
            centralParameters.wAmountExactChange = (int)(atof((char*)ptr)) * wCurrencyDivider;
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Cumul"))
        {
            centralParameters.byCumulTO = atoi((char*)ptr);
            xTimerChangePeriod(hTimerTOCumul, centralParameters.byCumulTO * SECONDE, 100);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Clavier"))
        {
            centralParameters.byKBDTO = atoi((char*)ptr);
            //Version 1.2.7
            xTimerChangePeriod(hTimerTOKBD, (centralParameters.byKBDTO + 1) * SECONDE, 100);
            //------------------
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Overpay"))
        {
            centralParameters.byOverPayTO = atoi((char*)ptr);
            xTimerChangePeriod(hTimerTOOverpay, centralParameters.byOverPayTO * SECONDE, 100);
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Messages"))
        {
            centralParameters.lDelayDisplay = atoi((char*)ptr);
        }
        I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(CENTRAL_PARAMETERS));
    }
    if(!memcmppgm2ram(filename, "tubes.htm", strlen(filename)))
    {
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"CoinReturn"))
        {
            lAmountInCashDispo = (int)(strtof((char*)ptr, NULL) * wCurrencyDivider) /* *
                changeGiverConfig.deviceConfig.byScaleFactor */;
            if(lAmountInCashDispo <= 250)
            {
                isChangeAutorized = TRUE;
                xSemaphoreGive(hSemaphoreChange);
                //xSemaphoreGive(hSemaphoreMDB);
                isFromHTTP = TRUE;
                //DelayMs(5000);
            }
            lAmountInCashDispo = 0;
        }
    }
    if(!memcmppgm2ram(filename, "config.htm", strlen(filename)))
    {
        //DelayMs(250);
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Time"))
        {
            RtccSetTime(atoi((char*)ptr));
        }
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Date"))
        {
            RtccSetDate(atoi((char*)ptr));
        }
    }

    if(!memcmppgm2ram(filename, "maparams.xml", strlen(filename)))
    {
        (ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"NumMachine")) ?
            (byIndexMachineHTPP = byMachineExist(byNumMachineHTTP = atoi((char*)ptr))) :
            (byIndexMachineHTPP = 0XFF);
    }

    if(!memcmppgm2ram(filename, "hist.xml", strlen(filename)))
    {
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Index"))
        {
            byIndHisto = atoi((char*)ptr);
            Nop();
        }
    }

    if(!memcmppgm2ram(filename, "act.xml", strlen(filename)))
    {
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"numMach"))
        {
            byNummch = atoi((char*)ptr);
        }
    }

    if(!memcmppgm2ram(filename, "dir.cgi", strlen(filename)))
    {
        if(ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"direction"))
        {
            if((byDir = atoi((char*)ptr)) > 0)
            {
                wE2OperationPosBack += (sizeof(UOPERATION) * (HistoSheetSize * 2));
                if((wE2OperationPosBack > wE2OperationPos) || (wE2OperationPosBack < ADDRESS_HISTO))
                {
                    wE2OperationPosBack = wE2OperationPos;
                }
            }
        }
    }
    return HTTP_IO_DONE;
}
/****************************************************************************
Section:
POST Form Handlers
 ***************************************************************************/
#if defined(HTTP_USE_POST)

/*****************************************************************************
Function:
HTTP_IO_RESULT HTTPExecutePost(void)

Internal:
See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{
    // Resolve which function to use and pass along
    BYTE filename[20];

    // Load the file name
    // Make sure BYTE filename[] aisve is large enough for your longest name
    MPFSGetFilename(curHTTP.file, filename, sizeof(filename));

#if defined(USE_LCD)
    if(!memcmppgm2ram(filename, "forms.htm", 9))
        return HTTPPostLCD();
#endif

#if defined(STACK_USE_HTTP_MD5_DEMO)
    if(!memcmppgm2ram(filename, "upload.htm", 10))
        return HTTPPostMD5();
#endif
#if defined(STACK_USE_AUTOUPDATE_HTTPSERVER) && defined(WF_CS_TRIS) && defined(MRF24WG)
    if(!memcmppgm2ram(filename, "upload_Image.htm", 16))
        return HTTPPostImage();
#endif

#if defined(STACK_USE_HTTP_APP_RECONFIG)
    if(!memcmppgm2ram(filename, "protect/config.htm", 18))
        return HTTPPostConfig();
#if defined(STACK_USE_SNMP_SERVER)
    else if(!memcmppgm2ram(filename, "snmp/snmpconfig.htm", 19))
        return HTTPPostSNMPCommunity();
#endif
#endif

#if defined(STACK_USE_SMTP_CLIENT)
    if(!strcmppgm2ram((char*)filename, "email/index.htm"))
        return HTTPPostEmail();
#endif

#if defined(STACK_USE_DYNAMICDNS_CLIENT)

    if(!strcmppgm2ram((char*)filename, "dyndns/index.htm"))
    {
        return HTTPPostDDNSConfig();
    }
    if(!memcmppgm2ram(filename, "nummachine.cgi", 14))
    {
        Nop();
    }
#endif

    return HTTP_IO_DONE;
}

/*****************************************************************************
Function:
static HTTP_IO_RESULT HTTPPostLCD(void)

Summary:
Processes the LCD form on forms.htm

Description:
Locates the 'lcd' parameter and uses it to update the text displayed
on the isard's LCD display.

This function has four states.  The first reads a name from the data
string returned as part of the POST request.  If a name cannot
be found, it returns, asking for more data.  Otherwise, if the name
is expected, it reads the associated value and writes it to the LCD.
If the name is not expected, the value is discarded and the next name
parameter is read.

In the case where the expected string is never found, this function
will eventually return HTTP_IO_NEED_DATA when no data is left.  In that
case, the HTTP2 server will automatically trap the error and issue an
Internal Server Error to the browser.

Precondition:
None

Parameters:
None

Return Values:
HTTP_IO_DONE - the parameter has been found and saved
HTTP_IO_WAITING - the function is pausing to continue later
HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
 ***************************************************************************/
#if defined(USE_LCD)

static HTTP_IO_RESULT HTTPPostLCD(void)
{
    BYTE* cDest;

#define SM_POST_LCD_READ_NAME		(0u)
#define SM_POST_LCD_READ_VALUE		(1u)

    switch(curHTTP.smPost)
    {
            // Find the name
        case SM_POST_LCD_READ_NAME:

            // Read a name
            if(HTTPReadPostName(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            curHTTP.smPost = SM_POST_LCD_READ_VALUE;
            // No break...continue reading value

            // Found the value, so store the LCD and return
        case SM_POST_LCD_READ_VALUE:

            // If value is expected, read it to data buffer,
            // otherwise ignore it (by reading to NULL)
            if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"lcd"))
                cDest = curHTTP.data;
            else
                cDest = NULL;

            // Read a value string
            if(HTTPReadPostValue(cDest, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // If this was an unexpected value, look for a new name
            if(!cDest)
            {
                curHTTP.smPost = SM_POST_LCD_READ_NAME;
                break;
            }

            // Copy up to 32 characters to the LCD
            if(strlen((char*)cDest) < 32u)
            {
                memset(LCDText, ' ', 32);
                strcpy((char*)LCDText, (char*)cDest);
            }
            else
            {

                memcpy(LCDText, (void *)cDest, 32);
            }
            LCDUpdate();

            // This is the only expected value, so callback is done
            strcpypgm2ram((char*)curHTTP.data, "/forms.htm");
            curHTTP.httpStatus = HTTP_REDIRECT;
            return HTTP_IO_DONE;
    }

    // Default assumes that we're returning for state machine convenience.
    // Function will be called again later.
    return HTTP_IO_WAITING;
}
#endif

/*****************************************************************************
Function:
static HTTP_IO_RESULT HTTPPostConfig(void)

Summary:
Processes the configuration form on config/index.htm

Description:
Accepts configuration parameters from the form, saves them to a
temporary location in RAM, then eventually saves the data to EEPROM or
external Flash.

When complete, this function redirects to config/reisot.htm, which will
display information on reconnecting to the isard.

This function creates a shadow copy of the AppConfig structure in
RAM and then overwrites incoming data there as it arrives.  For each
name/value pair, the name is first read to curHTTP.data[0:5].  Next, the
value is read to newAppConfig.  Once all data has been read, the new
AppConfig is saved back to EEPROM and the browser is redirected to
reisot.htm.  That file includes an AJAX call to reisot.cgi, which
performs the actual reisot of the machine.

If an IP address cannot be parsed, too much data is POSTed, or any other
parsing error occurs, the browser reloads config.htm and displays an error
message at the top.

Precondition:
None

Parameters:
None

Return Values:
HTTP_IO_DONE - all parameters have been processed
HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
 ***************************************************************************/
#if defined(STACK_USE_HTTP_APP_RECONFIG)

static HTTP_IO_RESULT HTTPPostConfig(void)
{
    APP_CONFIG newAppConfig;
    BYTE *ptr;
    BYTE i;

    // Check to see if the browser is attempting to submit more data than we
    // can parse at once.  This function needs to receive all updated
    // parameters and validate them all before committing them to memory so that
    // orphaned configuration parameters do not get written (for example, if a
    // static IP address is given, but the subnet mask fails parsing, we
    // should not use the static IP address).  Everything needs to be processed
    // in a single transaction.  If this is impossible, fail and notify the user.
    // As a web devloper, if you add parameters to AppConfig and run into this
    // problem, you could fix this by to splitting your update web page into two
    // seperate web pages (causing two transactional writes).  Alternatively,
    // you could fix it by storing a static shadow copy of AppConfig someplace
    // in memory and using it instead of newAppConfig.  Lastly, you could
    // increase the TCP RX FIFO size for the HTTP server.  This will allow more
    // data to be POSTed by the web browser before hitting this limit.
    if(curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP))
        goto ConfigFailure;

    // Ensure that all data is waiting to be parsed.  If not, keep waiting for
    // all of it to arrive.
    if(TCPIsGetReady(sktHTTP) < curHTTP.byteCount)
        return HTTP_IO_NEED_DATA;


    // Use current config in non-volatile memory as defaults
#if defined(EEPROM_CS_TRIS)
    XEEReadArray(sizeof(NVM_VALIDATION_STRUCT), (BYTE*) & newAppConfig, sizeof(newAppConfig));
#elif defined(SPIFLASH_CS_TRIS)
    SPIFlashReadArray(sizeof(NVM_VALIDATION_STRUCT), (BYTE*) & newAppConfig, sizeof(newAppConfig));
#endif

    // Start out assuming that DHCP is disabled.  This is necessary since the
    // browser doesn't submit this field if it is unchecked (meaning zero).
    // However, if it is checked, this will be overridden since it will be
    // submitted.
    newAppConfig.Flags.bIsDHCPEnabled = 0;


    // Read all browser POST data
    while(curHTTP.byteCount)
    {
        // Read a form field name
        if(HTTPReadPostName(curHTTP.data, 6) != HTTP_READ_OK)
            goto ConfigFailure;

        // Read a form field value
        if(HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data) - 6 - 2) != HTTP_READ_OK)
            goto ConfigFailure;

        // Parse the value that was read
        if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"ip"))
        {// Read new static IP Address
            if(!StringToIPAddress(curHTTP.data + 6, &newAppConfig.MyIPAddr))
                goto ConfigFailure;

            newAppConfig.DefaultIPAddr.Val = newAppConfig.MyIPAddr.Val;
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"gw"))
        {// Read new gateway address
            if(!StringToIPAddress(curHTTP.data + 6, &newAppConfig.MyGateway))
                goto ConfigFailure;
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"sub"))
        {// Read new static subnet
            if(!StringToIPAddress(curHTTP.data + 6, &newAppConfig.MyMask))
                goto ConfigFailure;

            newAppConfig.DefaultMask.Val = newAppConfig.MyMask.Val;
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dns1"))
        {// Read new primary DNS server
            if(!StringToIPAddress(curHTTP.data + 6, &newAppConfig.PrimaryDNSServer))
                goto ConfigFailure;
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dns2"))
        {// Read new secondary DNS server
            if(!StringToIPAddress(curHTTP.data + 6, &newAppConfig.SecondaryDNSServer))
                goto ConfigFailure;
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"mac"))
        {
            // Read new MAC address
            WORD w;
            BYTE i;

            ptr = curHTTP.data + 6;

            for(i = 0; i < 12u; i++)
            {// Read the MAC address

                // Skip non-hex bytes
                while(*ptr != 0x00u && !(*ptr >= '0' && *ptr <= '9') && !(*ptr >= 'A' && *ptr <= 'F') && !(*ptr >= 'a' && *ptr <= 'f'))
                    ptr++;

                // MAC string is over, so zeroize the rest
                if(*ptr == 0x00u)
                {
                    for(; i < 12u; i++)
                        curHTTP.data[i] = '0';
                    break;
                }

                // Save the MAC byte
                curHTTP.data[i] = *ptr++;
            }

            // Read MAC Address, one byte at a time
            for(i = 0; i < 6u; i++)
            {
                ((BYTE*) & w)[1] = curHTTP.data[i * 2];
                ((BYTE*) & w)[0] = curHTTP.data[i * 2 + 1];
                newAppConfig.MyMACAddr.v[i] = hexatob(*((WORD_VAL*) & w));
            }
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"host"))
        {// Read new hostname
            FormatNetBIOSName(&curHTTP.data[6]);
            memcpy((void*)newAppConfig.NetBIOSName, (void*)curHTTP.data + 6, 16);
        }
        else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dhcp"))
        {// Read new DHCP Enabled flag
            if(curHTTP.data[6] == '1')
                newAppConfig.Flags.bIsDHCPEnabled = 1;
        }
    }


    // All parsing complete!  Save new settings and force a reisot
    SaveAppConfig(&newAppConfig);

    // Set the isard to reisot and display reconnecting information
    strcpypgm2ram((char*)curHTTP.data, "/protect/reisot.htm?");
    memcpy((void*)(curHTTP.data + 20), (void*)newAppConfig.NetBIOSName, 16);
    curHTTP.data[20 + 16] = 0x00; // Force null termination
    for(i = 20; i < 20u + 16u; i++)
    {

        if(curHTTP.data[i] == ' ')
            curHTTP.data[i] = 0x00;
    }
    curHTTP.httpStatus = HTTP_REDIRECT;

    return HTTP_IO_DONE;


ConfigFailure:
    lastFailure = TRUE;
    strcpypgm2ram((char*)curHTTP.data, "/protect/config.htm");
    curHTTP.httpStatus = HTTP_REDIRECT;

    return HTTP_IO_DONE;
}

#if defined(STACK_USE_SNMP_SERVER)

static HTTP_IO_RESULT HTTPPostSNMPCommunity(void)
{
    BYTE vCommunityIndex;
    BYTE *dest;

#define SM_CFG_SNMP_READ_NAME	(0u)
#define SM_CFG_SNMP_READ_VALUE	(1u)

    switch(curHTTP.smPost)
    {
        case SM_CFG_SNMP_READ_NAME:
            // If all parameters have been read, end
            if(curHTTP.byteCount == 0u)
            {
                SaveAppConfig(&AppConfig);
                return HTTP_IO_DONE;
            }

            // Read a name
            if(HTTPReadPostName(curHTTP.data, sizeof(curHTTP.data) - 2) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move to reading a value, but no break
            curHTTP.smPost = SM_CFG_SNMP_READ_VALUE;

        case SM_CFG_SNMP_READ_VALUE:
            // Read a value
            if(HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data) - 6 - 2) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Default action after this is to read the next name, unless there's an error
            curHTTP.smPost = SM_CFG_SNMP_READ_NAME;

            // See if this is a known parameter and legal (must be null
            // terminator in 4th field name byte, string must no greater than
            // SNMP_COMMUNITY_MAX_LEN bytes long, and SNMP_MAX_COMMUNITY_SUPPORT
            // must not be violated.
            vCommunityIndex = curHTTP.data[3] - '0';
            if(vCommunityIndex >= SNMP_MAX_COMMUNITY_SUPPORT)
                break;
            if(curHTTP.data[4] != 0x00u)
                break;
            if(memcmppgm2ram((void*)curHTTP.data, (ROM void*)"rcm", 3) == 0)
                dest = AppConfig.readCommunity[vCommunityIndex];
            else if(memcmppgm2ram((void*)curHTTP.data, (ROM void*)"wcm", 3) == 0)
                dest = AppConfig.writeCommunity[vCommunityIndex];
            else
                break;

            if(strlen((char*)curHTTP.data + 6) > SNMP_COMMUNITY_MAX_LEN)
                break;

            // String seems valid, lets copy it to AppConfig
            strcpy((char*)dest, (char*)curHTTP.data + 6);
            break;
    }

    return HTTP_IO_WAITING; // Assume we're waiting to process more data
}
#endif //#if defined(STACK_USE_SNMP_SERVER)

#endif	// #if defined(STACK_USE_HTTP_APP_RECONFIG)

/*****************************************************************************
Function:
static HTTP_IO_RESULT HTTPPostImage(void)

Summary:
Processes the file upload form on upload_Image.htm

Description:
This function demonstrates the processing of file uploads.  First, the
function locates the file data, skipping over any headers that arrive.
Second, it reads the file 64 bytes at a time and hashes that data.  Once
all data has been received, the function calculates the MD5 sum and
stores it in curHTTP.data.

After the headers, the first line from the form will be the MIME
separator.  Following that is more headers aisut the file, which we
discard.  After another CRLFCRLF, the file data begins, and we read
it 16 bytes at a time and add that to the update.  The reading
terminates when the separator string is encountered again on its own
line.  Notice that the actual file data is trashed in this process,
allowing us to accept files of arbitrary size, not limited by RAM.
Also notice that the data buffer is used as an arbitrary storage array
for the result.  The ~uploadeImage~ callback reads this data later to
send back to the client.

Precondition:
None

Parameters:
None

Return Values:
HTTP_IO_DONE - all parameters have been processed
HTTP_IO_WAITING - the function is pausing to continue later
HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
 ***************************************************************************/

#if defined(STACK_USE_AUTOUPDATE_HTTPSERVER) && defined(WF_CS_TRIS) && defined(MRF24WG)

UINT32 ImageUpdate_Addr = 0;
UINT8 Flag_ImageUpdate_running = 0;
UINT32 ImageUpdate_Checksum = 0;
UINT32 ImageUpdate_Size = 0;

static HTTP_IO_RESULT HTTPPostImage(void)
{
    WORD lenA, lenB;
    UINT8 buf_im[32] = {0};

#define SM_IMAGE_READ_SEPARATOR	(0u)
#define SM_IMAGE_SKIP_TO_DATA	(1u)
#define SM_IMAGE_READ_DATA		(2u)
#define SM_IMAGE_POST_COMPLETE	(3u)

    // Don't care aisut curHTTP.data at this point, so use that for buffer
    switch(curHTTP.smPost)
    {
            // Just started, so try to find the separator string
        case SM_IMAGE_READ_SEPARATOR:

            // See if a CRLF is in the buffer
            lenA = TCPFindROMArray(sktHTTP, (ROM BYTE*)"\r\n", 2, 0, FALSE);
            if(lenA == 0xffff)
            {//if not, ask for more data
                return HTTP_IO_NEED_DATA;
            }

            // If so, figure out where the last byte of data is
            // Data ends at CRLFseparator--CRLF, so 6+len bytes
            curHTTP.byteCount -= lenA + 6;

            // Read past the CRLF
            curHTTP.byteCount -= TCPGetArray(sktHTTP, NULL, lenA + 2);

            // Save the next state (skip to CRLFCRLF)
            curHTTP.smPost = SM_IMAGE_SKIP_TO_DATA;

            // No break...continue reading the headers if possible
#if defined(MRF24WG) // Intialize AutoUpdate
        {
            UINT8 buf_command[4];
            Flag_ImageUpdate_running = 1;
            ImageUpdate_Addr = 12;
            ImageUpdate_Checksum = 0;
            ImageUpdate_Size = 0;
            putrsUART("Update Image Begin..\r\n");

            buf_command[1] = UPDATE_SERITY_KEY_1;
            buf_command[2] = UPDATE_SERITY_KEY_2;
            buf_command[3] = UPDATE_SERITY_KEY_3;

            buf_command[0] = UPDATE_CMD_ERASE1; //Erase bank1
            SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
            DelayMs(000);
            buf_command[0] = UPDATE_CMD_CPY_0TO1; //Copy bank0 to bank1
            buf_command[1] = UPDATE_SERITY_KEY_1;
            buf_command[2] = UPDATE_SERITY_KEY_2;
            buf_command[3] = UPDATE_SERITY_KEY_3;
            SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
            DelayMs(000);
            buf_command[0] = UPDATE_CMD_ERASE0; //Erase bank0
            buf_command[1] = UPDATE_SERITY_KEY_1;
            buf_command[2] = UPDATE_SERITY_KEY_2;
            buf_command[3] = UPDATE_SERITY_KEY_3;
            SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
            DelayMs(000);
        }
#endif
            // Skip the headers
        case SM_IMAGE_SKIP_TO_DATA:
            // Look for the CRLFCRLF
            lenA = TCPFindROMArray(sktHTTP, (ROM BYTE*)"\r\n\r\n", 4, 0, FALSE);

            if(lenA != 0xffff)
            {// Found it, so remove all data up to and including
                lenA = TCPGetArray(sktHTTP, NULL, lenA + 4);
                curHTTP.byteCount -= lenA;
                curHTTP.smPost = SM_IMAGE_READ_DATA;
            }
            else
            {// Otherwise, remove as much as possible
                lenA = TCPGetArray(sktHTTP, NULL, TCPIsGetReady(sktHTTP) - 4);
                curHTTP.byteCount -= lenA;

                // Return the need more data flag
                return HTTP_IO_NEED_DATA;
            }

            // No break if we found the header terminator

            // Read and hash file data
        case SM_IMAGE_READ_DATA:
            // Find out how many bytes are available to be read
            lenA = TCPIsGetReady(sktHTTP);
            if(lenA > curHTTP.byteCount)
                lenA = curHTTP.byteCount;
            while(lenA > 0u)
            {// Add up to 64 bytes at a time to the sum
                lenB = TCPGetArray(sktHTTP, curHTTP.data, (lenA < 64u) ? lenA : 64);
                curHTTP.byteCount -= lenB;
                lenA -= lenB;
#if defined(MRF24WG)        //AutoUpdate, Write data into Module
                {

                    int i;
                    UINT8 buf[68] = {0};
                    //Odd or Even
                    static BOOL Odd_or_Even = FALSE;
                    static UINT8 Save_Odd = 0;
                    if(ImageUpdate_Size == 0)
                    {
                        Odd_or_Even = FALSE;
                        Save_Odd = 0;
                    } //First byte

                    { //Size and CheckSum

                        for(i = 0; i < lenB; i++)
                        {
                            if((ImageUpdate_Size % 4) == 0) ImageUpdate_Checksum += (UINT32)curHTTP.data[i] << 24;
                            if((ImageUpdate_Size % 4) == 1) ImageUpdate_Checksum += (UINT32)curHTTP.data[i] << 16;
                            if((ImageUpdate_Size % 4) == 2) ImageUpdate_Checksum += (UINT32)curHTTP.data[i] << 8;
                            if((ImageUpdate_Size % 4) == 3) ImageUpdate_Checksum += (UINT32)curHTTP.data[i];

                            ImageUpdate_Size++;
                        }


                        if(TRUE == Odd_or_Even) //Last it is Odd
                        {
                            buf[4] = Save_Odd;
                            for(i = 0; i < lenB; i++) buf[5 + i] = curHTTP.data[i];
                            lenB++;
                        }
                        else
                        {
                            for(i = 0; i < lenB; i++) buf[4 + i] = curHTTP.data[i];
                        }

                        if((lenB % 2) == 1) //Odd now?
                        {
                            Odd_or_Even = TRUE;
                            Save_Odd = buf[4 + lenB - 1];
                            lenB--;
                        }
                        else
                        {
                            Odd_or_Even = FALSE;
                        }
                    }
                    if(lenB > 32)
                    {
                        buf[0] = (ImageUpdate_Addr & 0x00FF0000) >> 16;
                        buf[1] = (ImageUpdate_Addr & 0x0000FF00) >> 8;
                        buf[2] = (ImageUpdate_Addr & 0xFF);
                        buf[3] = 32;
                        SendSetParamMsg(PARAM_FLASH_WRITE, buf, 32 + 4);
                        ImageUpdate_Addr += 32;
                        DelayMs(1);

                        lenB -= 32;
                        buf[0 + 32] = (ImageUpdate_Addr & 0x00FF0000) >> 16;
                        buf[1 + 32] = (ImageUpdate_Addr & 0x0000FF00) >> 8;
                        buf[2 + 32] = (ImageUpdate_Addr & 0xFF);
                        buf[3 + 32] = lenB;
                        SendSetParamMsg(PARAM_FLASH_WRITE, buf + 32, lenB + 4);
                        ImageUpdate_Addr += lenB;
                        DelayMs(1);
                    }
                    else
                    {
                        buf[0] = (ImageUpdate_Addr & 0x00FF0000) >> 16;
                        buf[1] = (ImageUpdate_Addr & 0x0000FF00) >> 8;
                        buf[2] = (ImageUpdate_Addr & 0xFF);
                        buf[3] = lenB;
                        SendSetParamMsg(PARAM_FLASH_WRITE, buf, lenB + 4);
                        ImageUpdate_Addr += lenB;
                        DelayMs(1);
                    }

                }
#endif
            }

            // If we've read all the data
            if(curHTTP.byteCount == 0u)
            {// Calculate and copy result to curHTTP.data for printout
                curHTTP.smPost = SM_IMAGE_POST_COMPLETE;
#if defined(MRF24WG)   		//AutoUpdate , complete update
                {
#define PATCH_SIGNATURE              (UINT32)(~(0x00047fbc))

                    UINT8 SignatureData[4 + 12];
                    UINT8 buf_command[4] = {UPDATE_CMD_CPY_CALIBRATION, (UINT8)(UPDATE_SERITY_KEY >> 16), (UINT8)(UPDATE_SERITY_KEY >> 8), (UINT8)UPDATE_SERITY_KEY}; //Copy last 128 Bytes from Bank0 to Bank1
                    ImageUpdate_Addr = 0;
                    SignatureData[0] = (ImageUpdate_Addr & 0x00FF0000) >> 16;
                    SignatureData[1] = (ImageUpdate_Addr & 0x0000FF00) >> 8;
                    SignatureData[2] = (ImageUpdate_Addr & 0xFF);
                    SignatureData[3] = 12;

                    SignatureData[4 + 0] = (PATCH_SIGNATURE >> 24)&0xFF;
                    SignatureData[4 + 1] = (PATCH_SIGNATURE >> 16)&0xFF;
                    SignatureData[4 + 2] = (PATCH_SIGNATURE >> 8)&0xFF;
                    SignatureData[4 + 3] = (PATCH_SIGNATURE)&0xFF;

                    SignatureData[4 + 4] = (ImageUpdate_Size >> 24)&0xFF;
                    SignatureData[4 + 5] = (ImageUpdate_Size >> 16)&0xFF;
                    SignatureData[4 + 6] = (ImageUpdate_Size >> 8)&0xFF;
                    SignatureData[4 + 7] = (ImageUpdate_Size)&0xFF;

                    SignatureData[4 + 8] = (ImageUpdate_Checksum >> 24)&0xFF;
                    SignatureData[4 + 9] = (ImageUpdate_Checksum >> 16)&0xFF;
                    SignatureData[4 + 10] = (ImageUpdate_Checksum >> 8)&0xFF;
                    SignatureData[4 + 11] = (ImageUpdate_Checksum)&0xFF;
                    SendSetParamMsg(PARAM_FLASH_WRITE, SignatureData, sizeof(SignatureData));


                    sprintf((char *)buf_im, "Size=%x, sum=%x\r\n", (unsigned int)ImageUpdate_Size, (unsigned int)ImageUpdate_Checksum);
                    putsUART((char *)buf_im);

                    SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
                    Flag_ImageUpdate_running = 0;
                    putrsUART("Update Image Done!\r\n");
                }
#endif

                return HTTP_IO_DONE;
            }

            // Ask for more data
            return HTTP_IO_NEED_DATA;
    }

    return HTTP_IO_DONE;
}
#endif
/*****************************************************************************
  Function:
                                static HTTP_IO_RESULT HTTPPostMD5(void)

  Summary:
                                Processes the file upload form on upload.htm

  Description:
                                This function demonstrates the processing of file uploads.  First, the
                                function locates the file data, skipping over any headers that arrive.
                                Second, it reads the file 64 bytes at a time and hashes that data.  Once
                                all data has been received, the function calculates the MD5 sum and
                                stores it in curHTTP.data.

                                After the headers, the first line from the form will be the MIME
                                separator.  Following that is more headers aisut the file, which we
                                discard.  After another CRLFCRLF, the file data begins, and we read
                                it 16 bytes at a time and add that to the MD5 calculation.  The reading
                                terminates when the separator string is encountered again on its own
                                line.  Notice that the actual file data is trashed in this process,
                                allowing us to accept files of arbitrary size, not limited by RAM.
                                Also notice that the data buffer is used as an arbitrary storage array
                                for the result.  The ~uploadedmd5~ callback reads this data later to
                                send back to the client.

  Precondition:
                                None

  Parameters:
                                None

  Return Values:
                                HTTP_IO_DONE - all parameters have been processed
                                HTTP_IO_WAITING - the function is pausing to continue later
                                HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
 ***************************************************************************/

#if defined(STACK_USE_HTTP_MD5_DEMO)

static HTTP_IO_RESULT HTTPPostMD5(void)
{
    WORD lenA, lenB;
    static HASH_SUM md5; // Assume only one simultaneous MD5

#define SM_MD5_READ_SEPARATOR	(0u)
#define SM_MD5_SKIP_TO_DATA		(1u)
#define SM_MD5_READ_DATA		(2u)
#define SM_MD5_POST_COMPLETE	(3u)

    // Don't care aisut curHTTP.data at this point, so use that for buffer
    switch(curHTTP.smPost)
    {
            // Just started, so try to find the separator string
        case SM_MD5_READ_SEPARATOR:
            // Reset the MD5 calculation
            MD5Initialize(&md5);

            // See if a CRLF is in the buffer
            lenA = TCPFindROMArray(sktHTTP, (ROM BYTE*)"\r\n", 2, 0, FALSE);
            if(lenA == 0xffff)
            {//if not, ask for more data
                return HTTP_IO_NEED_DATA;
            }

            // If so, figure out where the last byte of data is
            // Data ends at CRLFseparator--CRLF, so 6+len bytes
            curHTTP.byteCount -= lenA + 6;

            // Read past the CRLF
            curHTTP.byteCount -= TCPGetArray(sktHTTP, NULL, lenA + 2);

            // Save the next state (skip to CRLFCRLF)
            curHTTP.smPost = SM_MD5_SKIP_TO_DATA;

            // No break...continue reading the headers if possible

            // Skip the headers
        case SM_MD5_SKIP_TO_DATA:
            // Look for the CRLFCRLF
            lenA = TCPFindROMArray(sktHTTP, (ROM BYTE*)"\r\n\r\n", 4, 0, FALSE);

            if(lenA != 0xffff)
            {// Found it, so remove all data up to and including
                lenA = TCPGetArray(sktHTTP, NULL, lenA + 4);
                curHTTP.byteCount -= lenA;
                curHTTP.smPost = SM_MD5_READ_DATA;
            }
            else
            {// Otherwise, remove as much as possible
                lenA = TCPGetArray(sktHTTP, NULL, TCPIsGetReady(sktHTTP) - 4);
                curHTTP.byteCount -= lenA;

                // Return the need more data flag
                return HTTP_IO_NEED_DATA;
            }

            // No break if we found the header terminator

            // Read and hash file data
        case SM_MD5_READ_DATA:
            // Find out how many bytes are available to be read
            lenA = TCPIsGetReady(sktHTTP);
            if(lenA > curHTTP.byteCount)
                lenA = curHTTP.byteCount;

            while(lenA > 0u)
            {// Add up to 64 bytes at a time to the sum
                lenB = TCPGetArray(sktHTTP, curHTTP.data, (lenA < 64u) ? lenA : 64);
                curHTTP.byteCount -= lenB;
                lenA -= lenB;
                MD5AddData(&md5, curHTTP.data, lenB);
            }

            // If we've read all the data
            if(curHTTP.byteCount == 0u)
            {// Calculate and copy result to curHTTP.data for printout

                curHTTP.smPost = SM_MD5_POST_COMPLETE;
                MD5Calculate(&md5, curHTTP.data);
                return HTTP_IO_DONE;
            }

            // Ask for more data
            return HTTP_IO_NEED_DATA;
    }

    return HTTP_IO_DONE;
}
#endif // #if defined(STACK_USE_HTTP_MD5_DEMO)

/*****************************************************************************
Function:
static HTTP_IO_RESULT HTTPPostEmail(void)

Summary:
Processes the e-mail form on email/index.htm

Description:
This function sends an e-mail message using the SMTP client and
optionally encrypts the connection to the SMTP server using SSL.  It
demonstrates the use of the SMTP client, waiting for asynchronous
processes in an HTTP callback, and how to send e-mail attachments using
the stack.

Messages with attachments are sent using multipart/mixed MIME encoding,
which has three sections.  The first has no headers, and is only to be
displayed by old clients that cannot interpret the MIME format.  (The
overwhelming majority of these clients have been obseleted, but the
so-called "ignored" section is still used.)  The second has a few
headers to indicate that it is the main isdy of the message in plain-
text encoding.  The third section has headers indicating an attached
file, along with its name and type.  All sections are separated by a
isundary string, which cannot appear anywhere else in the message.

Precondition:
None

Parameters:
None

Return Values:
HTTP_IO_DONE - the message has been sent
HTTP_IO_WAITING - the function is waiting for the SMTP process to complete
HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
 ***************************************************************************/
#if defined(STACK_USE_SMTP_CLIENT)

static HTTP_IO_RESULT HTTPPostEmail(void)
{
    static BYTE *ptrData;
    static BYTE *szPort;
#if defined(STACK_USE_SSL_CLIENT)
    static BYTE *szUseSSL;
#endif
    WORD len, rem;
    BYTE cName[8];

#define SM_EMAIL_CLAIM_MODULE				(0u)
#define SM_EMAIL_READ_PARAM_NAME			(1u)
#define SM_EMAIL_READ_PARAM_VALUE			(2u)
#define SM_EMAIL_PUT_IGNORED				(3u)
#define SM_EMAIL_PUT_BODY					(4u)
#define SM_EMAIL_PUT_ATTACHMENT_HEADER		(5u)
#define SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS	(6u)
#define SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS	(7u)
#define SM_EMAIL_PUT_ATTACHMENT_DATA_POT	(8u)
#define SM_EMAIL_PUT_TERMINATOR				(9u)
#define SM_EMAIL_FINISHING					(10u)

#define EMAIL_SPACE_REMAINING				(HTTP_MAX_DATA_LEN - (ptrData - curHTTP.data))

    switch(curHTTP.smPost)
    {
        case SM_EMAIL_CLAIM_MODULE:
            // Try to claim module
            if(SMTPBeginUsage())
            {// Module was claimed, so set up static parameters
                SMTPClient.Subject.szROM = (ROM BYTE*)"Microchip TCP/IP Stack Status Update";
                SMTPClient.ROMPointers.Subject = 1;
                SMTPClient.From.szROM = (ROM BYTE*)"\"SMTP Service\" <mchpisard@picsaregood.com>";
                SMTPClient.ROMPointers.From = 1;

                // The following two lines indicate to the receiving client that
                // this message has an attachment.  The isundary field *must not*
                // be included anywhere in the content of the message.  In real
                // applications it is typically a long random string.
                SMTPClient.OtherHeaders.szROM = (ROM BYTE*)"MIME-version: 1.0\r\nContent-type: multipart/mixed; isundary=\"frontier\"\r\n";
                SMTPClient.ROMPointers.OtherHeaders = 1;

                // Move our state machine forward
                ptrData = curHTTP.data;
                szPort = NULL;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_NAME;
            }
            return HTTP_IO_WAITING;

        case SM_EMAIL_READ_PARAM_NAME:
            // Search for a parameter name in POST data
            if(HTTPReadPostName(cName, sizeof(cName)) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Try to match the name value
            if(!strcmppgm2ram((char*)cName, (ROM char*)"server"))
            {// Read the server name
                SMTPClient.Server.szRAM = ptrData;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }
            else if(!strcmppgm2ram((char*)cName, (ROM char*)"port"))
            {// Read the server port
                szPort = ptrData;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }
#if defined(STACK_USE_SSL_CLIENT)
            else if(!strcmppgm2ram((char*)cName, (ROM char*)"ssl"))
            {// Read the server port
                szUseSSL = ptrData;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }
#endif
            else if(!strcmppgm2ram((char*)cName, (ROM char*)"user"))
            {// Read the user name
                SMTPClient.Username.szRAM = ptrData;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }
            else if(!strcmppgm2ram((char*)cName, (ROM char*)"pass"))
            {// Read the password
                SMTPClient.Password.szRAM = ptrData;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }
            else if(!strcmppgm2ram((char*)cName, (ROM char*)"to"))
            {// Read the To string
                SMTPClient.To.szRAM = ptrData;
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }
            else if(!strcmppgm2ram((char*)cName, (ROM char*)"msg"))
            {// Done with headers, move on to the message
                // Delete paramters that are just null strings (no data from user) or illegal (ex: password without username)
                if(SMTPClient.Server.szRAM)
                    if(*SMTPClient.Server.szRAM == 0x00u)
                        SMTPClient.Server.szRAM = NULL;
                if(SMTPClient.Username.szRAM)
                    if(*SMTPClient.Username.szRAM == 0x00u)
                        SMTPClient.Username.szRAM = NULL;
                if(SMTPClient.Password.szRAM)
                    if((*SMTPClient.Password.szRAM == 0x00u) || (SMTPClient.Username.szRAM == NULL))
                        SMTPClient.Password.szRAM = NULL;

                // Decode server port string if it exists
                if(szPort)
                    if(*szPort)
                        SMTPClient.ServerPort = (WORD)atol((char*)szPort);

                // Determine if SSL should be used
#if defined(STACK_USE_SSL_CLIENT)
                if(szUseSSL)
                    if(*szUseSSL == '1')
                        SMTPClient.UseSSL = TRUE;
#endif

                // Start sending the message
                SMTPSendMail();
                curHTTP.smPost = SM_EMAIL_PUT_IGNORED;
                return HTTP_IO_WAITING;
            }
            else
            {// Don't know what we're receiving
                curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
            }

            // No break...continue to try reading the value

        case SM_EMAIL_READ_PARAM_VALUE:
            // Search for a parameter value in POST data
            if(HTTPReadPostValue(ptrData, EMAIL_SPACE_REMAINING) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move past the data that was just read
            ptrData += strlen((char*)ptrData);
            if(ptrData < curHTTP.data + HTTP_MAX_DATA_LEN - 1)
                ptrData += 1;

            // Try reading the next parameter
            curHTTP.smPost = SM_EMAIL_READ_PARAM_NAME;
            return HTTP_IO_WAITING;

        case SM_EMAIL_PUT_IGNORED:
            // This section puts a message that is ignored by compatible clients.
            // This text will not display unless the receiving client is obselete
            // and does not understand the MIME structure.
            // The "--frontier" indicates the start of a section, then any
            // needed MIME headers follow, then two CRLF pairs, and then
            // the actual content (which will be the isdy text in the next state).

            // Check to see if a failure occured
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(SMTPIsPutReady() < 90u)
                return HTTP_IO_WAITING;

            // Write the ignored text
            SMTPPutROMString((ROM BYTE*)"This is a multi-part message in MIME format.\r\n");
            SMTPPutROMString((ROM BYTE*)"--frontier\r\nContent-type: text/plain\r\n\r\n");
            SMTPFlush();

            // Move to the next state
            curHTTP.smPost = SM_EMAIL_PUT_BODY;

        case SM_EMAIL_PUT_BODY:
            // Write as much isdy text as is available from the TCP buffer
            // return HTTP_IO_NEED_DATA or HTTP_IO_WAITING
            // On completion, => PUT_ATTACHMENT_HEADER and continue

            // Check to see if a failure occurred
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // Loop as long as data remains to be read
            while(curHTTP.byteCount)
            {
                // See if space is available to write
                len = SMTPIsPutReady();
                if(len == 0u)
                    return HTTP_IO_WAITING;

                // See if data is ready to be read
                rem = TCPIsGetReady(sktHTTP);
                if(rem == 0u)
                    return HTTP_IO_NEED_DATA;

                // Only write as much as we can handle
                if(len > rem)
                    len = rem;
                if(len > HTTP_MAX_DATA_LEN - 2)
                    len = HTTP_MAX_DATA_LEN - 2;

                // Read the data from HTTP POST buffer and send it to SMTP
                curHTTP.byteCount -= TCPGetArray(sktHTTP, curHTTP.data, len);
                curHTTP.data[len] = '\0';
                HTTPURLDecode(curHTTP.data);
                SMTPPutString(curHTTP.data);
                SMTPFlush();
            }

            // We're done with the POST data, so continue
            curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_HEADER;

        case SM_EMAIL_PUT_ATTACHMENT_HEADER:
            // This section writes the attachment to the message.
            // This portion generally will not display in the reader, but
            // will be downloadable to the local machine.  Use caution
            // when selecting the content-type and file name, as certain
            // types and extensions are blocked by virus filters.

            // The same structure as the message isdy is used.
            // Any attachment must not include high-bit ASCII characters or
            // binary data.  If binary data is to be sent, the data should
            // be encoded using Base64 and a MIME header should be added:
            // Content-transfer-encoding: base64

            // Check to see if a failure occurred
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(SMTPIsPutReady() < 100u)
                return HTTP_IO_WAITING;

            // Write the attachment header
            SMTPPutROMString((ROM BYTE*)"\r\n--frontier\r\nContent-type: text/csv\r\nContent-Disposition: attachment; filename=\"status.csv\"\r\n\r\n");
            SMTPFlush();

            // Move to the next state
            curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS;

        case SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS:
            // The following states output the system status as a CSV file.

            // Check to see if a failure occurred
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(SMTPIsPutReady() < 36u)
                return HTTP_IO_WAITING;

            // Write the header and button strings
            SMTPPutROMString((ROM BYTE*)"SYSTEM STATUS\r\n");
            SMTPPutROMString((ROM BYTE*)"Buttons:,");
            SMTPPut(BUTTON0_IO + '0');
            SMTPPut(',');
            SMTPPut(BUTTON1_IO + '0');
            SMTPPut(',');
            SMTPPut(BUTTON2_IO + '0');
            SMTPPut(',');
            SMTPPut(BUTTON3_IO + '0');
            SMTPPut('\r');
            SMTPPut('\n');
            SMTPFlush();

            // Move to the next state
            curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS;

        case SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS:
            // Check to see if a failure occurred
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(SMTPIsPutReady() < 30u)
                return HTTP_IO_WAITING;

            // Write the header and button strings
            SMTPPutROMString((ROM BYTE*)"LEDs:,");
            SMTPPut(LED0_IO + '0');
            SMTPPut(',');
            SMTPPut(LED1_IO + '0');
            SMTPPut(',');
            SMTPPut(LED2_IO + '0');
            SMTPPut(',');
            SMTPPut(LED3_IO + '0');
            SMTPPut(',');
            SMTPPut(LED4_IO + '0');
            SMTPPut(',');
            SMTPPut(LED5_IO + '0');
            SMTPPut(',');
            SMTPPut(LED6_IO + '0');
            SMTPPut(',');
            SMTPPut(LED7_IO + '0');
            SMTPPut('\r');
            SMTPPut('\n');
            SMTPFlush();

            // Move to the next state
            curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_DATA_POT;

        case SM_EMAIL_PUT_ATTACHMENT_DATA_POT:
            // Check to see if a failure occurred
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(SMTPIsPutReady() < 16u)
                return HTTP_IO_WAITING;

            // Do the A/D conversion
#if defined(__18CXX)
            // Wait until A/D conversion is done
            ADCON0bits.GO = 1;
            while(ADCON0bits.GO);
            // Convert 10-bit value into ASCII string
            len = (WORD)ADRES;
            uitoa(len, (BYTE*) & curHTTP.data[1]);
#else
            len = (WORD)ADC1BUF0;
            uitoa(len, (BYTE*) & curHTTP.data[1]);
#endif

            // Write the header and button strings
            SMTPPutROMString((ROM BYTE*)"Pot:,");
            SMTPPutString(&curHTTP.data[1]);
            SMTPPut('\r');
            SMTPPut('\n');
            SMTPFlush();

            // Move to the next state
            curHTTP.smPost = SM_EMAIL_PUT_TERMINATOR;

        case SM_EMAIL_PUT_TERMINATOR:
            // This section finishes the message
            // This consists of two dashes, the isundary, and two more dashes
            // on a single line, followed by a CRLF pair to terminate the message.

            // Check to see if a failure occured
            if(!SMTPIsBusy())
            {
                curHTTP.smPost = SM_EMAIL_FINISHING;
                return HTTP_IO_WAITING;
            }

            // See if we're ready to write data
            if(SMTPIsPutReady() < 16u)
                return HTTP_IO_WAITING;

            // Write the ignored text
            SMTPPutROMString((ROM BYTE*)"--frontier--\r\n");
            SMTPPutDone();
            SMTPFlush();

            // Move to the next state
            curHTTP.smPost = SM_EMAIL_FINISHING;

        case SM_EMAIL_FINISHING:
            // Wait for status
            if(!SMTPIsBusy())
            {
                // Release the module and check success
                // Redirect the user based on the result
                if(SMTPEndUsage() == SMTP_SUCCESS)
                    lastSuccess = TRUE;

                else
                    lastFailure = TRUE;

                // Redirect to the page
                strcpypgm2ram((char*)curHTTP.data, "/email/index.htm");
                curHTTP.httpStatus = HTTP_REDIRECT;
                return HTTP_IO_DONE;
            }

            return HTTP_IO_WAITING;
    }

    return HTTP_IO_DONE;
}
#endif	// #if defined(STACK_USE_SMTP_CLIENT)

/****************************************************************************
Function:
HTTP_IO_RESULT HTTPPostDDNSConfig(void)

Summary:
Parsing and collecting http data received from http form.

Description:
This routine will be excuted every time the Dynamic DNS Client
configuration form is submitted.  The http data is received
as a string of the variables seperated by '&' characters in the TCP RX
buffer.  This data is parsed to read the required configuration values,
and those values are populated to the global array (DDNSData) reserved
for this purpose.  As the data is read, DDNSPointers is also populated
so that the dynamic DNS client can execute with the new parameters.

Precondition:
curHTTP is loaded.

Parameters:
None.

Return Values:
HTTP_IO_DONE 		-  Finished with procedure
HTTP_IO_NEED_DATA	-  More data needed to continue, call again later
HTTP_IO_WAITING 	-  Waiting for asynchronous process to complete,
                                                                                                                                                             call again later
 ***************************************************************************/
#if defined(STACK_USE_DYNAMICDNS_CLIENT)

static HTTP_IO_RESULT HTTPPostDDNSConfig(void)
{
    static BYTE *ptrDDNS;

#define SM_DDNS_START			(0u)
#define SM_DDNS_READ_NAME		(1u)
#define SM_DDNS_READ_VALUE		(2u)
#define SM_DDNS_READ_SERVICE	(3u)
#define SM_DDNS_DONE			(4u)

#define DDNS_SPACE_REMAINING				(sizeof(DDNSData) - (ptrDDNS - DDNSData))

    switch(curHTTP.smPost)
    {
            // Sets defaults for the system
        case SM_DDNS_START:
            ptrDDNS = DDNSData;
            DDNSSetService(0);
            DDNSClient.Host.szROM = NULL;
            DDNSClient.Username.szROM = NULL;
            DDNSClient.Password.szROM = NULL;
            DDNSClient.ROMPointers.Host = 0;
            DDNSClient.ROMPointers.Username = 0;
            DDNSClient.ROMPointers.Password = 0;
            curHTTP.smPost++;

            // Searches out names and handles them as they arrive
        case SM_DDNS_READ_NAME:
            // If all parameters have been read, end
            if(curHTTP.byteCount == 0u)
            {
                curHTTP.smPost = SM_DDNS_DONE;
                break;
            }

            // Read a name
            if(HTTPReadPostName(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"service"))
            {
                // Reading the service (numeric)
                curHTTP.smPost = SM_DDNS_READ_SERVICE;
                break;
            }
            else if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"user"))
                DDNSClient.Username.szRAM = ptrDDNS;
            else if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"pass"))
                DDNSClient.Password.szRAM = ptrDDNS;
            else if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"host"))
                DDNSClient.Host.szRAM = ptrDDNS;

            // Move to reading the value for user/pass/host
            curHTTP.smPost++;

            // Reads in values and assigns them to the DDNS RAM
        case SM_DDNS_READ_VALUE:
            // Read a name
            if(HTTPReadPostValue(ptrDDNS, DDNS_SPACE_REMAINING) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move past the data that was just read
            ptrDDNS += strlen((char*)ptrDDNS);
            if(ptrDDNS < DDNSData + sizeof(DDNSData) - 1)
                ptrDDNS += 1;

            // Return to reading names
            curHTTP.smPost = SM_DDNS_READ_NAME;
            break;

            // Reads in a service ID
        case SM_DDNS_READ_SERVICE:
            // Read the integer id

            if(HTTPReadPostValue(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Convert to a service ID
            DDNSSetService((BYTE)atol((char*)curHTTP.data));

            // Return to reading names
            curHTTP.smPost = SM_DDNS_READ_NAME;
            break;

            // Sets up the DDNS client for an update
        case SM_DDNS_DONE:
            // Since user name and password changed, force an update immediately
            DDNSForceUpdate();

            // Redirect to prevent POST errors
            lastSuccess = TRUE;
            strcpypgm2ram((char*)curHTTP.data, "/dyndns/index.htm");
            curHTTP.httpStatus = HTTP_REDIRECT;
            return HTTP_IO_DONE;
    }

    return HTTP_IO_WAITING; // Assume we're waiting to process more data
}
#endif	// #if defined(STACK_USE_DYNAMICDNS_CLIENT)

#endif //(use_post)

void HTTPPrint_mac(void)
{
    BYTE bylBuffer[16];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X%02X%02X%02X%02X%02X",
            0XFC, EMAC1SA2 / 256, EMAC1SA1 % 256, EMAC1SA1 / 256,
            EMAC1SA0 % 256, EMAC1SA0 / 256);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Val(WORD byIndex)
{
    BYTE bylBuffer[10];
    if(isFormCG)
    {
        snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos, changeGiverConfig.byCoinValue[byIndex] == 0XFF ? (double)(0) :
                (double)(changeGiverConfig.byCoinValue[byIndex] * changeGiverConfig.deviceConfig.byScaleFactor) /
                wCurrencyDivider);
    }
    else
    {
        snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos, billValidatorConfig.byBillValue[byIndex] == 0XFF ? (double)(0) :
                (double)(billValidatorConfig.byBillValue[byIndex] * billValidatorConfig.wScaleFactor) /
                wCurrencyDivider);
    }
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Lev(WORD byIndex)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", tubeStatus.byLevel[byIndex]);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_status(WORD wIndex)
{
    if(tubeStatus.byLevel[wIndex] < 5)
    {
        TCPPutROMString(sktHTTP, (ROM BYTE*)"low");
    }
    else
    {
        if(tubeStatus.byLevel[wIndex] < 10)
        {
            TCPPutROMString(sktHTTP, (ROM BYTE*)"advise");
        }
        else
        {
            TCPPutROMString(sktHTTP, (ROM BYTE*)"ok");
        }
    }
}

void HTTPPrint_intialisation(void)
{
 //   xSemaphoreTake(hSemaphoreMDB, 5000);
    DelayMs(100);
    isGetMDBTubeStatus(&tubeStatus); //Récupère le niveau des tubes.
    DelayMs(100);
//    xSemaphoreGive(hSemaphoreMDB);
}

void HTTPPrint_debut(void)
{
    wE2OperationPosBack = wE2OperationPos;
}

void HTTPPrint_Op(void)
{
    UOPERATION tmpHistoData;
    BYTE bylBuffer[32] = {0};
    //DelayMs(100);
    I2CE2promLReadBuffer(wE2OperationPosBack, &lHistoData, sizeof(UOPERATION)); //Lecture des infos à utiliser.
    //Préparation de la lecture suivante.
    wE2OperationPosBack -= sizeof(UOPERATION); //Pointe sur la position suivante à lire.
    if(wE2OperationPosBack < ADDRESS_HISTO) //Si l'adresse est passé au-dessous de l'adresse minimum
    {
        wE2OperationPosBack = (0XFFFF - sizeof(UOPERATION) + 1); //On effectue une rotation vers le haut.
    }
    I2CE2promLReadBuffer(wE2OperationPosBack, &tmpHistoData, sizeof(UOPERATION)); //Lecture de l'opération à utiliser pour vérifier la validité de l'enregistrement.
    if((BYTE)tmpHistoData.Operation == NONEOP) //S'il n'y a pas d'enregistrement à cet endroit
    {
        //on repositonne le pointeur.
        wE2OperationPosBack += sizeof(UOPERATION);
        if(wE2OperationPosBack < ADDRESS_HISTO)
        {
            wE2OperationPosBack = ADDRESS_HISTO;
        }
    }

    switch(lHistoData.Operation)
    {
        case PASSWORDENTRANCE:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Saisie password");
            break;
        }
        case INITIALISATION:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Mise en route");
            break;
        }
        case TEST_START:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Entree test");
            break;
        }
        case LANCEMENT:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Fin paiement et activation");
            break;
        }
        case INCG:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Insert. pieces");
            break;
        }
        case OUCG:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Rendu");
            break;
        }
        case INBV:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Insert. billets");
            break;
        }
        case OUTBV:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Retour billets");
            break;
        }
        case PAYCASHLESS:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Pai. cashless");
            break;
        }
        case REVALUECASHLESS:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Rech. cashless");
            break;
        }
        case KEYPRESENT:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Clef presentee");
            break;
        }
        case OVERPAYOP:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Trop percu");
            break;
        }
        case FILLINGOP:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Remplissage");
            break;
        }
        case USBKEYINSERTED:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "USB Presentee");
            break;
        }
        case USBPAY:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Paiement USB");
            break;
        }
        case USBSAVEAUDIT:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Save audit USB");
            break;
        }
        case USBREINITCODE:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "USB init code");
            break;
        }
        case RAZAUDITOP:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "RAZ audit");
            break;
        }
        case USBSAVEHISTO:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Save histo USB");
            break;
        }
        case SELECTION:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Selection");
            break;
        }
        case REFUSED:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Piece refusee");
            break;
        }
        case TEST_LEFT:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Sortie test");
            break;
        }
        case USB_LEFT:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Retrait USB");
            break;
        }
        case PULSE_END:
        {
            //Version 1.2.1
            //2015 10 10
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Fin activation");
            //snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Fin activation machine");
            //-------------
            break;
        }
        default:
        {
            snprintf(bylBuffer, sizeof(bylBuffer),  "%s", "Inconnu");
        }
    }
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Date(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X-%02X-%02X", lHistoData.date.mday, lHistoData.date.mon, lHistoData.date.year);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Machine(void)
{
    BYTE bylBuffer[3];
    lHistoData.byMachine ? snprintf(bylBuffer, sizeof(bylBuffer),  "%u", lHistoData.byMachine) : snprintf(bylBuffer, sizeof(bylBuffer),  "-");
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Heure(void)
{
    BYTE bylBuffer[9];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X:%02X:%02X", lHistoData.time.hour, lHistoData.time.min, lHistoData.time.sec);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Montant(void)
{
    BYTE bylBuffer[8];
    lHistoData.lAmount || (lHistoData.Operation == OUCG) ? snprintf(bylBuffer, sizeof(bylBuffer),  "%s%.*f",
                                                                   (lHistoData.Operation == OUCG) ? "-" : "", byDecimalPos,
                                                                   (double)lHistoData.lAmount / wCurrencyDivider) :
        snprintf(bylBuffer, sizeof(bylBuffer),  "-");
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Key(void)
{
    BYTE bylBuffer[9];
    lHistoData.lKeyNumber ? snprintf(bylBuffer, sizeof(bylBuffer),  "%u", lHistoData.lKeyNumber) : snprintf(bylBuffer, sizeof(bylBuffer),  "-");
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_total(void)
{
    DWORD dwTotalTubes = 0;
    BYTE byIndex;
    BYTE bylBuffer[8] = {0};
    for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
    {
        dwTotalTubes += (tubeStatus.byLevel[byIndex] * changeGiverConfig.byCoinValue[byIndex] *
                         changeGiverConfig.deviceConfig.byScaleFactor);
    }
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos, (double)dwTotalTubes / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_color(void)
{
    lHistoData.result ? TCPPutROMString(sktHTTP, (ROM BYTE*)"ok") : //  GREEN
        TCPPutROMString(sktHTTP, (ROM BYTE*)"low"); // otherwise RED
}

void HTTPPrint_etat(void)
{
    BYTE bylBuffer[4];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%s", lHistoData.result ? "OK" : "NOK");
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_buzzer(void)
{
    centralParameters.isBuzzer ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_escrow(void)
{
    centralParameters.isEscrow ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_appoint(void)
{
    BYTE bylBuffer[8] = {0};
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos, (double)centralParameters.wAmountExactChange / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_cumul(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", centralParameters.byCumulTO);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_clavier(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", centralParameters.byKBDTO);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_to_overpay(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", centralParameters.byOverPayTO);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_message(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", centralParameters.lDelayDisplay);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_state(WORD wIndex)
{
    wCopyEnable & (1 << wIndex) ? TCPPutROMString(sktHTTP, (ROM BYTE*)"ok") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"low");
}

void HTTPPrint_cenable(WORD wIndex)
{
    wCopyEnable & (1 << wIndex) ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_cg(void)
{
    wCopyEnable = WORD_SWAP(centralParameters.coinType.wCoinEnable);
    isFormCG = TRUE;
}

void HTTPPrint_bv(void)
{
    wCopyEnable = WORD_SWAP(centralParameters.billType.wBillEnable);
    isFormCG = FALSE;
}

void HTTPPrint_x60(void)
{
    centralParameters.byCLAddress == 0X60 ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_x10(void)
{
    centralParameters.byCLAddress == 0X10 ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_timeCentrale(void)
{
    BYTE bylBuffer[6];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02XH%02X", Now.hour, Now.min);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_machineList(void)
{
    BYTE byNumMachine;
    BYTE byShortBuffer[3] = {0};
    BYTE bylBuffer[(MAXMACHINES * sizeof(byShortBuffer)) + 10] = {0};
    for(byNumMachine = 10; byNumMachine < 100; byNumMachine++)
    {
        if(byMachineExist(byNumMachine) < MAXMACHINES)
        {
            snprintf(byShortBuffer,sizeof(byShortBuffer), "%u-", byNumMachine);
            strcat(bylBuffer, byShortBuffer);
        }
    }
    bylBuffer[strlen(bylBuffer)] = 0;
    TCPPutString(sktHTTP, bylBuffer);
    byIndexMachineHTPP = 0;
}

void HTTPPrint_BasePrice(void)
{
    BYTE bylBuffer[8] = {0};
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos,
            ((double)modules[byIndexMachineHTPP].config.wCashPrice + 0.001) / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_KeyPrice(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos,
            ((double)modules[byIndexMachineHTPP].config.wCashLessPrice + 0.001) / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_BasePriceHH(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos,
            ((double)modules[byIndexMachineHTPP].config.wCashPriceHH + 0.001) / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_KeyPriceHH(void)
{
    BYTE bylBuffer[8];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f", byDecimalPos,
            ((double)modules[byIndexMachineHTPP].config.wCashLessPriceHH + 0.001) / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Pulse(void)
{
    BYTE bylBuffer[10];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", modules[byIndexMachineHTPP].config.lPulseInMS);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_isRemaining(void)
{
    modules[byIndexMachineHTPP].config.isDisplayedTimeRemaining ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_Displayed(void)
{
    BYTE bylBuffer[10];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", modules[byIndexMachineHTPP].config.lTimeToDisplay);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_OverBusy(void)
{
    BYTE bylBuffer[10];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", modules[byIndexMachineHTPP].config.lOverBusy);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_Start(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X:%02X", modules[byIndexMachineHTPP].config.utBeginSelect.hour,
            modules[byIndexMachineHTPP].config.utBeginSelect.min);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_End(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X:%02X", modules[byIndexMachineHTPP].config.utEndSelect.hour,
            modules[byIndexMachineHTPP].config.utEndSelect.min);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_StartHH(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X:%02X", modules[byIndexMachineHTPP].config.utBeginHH.hour,
            modules[byIndexMachineHTPP].config.utBeginHH.min);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_EndHH(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%02X:%02X", modules[byIndexMachineHTPP].config.utEndHH.hour,
            modules[byIndexMachineHTPP].config.utEndHH.min);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_isCumul(void)
{
    modules[byIndexMachineHTPP].config.isCumulEnable ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_index(void)
{
    BYTE bylBuffer[2];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", byIndHisto);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_dir()
{
    BYTE bylBuffer[2];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", byDir);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_cash(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f\r\n", byDecimalPos, (double)auditData.data.dwVendCash / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_cashless(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f\r\n", byDecimalPos, (double)auditData.data.dwVendCL / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_reload(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f\r\n", byDecimalPos, (double)auditData.data.dwRevalueCL / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_refilling(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f\r\n", byDecimalPos, (double)auditData.data.dwRefilling / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_troppercu(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f\r\n", byDecimalPos, (double)auditData.data.dwOverPay / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_coinIn(WORD wIndex)
{
    BYTE bylBuffer[5];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", auditData.data.wNumberChannelCGIn[wIndex]);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_coinOut(WORD wIndex)
{
    BYTE bylBuffer[5];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", auditData.data.wNumberChannelCGOut[wIndex]);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_BillIn(WORD wIndex)
{
    BYTE bylBuffer[5];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", auditData.data.wNumberChannelBV[wIndex]);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_sellUSB(void)
{
    BYTE bylBuffer[12];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%.*f\r\n", byDecimalPos, (double)auditData.data.dwVendUSB / wCurrencyDivider);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_nummch(void)
{
    BYTE bylBuffer[5];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", byNummch);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_numact(void)
{
    BYTE bylBuffer[5];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", ((byIndHisto = byMachineExist(byNummch)) < MAXMACHINES) ? auditData.data.wNumberServices[byIndHisto] : 0);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_isPower(void)
{
    modules[byIndexMachineHTPP].config.isMachinePowered ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_isBill()
{
    modules[byIndexMachineHTPP].config.isBillAccepted ? TCPPutROMString(sktHTTP, (ROM BYTE*)"checked") :
        TCPPutROMString(sktHTTP, (ROM BYTE*)"");
}

void HTTPPrint_Sens(void)
{
    BYTE bylBuffer[5];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%u", modules[byIndexMachineHTPP].config.BusyLevel.wBusyLevel);
    TCPPutString(sktHTTP, bylBuffer);
}

void HTTPPrint_dspproperty(void)
{
    TCPPutString(sktHTTP, isHttpAccountantEnable ? "" : "none");
}

void HTTPPrint_coinUsed(WORD wIndex)
{
    TCPPutString(sktHTTP, (changeGiverConfig.byCoinValue[(BYTE)wIndex] > 0) &&
                 (changeGiverConfig.byCoinValue[(BYTE)wIndex] < 255) ? "" : "none");
}

void HTTPPrint_billUsed(WORD wIndex)
{
    BYTE bylBuffer[10];
    snprintf(bylBuffer, sizeof(bylBuffer),  "%s", (billValidatorConfig.byBillValue [(BYTE)wIndex] > 0) ? "" : "none");
    TCPPutString(sktHTTP, bylBuffer);
}

void UpdateCashActivation(BOOL isCG)
{
    BYTE byIndex;
    BYTE bylBuffer[3] = {0};
    wCopyEnable = 0;
    for(byIndex = 0; byIndex < MAXNUMBERCHANNELSCG; byIndex++)
    {
        snprintf(bylBuffer, sizeof(bylBuffer),  "%u", byIndex);
        if(HTTPGetROMArg(curHTTP.data, bylBuffer) != NULL)
        {
            wCopyEnable += (1 << atoi(bylBuffer));
        }
    }
    isCG ? (centralParameters.coinType.wCoinEnable = WORD_SWAP(wCopyEnable)) :
        (centralParameters.billType.wBillEnable = WORD_SWAP(wCopyEnable));
    I2CE2promLWriteBuffer(ADDRESS_CENTRAL_PARAMETERS, &centralParameters, sizeof(CENTRAL_PARAMETERS));
}

#endif
