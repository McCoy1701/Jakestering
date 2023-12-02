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

#include "jakestering.h"
#include "lcd128x64.h"

LCD128 *lcd;

uint16_t array[64][16] = { 0 };

uint8_t temp;

int main( int argc, char **argv )
{
  setupIO();

  lcd = initLcd128( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10, 11, 12 );

  setGraphicsMode( lcd );

  lcd128ClearGraphics( lcd );

  for ( int y = 0; y < 64; y++ )
  {
    for ( int x = 0; x < 16; x++ )
    {
      lcd->buffer[y][x] = 0xFFFF;
    }
  }
  
  /*for ( int y = 0; y < 64; y++ )
  {
    if ( y < 32 )
    {
      sendInstruction128( lcd, 0x80 | y );
      sendInstruction128( lcd, 0x80 );
    }

    else
    {
      sendInstruction128( lcd, 0x80 | y - 32 );
      sendInstruction128( lcd, 0x88 );
    }

    for ( int x = 0; x < 8; x++ )
    {
      temp = array[ y ][ x ] >> 8;
      sendData128( lcd, temp );
      temp = array[ y ][ x ];
      sendData128( lcd, temp );
    }
  }

    sendInstruction128( lcd, 0x80 );
    sendInstruction128( lcd, 0x80 );
    
    for ( int x = 0; x < 8; x++ )
    {
      temp = array[ 0 ][ x ] >> 8;
      sendData128( lcd, temp );
      temp = array[ 0 ][ x ];
      sendData128( lcd, temp );
    }*/
  return 0;
}

