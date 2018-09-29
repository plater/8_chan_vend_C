/* 
 * File:   gsm.h
 * Author: Dave Plater
 *
 * Created on September 26, 2018, 3:14 PM
 */

#ifndef GSM_H
#define	GSM_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "vend.h"
#include <xc.h>
#include "lcd.h"
#include "mcc_generated_files/mcc.h"

//Gsm related memory
uint8_t gsmbyte = 0;
uint8_t gsmmsg[];

//GSM messages
const uint8_t noecho = "ATE0";

void gsm_waitx(void);

void gsm_waitr(void);

void gsm_transmit(uint8_t txbyte);

void gsm_init(void);

void gsm_txAT(void);

void gsm_on(void);

void gsm_off(void);

#ifdef	__cplusplus
}
#endif

#endif	/* GSM_H */

