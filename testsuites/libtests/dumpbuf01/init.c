/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2011/02/22 07:34:07 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <tmacros.h>
#include "test_support.h"
#include <rtems/dumpbuf.h>

unsigned char Buffer[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890\n";

void do_test(
  int length
)
{
  printf( "====== Printing %d Bytes ======\n", length );
  rtems_print_buffer( Buffer, length );
  printf( "===============================\n\n" );
}

rtems_task Init(
  rtems_task_argument argument
)
{
  int i;

  puts( "\n\n*** TEST DUMPBUF01 ***" );

  for ( i = 0 ; i < sizeof(Buffer) ; i++ ) {
    do_test( i );
  }
  do_test( -1 );
  
  puts( "*** END OF TEST DUMPBUF01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             1
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
