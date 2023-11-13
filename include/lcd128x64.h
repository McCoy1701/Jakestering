#ifndef __LCD_128_X_64__
#define __LCD_128_X_64__

typedef struct _lcd128x64
{
  int RS;  // register select
  int RW;  // read/write
  int E;   // enable
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
} LCD128x64;

LCD128x64 initLcd( int RS, int RW, int E, int DB0, int DB1, int DB2, int DB3, int DB4, int DB5, int DB6, int DB7, int PSB, int RST );

void lcdData(  )

#endif

