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
#include "rtems/error.h"
#include <errno.h>

rtems_task Init(
  rtems_task_argument argument
)
{
  puts( "\n\n*** TEST Tests for error reporting routines - 01 ***" );

  errno = -1;
  rtems_error(RTEMS_ERROR_ERRNO, "Dummy: Resources unavailable");

  errno = ENOMEM;
  rtems_error(
    RTEMS_NO_MEMORY | RTEMS_ERROR_ERRNO,
    "Dummy: Resources unavailable"
  );

  puts( "Dummy: causing panic.. will print test end message, then..." );
  puts( "       print various error messages" );
  rtems_error(
    RTEMS_NO_MEMORY | RTEMS_ERROR_PANIC,
    "Dummy: Resources unavailable\n"
    "*** END OF TEST Tests for error reporting routines - 01 ***\n"
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
