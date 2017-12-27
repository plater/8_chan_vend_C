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
signed char count;
//Various lcd display constants
const char dispfunc1 = 0x24;    //4 bit operation, single line, 5x11 character
const char dispfunc2 = 0x28;    //4 bit operation, two lines, 5x8 character
const char dispfunc3 = 0x2C;    //4 bit operation, two lines, 5x11 character
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
const char line1 = 0x80;
const char line2 = 0xC0;
const char line3 = 0x94;
const char line4 = 0xD4;

//Message strings
const uint8_t inscoin[] = "Insert Coins or Notes";
const uint8_t credits[] = "  Credit = R";
const uint8_t service[] = "  Service Mode";
const uint8_t audit[] = "  Audit Mode";
const uint8_t hopcoin[] = "Hopper Coin         Value";
const uint8_t senset[] = "  Setup Sensor";
const uint8_t credclr[] = "Push button 1 to clear credits   and exit";
const uint8_t vendtest[] = " Push button to     vend";
const uint8_t notetest[] = "  Insert Note";
const uint8_t exit[] = "Exit";
const uint8_t servmsg[] = "Service Mode: press 1 = Audit 2 = Sensor3=Note-en 4=Cred-clr 5=Vend 6=Note 8=Exit";
const uint8_t noteerr[] = "   Note error     code = 0x";
const uint8_t inithop[] = "  Initialize Hopper";
const uint8_t initnote[] = "     Initialize          Note Reader";
const uint8_t nochange[] = "No Change Given";
const uint8_t setnotes[] = "Enable / Disable    1 = R10, 2 = R20    3 = R50, 4 = R100   5 = R200";
const uint8_t tenrand[] = "0 R10  ";
const uint8_t twentyrand[] = "1 R20  ";
const uint8_t fiftyrand[] = "2 R50  ";
const uint8_t hundredrand[] = "3 R100 ";
const uint8_t twohundredrand[] = "4 R200 ";
const uint8_t enabled[] = "enabled ";
const uint8_t disabled[] = "disabled";

uint8_t bflag;
uint8_t lcdfunc;
uint8_t lcdata;
uint8_t lcdline;
uint8_t stradd;
uint24_t hexnum;
uint8_t ercode;
uint8_t lcdaddress;

void lcd_dispadd(uint8_t lcdaddress);

void displ_code(uint8_t ercode);

void lcd_init(void);

void lcd_string(uint8_t *, uint8_t lcdline);
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

void displ_noteer(void);

void displ_test(void);

void displ_totals(void);

void displ_empty(void);
//Pointer to note value message displays it.
uint8_t displ_note(uint8_t *lcdstring);

void displ_nendis(uint8_t notenum);
 //Returns busy and  character position + 1
int8_t read_busy(void);


#endif

/**
 End of File
*/


