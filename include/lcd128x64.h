#ifndef __LCD_128_X_64__
#define __LCD_128_X_64__

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

