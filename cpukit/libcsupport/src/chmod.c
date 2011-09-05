/*
 *  chmod() - POSIX 1003.1b 5.6.4 - Change File Modes
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: chmod.c,v 1.14 2010/07/01 15:12:36 jennifer Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <rtems/libio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include <rtems/libio_.h>
#include <rtems/seterr.h>

int chmod(
  const char *path,
  mode_t      mode
)
{
  int                              status;
  rtems_filesystem_location_info_t loc;
  int                              result;

  status = rtems_filesystem_evaluate_path( path, strlen( path ), 0, &loc, true );
  if ( status != 0 )
    return -1;

  result = (*loc.handlers->fchmod_h)( &loc, mode );

  rtems_filesystem_freenode( &loc );

  return result;
}
