#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2835_BASE 0x20000000
#define GPIO_BASE ( BCM2835_BASE + 0x200000 )

#define PAGE_SIZE  ( 4 * 1024 )
#define BLOCK_SIZE ( 4 * 1024 )

#define INP_GPIO( g ) *( gpio + ( ( g ) / 10 ) ) &= ~( 7 << ( ( (g) % 10 ) * 3 ) )
#define OUT_GPIO( g ) *( gpio + ( ( g ) / 10 ) ) |=  ( 1 << ( ( (g) % 10 ) * 3 ) )
#define SET_GPIO_ALT( g, a ) *( gpio + ( ( ( g ) / 10 ) ) ) |= ( ( (a) <= 3 ? (a) + 4 : (a) == 4 ? 3 : 2) << ( ( (g) % 10 ) * 3 ) )

#define GPIO_SET *( gpio + 7 )
#define GPIO_CLR *( gpio + 10 )

#define GET_GPIO( g ) ( *( gpio + 13 ) & ( 1 << g ) )

#define GPIO_PULL *( gpio + 37 )
#define GPIO_PULLCLK0 *( gpio + 38 )

int memFd; // /dev/mem

void* gpioMap;

volatile unsigned *gpio;


void setupIO();

void printButton( int g )
{
  if ( GET_GPIO( g ) )
    printf( "Button Pressed\n" );
  else
    printf( "Button Released\n" );
}

int main( int argc, char **argv )
{
  int g, rep;

  setupIO();

  for ( g = 0; g <= 12; g++ )
  {
    INP_GPIO( g );
    OUT_GPIO( g );
  }

  for ( rep = 0; rep < 10; rep++ )
  {
    for ( g = 0; g <= 12; g++ )
    {
      GPIO_SET = 1 << g;
      sleep( 1 );
    }

    for ( g = 0; g <= 12; g++ )
    {
      GPIO_CLR = 1 << g;
      sleep( 1 );
    }
  }

  return 0;
}

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

