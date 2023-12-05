/*
 * bouncingBallLcd128x64.c:
 *  Example of bouncing ball on a 128x64 lcd
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
#include <string.h>
#include <time.h>

#include "jakestering.h"
#include "lcd128x64.h"

typedef struct _ball
{
  int x, y;
  int velx, vely;
  int speed;
  float friction;
} Ball;

Ball* ballInit( int x, int y, int speed, float friction );
float getRandomNumber( float value1, float value2 );

LCD128 *lcd;

Ball *ball;

int main( int argc, char **argv )
{
  srand( time( NULL ) );
  setupIO();

  lcd = initLcd128( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10, 11, 12 );
  
  ball = ballInit( 0, 0, 10, 0.89f);

  setGraphicsMode( lcd );

  lcd128ClearGraphics( lcd );
  
  while (1)
  {
    ball->x += ball->velx;
    ball->y += ball->vely;
    
    if ( ( ball->x >= ( 127 ) ) || ( ball->x <= 0 ) )
    {
      ball->velx = -ball->velx /* * getRandomNumber( 1.0f, 2.0f )*/;
    }
    
    if ( ( ball->y >= ( 63 ) ) || ( ball->y <= 0 ) )
    {
      ball->vely = -ball->vely /* * getRandomNumber( 1.0f, 2.0f )*/;
    }

  //  ball->velx *= ball->friction;
  //  ball->vely *= ball->friction;
    
    lcd128DrawPixel( lcd, ball->x, ball->y );

    lcd128UpdateScreen( lcd );
  }

  free( lcd );
  free( ball );

  return 0;
}

Ball* ballInit( int x, int y, int speed, float friction )
{
  Ball *ball = ( Ball* )malloc( sizeof( Ball ) );
  
  ball->x = x;
  ball->y = y;
  ball->speed = speed;
  ball->velx = speed;
  ball->vely = speed;
  ball->friction = friction;

  return ball;
}

float getRandomNumber( float value1, float value2 )
{
  return value1 + ( rand() / ( float )RAND_MAX ) * ( value2 - value1 );
}

