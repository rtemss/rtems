/*
 *  $Id: getppid.c,v 1.4 2011/07/24 23:55:06 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/seterr.h>

pid_t _POSIX_types_Ppid = 0;

/*
 *  4.1.1 Get Process and Parent Process IDs, P1003.1b-1993, p. 83
 */

pid_t getppid( void )
{
  return _POSIX_types_Ppid;
}
