/*
 *  This test file is used to verify that the header files associated with
 *  invoking this function are correct.
 *
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: timer06.c,v 1.10 2011/02/22 09:47:34 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>

#ifndef _POSIX_TIMERS
#error "rtems is supposed to have nanosleep"
#endif

void test( void );

void test( void )
{
  struct timespec rqtp;
  struct timespec rmtp;
  int             result;

  rqtp.tv_sec = 0;
  rqtp.tv_nsec = 0;
  result = nanosleep( &rqtp, &rmtp );
}
