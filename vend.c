/* 
 * File:   vend.h
 * Author: Dave Plater
 *
 * Created on 16 October 2017, 12:38 PM
 */
#include "vend.h"

//This location holds the value of cash in hand


//Initialize vend flags
void vend_init(void)
{
    lcd_string(inithop, line1);
    cctalk_init();
    //Turn on MDB
    lcd_string(initnote, line1);
    mdb_init();
    
    venflags.service = 0;
    venflags.initialrun = 1;
    if(credit_check() == 0)
    {
        venflags.iscredit = 0;
        venflags.inscoin = 1;
        venflags.credisplay = 0;
        mdbflags.noteerr = 0;
    }
    else
    {
        venflags.iscredit = 1;
        venflags.inscoin = 0;
        venflags.credisplay = 1;
        mdbflags.noteerr = 0;
    }
    //Allow service switch read only
    DAC1_SetOutput(0x00);
        
}

void credit_add(uint8_t credit)
{
    cash = DATAEE_ReadByte(credmem);
    cash = cash + credit;
    DATAEE_WriteByte(credmem, cash);
    if(cash != 0)
    {
        venflags.iscredit = 1;
        venflags.inscoin = 0;
        venflags.credisplay = 1;

    }
}

void credit_subtract(uint8_t credit)
{
    cash = DATAEE_ReadByte(credmem);
    cash = (cash - credit) & 0xFF;
    DATAEE_WriteByte(credmem, cash);
    if(cash == 0)
    {
        venflags.iscredit = 0;
        venflags.inscoin = 1;
        venflags.credisplay = 0;
    }
}

uint8_t credit_check(void)
{
    cash = DATAEE_ReadByte(credmem);
    return(cash);
}

uint8_t butindb(void)
{
    uint8_t butt = butin();
    uint8_t butval = buttons;
    while(butval != 0x00)
    {
        butval = butin();
    }
    //Return when button released
    return butt;
}

uint8_t butin(void)
{
    LATA7 = 0;
    LATA6 = 1;
    __delay_us(15);
    //Read buttons 5 to 8
    buttons = ((PORTA >> 1) & 0x0F) << 4;
    LATA7 = 1;
    LATA6 = 0;
    __delay_us(15);
    //Read buttons 1 to 4
    buttons = ((PORTA >> 1) & 0x0F) | buttons;
    LATA7 = 1;
    LATA6 = 1;
    return ~buttons;
}

void setup(void)
{
    
}

void Audit(void)
{
    
}

void Hopper_coin(void)
{
    
}

void Sensor_set(void)
{
    
}

void Clear_cred(void)
{
    
}

void Vend_test(void)
{
    
}

void Note_test(void)
{
    
}

