#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jakestering.h"
#include "lcd.h"

LCD lcd;

int main( int argc, char **argv )
{
  setupIO();

  lcd = initLcd( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10 );
  
  sendInstruction( lcd, 0b00000001 );

  lcdPrintf(lcd, "holy shit, %d, %d", 10, 11);

  return 0;
}

