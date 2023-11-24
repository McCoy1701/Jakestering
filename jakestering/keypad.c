/*
 * keypad.c:
 *  Routines for interfacing with a 4x4 keypad
 *
 * Copyright (c) 2023 Jacob Kellum
 *************************************************************************
 * This file is apart of Jakestering:
 *    https://github.com/McCoy1701/Jakestering
 *
 * Jakestering is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Jakestering is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Jakestering; if not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************
 */

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

/*
 * Initialize a 4x4 keypad matrix
 *
 * Parameters:
 *  c0: column 1
 *  c1: column 2
 *  c2: column 3
 *  c3: column 4
 *  r0: row 1
 *  r1: row 2
 *  r2: row 3
 *  r3: row 4
 *
 * Return:
 *  Keypad that has been initialized 
 */

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

/*
 * Check the keypad for any keys being pressed
 *
 * Parameters:
 *  kp        : keypad that is being checked
 *  pageNumber: what page of the keypad are you on
 *
 * Return:
 *  char that has been pressed 
 */

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

