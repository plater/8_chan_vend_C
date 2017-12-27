
/* 
 * File:   mdb.c
 * Author: Dave Plater
 *
 * Created on 16 October 2017, 12:38 PM
 */
#include "mdb.h"

//MDB routines begin here
//Command for mdb

void init_mdbdata(uint8_t initdata)
{
    for(uint8_t i = 0;i < 33; i++)
    {
        mdbdata[i] = initdata;
    }
}

void mdb_init(void)
{
    noteen_byte = DATAEE_ReadByte(notebits);
    eusartmdb_Initialize();
    mdbflags.noteerr = 0;
    mdbflags.isdata = 0;
    mdb_reset();
    mdb_noten();
    mdb_security();
    uint8_t i = mdb_comm(note_poll, 0x00);
    
}

uint8_t mdb_reset(void)
{
    //Enable 9 bit for MDB
//    RC1STA = 0xD0;
//    TX1STA = 0xEC;
    mdbflags.timeout = 1;
    while(mdbflags.timeout)
    {
        uint8_t i = mdb_comm(note_reset, 0x00);
    }
    asm("nop");
    uint8_t i = mdb_comm(note_poll, 0x00);
    if(mdbdata[--i] == just_reset)
    {
    //    mdb_noten();
        //Get status
        i = mdb_comm(note_poll, 0x00);
    }
    
    return i;
}

void set_notes(void)
{
    lcd_string(setnotes, line1);
    noteen.noteset = 1;
    noteen.endis = 1;
    while(noteen.noteset)
    {
        buttons = butindb();
        switch(buttons)
        {
            //R10
            case 0x01 : enable_notes(displ_note(tenrand));
            
            //R20
            case 0x02 : enable_notes(displ_note(twentyrand));
            //R50
            case 0x04 : enable_notes(displ_note(fiftyrand));
            //R100
            case 0x08 : enable_notes(displ_note(hundredrand));
            //200
            case 0x10 : enable_notes(displ_note(twohundredrand));
            //Exit
            case 0x80 : lcd_string(servmsg, line1);
            noteen.noteset = 0;
            default : break;
        }
    }
}

void enable_notes(uint8_t notenum)
{
    noteen.endis = 1;
    displ_nendis(notenum);
    while(noteen.endis)
    {
        buttons = butindb();
        switch(buttons)
        {
            case 0x01 : noteen_byte = noteen_byte | notenum;
            displ_nendis(notenum);
            break;
            case 0x02 : noteen_byte = noteen_byte & ~notenum;
            displ_nendis(notenum);
            break;
            case 0x04 : noteen.endis = 0;
            buttons = 0;
            default : break;
        }
    }
}

void note_disable(void)
{
    noteen_byte = 0x00;
    mdb_noten();
}

void save_notes(void)
{
    DATAEE_WriteByte(notebits, noteen_byte);
    
}

void mdb_noten(void)
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
    mcount = mdb_comm(note_type, mcount);
    mdbflags.vending = 0;
}
void mdb_security()
{
    init_mdbdata(0x00);
    mdb_comm(note_security, 0x01);
}

uint8_t mdb_poll(void)
{
    //Timer3 is the poll timer, poll every 50ms.
    //This timer is also used by cctalk time out.
    TMR3_Initialize();
    uint8_t i = mdb_comm(note_poll, 0x00);
    notebyte = mdbdata[0];
    //if only an ACK is received, no data to process.
    if((mdbdata[0] & 0x80) != 0)
    {
        notebyte = mdbdata[0] & 0x7F;
        switch(notebyte)
        {
            case 0: credit = 10;
            return credit;
            case 1: credit = 20;
            return credit;
            case 2: credit = 50;
            return credit;
            case 3: credit = 100;
            return credit;
            case 4: credit = 200;
            return credit;
            default: credit = 0x10;
            mdbflags.noteerr = 1;
            return credit;
        }
    }
    else
    {
        switch(mdbdata[0])
        {
            //Plain ACK
            case 0x00: credit = 0;
            return credit;
            //Motor error
            case 0x01:credit = 0x01;
            break;
            //Sensor error
            case 0x02:credit = 0x02;
            break;
            //Reader busy
            case 0x03:credit = 0x00;
            mdbflags.noteerr = 0;
            return credit;
            //ROM error
            case 0x04:credit = 0x04;
            break;
            //Note jam
            case 0x05:credit = 0x05;
            break;
            //Just reset
            case 0x06:credit = 0x06;
            break;
            //note_removed
            case 0x07: credit = 0x07;
            break;
            //cash box error
            case 0x08: credit = 0x08;
            break;
            //Note Disabled
            case 0x09:credit = 0x09;
            break;
            //invalid escrow
            case 0x0A:credit = 0x0A;
            break;
            //note_rejected
            case 0x0B:credit = 0x0B;
            break;
            //theft_attempt
            case 0x0C:credit = 0x0C;
            break;
            default: credit = 0;
        }
        mdbflags.noteerr = 1;
        return credit;
    }
    
}

uint8_t mdb_comm(uint8_t slvadd, uint8_t mcount)
{
    //Counter for data bytes in mdbdata
    uint8_t i = 0;
    //Mode bit to 1 indicates master address bit.
    TX1STAbits.TX9D = 1;
    mdb_on();
    //Write appropriate poll address
    //Only a bill acceptor at this time.
 //   
    mdb_transmit(slvadd);
    TX1STAbits.TX9D = 0;
    //Write CHK byte - checksum
    
    //Handle more bytes for enables etc
    chkbyte = slvadd;
    if(mcount != 0)
    {
        i = mcount + 1;
        while(i != 0)
        {
            mdb_transmit(mdbdata[mcount]);
            
            //Calculate check byte should be 0x53
            chkbyte = chkbyte + mdbdata[mcount];
            i--;
            mcount--;
        }
    }
    mdb_transmit(chkbyte);
    
    //Start the 5mS timeout for receiving status from device.
    //Monitor PIR4bits.TMR1IF for overflow EUSART1_Read();
    
    //initialize storage
    //mdb_ron();
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
        mdb_transmit(0x00);
        
    }
    //RC1STAbits.RX9D;
    mdb_on();
    // i contains the number of data blocks in mdbdata[]
    return(i);
}

void mdb_on(void)
{
    // SPEN enabled; RX9 9-bit; CREN enabled; ADDEN disabled; SREN disabled; 
//    RC1STA = 0xD0;
    // TX9 9-bit; TX9D 0; SENDB send_sync_break_next; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC master; 
//    TX1STA = 0xEC;
    LATCbits.LATC0 = 1;
    LATCbits.LATC1 = 0;
//    TX1STAbits.TXEN = 1;
//    mdb_comm(note_poll);
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

void mdb_test(void)
{
    uint8_t i = 0;
    uint8_t x = note_reset;
    TX1STAbits.TXEN = 1;
    while(i < 8)
    {
        
        
        TX1STAbits.TX9D = 1;
        mdb_transmit(x);
        
        TX1STAbits.TX9D = 0;
        mdb_transmit(x);
        
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
void mdb_unlock(void)
{
    LATC = 0x03;
    TRISC = 0x80;
    ANSELC = 0x00;
    WPUC = 0x00;
    ODCONC = 0x00;
}

void mdb_transmit(uint8_t txbyte)
{
    EUSART1_Write(txbyte);
    mdb_waitx();
}
