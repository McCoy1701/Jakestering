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
  
  sendInstruction( lcd, 0b00000001 ); //clear screen

  sendInstruction( lcd, 0b10000000 ); //DDRAM last spot

  lcdPutChar( lcd, 'h' );

  sendInstruction( lcd, 0b11000000 ); //DDRAM last spot

  lcdPutChar( lcd, 'e' );
  
  sendInstruction( lcd, 0b10010100 ); //DDRAM last spot

  lcdPutChar( lcd, 'l' );
  
  sendInstruction( lcd, 0b11010100 ); //DDRAM last spot

  lcdPutChar( lcd, 'o' );
  
  return 0;
}

