/*
 * lcd128x64.c:
 *  Routines for interfacing with ST7920 lcd driver
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

#ifndef __LCD_128_X_64_H__
#define __LCD_128_X_64_H__

#include <stdint.h>

//Instruction set 1: Basic
#define LCD128_DISPLAY_CLEAR     0b00000001
#define LCD128_RETURN_HOME       0b00000010
#define LCD128_ENTRY_MODE        0b00000100
#define LCD128_DISPLAY_CONTROL   0b00001000
#define LCD128_CURSOR_DISPLAY    0b00010000
#define LCD128_FUNCTION_SET      0b00100000
#define LCD128_GCRAM_SET         0b01000000
#define LCD128_DDRAM_SET         0b10000000

#define LCD128_ID_ENTRY          0b00000010 //Increment/Decrement address 
#define LCD128_S_ENTRY           0b00000001 //Scroll screen 

#define LCD128_D_CONTROL         0b00000100 //Display on/off
#define LCD128_C_CONTROL         0b00000010 //Cursor on/off
#define LCD128_B_CONTROL         0b00000001 //Blink cursor on/off

#define LCD128_SC_CONTROL        0b00001000 //Screen/Cursor shift
#define LCD128_RL_CONTROL        0b00000100 //Right/Left

#define LCD128_DL_FUNCTION       0b00010000 //Data length
#define LCD128_RE_FUNCTION       0b00000100 //Extended function set

//Instruction set 2: Extended
#define LCD128_STAND_BY          0b00000001
#define LCD128_SCROLL_RAM        0b00000010
#define LCD128_REVERSE           0b00000100
#define LCD128_EXTENDED_FUNCTION 0b00100000
#define LCD128_SCROLL_ADDRESS    0b01000000
#define LCD128_GRAPHICS_DISPLAY  0b10000000

#define LCD128_G_FUNCTION        0b00000010 //Graphics on/off

#define LCD128_WIDTH  128
#define LCD128_HEIGHT  64

#define LCD128_PIXELS ( LCD128_WIDTH * ( LCD128_HEIGHT / 8 ) )

typedef struct _lcd128
{
  int  RS; // register select
  int  RW; // read/write
  int   E; // enable
  int DB0; // data lines 0-7
  int DB1;
  int DB2;
  int DB3;
  int DB4;
  int DB5;
  int DB6;
  int DB7;
  int PSB; // high is using parallel low is serial
  int RST; // reset

  int cx;
  int cy;

  int cols;
  int rows;

  uint16_t buffer [ LCD128_HEIGHT ][ LCD128_WIDTH / 8 ];
  uint16_t current[ LCD128_HEIGHT ][ LCD128_WIDTH / 8 ];

} LCD128;

LCD128 *initLcd128( int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7, int PSB, int RST );

void pulseEnable128( LCD128 *lcd );

void sendData128( LCD128 *lcd, const int data );

void sendInstruction128( LCD128 *lcd, const int instruction );


void setGraphicsMode( LCD128 *lcd );

void lcd128ClearGraphics( LCD128 *lcd );

void lcd128DrawPixel( LCD128 *lcd, int x, int y );

void lcd128ClearPixel( LCD128 *lcd, int x, int y );

void lcd128UpdateScreen( LCD128 *lcd );


void setTextMode( LCD128 *lcd );

void lcd128ClearText( LCD128 *lcd );

void lcd128CursorPosition( LCD128 *lcd, int x, int y );

void lcd128PutChar( LCD128 *lcd, unsigned char character );

void lcd128Puts( LCD128 *lcd, const char* string );

void lcd128Printf( LCD128 *lcd, const char *string, ... );

#endif

