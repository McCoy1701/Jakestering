#include <stdio.h>
#include <stdlib.h>
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

void delay( int seconds )
{
  sleep( seconds );
}

void msDelay( int milliseconds )
{
  usleep( ( milliseconds % 1000 ) * 1000 );
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
  GPIO_PULL = PUD;
  sleep(0.015);
  GPIO_PULLCLK0 = pin;
  sleep(0.015);

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
  if ( GET_GPIO( pin ) )
    return 1;
  else
    return 0;
}

