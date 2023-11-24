#include "lcd.h"
#include "jakestering.h"


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

  setupLcd( lcd );

  return lcd;
}

void pulseEnable( LCD lcd )
{
  digitalWrite( lcd.E, HIGH );
  delayMicro( 1 );
  digitalWrite( lcd.E, LOW  );
  delayMicro( 5 );
}

void sendData( LCD lcd, const int data )
{
  digitalWriteByte( data, lcd.DB0, lcd.DB7 );
  pulseEnable( lcd );
  delay( 2 );
}

void sendInstruction( LCD lcd, const int instruction )
{
  digitalWrite( lcd.RS, LOW  );
  sendData( lcd, instruction );
  digitalWrite( lcd.RS, HIGH );
}

void setupLcd( LCD lcd )
{
  sendInstruction( lcd, 0b00111000 ); //Set 8-bit operation, 2-line mode, 5x8 character font
  sendInstruction( lcd, 0b00001110 ); //Set display on, cursor on, cursor blinking on
  sendInstruction( lcd, 0b00000110 ); //Set entry mode, increment address
}

void lcdPutChar( LCD lcd, char character )
{
  sendData( lcd, character );
}

void lcdPrintf( LCD lcd, char *string, ... )
{
  while( *string )
  {
    lcdPutChar( lcd, *string++ );
  }
}

