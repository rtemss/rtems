/*
 *  COPYRIGHT (c) 2010
 *  Bharath Suri<bharath.s.jois@gmail.com>.
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.5 2011/02/22 07:37:02 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/stat.h>
#include <stdio.h>

#include "tmacros.h"

#define FIFO_PATH "/fifo01"

static void test_main(void)
{
  int status = -1;

  puts("\n\n*** FIFO / PIPE OPEN TEST - 1 ***");

  puts(
    "\nConfiguration: Pipes disabled.\n"
    "Creating named fifo '" FIFO_PATH "'.\n"
    "Must result in failure since pipes are disabled in the configuration."
  );
  status = mkfifo(FIFO_PATH, 0777);
  rtems_test_assert(status == -1);

  puts("*** END OF FIFO / PIPE OPEN TEST - 1 ***");
}

rtems_task Init(rtems_task_argument not_used)
{
  test_main();
  rtems_test_exit(0);
}

#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_USE_IMFS_AS_BASE_FILESYSTEM

#define CONFIGURE_MAXIMUM_TASKS 1

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
