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
 *  $Id: mutex10.c,v 1.10 2011/02/22 09:47:33 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <pthread.h>

#ifndef _POSIX_THREADS
#error "rtems is supposed to have pthread_mutexattr_getpshared"
#endif
#ifndef _POSIX_THREAD_PROCESS_SHARED
#error "rtems is supposed to have pthread_mutexattr_setpshared"
#endif

void test( void );

void test( void )
{
  pthread_mutexattr_t attribute;
  int                 pshared;
  int                 result;

  result = pthread_mutexattr_getpshared( &attribute, &pshared );
}
