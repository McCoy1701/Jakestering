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

#endif

