/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: testcase.h,v 1.1 2010/06/22 01:28:13 joel Exp $
 */

/* generate fatal errors in open_dev_console.c */
#define FATAL_ERROR_TEST_NAME            "15"
#define FATAL_ERROR_DESCRIPTION          "fail to open stderr"
#define FATAL_ERROR_EXPECTED_SOURCE      INTERNAL_ERROR_RTEMS_API
#define FATAL_ERROR_EXPECTED_IS_INTERNAL FALSE
#define FATAL_ERROR_EXPECTED_ERROR       0x55544432

#define CONFIGURE_APPLICATION_PREREQUISITE_DRIVERS \
  { consume_semaphores_initialize, NULL, NULL, NULL, NULL, NULL }

void force_error()
{
  /* we will not run this far */
}
