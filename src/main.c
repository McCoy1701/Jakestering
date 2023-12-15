/*
 * main.c:
 *  Entry Point for jakestering
 *
 * Copyright (c) 2023 Jacob Kellum <jkellum819@gmail.com>
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

#include <stdio.h>
#include <stdlib.h>

#include "jakestering.h"
#include "lcd.h"

typedef struct _ball
{
  int x, y;
  int velx, vely;
  int speed;
} Ball;

Ball* ballInit( int x, int y, int speed );

LCD *lcd;

Ball *ball;

int main( int argc, char **argv )
{
  setupIO();

  lcd = initLcd( 4, 20, 0, 13,  3, 4, 5, 6, 7, 8, 9, 10 );
  
  ball = ballInit( 0, 0, 1);

  lcdClear( lcd );

  while (1)
  {

    ball->x += ball->velx;
    ball->y += ball->vely;
    
    if ( ( ball->x >= ( lcd->cols - 1 ) ) || ( ball->x <= 0 ) )
    {
      ball->velx = -ball->velx;
    }
    
    if ( ( ball->y >= ( lcd->rows - 1 ) ) || ( ball->y <= 0 ) )
    {
      ball->vely = -ball->vely;
    }
    
    lcdClear( lcd );

    lcdPosition( lcd, ball->x, ball->y );
    lcdPutChar( lcd, 'o' );
    printf( "x, y: %d, %d\n", ball->x, ball->y );
    delay( 1000 );
  }

  free( lcd );
  free( ball );

  return 0;
}

Ball* ballInit( int x, int y, int speed )
{
  Ball *ball = ( Ball* )malloc( sizeof( Ball ) );
  
  ball->x = x;
  ball->y = y;
  ball->speed = speed;
  ball->velx = speed;
  ball->vely = speed;

  return ball;
}

