#include "keypad.h"
#include "jakestering.h"

Keypad initKeypad( int row, int col, int c0, int c1, int c2, int c3, int r0, int r1, int r2, int r3 )
{
  Keypad kp;
  kp.ROW = row;
  kp.COL = col;

  kp.COLS[ 0 ] = c0;
  kp.COLS[ 1 ] = c1;
  kp.COLS[ 2 ] = c2;
  kp.COLS[ 3 ] = c3;

  kp.ROWS[ 0 ] = r0;
  kp.ROWS[ 1 ] = r1;
  kp.ROWS[ 2 ] = r2;
  kp.ROWS[ 3 ] = r3;
  
  for ( int i = 0; i < kp.ROW; i++ )
  {
    pinMode( kp.COLS[ i ], INPUT );
    pudController( kp.COLS[ i ], PUD_UP );
  }

  for ( int i = 0; i < kp.COL; i++ )
  {
    pinMode( kp.ROWS[ i ], OUTPUT );
    digitalWrite( kp.ROWS[ i ], HIGH );
  }

  return kp;
}

char checkKeypad( Keypad kp, char keypadTable[ 4 ][ 4 ] )
{
  for ( int i = kp.ROW; i >= 0; i--  )
  {
    digitalWrite( kp.ROWS[ i ], LOW );
    
    for ( int j = 0; j < kp.COL; i++ )
    {
    
      if ( digitalRead( kp.COLS[ j ] ) == 0 )
      {
      
        digitalWrite( kp.ROWS[ i ], HIGH );
        delay( 250 );
        return keypadTable[ i ][ j ];
      }
    }

    digitalWrite( kp.ROWS[ i ], HIGH );
  }
  return '\0';
}

