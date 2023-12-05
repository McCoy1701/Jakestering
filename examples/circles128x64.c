/*
 * circles128x64.c:
 *  Show off the circle drawing and fill routines
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
#include "lcd128x64.h"

LCD128 *lcd;
int main( int argc, char **argv )
{
  setupIO();

  lcd = initLcd128( 0, 1, 2,  3, 4, 5, 6, 7, 8, 9, 10, 11, 12 ); //Initalize the 128x64 lcd
  
  setGraphicsMode( lcd );

  lcd128ClearGraphics( lcd );

  lcd128DrawCircle( lcd, 34, 25, 12 );
  lcd128DrawCircle( lcd, 60, 25, 12 );
  lcd128DrawCircle( lcd, 86, 25, 12 );
  
  lcd128DrawCircle( lcd, 47, 37, 12 );
  lcd128DrawCircle( lcd, 73, 37, 12 );
 
  lcd128DrawFilledCircle( lcd, 100, 50, 8 );

  lcd128UpdateScreen( lcd );

  free( lcd );
  
  return 0;
}

