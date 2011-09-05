/*  Task_1
 *
 *  This routine serves as a test task.  It verifies the basic task
 *  switching capabilities of the executive.
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
 *  $Id: task1.c,v 1.5 2011/02/22 09:47:31 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"
#include <errno.h>

void *Task_1(
  void *argument
)
{
  puts( "Task_1: exitting" );

  return( &Task1_id );
}