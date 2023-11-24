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

void setupIO()
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

void delayMicro( int microSeconds )
{
  usleep( microSeconds );
}

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

void pudController( int pin, int PUD )
{
  GPIO_PULL = PUD & 0b11;
  usleep( 5 );
  GPIO_PULLCLK0 = 1 << pin;
  usleep( 5 );

  GPIO_PULL = 0;
  GPIO_PULLCLK0 = 0;
}

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

int digitalRead( int pin )
{
  if ( GET_GPIO( pin ))
    return HIGH;
  else
    return LOW;
}

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

