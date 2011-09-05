/*  Task_4
 *
 *  This routine serves as a test task.  It waits forever attempting
 *  to obtain semaphore 1.  However, it should never get the semaphore!
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: task4.c,v 1.8 2011/02/22 07:36:59 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"

rtems_task Task_4(
  rtems_task_argument argument
)
{
  rtems_status_code status;

  puts( "TA4 - rtems_semaphore_obtain - wait forever on SM1" );
  status = rtems_semaphore_obtain(
    Semaphore_id[ 1 ],
    RTEMS_DEFAULT_OPTIONS,
    RTEMS_NO_TIMEOUT
  );
  directive_failed( status, "rtems_semaphore_obtain on SM1" );
}
