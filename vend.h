/* 
 * File:   vend.h
 * Author: Dave Plater
 *
 * Created on 16 October 2017, 12:38 PM
 */

#ifndef VEND_H
#define	VEND_H

#include <xc.h>
#include "lcd.h"
#include "mdb.h"
#include "cctalk.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/pin_manager.h"
//This location is the value of cash to be added or
//subtracted from credit memory
volatile uint8_t credit;
volatile uint8_t cash;
volatile uint8_t buttons;
//NVRAM address location definitions
//This location holds the value of cash in hand
const uint16_t credmem = 0x00;
//Clearable total cash uint16_t
const uint16_t  cashinv = 0x02;
//Non clearable total cash uint_24_t
const uint16_t cashint = 0x04;
//Total vends, clearable 8 x uint8_t
const uint16_t vendstore = 0x07;
//Prices per vend 8 x uint8_t
const uint16_t pricestore = 0x0F;
//Vend error flags bits 0 to 7 uint8_t
const uint16_t venderrors = 0x17;
//Note enable bits 0 to 4 uint8_t
const uint16_t notebits = 0x18;
//

/*vend flags bit 0=still credit bit 1=error bit 2=display insert coin
  bit 3=no change bit4=credit display bit5=Buy another?*/
struct
{
   unsigned iscredit : 1;
   unsigned error : 1;
   unsigned inscoin : 1;
   unsigned nochange : 1;
   unsigned credisplay : 1;
   unsigned initialrun : 1;
   unsigned noterr : 1;
   unsigned service : 1;
} venflags;
//added to credit memory
void credit_add(uint8_t credit);
//subtracted from credit memory
void credit_subtract(uint8_t credit);
//Initialize flags
void vend_init(void);

//Return credit in memory
uint8_t credit_check(void);

void setup(void);
// Only return when button released
uint8_t butindb(void);
//Read buttons return 1 for pressed button.
uint8_t butin(void);
//Audit display erasable total cash, vends and hopper coins out, clear totals
// also display unclearable total cash
void Audit(void);
//Set the value of dispensed coin
void Hopper_coin(void);

void Sensor_set(void);

void Clear_cred(void);

void Vend_test(void);

void Note_test(void);


#endif	/* VEND_H */

