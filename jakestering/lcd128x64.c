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
#include <string.h>
#include <math.h>

#include "jakestering.h"
#include "lcd128x64.h"

static const int rowsOffset[4] = { 0x80, 0x90, 0x88, 0x98 };

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
  delayMicro( 72 );
  digitalWriteByte( data, lcd->DB0, lcd->DB7 );
  pulseEnable128( lcd );
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
  lcd->cx = 0;
  lcd->cy = 0;
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
  if ( ( x > lcd->cols ) || ( x < 0 ) )
  {
    return;
  }

  if ( ( y > lcd->rows ) || ( y < 0 ) )
  {
    return;
  }

  sendInstruction128( lcd, x + ( LCD128_DDRAM_SET | rowsOffset[ y ] ) );

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

void lcd128PutChar( LCD128 *lcd, unsigned char character, int byte )
{
  if( byte ) sendData128( lcd, 0x20 );
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

void lcd128Puts( LCD128 *lcd, const char* string, int byte )
{
  while ( *string )
  {
    lcd128PutChar( lcd, *string++, byte );
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

void lcd128Printf( LCD128 *lcd, int byte, const char *string, ... )
{
  char buffer[ 1024 ];
  va_list args;

  va_start( args, string );
  vsnprintf( buffer, sizeof( buffer ), string, args );
  va_end( args );

  lcd128Puts( lcd, buffer, byte );
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
  if ( ( x < LCD128_WIDTH && x >= 0 ) || ( y < LCD128_HEIGHT && y >= 0 ) )
  {
    lcd->buffer[ y ][ x / 16 ] |= ( 1 << ( 15 - ( x % 16 ) ) );
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
  if ( ( x < LCD128_WIDTH && x > 0 ) || ( y < LCD128_HEIGHT && y > 0 ) )
  {
    lcd->buffer[ y ][ x / 16 ] &= ~( 0x01 << ( 15 - ( y % 16 ) ) );
  }
}

/*
 * Draw a line between two points
 *
 * Parameters:
 *  x1: first x position
 *  y1: first y position
 *  x2: second x position
 *  y2: second y position
 *  
 * Return:
 *  void
 **************************************************************
 */

void lcd128DrawLine( LCD128 *lcd, int x1, int y1, int x2, int y2 )
{
  int deltaX =  abs( x2 - x1 ), screenX = x1 < x2 ? 1 : -1;
  int deltaY = -abs( y2 - y1 ), screenY = y1 < y2 ? 1 : -1;
  int error = deltaX + deltaY;
  int error2;

  while ( 1 )
  {
    lcd128DrawPixel( lcd, x1, y1 );
    
    if ( x1 == x2 && y1 == y2 ) break;
    
    error2 = 2 * error;
    
    if ( error2 >= deltaY )
    { 
      error += deltaY;
      x1 += screenX;
    }

    if ( error2 <= deltaX )
    {
      error += deltaX;
      y1 += screenY;
    }
  }
}

/*
 * Draws a rect to the screen at the given point with the given width and height
 *
 * Parameters:
 *  lcd   : Holds screen frame buffer
 *  x     : Horizontal position
 *  y     : Vertical position
 *  width : 
 *  height:
 *
 * Remove:
 *  void
 **************************************************************
 */

void lcd128DrawRect(LCD128 *lcd, int x, int y, int width, int height )
{
  lcd128DrawLine( lcd, x, y, width, y );
  lcd128DrawLine( lcd, width, y, width, height );
  lcd128DrawLine( lcd, width, height, x, height );
  lcd128DrawLine( lcd, x, height, x, y );
}

/*
 * Draws a filled rect to the screen at the given point with the given width and height
 *
 * Parameters:
 *  lcd   : Holds screen frame buffer
 *  x     : Horizontal position
 *  y     : Vertical position
 *  width : 
 *  height:
 *
 * Remove:
 *  void
 **************************************************************
 */

void lcd128DrawFilledRect(LCD128 *lcd, int x, int y, int width, int height )
{
  for ( int i = x; i <= width; i++ )
  {
    lcd128DrawLine( lcd, i, y, i, height );
  }
}

/*
 * Internal circle draw routine
 *
 * Parameters:
 *  xc: center x position
 *  yc: center y position
 *  x : offset
 *  y : offset
 *
 * Return:
 *  void
 **************************************************************
 */

void circleInternal( LCD128 *lcd, int xc, int yc, int x, int y )
{
  lcd128DrawPixel( lcd, xc + x, yc + y );
  lcd128DrawPixel( lcd, xc + x, yc - y );
  lcd128DrawPixel( lcd, xc - x, yc + y );
  lcd128DrawPixel( lcd, xc - x, yc - y );
  lcd128DrawPixel( lcd, xc + y, yc + x );
  lcd128DrawPixel( lcd, xc + y, yc - x );
  lcd128DrawPixel( lcd, xc - y, yc + x );
  lcd128DrawPixel( lcd, xc - y, yc - x );
}

/*
 * Draw a circle at given x, y with given radius using bresenham's circle algorithm
 *
 * Parameters:
 *  xc: center x position
 *  xy: center y position
 *  r : radius
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128DrawCircle( LCD128 *lcd, int xc, int yc, int r )
{
  int x = 0;
  int y = r;
  int decision = 5 - ( 4 * r );

  while ( x <= y )
  {
    circleInternal( lcd, xc, yc, x, y );
    if ( decision > 0 )
    {
      y--;
      decision -= 8 *  y;
    }

    x++;
    
    decision += 8 * x + 4;
  }
}

/*
 * Draw a circle at given x, y with given radius using bresenham's circle algorithm
 *
 * Parameters:
 *  xc: center x position
 *  xy: center y position
 *  r : radius
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128DrawFilledCircle( LCD128 *lcd, int xc, int yc, int r )
{
  int x = 0;
  int y = r;
  int decision = 5 - ( 4 * r );

  while ( x <= y )
  {
    lcd128DrawLine( lcd, xc - x, yc - y, xc + x, yc - y );
    lcd128DrawLine( lcd, xc - y, yc - x, xc + y, yc - x );
    lcd128DrawLine( lcd, xc - y, yc + x, xc + y, yc + x );
    lcd128DrawLine( lcd, xc - x, yc + y, xc + x, yc + y );

    if ( decision > 0 )
    {
      y--;
      decision -= 8 *  y;
    }

    x++;
    
    decision += 8 * x + 4;
  }
}

/*
 * Draw a triganle at given coordinates 
 *
 * Parameters:
 * x1: first point x
 * y1: first point y
 * x2: second point x
 * y2: second point y
 * x3: third point x
 * x3: third point y
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128DrawTriangle( LCD128 *lcd, int x1, int y1, int x2, int y2, int x3, int y3 )
{
  lcd128DrawLine( lcd, x1, y1, x2, y2 );
  lcd128DrawLine( lcd, x2, y2, x3, y3 );
  lcd128DrawLine( lcd, x3, y3, x1, y1 );
}

/*
 * Draw a triganle at given coordinates 
 *
 * Parameters:
 * x1: first point x
 * y1: first point y
 * x2: second point x
 * y2: second point y
 * x3: third point x
 * x3: third point y
 *
 * Return:
 *  void
 **************************************************************
 */

void lcd128DrawFilledTriangle( LCD128 *lcd, int x1, int y1, int x2, int y2, int x3, int y3 )
{
 int maxX = MAX( x1, MAX( x2, x3 ) );
 int minX = MIN( x1, MIN( x2, x3 ) );
 int maxY = MAX( y1, MAX( y2, y3 ) );
 int minY = MIN( y1, MIN( y2, y3 ) );

 int vx1 = x2 - x1;
 int vy1 = y2 - y1;

 int vx2 = x3 - x1;
 int vy2 = y3 - y1;

 for ( int x = minX; x <= maxX; x++ )
 {
    for ( int y = minY; y <= maxY; y++)
    {
      int qx = x - x1;
      int qy = y - y1;

      float s = (float)( ( qx * vy2 ) - ( qy * vx2 ) ) / ( ( vx1 * vy2 ) - ( vy1 * vx2 ) );
      float t = (float)( ( vx1 * qy ) - ( vy1 * qx ) ) / ( ( vx1 * vy2 ) - ( vy1 * vx2 ) );

      if ( ( s >= 0 ) && ( t >= 0 ) && ( s + t <= 1 ) )
      {
        lcd128DrawPixel( lcd, x, y );
      }
    }
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
  uint8_t temp, dataBit;

  if ( memcmp( lcd->current, lcd->buffer, sizeof( lcd->buffer ) ) != 0 )
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
        temp = lcd->buffer[ y ][ x ] >> 8;
        sendData128( lcd, temp );
        temp = lcd->buffer[ y ][ x ];
        sendData128( lcd, temp );
      }
    }

    memcpy( lcd->current, lcd->buffer, sizeof( lcd->current ) );
    memset( lcd->buffer, 0, sizeof( lcd->buffer ) );
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

LCD128 *initLcd128( int RS, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7, int RST )
{
  LCD128 *lcd = ( LCD128* )malloc( sizeof( LCD128 ) );

  lcd->RS  =  RS;
  lcd->E   =   E;
  lcd->DB0 = DB0;
  lcd->DB1 = DB1;
  lcd->DB2 = DB2;
  lcd->DB3 = DB3;
  lcd->DB4 = DB4;
  lcd->DB5 = DB5;
  lcd->DB6 = DB6;
  lcd->DB7 = DB7;
  lcd->RST = RST;
  
  lcd->cols = 16;
  lcd->rows = 4;

  lcd->cx = 0;
  lcd->cy = 0;

  pinMode( lcd->RS , OUTPUT );
  pinMode( lcd->E  , OUTPUT );
  pinMode( lcd->DB0, OUTPUT );
  pinMode( lcd->DB1, OUTPUT );
  pinMode( lcd->DB2, OUTPUT );
  pinMode( lcd->DB3, OUTPUT );
  pinMode( lcd->DB4, OUTPUT );
  pinMode( lcd->DB5, OUTPUT );
  pinMode( lcd->DB6, OUTPUT );
  pinMode( lcd->DB7, OUTPUT );
  pinMode( lcd->RST, OUTPUT );

  digitalWrite( lcd->RS , HIGH );
  digitalWrite( lcd->E  , LOW  );
  digitalWrite( lcd->RST, HIGH  );

  delay( 10 );                      //Reset lcd active low
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

