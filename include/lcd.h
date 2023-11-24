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

