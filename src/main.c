#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "jakestering.h"
#include "lcd128x64.h"

LCD128 *lcd;

int main( int argc, char **argv )
{
  setupIO();
  lcd = initLcd128( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 );

  setGraphicsMode( lcd );

  lcd128ClearGraphics( lcd );
  
  delay( 1000 );

  for ( int x = 0; x < 128; x++ )
  {
    for ( int y = 0; y < 64; y++ )
    {
      if ( x == y )
      {
        lcd128DrawPixel( lcd, 128 - x, 64 - y );
        lcd128DrawPixel( lcd, x, y );
      }
    }
  }

  lcd128UpdateScreen( lcd );

  free( lcd );
  return 0;
}

