#include <Timer.h>
#include <Sync.h>

void initTirax(){
	// Watchdog Timer initialization: OSC/1024k: 1Sec
	WDTCR=(0<<WDTOE) | (1<<WDE) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0);
	initTimer();
	initSync();
}

void RunTirax(){
    #asm("wdr");
	RunTimer();
	RunInterrupts();
}