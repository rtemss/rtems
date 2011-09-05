/*
 *  COPYRIGHT (c) 2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: schedulerpriorityenqueuefirst.c,v 1.2 2011/05/24 02:44:57 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/config.h>
#include <rtems/score/chain.h>
#include <rtems/score/schedulerpriority.h>

void _Scheduler_priority_Enqueue_first(
  Thread_Control      *the_thread
)
{
  _Scheduler_priority_Ready_queue_enqueue_first( the_thread );
}

