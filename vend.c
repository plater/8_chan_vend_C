/* 
 * File:   vend.h
 * Author: Dave Plater
 *
 * Created on 16 October 2017, 12:38 PM
 */
#include "vend.h"

//This location holds the value of cash in hand


//This location is the value of cash to be added or
//subtracted from credit memory
volatile uint8_t credit;
volatile uint8_t cash;
//Initialize vend flags
void vend_init(void)
{
    //Turn on MDB
    mdbflags.noteerr = 0;
    mdbflags.isdata = 0;
    //mdb_ron();
//    mdb_test();
    mdb_reset();
    mdb_noten();
    uint8_t i = mdb_poll(note_poll, 0x00);
    venflags.initialrun = 1;
    if(credit_check() == 0)
    {
        venflags.iscredit = 0;
        venflags.inscoin = 1;
        venflags.credisplay = 0;
    }
    else
    {
        venflags.iscredit = 1;
        venflags.inscoin = 0;
        venflags.credisplay = 1;
    }
    
        
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

//MDB routines begin here
//Command for mdb
uint8_t slvadd;
uint8_t mcount = 0;
//32 bytes allowed location 32 should always be zero
uint8_t mdbdata[32];
uint8_t chkbyte;
uint16_t dbcount=0;

void init_mdbdata(uint8_t initdata)
{
    for(uint8_t i = 0;i < 33; i++)
    {
        mdbdata[i] = initdata;
    }
}

uint8_t mdb_reset(void)
{
    uint8_t i = mdb_poll(note_reset, 0x00);
    asm("nop");
    uint8_t i = mdb_poll(note_poll, 0x00);
    if(mdbdata[--i] == just_reset)
    {
        //Get status
        uint8_t i = mdb_poll(note_poll, 0x00);
    }
    else
    {
        //Problem
        return mdbflags.noteerr = 1;
    }
    i = mdb_poll(note_setup, 0x00);
    
    return i;
}

bool mdb_noten(void)
{
    //Initialize message store to 0s
    init_mdbdata(0x00);
    //Note enable message is 4 bytes long
    mcount = 3;
    //Escrow is bytes 3 and 2 all disabled
    mdbdata[0] = 0x00;
    mdbdata[1] = 0x00;
    //noteen structure has individual bits
    mdbdata[2] = noteen_byte;
    //We only use 5 channels.
    mdbdata[3] = 0x00;
    mcount = mdb_poll(note_type, mcount);
}

uint8_t mdb_poll(uint8_t slvadd, uint8_t mcount)
{
    //Counter for data bytes in mdbdata
    uint8_t i = 0;
    //Mode bit to 1 indicates master address bit.
    TX1STAbits.TX9D = 1;
    mdb_on();
    //Write appropriate poll address
    //Only a bill acceptor at this time.
 //   mdb_waitx();
    EUSART1_Write(slvadd);
    TX1STAbits.TX9D = 0;
    //Write CHK byte - checksum
    mdb_waitx();
    //Handle more bytes for enables etc
    chkbyte = slvadd;
    if(mcount != 0)
    {
        i = mcount + 1;
        while(i != 0)
        {
            EUSART1_Write(mdbdata[mcount]);
            mdb_waitx();
            //Calculate check byte should be 0x53
            chkbyte = chkbyte + mdbdata[mcount];
            i--;
            mcount--;
        }
    }
    EUSART1_Write(chkbyte);
    mdb_waitx();
    //Start the 5mS timeout for receiving status from device.
    //Monitor PIR4bits.TMR1IF for overflow EUSART1_Read();
    
    //initialize storage
    init_mdbdata(0xFF);
    TMR1_Initialize();
    dbcount = 0;
    mdbflags.isdata = 0;
    i = 0;
    //Continue until either timeout or data present.
    while(!PIR4bits.TMR1IF && !mdbflags.isdata)
    {
        //debug count of timer
        dbcount++;
        mdbflags.isdata = 0;
        //RC1STAbits.SPEN 
        //RC1IF goes high when there's data
        while(PIR3bits.RC1IF && !mdbflags.isdata)
        {
            
            //mdb_ron();
            mdbdata[i] = EUSART1_Read();
            mdb_waitr();
            //End of transmission when 9th bit set.
            mdbflags.isdata = RC1STAbits.RX9D;
            TMR1_Initialize();
            i++;
            
        }
        
    }
    //Correct i to point to last received data
    i--;
    //If timeout occurred TMR1IF is set.
    mdbflags.timeout = PIR4bits.TMR1IF;
     //Send ACK on successful receive except for an ACK which = 0
    if(mdbflags.isdata == 1 && mdbdata[i] != 0x00)
    {
        TX1STAbits.TX9D = 1;
        mdb_on();
        EUSART1_Write(0x00);
        mdb_waitx();
    }
    //RC1STAbits.RX9D;
    mdb_on();
    // i contains the number of data blocks in mdbdata[]
    return(i);
}

void mdb_on(void)
{
    LATCbits.LATC0 = 1;
    LATCbits.LATC1 = 1;
//    TX1STAbits.TXEN = 1;
//    mdb_poll(note_poll);
}

void mdb_ron(void)
{
    LATCbits.LATC0 = 1;
    LATCbits.LATC1 = 0;
//    TX1STAbits.TXEN = 0;
}
//Wait for buffer empty
void mdb_waitx(void)
{
    while(TX1STAbits.TRMT == 0)
    {
        
    }
}
//Wait for buffer empty
void mdb_waitr(void)
{
    while(BAUD1CONbits.RCIDL == 0)
    {
        
    }
}

uint8_t wait_ack(void)
{
    
}

void cctalk_on(void)
{
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 1;
}
void mdb_test(void)
{
    uint8_t i = 0;
    uint8_t x = note_reset;
    TX1STAbits.TXEN = 1;
    while(i < 8)
    {
        
        
        TX1STAbits.TX9D = 1;
        EUSART1_Write(x);
        mdb_waitx();
        TX1STAbits.TX9D = 0;
        EUSART1_Write(x);
        mdb_waitx();
        TX1STAbits.TXEN = 0;
        asm("nop");
        mdb_ron();
        wait_ack();
        i++;
        x++;
        TX1STAbits.TXEN = 1;
        mdb_on();
    }
    TX1STAbits.TXEN = 0;
}

