/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: testcase.h,v 1.1 2010/07/14 16:02:40 joel Exp $
 */

#define FATAL_ERROR_TEST_NAME            "FATAL 22"
#define FATAL_ERROR_DESCRIPTION          "libio init out of memory"
#define FATAL_ERROR_EXPECTED_SOURCE      INTERNAL_ERROR_RTEMS_API
#define FATAL_ERROR_EXPECTED_IS_INTERNAL FALSE
#define FATAL_ERROR_EXPECTED_ERROR       RTEMS_NO_MEMORY

#include <rtems/libio.h>
#include "test_support.h"

void force_error()
{
  Allocate_majority_of_heap( 1 );

  rtems_libio_init();
}
