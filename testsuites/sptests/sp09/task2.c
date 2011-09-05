/*  Task_2
 *
 *  This routine serves as a test task.  Its only purpose is to generate the
 *  error where a semaphore is deleted while a task is waiting for it.
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
 *  $Id: task2.c,v 1.9 2011/02/22 07:36:58 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"

rtems_task Task_2(
  rtems_task_argument argument
)
{
  rtems_status_code status;

  puts( "TA2 - rtems_semaphore_obtain - sem 1 - RTEMS_WAIT FOREVER" );
  status = rtems_semaphore_obtain(
    Semaphore_id[ 1 ],
    RTEMS_DEFAULT_OPTIONS,
    RTEMS_NO_TIMEOUT
  );
  fatal_directive_status(
    status,
    RTEMS_OBJECT_WAS_DELETED,
    "rtems_semaphore_obtain waiting to be deleted"
  );
  puts(
    "TA2 - rtems_semaphore_obtain - woke up with RTEMS_OBJECT_WAS_DELETED"
  );

  puts( "TA2 - rtems_task_delete - delete self - RTEMS_SUCCESSFUL" );
  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of TA2" );
}
