/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35.7
        Device            :  PIC18F47K40
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"



void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */   
    LATE = 0x00;    
    LATD = 0x00;    
    LATA = 0xC0;    
    LATB = 0x00;    
    LATC = 0x40;    

    /**
    TRISx registers
    */    
    TRISE = 0x00;
    TRISA = 0x1F;
    TRISB = 0xD0;
    TRISC = 0x90;
    TRISD = 0x00;

    /**
    ANSELx registers
    */   
    ANSELC = 0x00;
    ANSELB = 0xC0;
    ANSELD = 0x00;
    ANSELE = 0x00;
    ANSELA = 0x01;

    /**
    WPUx registers
    */ 
    WPUD = 0x00;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */   
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x20;
    ODCONC = 0x08;
    ODCOND = 0x00;
    


   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
    
    RX1PPSbits.RXPPS = 0x17;   //RC7->EUSART1:RX1;
    RC6PPS = 0x09;   //RC6->EUSART1:TX1;
    RB5PPS = 0x0B;   //RB5->EUSART2:TX2;
    RX2PPSbits.RXPPS = 0x0C;   //RB4->EUSART2:RX2;

}       

void PIN_MANAGER_IOC(void)
{   
    
    // Clear global Interrupt-On-Change flag
    PIR0bits.IOCIF = 0;

}

/**
 End of File
*/