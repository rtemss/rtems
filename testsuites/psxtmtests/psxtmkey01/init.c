/*
 *  COPYRIGHT (c) 1989-2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.1 2011/07/20 13:20:25 joel Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <timesys.h>
#include <rtems/timerdrv.h>
#include <errno.h>
#include <pthread.h>
#include "test_support.h"

pthread_key_t Key;

void benchmark_pthread_key_create(void)
{
  long end_time;
  int  status;

  benchmark_timer_initialize();
    status = pthread_key_create(&Key, NULL);
  end_time = benchmark_timer_read();
  rtems_test_assert( status == 0 );

  put_time(
    "pthread_key_create",
    end_time,
    1,        /* Only executed once */
    0,
    0
  );

}

void benchmark_pthread_key_delete(void)
{
  long end_time;
  int  status;

  benchmark_timer_initialize();
    status = pthread_key_delete(Key);
  end_time = benchmark_timer_read();
  rtems_test_assert( status == 0 );

  put_time(
    "pthread_key_delete",
    end_time,
    1,        /* Only executed once */
    0,
    0
  );

}

void *POSIX_Init(void *argument)
{

  puts( "\n\n*** POSIX TIME TEST PSXTMKEY01 ***" );

  /*key creation, using NULL destructor*/
  benchmark_pthread_key_create();
  
  /* key deletion*/
  benchmark_pthread_key_delete();
  
  puts( "*** END OF POSIX TIME TEST PSXTMKEY01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_TIMER_DRIVER

#define CONFIGURE_MAXIMUM_POSIX_THREADS     2
#define CONFIGURE_MAXIMUM_POSIX_KEYS     1
#define CONFIGURE_POSIX_INIT_THREAD_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
