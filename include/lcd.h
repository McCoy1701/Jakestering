/*
 * lcd.h:
 *  Routines for interfacing with HD44780 lcd driver
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

#ifndef __LCD_H__
#define __LCD_H__

#define LCD_CLEAR        0b00000001  //Clear display
#define LCD_HOME         0b00000010  //Return home
#define LCD_ENTRY        0b00000100  //Set entry mode
#define LCD_CONTROL      0b00001000  //Display on/off control
#define LCD_CURSOR_SHIFT 0b00010000  //Cursor display shift
#define LCD_FUNCTION     0b00100000  //Function set
#define LCD_CGRAM        0b01000000  //Character generator ram
#define LCD_DDRAM        0b10000000  //Display data ram

/*
 * Entry mode parameters
 *  I/D: Increment or Decrement address registers
 *  S  : Accompanies display shift
 */

#define ID_ENTRY         0b00000010
#define S_ENTRY          0b00000001

/*
 * Display on/off control
 *  D: Display on/off
 *  C: Cursor on/off
 *  B: Cursor blinking on/off
 */

#define D_CONTROL        0b00000100
#define C_CONTROL        0b00000010
#define B_CONTROL        0b00000001

/*
 * Cursor or display shift
 *  S/C: Screen or cursor
 *  R/L: Right or left
 */

#define LCD_SC_SHIFT     0b00001000
#define LCD_RL_SHIFT     0b00000100

/*
 * Function set
 *  DL: Data length 1 = 8-bits | 0 = 4-bits
 *  N : Number of lines 1 = 2 lines | 0 = 1 line
 *  F : Font 1 = 5x10 font | 0 = 5x8 font
 */

#define DL_FUNC          0b00010000
#define N_FUNC           0b00001000
#define F_FUNC           0b00000100

typedef struct _lcd
{
  int RS;
  int RW;
  int E;
  int DB0;
  int DB1;
  int DB2;
  int DB3;
  int DB4;
  int DB5;
  int DB6;
  int DB7;
  int cx;
  int cy;
  int rows;
  int cols;
} LCD;

LCD* initLcd( int rows, int cols, int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7 );

void pulseEnable( LCD *lcd );

void sendData( LCD *lcd, const int data );

void sendInstruction( LCD *lcd, const int instruction );

void lcdPutChar( LCD *lcd, unsigned char character );

void lcdPuts( LCD *lcd, const char* string );

void lcdPrintf( LCD *lcd, const char *string, ... );

void lcdPosition( LCD *lcd, int x, int y );

void lcdClear( LCD *lcd );

void lcdDisplay( LCD *lcd, int value );

void lcdCursor( LCD *lcd, int value );

void lcdCursorBlink( LCD *lcd, int value );

#endif

