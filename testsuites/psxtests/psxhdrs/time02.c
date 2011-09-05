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
 *  $Id: time02.c,v 1.10 2011/02/22 09:47:34 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <time.h>

void test( void );

void test( void )
{
  time_t time1;
  time_t time2;
  double difference;

  time1 = 0;
  time2 = 0;

  difference = difftime( time1, time2 );
}