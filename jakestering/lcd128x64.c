/*
 * lcd128x64.c:
 *  Interface for ST7920 lcd driver
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

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "jakestering.h"
#include "lcd128x64.h"

/*
 * Pulse the enable line 
 *
 * Parameters:
 *  lcd: which lcd to enable
 *
 * Return:
 *  void
 **************************************************************
 */

void pulseEnable128( LCD128 *lcd )
{
  digitalWrite( lcd->E, HIGH );
  delayMicro( 1 );
  digitalWrite( lcd->E, LOW );
  delayMicro( 5 );
}

/*
 * Send data to the lcd
 *
 * Parameters:
 *  lcd : which lcd to receive the data
 *  data: data to be sent
 *
 * Return:
 *  void
 **************************************************************
 */

void sendData128( LCD128 *lcd, const int data )
{
  digitalWriteByte( data, lcd->DB0, lcd->DB7 );
  pulseEnable( lcd );
  delay( 2 );
}

/*
 * Send instruction to the lcd
 *
 * Parameters:
 *  lcd        : which lcd to receive the instruction
 *  instruction: instruction to be sent 
 *
 * Return:
 *  void
 **************************************************************
 */

void sendInstruction128( LCD128 *lcd, const int instruction )
{
  digitalWrite( lcd->RS, LOW  );
  sendData( lcd, instruction );
  digitalWrite( lcd->RS, HIGH );
}

/*
 * Set lcd to Text mode
 *
 * Parameters:
 *  lcd: to set text mode
 *
 * Return:
 *  void
 **************************************************************
 */

void setTextMode( LCD128 *lcd )
{
  sendInstruction( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION );
  lcdClear( lcd );
}

/*
 * Set lcd to graphics mode
 *
 * Parameters:
 *  lcd: to set graphics mode
 *
 * Return:
 *  void
 **************************************************************
 */

void setGraphicsMode( LCD128 *lcd )
{
  sendInstruction( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION | LCD128_RE_FUNCTION );
  sendInstruction( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION | LCD128_RE_FUNCTION | LCD128_G_FUNCTION );
  delay( 5 );
}

/*
 * Set the pixel at x, y
 *
 * Parameters:
 *  lcd: holds the pixel info
 *  x  : horizontal position
 *  y  : vertical position
 *
 * Return:
 *  void
 **************************************************************
 */

void lcdGraphicsPosition( LCD128 *lcd, int x, int y )
{

}

/*
 * Update the lcd with contents of buffer
 *
 * Parameters:
 *  lcd   : holds the cursor info
 *  buffer: 128 x 64 array with the new contents of the screen
 *
 * Return:
 *  void
 **************************************************************
 */

void lcdUpdateScreen( LCD128 *lcd )
{

}

/*
 * Initialize the lcd
 *
 * Parameters:
 *  RS   : register select
 *  RW   : read/write
 *  E    : enable
 *  DB0-7: data lines
 *  PSB  : interface selection 1 for 8-bit parallel
 *  RST  : reset
 *
 * Return:
 *  LCD128 that has been initialized
 **************************************************************
 */

LCD128 *initLcd128( int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7, int PSB, int RST )
{
  LCD128 *lcd = ( LCD128* )malloc( sizeof( LCD128 ) );

  lcd->RS  =  RS;
  lcd->RW  =  RW;
  lcd->E   =   E;
  lcd->DB0 = DB0;
  lcd->DB1 = DB1;
  lcd->DB2 = DB2;
  lcd->DB3 = DB3;
  lcd->DB4 = DB4;
  lcd->DB5 = DB5;
  lcd->DB6 = DB6;
  lcd->DB7 = DB7;
  lcd->PSB = PSB;
  lcd->RST = RST;

  lcd->cx = 0;
  lcd->cy = 0;

  lcd->newBuffer = ( Buffer* )malloc( sizeof( Buffer ) );
  lcd->current   = ( Buffer* )malloc( sizeof( Buffer ) );

  pinMode( lcd->RS , OUTPUT );
  pinMode( lcd->RW , OUTPUT );
  pinMode( lcd->E  , OUTPUT );
  pinMode( lcd->DB0, OUTPUT );
  pinMode( lcd->DB1, OUTPUT );
  pinMode( lcd->DB2, OUTPUT );
  pinMode( lcd->DB3, OUTPUT );
  pinMode( lcd->DB4, OUTPUT );
  pinMode( lcd->DB5, OUTPUT );
  pinMode( lcd->DB6, OUTPUT );
  pinMode( lcd->DB7, OUTPUT );
  pinMode( lcd->PSB, OUTPUT );
  pinMode( lcd->RST, OUTPUT );

  digitalWrite( lcd->RS , HIGH );
  digitalWrite( lcd->RW , LOW  );
  digitalWrite( lcd->E  , LOW  );
  digitalWrite( lcd->PSB, HIGH );
  digitalWrite( lcd->RST, LOW  );

  delay( 10 );
  digitalWrite( lcd->RST, HIGH );
  delay( 10 );
  digitalWrite( lcd->RST, LOW );
  delay( 50 );

  sendInstruction( lcd, 0b00110000 );
  sendInstruction( lcd, 0b00110000 );
  sendInstruction( lcd, 0b00001100 );
  sendInstruction( lcd, 0b00110000 );
  sendInstruction( lcd, 0b00110100 );
  sendInstruction( lcd, 0b00110110 );
  delay( 10 );

  sendInstruction( lcd, 0b10000000 );
  sendInstruction( lcd, 0b10000000 );

  sendData( lcd, 0b11111111 );
  sendData( lcd, 0b11111111 );

  return lcd;
}

