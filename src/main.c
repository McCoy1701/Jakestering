#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jakestering.h"
#include "keypad.h"

Keypad keypad;

int main( int argc, char **argv )
{
  setupIO();

  keypad = initKeypad( 0, 1, 2, 3, 7, 6, 5, 4 );
  
  while ( 1 )
  {
    char key = checkKeypad( keypad, 0 );
    if ( key != '\0' )
    {
      printf( "key: %c\n", key );
    }
  }

  return 0;
}

