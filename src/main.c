/*
 * main.c:
 *  Entry Point for jakestering
 *
 * Copyright (c) 2023 Jacob Kellum <jkellum819@gmail.com>
 *************************************************************************
 * This file is apart of Jakestering:
 *    https://github.com/McCoy1701/Jakestering
 *
 * Jakestering is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Jakestering is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Jakestering; if not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "jakestering.h"
#include "lcd128x64.h"
#include "lcd.h"
#include "keypad.h"

LCD128 *lcd128;

LCD *lcd;

Keypad keypad;

int main( int argc, char **argv )
{
  setupIO();

/*  pinMode( 0, OUTPUT );
  pinMode( 2, OUTPUT );
  pinMode( 3, OUTPUT );
  pinMode( 4, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );
  pinMode( 8, OUTPUT );
  pinMode( 9, OUTPUT );
  pinMode( 10, OUTPUT );
  pinMode( 12, OUTPUT );

  digitalWrite( 0 , LOW );
  digitalWrite( 2 , LOW );
  digitalWrite( 3 , LOW );
  digitalWrite( 4 , LOW );
  digitalWrite( 5 , LOW );
  digitalWrite( 6 , LOW );
  digitalWrite( 7 , LOW );
  digitalWrite( 8 , LOW );
  digitalWrite( 9 , LOW );
  digitalWrite( 10 , LOW );
  digitalWrite( 12 , LOW );

  delay( 500 );
  digitalWrite( 0, HIGH );
  
  delay( 500 );
  digitalWrite( 2, HIGH );
  
  delay( 500 );
  digitalWrite( 3, HIGH );
  
  delay( 500 );
  digitalWrite( 4, HIGH );
  
  delay( 500 );
  digitalWrite( 5, HIGH );
  
  delay( 500 );
  digitalWrite( 6, HIGH );
  
  delay( 500 );
  digitalWrite( 7, HIGH );
  
  delay( 500 );
  digitalWrite( 8, HIGH );
  
  delay( 500 );
  digitalWrite( 9, HIGH );
  
  delay( 500 );
  digitalWrite( 10, HIGH );
  
  delay( 500 );
  digitalWrite( 12, HIGH );
*/
  lcd128 = initLcd128( 0, 2,  3, 4, 5, 6, 7, 8, 9, 10,  12 ); //Initalize the 128x64 lcd
  
  lcd = initLcd( 4, 20,  0, 13,  3, 4, 5, 6, 7, 8, 9, 10 ); //Initialize the 4x20 lcd

  keypad = initKeypad( 14, 15, 16, 17, 21, 20, 19, 18  );

  setGraphicsMode( lcd128 );

  lcd128ClearGraphics( lcd128 );

  lcd128DrawFilledCircle( lcd128, 20, 20, 15 ); 

  lcd128UpdateScreen( lcd128 );

  lcdClear( lcd );
  lcdPosition( lcd, 0, 0 );
  lcdPrintf( lcd, "Hello, World!" );

  while ( 1 )
  {
    char key = checkKeypad( keypad, 0 );
    if ( key != '\0' )
    {
      printf( "%c\n", key );

      lcdPosition( lcd, 0, 3 );
      
      lcdPrintf( lcd, "%c", key );
    }
  }

  free( lcd128 );
  free( lcd );
  
  return 0;
}

