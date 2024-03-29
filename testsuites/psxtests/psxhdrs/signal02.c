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
 *  $Id: signal02.c,v 1.10 2011/02/22 09:47:33 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <signal.h>

void test( void );

void test( void )
{
  sigset_t signal_set;
  int      signal_number;
  int      result;

  signal_number = SIGALRM;

  result = sigdelset( &signal_set, signal_number );
}
