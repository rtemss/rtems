/*
 *  Written by: Vinu Rajashekhar <vinutheraj@gmail.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: utimes.c,v 1.1 2010/07/01 17:22:03 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/types.h>
#include <utime.h>
#include <sys/time.h>

int utimes(
  const char           *path,
  const struct timeval  times[2]
) 
{
  struct utimbuf timeinsecs;

  if ( times == NULL )
    return utime( path, NULL );

  timeinsecs.actime  = (time_t) times[0].tv_sec;
  timeinsecs.modtime = (time_t) times[1].tv_sec;

  return utime( path, &timeinsecs );
}
