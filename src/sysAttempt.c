#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <bcm2835.h>

//#include "jakestering.h"

#define MAX_BUFFER 32 

int pin = 0;

int pinFD[32] = {0};

void openPin( int pin, int direction );
void writePin( int pin, int value );
int readPin( int pin );
void edgeControl( int pin, char *mode );

int main( int argc, char *argv[] )
{

  openPin( pin, 0 );
  //writePin( pin, 1 );
  //delay(100);
  //int test = readPin(pin);
  //printf("test %d\n", test);
  //writePin( pin, 0 );
  edgeControl( pin, "rising" );
  struct pollfd fdset[1];

  for (;;)
  {
    fdset[0].fd = pinFD[pin];
    fdset[0].events = POLLPRI;
    fdset[0].revents = 0;

    int rc = poll( fdset, 1, -1 );
    if ( rc < 0 )
    {
      printf("\n poll() failed\n");
      return -1;
    }
    
    if ( rc == 0 )
    {
      printf(".");
    }
    
    if (fdset[0].revents & POLLPRI )
    {
      lseek( fdset[0].fd, 0, SEEK_SET );
      int val = readPin( pin );
      printf( "\npoll() GPIO%d interrupt occurred %d\n\r", pin, val );
      fflush(stdout);
    }
  }

  return 0;
}

void openPin( int pin, int direction )
{
  int len;
  char buf[MAX_BUFFER];

  if ( pinFD[pin] != 0 )
  {
    close( pinFD[pin] );
    pinFD[pin] = open( "/sys/class/gpio/unexport", O_WRONLY );
    len = snprintf( buf, MAX_BUFFER, "%d", pin );
    write( pinFD[pin], buf, len );
    close( pinFD[pin] );
    pinFD[pin] = 0;
  }

  pinFD[pin] = open( "/sys/class/gpio/export", O_WRONLY );
  len = snprintf( buf, MAX_BUFFER, "%d", pin );
  write( pinFD[pin], buf, len );
  close( pinFD[pin] );
  
  len = snprintf( buf, MAX_BUFFER, "/sys/class/gpio/gpio%d/direction", pin );
  pinFD[pin] = open( buf, O_WRONLY );
  if ( direction )
  {
    write( pinFD[pin], "out", 4 );
    close( pinFD[pin] );
    len = snprintf( buf, MAX_BUFFER, "/sys/class/gpio/gpio%d/value", pin );
    pinFD[pin] = open( buf, O_WRONLY );
  }
  else
  {
    write( pinFD[pin], "in", 3 );
    close( pinFD[pin] );
    len = snprintf( buf, MAX_BUFFER, "/sys/class/gpio/gpio%d/value", pin );
    pinFD[pin] = open( buf, O_WRONLY );
  }
}

void writePin( int pin, int value )
{
  if (value)
  {
    write(pinFD[pin], "1", 1);
  }
  
  else
  {
    write(pinFD[pin], "0", 1);
  }
}

int readPin( int pin )
{
  char value_str[3];
  int c = read( pinFD[pin], value_str, 3 );
  lseek( pinFD[pin], 0, SEEK_SET );

  if ( value_str[0] == '0' )
  {
    return 0;
  }
  
  else
  {
    return 1;
  }
}

void edgeControl( int pin, char *mode )
{
  char buf[MAX_BUFFER];
  int len = snprintf( buf, MAX_BUFFER, "/sys/class/gpio/gpio%d/edge", pin );
  int fd = open( buf, O_WRONLY );
  write( fd, mode, strlen( mode ) + 1 );
  close(fd);
}

