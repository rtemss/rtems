/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.2 2011/02/22 07:37:02 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <tmacros.h>
#include "test_support.h"
#include <errno.h>
#include <rtems/error.h>

rtems_task Init(
  rtems_task_argument argument
)
{
  puts( "\n\n*** TEST Tests for error reporting routines - 02 ***" );

  errno = ENOMEM;
  rtems_error(
    RTEMS_NO_MEMORY | RTEMS_ERROR_ABORT, 
    "Dummy: Resources unavailable\n"
    "*** END OF TEST Tests for error reporting routines - 02 ***\n"
  );
  

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
