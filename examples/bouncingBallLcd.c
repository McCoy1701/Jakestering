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

  lcd = initLcd( 4, 20, 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10 );
  
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

