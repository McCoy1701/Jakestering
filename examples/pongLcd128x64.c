/*
 * pongLcd128x64.c:
 *  Simple implemenation of pong.
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

typedef struct _paddle
{
  int x1, y1;
  int x2, y2;

  int vely;

} Paddle;

Ball *ballInit( int x, int y, int speed, float friction );

Paddle *paddleInit( int x1, int y1, int x2, int y2, int vely );

float getRandomNumber( float value1, float value2 );

LCD128 *lcd;

Ball *ball;

Paddle *paddleLeft;
Paddle *paddleRight;

int left;
int right;

int leftHit;
int rightHit;

int main( int argc, char **argv )
{
  srand( time( NULL ) );
  
  setupIO();

  lcd = initLcd128( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ); //Initalize the 128x64 lcd
  
  ball = ballInit( 64, 24, 8, 0.89f );
  
  paddleLeft = paddleInit( 8, 24, 8, 40, 8 ); 
  paddleRight = paddleInit( 120, 24, 120, 40, -8 ); 

  setGraphicsMode( lcd );

  lcd128ClearGraphics( lcd );
  
  left = 0;
  right = 0;
  
  leftHit = 0;
  rightHit = 0;

  while (1)
  {
    ball->x += ball->velx; //Move the ball
    ball->y += ball->vely;
    
    if ( ( ball->x > 128 ) && !rightHit ) //Truncate the ball x position to be within the screen size
    {
      ball->x = 127;
    }

    if ( ( ball->x < 0 ) && !leftHit ) 
    {
      ball->x = 0;
    }
    
    paddleLeft->y1 = ball->y - 8; //Simple "AI" so the paddles will match the ball's y position and always make a hit
    paddleLeft->y2 = paddleLeft->y1 + 16;

    paddleRight->y1 = ball->y - 8;
    paddleRight->y2 = paddleRight->y1 + 16;
    
    if ( ( ball->x >= 127 ) || ( ball->x <= 0 ) ) //Check if ball hit play field egde if it hits on the x game ball is reset to the center
    {
      ball->x = 64  /* * getRandomNumber( 1.0f, 2.0f )*/;
    }

    if ( ( ball->y >= 63 ) || ( ball->y <= 0 ) ) //If ball hits on the y egde the velocity is reversed
    {
      ball->vely = -ball->vely /* * getRandomNumber( 1.0f, 2.0f )*/;
    }

    if ( ( ( ball->x <= paddleLeft->x2 ) && ( ball->x >= paddleLeft->x1 ) && ( ball->y <= paddleLeft->y2 ) && ( ball->y >= paddleLeft->y1 ) ) && !leftHit ) //Check if the ball is within the paddles and it hasn't just been hit
    {
      ball->velx = -ball->velx /* * getRandomNumber( 1.0f, 2.0f )*/;
      left++;
      leftHit = 1;
      printf( "ball hit left: %d\n", left );
    }
    
    else
    {
      leftHit = 0;
    }

    if ( ( ( ball->x <= paddleRight->x2 ) && ( ball->x >= paddleRight->x1 ) && ( ball->y <= paddleRight->y2 ) && ( ball->y >= paddleRight->y1 ) ) && !rightHit )
    {
      ball->velx = -ball->velx /* * getRandomNumber( 1.0f, 2.0f )*/;
      right++;
      rightHit = 1;
      printf( "ball hit right: %d\n", right );
    }

    else
    {
      rightHit = 0;
    }
    
    if ( ( paddleLeft->y2 >= 63 ) || ( paddleLeft->y1 <= 0 ) ) //Reverse the paddle velocity if it hits a edge
    {
      paddleLeft->vely = -paddleLeft->vely;
    }

    if ( ( paddleRight->y2 >= 63 ) || ( paddleRight->y1 <= 0 ) )
    {
      paddleRight->vely = -paddleRight->vely;
    }

  //  ball->velx *= ball->friction;
  //  ball->vely *= ball->friction;

    setGraphicsMode( lcd ); //Have to set graphics mode if you want to draw graphics

    lcd128DrawPixel( lcd, ball->x, ball->y );

    lcd128DrawLine( lcd, paddleLeft->x1, paddleLeft->y1, paddleLeft->x2, paddleLeft->y2 );
    lcd128DrawLine( lcd, paddleRight->x1, paddleRight->y1, paddleRight->x2, paddleRight->y2 );

    lcd128DrawLine( lcd, 64, 0, 64, 64 );

    lcd128UpdateScreen( lcd ); //This updates the screen with the current frame buffer

    setTextMode( lcd ); //Have to set text mode if you want to draw text

    lcd128CursorPosition( lcd, 3, 0 );
    lcd128Printf( lcd, 0, "%d", left );

    lcd128CursorPosition( lcd, 4, 0 );
    lcd128Printf( lcd, 1, "%d", right );

    if ( right >= 9 ) //Check which side has won
    {
      lcd128ClearText( lcd );
      lcd128CursorPosition(lcd, 2, 1 );
      lcd128Puts( lcd, "Winner!", 0 );
      lcd128CursorPosition(lcd, 3, 2 );
      lcd128Printf( lcd, 0, "Right: %d", right );
      break;
    }

    else if( left >= 9 )
    {
      lcd128ClearText( lcd );
      lcd128CursorPosition(lcd, 2, 1 );
      lcd128Puts( lcd, "Winner!", 0 );
      lcd128CursorPosition(lcd, 3, 2 );
      lcd128Printf( lcd, 0, "Left: %d", left );
      break;
    }
  }

  free( lcd );
  free( ball );
  free( paddleLeft );
  free( paddleRight );

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

Paddle *paddleInit( int x1, int y1, int x2, int y2, int vely )
{
  Paddle *paddle = ( Paddle* )malloc( sizeof( Paddle ) );

  paddle->x1 = x1;
  paddle->y1 = y1;
  paddle->x2 = x2;
  paddle->y2 = y2;

  paddle->vely = vely;

  return paddle;
}

float getRandomNumber( float value1, float value2 )
{
  return value1 + ( rand() / ( float )RAND_MAX ) * ( value2 - value1 );
}

