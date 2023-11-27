/*
 * jakestering.h:
 *  GPIO access library for raspberry pi zero v1.3
 *
 * Copyright (c) 2023 Jacob Kellum <jkellum819@gmail.com>
 *************************************************************************
 * This file is apart of Jakestering:
 *    https://github.com/McCoy1701/Jakestering
 *
 * Jakestering is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Jakestering is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Jakestering; if not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************
 */

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

