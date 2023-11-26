#include <stdio.h>
#include <stdlib.h>

#include "jakestering.h"
#include "lcd.h"

LCD *lcd;

int main( int argc, char **argv )
{
  setupIO();

  lcd = initLcd( 4, 20, 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10 );
  
  lcdClear( lcd );

  free( lcd );

  return 0;
}

