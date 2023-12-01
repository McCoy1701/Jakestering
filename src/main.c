#include <stdio.h>
#include <stdlib.h>

#include "jakestering.h"
#include "lcd128x64.h"

LCD128 *lcd;

int main( int argc, char **argv )
{
  setupIO();
  lcd = initLcd128( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 );

  lcd128Puts( lcd, "The quick brown fox jumps over the lazy dog!" );

  free( lcd->newBuffer );
  free( lcd->current );
  free( lcd );
  return 0;
}

