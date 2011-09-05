/**
 * @file rtems/btimer.h
 *
 *  RTEMS benchmark timer API for all boards.
 */

/*
 *  COPYRIGHT (c) 2011 Ralf Corsépius Ulm/Germany
 *
 *  Derived from libcsupport/include/timerdrv.h:
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: btimer.h,v 1.1 2011/02/09 06:15:53 ralf Exp $
 */
 
/*
 * All the functions declared as extern after this comment
 * MUST be implemented in each BSP.
 */

#ifndef _RTEMS_BTIMER_H
#define _RTEMS_BTIMER_H

#include <stdbool.h>
#include <stdint.h>
#include <rtems/rtems/status.h>

#ifdef __cplusplus
extern "C" {
#endif

/* functions */

extern void benchmark_timer_initialize( void );

extern uint32_t   benchmark_timer_read( void );

extern rtems_status_code benchmark_timer_empty_function( void );

extern void benchmark_timer_disable_subtracting_average_overhead(
  bool find_flag
);

#ifdef __cplusplus
}
#endif

#endif
