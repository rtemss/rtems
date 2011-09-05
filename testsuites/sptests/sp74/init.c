/* 
 *  COPYRIGHT (c) 2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.3 2011/07/26 19:44:20 joel Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <tmacros.h>


rtems_task Test_task(
  rtems_task_argument index
)
{
  puts( "Successfully yielded it to higher priority task" );

  puts( "*** END OF SP74 TEST ***" );
  rtems_test_exit( 0 );
}

rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_status_code  status;
  rtems_id           id;

  puts( "\n\n*** SP74 (YIELD) TEST ***" );

  puts( "Create TA1 at higher priority task" );
  status = rtems_task_create(
    rtems_build_name( 'T', 'A', '1', ' ' ),
    1,
    RTEMS_MINIMUM_STACK_SIZE,
    RTEMS_DEFAULT_MODES,
    RTEMS_DEFAULT_ATTRIBUTES,
    &id
  );
  directive_failed( status, "create 1" );

  status = rtems_task_start( id, Test_task, 1 );
  directive_failed( status, "start 1" );

  puts( "Yield to TA1" );
  status = rtems_task_wake_after( RTEMS_YIELD_PROCESSOR );
  directive_failed( status, "yield" );

  puts( "*** should now get here ***" );
}

/* configuration information */
#include <bsp.h> /* for device driver prototypes */

#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS           3
#define CONFIGURE_INIT_TASK_PRIORITY      2

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT
#include <rtems/confdefs.h>
/* end of file */
