#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

#include "jakestering.h"

#define MAX_BUFFER 32 

typedef void(*function)(void);

static volatile int pin_pass = -1;
static pthread_mutex_t pin_mutex;

static int chip_FD = -1;
static int pin_FDs[32] = {-1};
static void(*isr_functions[32])(void);
static pthread_t isr_threads[32];
static int isr_modes[32];

static void *interrupt_handler(void *arg);

int wait_for_interrupt( const int pin, const int ms );
int wait_for_interrupt_to_close( const int pin );
int interrupt_init( const int pin, const int mode );
int jakestering_ISR( const int pin, const int mode, void (*function)(void) );

void test_handler(void);

int main( int argc, char *argv[] )
{
  setupIO();

  pinMode( 0, INPUT );

  jakestering_ISR( 0, RISING_EDGE, &test_handler );
  
  while (1)
  {
    delay( 1000 );
    printf("looping\n");
  }
  return 0;
}

void test_handler(void)
{
  printf("Had egde trigger\n");
}

static void *interrupt_handler(void *arg)
{
  int pin;
  pin = pin_pass;
  pin_pass = -1;

  for (;;)
  {
    int ret = wait_for_interrupt( pin, -1 );
    if ( ret > 0 )
    {
      if ( isr_functions[pin] )
      {
        isr_functions[pin]();
      }
    }

    else if ( ret < 0 )
    {
      break;
    }
  }

  wait_for_interrupt_to_close( pin );

  return NULL;
}

int wait_for_interrupt( const int pin, const int ms )
{
  int fd, ret;
  struct pollfd polls;
  struct gpioevent_data event_data;

  if ( ( fd = pin_FDs[pin] ) == -1 )
  {
    return -2;
  }

  polls.fd = fd;
  polls.events = POLLIN | POLLERR;
  polls.revents = 0;

  ret = poll( &polls, 1, ms );
  if ( ret <= 0 )
  {
    printf( "Failed: poll returned %d\n", ret );
  }
  else
  {
    int readret = read( pin_FDs[pin], &event_data, sizeof(event_data) );
    
    if ( readret == sizeof(event_data) )
    {
      ret = event_data.id;
    }

    else
    {
      ret = 0;
    }
  }

  return ret;
}

int wait_for_interrupt_to_close( const int pin )
{
  if ( pin_FDs[pin] > 0 )
  {
    if ( pthread_cancel( isr_threads[pin] ) == 0 )
    {
      //printf("thread cnacnled successfully\n")
    }

    else
    {
      printf( "Failed: could not cancel thread\n" );
    }
    close( pin_FDs[pin] );
  }
  pin_FDs[pin] = -1;
  isr_functions[pin] = NULL;

  return 0;
}

int interrupt_init( const int pin, const int mode )
{
  const char* strmode = "";
  sleep(1);
  const char *gpio_chip = "/dev/gpiochip0";

  if ( chip_FD < 0 )
  {
    chip_FD = open( gpio_chip, O_RDWR );
    if ( chip_FD < 0 )
    {
      printf( "Error opening: %s open ret=%d\n", gpio_chip, chip_FD );
      return -1;
    }
  }

  struct gpioevent_request req;
  req.lineoffset = pin;
  req.handleflags = GPIOHANDLE_REQUEST_INPUT;
  switch( mode )
  {
    case FALLING_EDGE:
      req.eventflags = GPIOEVENT_REQUEST_FALLING_EDGE;
      strmode = "falling";
      break;
    case RISING_EDGE:
      req.eventflags = GPIOEVENT_REQUEST_RISING_EDGE;
      strmode = "rising";
      break;
    case BOTH_EDGE:
      req.eventflags = GPIOEVENT_REQUEST_BOTH_EDGES;
      strmode = "both";
      break;
  }
  strncpy( req.consumer_label, "jakestering_gpio_irq", sizeof( req.consumer_label ) - 1 );

  int ret = ioctl( chip_FD, GPIO_GET_LINEEVENT_IOCTL, &req );
  if ( ret )
  {
    printf("Failed: %s ioctl get line %d %s returned %d\n", gpio_chip, pin, strmode, ret );
    return -1;
  }

  int fd_line = req.fd;
  pin_FDs[pin] = fd_line;
  int flags = fcntl( fd_line, F_GETFL );
  flags |= O_NONBLOCK;
  ret = fcntl( fd_line, F_SETFL, flags );

  if (ret)
  {
    printf( "Failed: %s fcntl set nonblock read=%d\n", gpio_chip, chip_FD );
    return -1;
  }

  return 0;
}

int jakestering_ISR( const int pin, const int mode, void (*function)(void) )
{
  isr_functions[pin] = function;
  isr_modes[pin] = mode;
  if ( interrupt_init( pin, mode ) < 0 )
  {
    printf("Waiting for interrupt init failed\n");
  }
  
  pthread_mutex_lock( &pin_mutex );
    pin_pass = pin;

    if ( pthread_create( &isr_threads[pin], NULL, interrupt_handler, NULL ) == 0 )
    {
      while ( pin_pass != -1 )
      {
        delay(1);
      }
    }

    else
    {
      printf("Failed to create thread\n");
    }
  pthread_mutex_unlock( &pin_mutex );

  return 0;
}
