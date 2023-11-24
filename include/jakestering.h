#ifndef __JAKESTERING_H__
#define __JAKESTERING_H__

#include "definitions.h"

extern int memFd; // /dev/mem

extern void* gpioMap; //Pointer to the GPIO memory map

extern volatile unsigned *gpio; //Access to the input / output

void setupIO(); //Setup function to create memory regions to access the GPIO

void delay(int milliSeconds);

void delayMicro(int microSeconds);

void pinMode( int pin, int mode );

void pudController( int pin, int PUD );

void digitalWrite( int pin, int value );

int digitalRead( int pin );

void digitalWriteByte( const int value, int pinStart, int pinEnd );

#endif

