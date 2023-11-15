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

  digitalWriteByte( 0b10101010, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b11110000, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b00001111, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b01010101, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b00111100, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b11000011, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b00011000, 0, 7 );
  delay( 1000 );
  
  digitalWriteByte( 0b01010101, 0, 7 );
  delay( 1000 );

  digitalWriteByte( 0b00000000, 0, 7 );

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

