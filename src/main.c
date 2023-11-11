#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jakestering.h"

int main( int argc, char **argv )
{
  setupIO();
  
  for ( int i = 0; i < 4; i++ )
  {
    pinMode( i, INPUT );
  }
  
  for ( int i = 0; i < 4; i++ )
  {
    pudController( i, PUD_PULL_UP );
  }

  for ( int i = 4; i <= 12; i++ )
  {
    pinMode( i, OUTPUT );
  }

  for ( int i = 4; i <= 12; i++ )
  {
    digitalWrite( i, HIGH );
    msDelay( 500 );

  }

  for ( int i = 4; i <= 12; i++)
  {
    digitalWrite( i, LOW );
    msDelay( 500 );
  }

  return 0;
}

