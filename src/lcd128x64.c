#include "jakestering.h"
#include "lcd128x64.h"


LCD128x64 initLcd( int RS, int RW, int E, int DB0, int DB7, int PSB, int RST )
{
  LCD128x64 lcd;

  lcd.RS  =  RS;
  lcd.RW  =  RW;
  lcd.E   =   E;
  lcd.PSB = PSB;
  lcd.RST = RST;
  
  int count = 0;
  
  for ( int i = DB0; i <= DB7; i++ )
  {
    lcd.DB[count] = i;
    count++;
  }
  
  pinMode( lcd.RS , OUTPUT );
  pinMode( lcd.RW , OUTPUT );
  pinMode( lcd.E  , OUTPUT );
  pinMode( lcd.PSB, OUTPUT );
  pinMode( lcd.RST, OUTPUT );

  for ( int i = 0; i < 8; i++ )
  {
    pinMode( lcd.DB[i], OUTPUT );
  }

  digitalWrite( lcd.RS , HIGH );
  digitalWrite( lcd.RW , LOW  );
  digitalWrite( lcd.E  , LOW  );
  digitalWrite( lcd.PSB, HIGH );
  digitalWrite( lcd.RST, LOW  );

  for ( int i = 0; i < 8; i++ )
  {
    digitalWrite( lcd.DB[i], LOW );
  }
  
  return lcd;
}

void lcdSetup( LCD128x64 lcd )
{
  
}

void lcdSendData( const int value )
{

}

void lcdSendInstruction( const int value )
{

}

void pulseEnable( LCD128x64 lcd )
{
  digitalWrite( lcd.E, HIGH );
  delayMicro( 1 );
  digitalWrite( lcd.E, LOW );
  delayMicro( 5 );
}

