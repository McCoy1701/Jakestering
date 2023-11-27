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
 */

void pulseEnable( LCD128x64 lcd )
{
  digitalWrite( lcd.E, HIGH );
  delayMicro( 1 );
  digitalWrite( lcd.E, LOW );
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
 */

void lcdSendData( LCD128x64 lcd, const int data )
{

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
 */

void lcdSendInstruction( LCD128x64 lcd, const int instruction )
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
 *  LCD128x64 that has been initialized
 */

LCD128x64 initLcd( int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7, int PSB, int RST )
{
  LCD128x64 lcd;

  lcd.RS  =  RS;
  lcd.RW  =  RW;
  lcd.E   =   E;
  lcd.DB0 = DB0;
  lcd.DB1 = DB1;
  lcd.DB2 = DB2;
  lcd.DB3 = DB3;
  lcd.DB4 = DB4;
  lcd.DB5 = DB5;
  lcd.DB6 = DB6;
  lcd.DB7 = DB7;
  lcd.PSB = PSB;
  lcd.RST = RST;

  pinMode( lcd.RS , OUTPUT );
  pinMode( lcd.RW , OUTPUT );
  pinMode( lcd.E  , OUTPUT );
  pinMode( lcd.DB0, OUTPUT );
  pinMode( lcd.DB1, OUTPUT );
  pinMode( lcd.DB2, OUTPUT );
  pinMode( lcd.DB3, OUTPUT );
  pinMode( lcd.DB4, OUTPUT );
  pinMode( lcd.DB5, OUTPUT );
  pinMode( lcd.DB6, OUTPUT );
  pinMode( lcd.DB7, OUTPUT );
  pinMode( lcd.PSB, OUTPUT );
  pinMode( lcd.RST, OUTPUT );

  digitalWrite( lcd.RS , HIGH );
  digitalWrite( lcd.RW , LOW  );
  digitalWrite( lcd.E  , LOW  );
  digitalWrite( lcd.PSB, HIGH );
  digitalWrite( lcd.RST, LOW  );

  

  return lcd;
}

