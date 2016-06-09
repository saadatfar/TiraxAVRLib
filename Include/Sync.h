#ifndef  REG_SIZE
    #error "REG_SIZE" Should be Defined in order to use Tirax Sync     
#endif
#ifndef  TRANS_RESEND_TIMER
    #error "TRANS_RESEND_TIMER" Should be Defined in order to use Tirax Sync     
#endif

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

#define REG_BIT_SIZE REG_SIZE/8+(REG_SIZE%8!=0) //Calculate number of bytes needed to store interrupt flags = ceil(REG_SIZE)

unsigned char syReg[REG_SIZE]; //Registers
unsigned char iFlag[REG_BIT_SIZE]; //Interrupts

//Sync Buffer Variables
unsigned char syw_wr_index=0,syw_rd_index=0,syw_counter=0;
bit syw_overflow=0;
unsigned char syw_buffer[SYW_BUFFER_SIZE];

//TX Buffer Variables
char tx_buffer[TX_BUFFER_SIZE];
unsigned char tx_wr_index=0,tx_rd_index=0,tx_counter=0;

unsigned char syw_chk; //Last sent parity byte

//Receiver state machine variables 
unsigned char read_reg_step=0,read_i;
unsigned char read_ack_step=0;

void(*intFunc[REG_SIZE])(char); //Interrupt functions variable

void pushSyncBuffer(char i); //Push i th register into sync buffer
unsigned char readSyncBuffer(); //Read first in sync buffer
void pullBuffer(); //Pull (delete) first in sync buffer

void putchar(char c); //Put a char in TX buffer 
void sendNextSy(); //Send first in sync buffer

void nop(char x);//Do nothing!

void setInterrupt(char n,void(*f)(char)); //Initiate an interrupt

void initSync(); //Initialize Sync system

void setReadReg(char n,char data); //Send acknowledge and set interrupt

void WriteReg(unsigned char i,unsigned char data);

#define SetBitReg(i,n) syReg[i]=(1<<n) | syReg[i]  ;pushSyncBuffer(i);
#define ResetBitReg(i,n) syReg[i]=(0<<n) & syReg[i] ;pushSyncBuffer(i);
#define ReadBitReg(i,n) (syReg[i] & (1<<n))!=0
#define ReadReg(i) syReg[i]


#include <Sync.c>