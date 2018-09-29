/* 
 * File:   gsm.c
 * Author: Dave Plater
 *
 * Created on September 26, 2018, 3:14 PM
 */
#include "gsm.h"

//Wait for buffer empty
void gsm_waitx(void)
{
    while(0 == PIR3bits.TX2IF)
    {
        
    }
}
//Wait for buffer empty
void gsm_waitr(void)
{
    while(!PIR3bits.RC2IF)
    {
        
    }
}

void gsm_transmit(uint8_t txbyte)
{
    EUSART2_Write(txbyte);
    gsm_waitx();
}

void gsm_init(void)
{
    gsm_on();
    while(!PIR3bits.RC2IF)
    {
        gsm_txAT();
        __delay_ms(10);
    }
    gsmbyte = EUSART2_Read();
//    gsm_off();
    asm("nop");
}

void gsm_txAT(void)
{
    gsm_transmit('A');
    gsm_transmit('T');
}

void gsm_on(void)
{
    LATCbits.LC3 = 1;
    
}

void gsm_off(void)
{
    LATCbits.LC3 = 0;
}