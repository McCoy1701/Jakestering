/*
 * keypad.h:
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

#ifndef __KEYPAD_H__
#define __KEYPAD_H__

typedef struct _keypad
{
  int COLS[ 4 ];
  int ROWS[ 4 ];
} Keypad;

Keypad initKeypad( int c0, int c1, int c2, int c3, int r0, int r1, int r2, int r3 );

char checkKeypad( Keypad kp, int pageNumber );

#endif

