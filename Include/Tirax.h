#ifndef _TIRAX_LIB_INCLUDED_
#define _TIRAX_LIB_INCLUDED_

#include <Timer.h>
#include <Sync.h>
#include <stdbool.h>

void initTirax();
void RunTirax();

bool readBitCharArr(char* arr,unsigned int n);
void setBitCharArr(char* arr,unsigned int n);
void resetBitCharArr(char* arr,unsigned int n);


#pragma library Tirax.lib

#endif