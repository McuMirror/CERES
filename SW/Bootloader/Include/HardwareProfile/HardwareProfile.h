/********************************************************************
 FileName:      HardwareProfile.h
 Dependencies:  See INCLUDES section
 Processor:     PIC32
 Hardware:      The code is natively intended to be used on the 
                  following hardware platforms: 
                  Explorer 16
                  USB Starter Kit
                  Ethernet Starter Kit
                  The firmware may be modified for use on other 
                  platforms by editing this file (HardwareProfile.h)
 Compiler:  	Microchip C32 (for PIC32)
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

 ********************************************************************/


#ifndef HARDWARE_PROFILE_H
    #define HARDWARE_PROFILE_H


    #define SYS_FREQ (80000000L)
    #define USE_USB_INTERFACE               // USB host MSD library

    #define LED IOPORT_C, BIT_1
    #define TESTKEY IOPORT_B, BIT_4
    #define VP IOPORT_B, BIT_3

// Common macros
// Clock frequency values
// These directly influence timed events using the Tick module.  They also are used for UART and SPI baud rate generation.
    #define GetSystemClock()		SYS_FREQ			// Hz
    #define GetInstructionClock()	(GetSystemClock()/1)	//
    #define GetPeripheralClock()	(GetSystemClock()/1)	// Divisor is dependent on the value of FPBDIV set(configuration bits).


#endif  //HARDWARE_PROFILE_H
