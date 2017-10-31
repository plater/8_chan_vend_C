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
#include "mcc_generated_files/mcc.h"
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

//Next are the MDB address commands
//Reset bill accepter
const uint8_t note_reset = 0x30;
//Setup request setup data and look for response.
const uint8_t note_setup = 0x31;
//Set security mode
const uint8_t note_security = 0x32;
//Poll the note reader and look for response.
const uint8_t note_poll = 0x33;
//Enable or disable note  channels, more data to be sent
const uint8_t note_type = 0x34;
//Send escrow accept or reject.
const uint8_t note_escrow = 0x35;
//Stacker commands
const uint8_t note_stacker = 0x36;
//Further feature setup commands
const uint8_t note_features = 0x33;
//These are received from note reader.
const uint8_t motr_error = 0x01;
const uint8_t sens_error = 0x02;
const uint8_t just_busy = 0x03;
const uint8_t rom_error = 0x04;
const uint8_t jammed_err = 0x05;
const uint8_t just_reset = 0x06;
const uint8_t note_removed = 0x07;
const uint8_t cashbox_err = 0x08;
const uint8_t acept_disabled = 0x09;
const uint8_t invalid_escrow = 0x0A;
const uint8_t note_rejected = 0x0B;
const uint8_t theft_attempt = 0x0C;


//const uint8_t note_reset = 0x30;

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
   unsigned spare1 : 1;
   unsigned spare2 : 1;
} venflags;
//MDB flags isdata noteer mode = 1 master address or end of slave transmission.
struct
{
    unsigned isdata : 1;
    unsigned noteerr : 1;
    unsigned mode : 1;
    unsigned timeout : 1;
    unsigned spare2 : 1;
    unsigned spare3 : 1;
    unsigned spare4 : 1;
    unsigned spare5 : 1;
}mdbflags;

//Notes enabled or disabled
//Initialize all enabled
struct 
{
    unsigned R10 : 1;
    unsigned R20 : 1;
    unsigned R50 : 1;
    unsigned R100 : 1;
    unsigned R200 : 1;
    unsigned spare : 3;
}noteen;
volatile uint8_t noteen_byte = 0x1F;

//Chanel disable flags
struct
{
    unsigned chan1 : 1;
    unsigned chan2 : 1;
    unsigned chan3 : 1;
    unsigned chan4 : 1;
    unsigned chan5 : 1;
    unsigned chan6 : 1;
    unsigned chan7 : 1;
    unsigned chan8 : 1;
 } errorflags;

//added to credit memory
void credit_add(uint8_t credit);
//subtracted from credit memory
void credit_subtract(uint8_t credit);
//Initialize flags
void vend_init(void);

//Return credit in memory
uint8_t credit_check(void);

//MDB and CCTALK defines
void init_mdbdata(uint8_t);

uint8_t mdb_reset(void);

bool mdb_noten(void);

uint8_t mdb_poll(uint8_t slvadd, uint8_t mcount);

void mdb_on(void);

void mdb_ron(void);

uint8_t wait_ack(void);

void mdb_test(void);

void mdb_waitx(void);

void mdb_waitr(void);

void cctalk_on(void);

#endif	/* VEND_H */

