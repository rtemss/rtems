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
 *  $Id: signal08.c,v 1.11 2011/02/22 09:47:34 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <signal.h>

#ifndef _POSIX_THREADS
#error "rtems is supposed to have pthread_sigmask"
#endif

void test( void );

void test( void )
{
  int       how;
  sigset_t  set;
  sigset_t  oset;
  int       result;

  how = SIG_BLOCK;
  how = SIG_UNBLOCK;
  how = SIG_SETMASK;

  result = pthread_sigmask( how, &set, &oset );
}
