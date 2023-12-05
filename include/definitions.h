/*
 * definitions.h:
 *  Macros and Definitions for Jakestering
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

#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define BCM2835_BASE 0x20000000
#define GPIO_BASE ( BCM2835_BASE + 0x200000 )

#define PAGE_SIZE  ( 4 * 1024 )
#define BLOCK_SIZE ( 4 * 1024 )

#define INP_GPIO( g ) *( gpio + ( ( g ) / 10 ) ) &= ~( 7 << ( ( (g) % 10 ) * 3 ) )
#define OUT_GPIO( g ) *( gpio + ( ( g ) / 10 ) ) |=  ( 1 << ( ( (g) % 10 ) * 3 ) )
#define SET_GPIO_ALT( g, a ) *( gpio + ( ( ( g ) / 10 ) ) ) |= ( ( (a) <= 3 ? (a) + 4 : (a) == 4 ? 3 : 2) << ( ( (g) % 10 ) * 3 ) )

#define GPIO_SET *( gpio + 7 )
#define GPIO_CLR *( gpio + 10 )

#define GET_GPIO( g ) ( *( gpio + 13 ) & ( 1 << g ) )

#define GPIO_PULL *( gpio + 37 )
#define GPIO_PULLCLK0 *( gpio + 38 )

#define HIGH 1
#define LOW  0

#define INPUT  0
#define OUTPUT 1

#define PUD_DISABLE   0
#define PUD_DOWN      1
#define PUD_UP        2

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#endif

