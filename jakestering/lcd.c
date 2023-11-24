/*
 * lcd.c:
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

#include <stdarg.h>
#include <stdio.h>

#include "lcd.h"
#include "jakestering.h"

/* 
 * Pulse the enable line
 *
 * Parameters:
 *  lcd: lcd to enable
 * 
 * Return:
 *  void
 **************************************************************
 */

void pulseEnable( LCD lcd )
{
  digitalWrite( lcd.E, HIGH );
  delayMicro( 1 );
  digitalWrite( lcd.E, LOW  );
  delayMicro( 5 );
}

/* 
 * Send a byte of data out to the lcd
 *
 * Parameters:
 *  lcd: lcd to receive data
 *  data: the byte to be sent
 * 
 * Return:
 *  void
 **************************************************************
 */

void sendData( LCD lcd, const int data )
{
  digitalWriteByte( data, lcd.DB0, lcd.DB7 );
  pulseEnable( lcd );
  delay( 2 );
}

/* 
 * Send an instruction to the lcd. Register select is set high for sending data
 * must be set low to send instruction.
 *
 * Parameters:
 *  lcd: lcd to receive instruction
 *  instruction: byte to send
 * 
 * Return:
 *  void
 **************************************************************
 */

void sendInstruction( LCD lcd, const int instruction )
{
  digitalWrite( lcd.RS, LOW  );
  sendData( lcd, instruction );
  digitalWrite( lcd.RS, HIGH );
}

/* 
 * Initialize the lcd
 *
 * Parameters:
 *  RS    : register select
 *  RW    : read/write
 *  E     : enable
 *  DB0-7 : data lines
 * 
 * Return:
 *  LCD : that has been initialized
 **************************************************************
 */

LCD initLcd( int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7 )
{
  LCD lcd;
  
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

  digitalWrite( lcd.RS, HIGH );
  digitalWrite( lcd.RW, LOW  );
  digitalWrite( lcd.E , LOW  );

  sendInstruction( lcd, 0b00111000 ); //Set 8-bit operation, 2-line mode, 5x8 character font
  sendInstruction( lcd, 0b00001111 ); //Set display on, cursor on, cursor blinking off
  sendInstruction( lcd, 0b00000110 ); //Set entry mode, increment address

  return lcd;
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

void lcdPutChar( LCD lcd, unsigned char character )
{
  sendData( lcd, character );
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

void lcdPuts( LCD lcd, const char* string )
{
  while( *string )
  {
    lcdPutChar( lcd, *string++ );
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

void lcdPrintf( LCD lcd, const char *string, ... )
{
  char buffer[ 1024 ];
  va_list args;

  va_start( args, string );
    vsnprintf( buffer, sizeof( buffer ), string, args );
  va_end( args );
  
  lcdPuts( lcd, buffer );
}

