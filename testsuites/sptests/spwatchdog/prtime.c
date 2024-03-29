/*  Print_time
 *
 *  This routine prints the name of Task_1 and the current time of day.
 *
 *  Input parameters:  NONE
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
 *  $Id: prtime.c,v 1.3 2011/02/22 07:37:03 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"

void Print_time( void )
{
  rtems_time_of_day time;
  rtems_status_code status;

  status = rtems_clock_get_tod( &time );
  directive_failed( status, "rtems_clock_get_tod" );

  put_name( Task_name[ 1 ], FALSE );
  print_time( "- rtems_clock_get_tod - ", &time, "\n" );
}
