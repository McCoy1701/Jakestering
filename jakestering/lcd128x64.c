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

static const int rowsOffset[4] = { 0x80, 0x90, 0x88, 0x98 };

uint8_t current[ LCD128_PIXELS ] = { 0 };

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
  pulseEnable128( lcd );
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
  sendData128( lcd, instruction );
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
  sendInstruction128( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION );
  sendInstruction128( lcd, LCD128_DISPLAY_CLEAR );
  sendInstruction128( lcd, LCD128_RETURN_HOME );
  delay( 5 );
}

/*
 * Clears the lcd
 *
 * Parameters:
 *  lcd: screen to clear
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128ClearText( LCD128 *lcd )
{
  sendInstruction128( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION );
  sendInstruction128( lcd, 0x01 );
  delay( 2 );
  sendInstruction128( lcd, 0x02 );
  lcd->cx = 0;
  lcd->cy = 0;
  delay( 5 );
}

/*
 * Move the cursor
 *
 * Parameters:
 *  x: move horizontally this amount
 *  y: move vertically this amount
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128CursorPosition( LCD128 *lcd, int x, int y )
{
  sendInstruction128( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION );
  
  if ( ( x > lcd->cols ) || ( x < 0 ) )
  {
    return;
  }

  if ( ( y > lcd->rows ) || ( y < 0 ) )
  {
    return;
  }

  sendInstruction128( lcd, x + ( LCD128_DDRAM_SET | rowsOffset[y] ) );

  lcd->cx = x;
  lcd->cy = y;
}

/* 
 * Print a char to the lcd
 *
 * Parameters:
 *  lcd      : lcd to print to  
 *  character: char
 *  
 * Return:
 *  void
 **************************************************************
 */

void lcd128PutChar( LCD128 *lcd, unsigned char character )
{
  sendData128( lcd, character );
  
  if ( ++lcd->cx == lcd->cols )
  {
    lcd->cx = 0;
    
    if ( ++lcd->cy == lcd->rows )
    {
      lcd->cy = 0;
    }

    lcd128CursorPosition( lcd, lcd->cx, lcd->cy );
  }
}

/* 
 * Print a string to the lcd
 *
 * Parameters:
 *  lcd   : lcd to print to  
 *  string: string
 *  
 * Return:
 *  void
 **************************************************************
 */

void lcd128Puts( LCD128 *lcd, const char* string )
{
  while ( *string )
  {
    lcd128PutChar( lcd, *string++ );
  }
}

/* 
 * Print a formated string to the lcd
 *
 * Parameters:
 *  lcd   : lcd to print to  
 *  string: formated string
 *  
 * Return:
 *  void
 **************************************************************
 */

void lcd128Printf( LCD128 *lcd, const char *string, ... )
{
  char buffer[ 1024 ];
  va_list args;

  va_start( args, string );
  vsnprintf( buffer, sizeof( buffer ), string, args );
  va_end( args );

  lcd128Puts( lcd, buffer );
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
  sendInstruction128( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION | LCD128_RE_FUNCTION );
  sendInstruction128( lcd, LCD128_FUNCTION_SET | LCD128_DL_FUNCTION | LCD128_RE_FUNCTION | LCD128_G_FUNCTION );
  delay( 5 );
}

/*
 * Clear the graphics buffer
 *
 * Parameters:
 *  lcd: pointer to screen buffer
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128ClearGraphics( LCD128 *lcd )
{
  for ( uint8_t y = 0; y < 64; y++ )
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

    for ( uint8_t x = 0; x < 8; x++ )
    {
      sendData128( lcd, 0x00 );
      sendData128( lcd, 0x00 );
    }
  }
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

void lcd128DrawPixel( LCD128 *lcd, int x, int y )
{
  if ( x < LCD128_WIDTH && y < LCD128_HEIGHT )
  {
    lcd->current[ ( ( x ) + ( ( y / 8 ) * 128 ) ) ] |= 0x01 << y % 8;
  }
}

/*
 * Clear the pixel at x, y
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

void lcd128ClearPixel( LCD128 *lcd, int x, int y )
{
  if ( x < LCD128_WIDTH && y < LCD128_HEIGHT )
  {
    lcd->current[ ( ( x ) + ( ( y / 8 ) * 128 ) ) ] &= 0xFE << y % 8;
  }
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

void lcd128UpdateScreen( LCD128 *lcd )
{
  uint16_t index = 0;
  uint8_t temp, dataBit;

  for ( uint8_t y = 0; y < 64; y++ )
  {
    for ( uint8_t x = 0; x < 8; x++ )
    {
      if ( y < 32 )
      {
        sendInstruction128( lcd, 0x80 | y );
        sendInstruction128( lcd, 0x80 | x );
      }

      else
      {
        sendInstruction128( lcd, 0x80 | y - 32 );
        sendInstruction128( lcd, 0x88 | x );
      }

      index = (((y / 8) * 128 ) + ( x * 16));
      dataBit = y % 8;

      temp = ( ( (lcd->current[ index     ] >> dataBit ) & 0x01 ) << 7 ) | ( ( (lcd->current[ index + 1 ] >> dataBit ) & 0x01 ) << 6 ) |
             ( ( (lcd->current[ index + 2 ] >> dataBit ) & 0x01 ) << 5 ) | ( ( (lcd->current[ index + 3 ] >> dataBit ) & 0x01 ) << 4 ) |
             ( ( (lcd->current[ index + 4 ] >> dataBit ) & 0x01 ) << 3 ) | ( ( (lcd->current[ index + 5 ] >> dataBit ) & 0x01 ) << 2 ) |
             ( ( (lcd->current[ index + 6 ] >> dataBit ) & 0x01 ) << 1 ) | ( ( (lcd->current[ index + 7 ] >> dataBit ) & 0x01 ) << 0 );

      sendData128( lcd, temp );
      
      temp = ( ( (lcd->current[ index +  8 ] >> dataBit ) & 0x01 ) << 7 ) | ( ( (lcd->current[ index +  9 ] >> dataBit ) & 0x01 ) << 6 ) |
             ( ( (lcd->current[ index + 10 ] >> dataBit ) & 0x01 ) << 5 ) | ( ( (lcd->current[ index + 11 ] >> dataBit ) & 0x01 ) << 4 ) |
             ( ( (lcd->current[ index + 12 ] >> dataBit ) & 0x01 ) << 3 ) | ( ( (lcd->current[ index + 13 ] >> dataBit ) & 0x01 ) << 2 ) |
             ( ( (lcd->current[ index + 14 ] >> dataBit ) & 0x01 ) << 1 ) | ( ( (lcd->current[ index + 15 ] >> dataBit ) & 0x01 ) << 0 );
      
      sendData128( lcd, temp );
    }
  }
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
  
  lcd->cols = 16;
  lcd->rows = 4;

  lcd->cx = 0;
  lcd->cy = 0;

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
  digitalWrite( lcd->RST, HIGH  );

  delay( 10 );
  digitalWrite( lcd->RST, LOW );
  delay( 10 );
  digitalWrite( lcd->RST, HIGH );
  delay( 50 );
  
  sendInstruction128( lcd, 0x30 ); //Function Set 
  sendInstruction128( lcd, 0x0C ); //Display Control
  sendInstruction128( lcd, 0x06 ); //Entry Mode
  sendInstruction128( lcd, 0x01 ); //Clear

  delay( 2 );

  return lcd;
}

