#ifndef _TIRAX_MAX7219_INCLUDED_
#define _TIRAX_MAX7219_INCLUDED_
// General 
#define DIGITS 8
// Registers
#define DR(i) i-1
#define DMR 0x09
#define IR 0x0a
#define SLR 0x0b
#define SDR 0x0c
#define DTR 0x0f
// ShutDown Mode Format
#define Shutdown 0x00
#define Normal 0x01
// Decode-Mode Format
#define NoDecode 0x00
// Intensity Format
#define INTENSITY(i) ((i*16)/101)
// Scan Limit Format
#define DIGIT_DISPLAY(i) i

#pragma used+

#pragma used-

#pragma library MAX7219.lib

#endif