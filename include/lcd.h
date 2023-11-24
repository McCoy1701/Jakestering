#ifndef __LCD_H__
#define __LCD_H__

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

void lcdPutChar( LCD lcd, char character );

void lcdPrintf( LCD lcd, char *string, ... );

#endif

