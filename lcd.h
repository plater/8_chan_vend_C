/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:    lcd.h c prototypes for lcd.c  
 * Author:  Dave Plater
 * Comments:
 * Revision history: 2017/10/06
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <stdint.h>
#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include <stdbool.h>
#include <p18f47k40.h>

#include <xc.h> // include processor files - each processor file is guarded. 
//Various lcd display constants
const char dispfunc1 = 0x24;    //4 bit operation, single line, 5x11 character
const char dispfunc2 = 0x28;    //4 bit operation, two lines, 5x8 character
const char dispon = 0x0C;	//Display on, cursor off and blink off
const char dispclr = 0x01;	//Write 20h to entire display
const char dispaddr = 0xA8;	//Upper 8 digit address
const char dsphome = 0x02;	//Select leftmost digit
const char dispnormal = 0x06;	//Static, increment address on write/read
const char dispcursor = 0x04;  // Switch on flashing cursor
const char dispshright = 0x05;	//Shift display right, increment address on write/read
const char dispshleft = 0x07;	//Shift display left, increment address on write/read
const char dispoff = 0x08;	//Display off
const char dispsr = 0x1B;	//Display shift right
const char dispsl = 0x18;	//Display shift left

//Message strings
const uint8_t inscoin[] = "Insert Coins or Notes";
const uint8_t credits[] = "  Credit = R";


void lcd_init(void);

void lcd_string(uint8_t *);
//Write to display character
void lcd_writeC(uint8_t);
//Write to display control
void lcd_write(uint8_t);
 //Clocks E high
void lcd_clockH(void);
 //Clocks E low
void lcd_clockL(void);
 //Clocks E low
void lcd_clockE(void);

void lcd_test(void);

void displ_hex(uint24_t);

void displ_credit(void);

void displ_test(void);

void displ_totals(void);

void displ_empty(void);
 //Returns busy and  register
int8_t read_busy(void);


#endif

/**
 End of File
*/


