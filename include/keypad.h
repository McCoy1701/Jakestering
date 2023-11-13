#ifndef __KEYPAD_H__
#define __KEYPAD_H__

typedef struct _keypad
{
  int COLS[ 4 ];
  int ROWS[ 4 ];
} Keypad;

Keypad initKeypad( int c0, int c1, int c2, int c3, int r0, int r1, int r2, int r3 );

char checkKeypad( Keypad kp, int pageNumber );

#endif

