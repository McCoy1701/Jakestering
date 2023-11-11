#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jakestering.h"

int main( int argc, char **argv )
{
  setupIO();

  for ( int i = 0; i <= 12; i++ )
  {
    pinMode( i, OUTPUT );
  }
  
  while ( 1 )
  {
    for ( int i = 0; i <= 12; i++ )
    {
      digitalWrite( i, HIGH );
      msDelay( 100 );

    }

    for ( int i = 12; i >= 0; i--)
    {
      digitalWrite( i, LOW );
      msDelay( 100 );
    }
  }

  return 0;
}

