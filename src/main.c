#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jakestering.h"

int ROW = 4;
int COL = 4;

int COLS[ 4 ] = { 0, 1, 2, 3 };
int ROWS[ 4 ] = { 4, 5, 6, 7 };

char keypadTable[ 4 ][ 4 ] = 
{
  'C', 'D', 'E', 'F',
  '8', '9', 'A', 'B',
  '4', '5', '6', '7',
  '0', '1', '2', '3',
};

char checkKeypad( void )
{
  for ( int i = ROW; i >= 0; i--  )
  {
    digitalWrite( ROWS[ i ], LOW );
    
    for ( int j = 0; j < COL; j++ )
    {
 
      if ( digitalRead( COLS[ j ] ) == LOW )
      {
      
        digitalWrite( ROWS[ i ], HIGH );
        delay( 250 );
        return keypadTable[ i ][ j ];
      }
    }

    digitalWrite( ROWS[ i ], HIGH );
  }
  return '\0';
}

int main( int argc, char **argv )
{
  setupIO();

  for ( int i = 0; i < ROW; i++ )
  {
    pinMode( ROWS[ i ], OUTPUT );
    digitalWrite( ROWS[ i ], HIGH );
  }

  for ( int i = 0; i < COL; i++ )
  {
    pinMode( COLS[ i ], INPUT );
    pudController( COLS[ i ], PUD_UP );
  }
  
  while ( 1 )
  {
    char key = checkKeypad();
    if ( key != '\0' )
    {
      printf( "key: %c\n", key );
    }
  }

  return 0;
}

