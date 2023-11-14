#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jakestering.h"
#include "keypad.h"

Keypad keypad;

int main( int argc, char **argv )
{
  setupIO();

  for ( int i = 0; i < 13; i++ )
  {
    pinMode( i , OUTPUT );
  }

  digitalWriteByte( 0x80, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x40, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x20, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x10, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x08, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x04, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x02, 4, 11 );
  sleep( 1 );
  
  digitalWriteByte( 0x01, 4, 11 );
  sleep( 1 );

  digitalWriteByte( 0x00, 4, 11 );
  sleep( 1 );

/*  keypad = initKeypad( 0, 1, 2, 3, 7, 6, 5, 4 );
  
  while ( 1 )
  {
    char key = checkKeypad( keypad, 0 );
    if ( key != '\0' )
    {
      printf( "key: %c\n", key );
    }
  }*/

  return 0;
}

