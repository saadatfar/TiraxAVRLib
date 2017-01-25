#ifndef _TIRAX_TIMER_INCLUDED_
#define _TIRAX_TIMER_INCLUDED_

#define TRANS_RESEND_TIMER 0

#define SETF(i)     tflag[i/8]= tflag[i/8] | (1<<(i%8))
#define RESETF(i)   tflag[i/8]= tflag[i/8] & (~(1<<(i%8)))
#define READF(i)    (tflag[i/8]&(1<<(i%8)))>>(i%8)


void StartTimer(unsigned char i,unsigned int t, void(*f)() );
void StartJob(unsigned char i,unsigned int t, void(*f)() );
void StopTimer(unsigned char i);
unsigned char StartNextTimer(unsigned int t, void(*f)() );
unsigned char StartNextJob(unsigned int t, void(*f)() );
unsigned char findFreeTimer();
  
void RunTimer();
void initTimer(unsigned char size);

#pragma library Timer.lib

#endif