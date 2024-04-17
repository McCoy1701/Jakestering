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

void function( void );

int main( int argc, char **argv )
{
  setupIO();
  
  pinMode( 0, INPUT );

  GPIO_REN |= 1 << 0;

  while ( 1 )
  {
    if ( GPIO_EDS( pin ) != 0 )
    {
      function();
      GPIO_SET_EDS |= 1 << pin; //Clear eds after detecting a edge
    }
  }

  //interrupt_service_routine( 0, RISING_EDGE, &function );
}

void function( void )
{
  printf("Rising edge\n");
}

