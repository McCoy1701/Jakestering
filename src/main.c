#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char readProcFile( void )
{
  FILE* f;
  char value;

  f = fopen( "/proc/jakestering-gpio", "r" );

  if ( f == NULL )
  {
    printf( "failed to open: %s\n", "/proc/jakestering-gpio" );
    return -1;
  }

  value = fgetc( f );
  
  fclose( f );
  
  return value;
}

void writeProcFile( int a, int b, int c )
{
  FILE* fd;
  
  fd = fopen( "/proc/jakestering-gpio", "w" );
  
  if ( fprintf( fd, "%d,%d,%d\n", a, b, c ) < 0)
  {
    printf( "Error writing to file\n" );
    fclose( fd );
    return;
  }

  fclose( fd );
}

int main( int argc, char* argv[] )
{
/*  for ( int i = 0; i < 13; i++)
  {
    writeProcFile( 1, i, 0 );
  }*/

  writeProcFile(1, 0, 0);

  while ( 1 )
  {
    sleep( 1 );
    writeProcFile( 3, 0, 1 );
    sleep( 1 );
    writeProcFile( 3, 0, 0 );
  }
}
