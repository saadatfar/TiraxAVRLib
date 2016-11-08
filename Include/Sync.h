#ifndef _TIRAX_SYNC_INCLUDED_
#define _TIRAX_SYNC_INCLUDED_

#define RESEND_T 300
#define SYW_BUFFER_SIZE 32
#define TX_BUFFER_SIZE 9
 
//Sync Starting Bytes
#define  READ_START 0xff
#define  ACK_START 0xfe

//TX Buffer Defines
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)
#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<DOR)
#define _ALTERNATE_PUTCHAR_

#define CREATE_ACK(i,data)  0x7f & (i ^ data) //MACRO: Create acknowledge parity byte using register number and data

#define SETI(i)     iFlag[i/8]= iFlag[i/8] | (1<<(i%8)) //MACRO: Set interrupt flag 
#define RESETI(i)   iFlag[i/8]= iFlag[i/8] & (~(1<<(i%8))) //MACRO: Reset interrupt flag
#define READI(i)    (iFlag[i/8]&(1<<(i%8)))>>(i%8) //MACRO: Read interrupt flag 

void pushSyncBuffer(char i); //Push i th register into sync buffer
unsigned char readSyncBuffer(); //Read first in sync buffer
void pullBuffer(); //Pull (delete) first in sync buffer

void putchar(char c); //Put a char in TX buffer 
void sendNextSy(); //Send first in sync buffer

void nop();//Do nothing!

void setInterrupt(char n,void(*f)()); //Initiate an interrupt

void initSync(unsigned char size); //Initialize Sync system

void setReadReg(char n,char data); //Send acknowledge and set interrupt

void WriteReg(unsigned char i,unsigned char data);

void RunInterrupts();

char ReadReg(char n);

void WriteBitReg(unsigned char reg,unsigned char b, unsigned char value);

void SetBitReg(unsigned char i,unsigned char n);
void ResetBitReg(unsigned char i,unsigned char n);
unsigned char ReadBitReg(unsigned char i,unsigned char n);

void setRecFunc(void (*f)());

#pragma library Sync.lib

#endif