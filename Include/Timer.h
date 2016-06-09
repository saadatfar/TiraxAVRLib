#ifndef _TIRAX_TIMER_INCLUDED_
#define _TIRAX_TIMER_INCLUDED_

#if  _MCU_CLOCK_FREQUENCY_!=8000000
    #error Timer Framework only works at 8 MHZ      
#endif

#define TimerN 16
#define TRANS_RESEND_TIMER 0

#define SETF(i)     tflag[i/8]= tflag[i/8] | (1<<(i%8))
#define RESETF(i)   tflag[i/8]= tflag[i/8] & (~(1<<(i%8)))
#define READF(i)    (tflag[i/8]&(1<<(i%8)))>>(i%8)

#define TIMER_BIT_SIZE TimerN/8+(TimerN%8!=0)

void StartTimer(unsigned char i,unsigned int t, void(*f)() );
void StartJob(unsigned char i,unsigned int t, void(*f)() );
void StopTimer(unsigned char i);
  
void RunTimer();
void initTimer();

#pragma library Timer.lib

#endif