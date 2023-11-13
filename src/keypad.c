#include "keypad.h"
#include "jakestering.h"

char keypadTablePage0[ 4 ][ 4 ] = 
{
  'C', 'D', 'E', 'F',
  '8', '9', 'A', 'B',
  '4', '5', '6', '7',
  '0', '1', '2', '3',
};

char keypadTablePage1[ 4 ][ 4 ] = 
{
  'A', 'B', 'C', 'D',
  'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L',
  'M', 'N', 'O', 'P',
};

char keypadTablePage2[ 4 ][ 4 ] = 
{
  'Q', 'R', 'S', 'T',
  'U', 'V', 'W', 'X',
  'Y', 'Z', ';', ':',
  '.', ' ', '&', '|',
};

Keypad initKeypad( int c0, int c1, int c2, int c3, int r0, int r1, int r2, int r3 )
{
  Keypad kp;

  kp.COLS[ 0 ] = c0;
  kp.COLS[ 1 ] = c1;
  kp.COLS[ 2 ] = c2;
  kp.COLS[ 3 ] = c3;

  kp.ROWS[ 0 ] = r0;
  kp.ROWS[ 1 ] = r1;
  kp.ROWS[ 2 ] = r2;
  kp.ROWS[ 3 ] = r3;
  
  for ( int i = 0; i < 4; i++ )
  {
    pinMode( kp.COLS[ i ], INPUT );
    pudController( kp.COLS[ i ], PUD_UP );
  }

  for ( int i = 0; i < 4; i++ )
  {
    pinMode( kp.ROWS[ i ], OUTPUT );
    digitalWrite( kp.ROWS[ i ], HIGH );
  }

  return kp;
}

char checkKeypad( Keypad kp, int pageNumber )
{
  for ( int i = 4; i >= 0; i--  )
  {
    digitalWrite( kp.ROWS[ i ], LOW );
    
    for ( int j = 0; j < 4; j++ )
    {
    
      if ( digitalRead( kp.COLS[ j ] ) == LOW )
      {
      
        digitalWrite( kp.ROWS[ i ], HIGH );
        delay( 250 );
        
        switch (pageNumber)
        {
          case 0:
            return keypadTablePage0[ i ][ j ];
            break;
        
          case 1:
            return keypadTablePage1[ i ][ j ];
            break;
        
          case 2:
            return keypadTablePage2[ i ][ j ];
            break;
        
          default:
            return keypadTablePage0[ i ][ j ];
            break;
        }
      }
    }

    digitalWrite( kp.ROWS[ i ], HIGH );
  }
  return '\0';
}

