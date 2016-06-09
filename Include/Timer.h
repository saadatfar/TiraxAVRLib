#if  _MCU_CLOCK_FREQUENCY_!=8000000
    #error Timer Framework only works at 8 MHZ      
#endif

#ifndef  TimerN
    #error "TimerN" Should be Defined in order to use Tirax Timer     
#endif

#define SETF(i)     tflag[i/8]= tflag[i/8] | (1<<(i%8))
#define RESETF(i)   tflag[i/8]= tflag[i/8] & (~(1<<(i%8)))
#define READF(i)    (tflag[i/8]&(1<<(i%8)))>>(i%8)

#define TIMER_BIT_SIZE TimerN/8+(TimerN%8!=0)

unsigned char tflag[TIMER_BIT_SIZE];//Timer Flag Register
void(*tfunc[TimerN])();// Timer Functions Addresses

unsigned int tt[TimerN];//Timer Time
unsigned int tj[TimerN];//Job Time

#define StartTimer(i,t,f) tfunc[i]=f;tt[i]=t;tj[i]=0;//i:Timer Number,t:Timer time,f: Function
#define StartJob(i,t,f) tfunc[i]=f;tt[i]=t;tj[i]=t;
#define StopTimer(i) tt[i]=0;tj[i]=0;
  
void RunTimer();
void initTimer();

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    unsigned char i;    
    TCNT0=0x83; 
    for (i=0;i<TimerN;i++){
        if (tt[i]>1){
            tt[i]--;      
        }else if(tt[i]==1){
            tt[i]--;
            tt[i]=tj[i];
            SETF(i);
        }
    }  
}

#include <Timer.c>