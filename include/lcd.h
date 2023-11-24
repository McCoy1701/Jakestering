/*
 * lcd.h:
 *  Routines for interfacing with HD44780 lcd driver
 *
 * Copyright (c) 2023 Jacob Kellum
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

#define LCD_CLEAR        0b00000001
#define LCD_HOME         0b00000010
#define LCD_ENTRY        0b00000100
#define LCD_CONTROL      0b00001000
#define LCD_CURSOR_SHIFT 0b00010000
#define LCD_FUNCTION     0b00100000
#define LCD_CGRAM        0b01000000
#define LCD_DDRAM        0b10000000

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
} LCD;

LCD initLcd( int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7 );

void setupLcd( LCD lcd );

void pulseEnable( LCD lcd );

void sendData( LCD lcd, const int data );

void sendInstruction( LCD lcd, const int instruction );

void lcdPutChar( LCD lcd, unsigned char character );

void lcdPuts( LCD lcd, const char* string );

void lcdPrintf( LCD lcd, const char *string, ... );

#endif

