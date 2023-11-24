/*
 * lcd128x64.c:
 *  Routines for interfacing with ST7920 lcd driver
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

#ifndef __LCD_128_X_64_H__
#define __LCD_128_X_64_H__

typedef struct _lcd128x64
{
  int RS;  // register select
  int RW;  // read/write
  int E;   // enable
  int DB[8] = { 0 }; // data lines 0-7
  int PSB; // high is using parallel low is serial
  int RST; // reset
} LCD128x64;

LCD128x64 initLcd( int RS, int RW, int E, int DB0, int DB7, int PSB, int RST );

void lcdSetup( LCD128x64 lcd );

void lcdSendData( const int value );

void lcdSendInstruction( const int value );

void pulseEnable( LCD128x64 lcd );

#endif

