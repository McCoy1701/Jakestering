/*
 * jakestering.c:
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "jakestering.h"

int memFd;

void* gpioMap;

volatile unsigned *gpio;

/*
 * Sets up the GPIO memory address space to be modified
 *
 * Parameters:
 *  void
 * 
 * Return:
 *  void
 **************************************************************
 */

void setupIO( void )
{
  if ( ( memFd = open ( "/dev/mem", O_RDWR|O_SYNC ) ) < 0)
  {
    printf( "can't open /dev/mem \n" );
    exit( -1 );
  }

  gpioMap = mmap( NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, memFd, GPIO_BASE );

  close( memFd );

  if ( gpioMap == MAP_FAILED )
  {
    printf( "mmap error %d\n", (int)gpioMap );
    exit( -1 );
  }

  gpio = ( volatile unsigned* )gpioMap;
}

/*
 * Delay in milli seconds, but if milliSecond is higer than 1000 delay in seconds
 *
 * Parameters:
 *  milliSeconds: amount of time to delay
 * 
 * Return:
 *  void
 **************************************************************
 */

void delay( int milliSeconds )
{
  if ( ( milliSeconds % 1000 ) == 0 )
  {
    sleep(milliSeconds / 1000);
  }
  
  else 
  {
    usleep( ( milliSeconds % 1000 ) * 1000 );
  }
}

/*
 * Delay in micro seconds
 *
 * Parameters:
 *  microSeconds: amount of time to delay
 * 
 * Return:
 *  void
 **************************************************************
 */

void delayMicro( int microSeconds )
{
  usleep( microSeconds );
}

/*
 * Pin mode sets the INPUT/OUTPUT state of a pin 
 *
 * Parameters:
 *  pin : GPIO pin to set
 *  mode: INPUT/OUTPUT 0/1
 * 
 * Return:
 *  void
 **************************************************************
 */

void pinMode( int pin, int mode )
{
  if ( mode == INPUT )
  {
    INP_GPIO( pin );
  }

  else if ( mode == OUTPUT )
  {
    INP_GPIO( pin );
    OUT_GPIO( pin );
  }
}

/*
 * Pull up/down controller for the built in resistors on each GPIO pin
 *
 * Parameters:
 *  pin: GPIO pin to set
 *  PUD: DISABLE/PULL_DOWN/PULL_UP 0/1/2
 * 
 * Return:
 *  void
 **************************************************************
 */

void pudController( int pin, int PUD )
{
  GPIO_PULL = PUD & 0b11;
  usleep( 5 );
  GPIO_PULLCLK0 = 1 << pin;
  usleep( 5 );

  GPIO_PULL = 0;
  GPIO_PULLCLK0 = 0;
}

/*
 * write a value to a given pin
 *
 * Parameters:
 *  pin  : GPIO pin to set
 *  value: LOW/HIGH 0/1 
 * 
 * Return:
 *  void
 **************************************************************
 */

void digitalWrite( int pin, int value )
{
  if ( value == LOW )
  {
    GPIO_CLR = 1 << pin;
  }

  else if ( value == HIGH )
  {
    GPIO_SET = 1 << pin;
  }
}

/*
 * read the value of a given pin
 *
 * Parameters:
 *  pin: GPIO pin to set
 * 
 * Return:
 *  value of the pin read (HIGH/LOW 1/0)
 **************************************************************
 */

int digitalRead( int pin )
{
  if ( GET_GPIO( pin ))
    return HIGH;
  else
    return LOW;
}

/*
 * Write a byte to a given range of 8 pins
 *
 * Parameters:
 *  value   : data to be writen
 *  pinStart: start of pin range
 *  pinEnd  : end of pin range
 *
 * Return:
 *  void
 **************************************************************
 */

void digitalWriteByte( const int value, int pinStart, int pinEnd ) //pin start must be less than pinEnd
{
  uint32_t pinSet = 0;
  uint32_t pinClr = 0;
  int mask = 1;
  
  if ( ( pinEnd - pinStart ) != 7 )
  {
    printf( "Must be 8 pins 0-7: %d\n", ( pinEnd - pinStart ) );
    return;
  }

  for ( int i = pinStart; i <= pinEnd; i++ )
  {
    if ( ( value & mask ) == 0 )
    {
      pinClr |= ( 1 << i ); //set the pin to be cleared
    }

    else 
    {
      pinSet |= ( 1 << i ); //set the pin the be set
    }

    mask <<= 1;
  }

  GPIO_CLR = pinClr;
  GPIO_SET = pinSet;
}

