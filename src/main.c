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

  lcd128 = initLcd128( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10,  11, 12 ); //Initalize the 128x64 lcd
  
  lcd = initLcd( 4, 20,  0, 1, 13,  3, 4, 5, 6, 7, 8, 9, 10 ); //Initialize the 4x20 lcd

  keypad = initKeypad( 14, 15, 17, 16, 20, 21, 19, 18 );

  setGraphicsMode( lcd128 );

  lcd128ClearGraphics( lcd128 );

  lcd128DrawFilledRect( lcd128, 0, 0, 20, 50 ); 

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

      //lcdPosition( lcd, 3, 0 );
      
      //lcdPrintf( lcd, "%c\n", key );
    }
  }

  free( lcd );
  free( lcd128 );
  
  return 0;
}

