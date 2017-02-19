#ifndef _TIRAX_LIB_INCLUDED_
#define _TIRAX_LIB_INCLUDED_

#if  _MCU_CLOCK_FREQUENCY_!=16000000
    #error Timer Framework only works at 16 MHZ      
#endif

#ifdef _CHIP_ATMEGA32A_
	#define VALID_CHIP
	#define M32
#endif


#ifdef _CHIP_ATMEGA64A_
	#define VALID_CHIP
	#define M64
#endif

#ifndef VALID_CHIP
	#error Unsupported Chip.
#endif

#include <Timer.h>
#include <Sync.h>
#include <stdbool.h>
#include <Registers.h>
#include <Errors.h>

void initTirax();
void RunTirax();

bool readBitCharArr(char* arr,unsigned int n);
void setBitCharArr(char* arr,unsigned int n);
void resetBitCharArr(char* arr,unsigned int n);
void raiseCriticalError(unsigned char e);


#pragma library Tirax.lib

#endif