/*
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: devstat.c,v 1.3 2010/07/23 00:11:32 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <rtems/io.h>
#include <rtems/seterr.h>
#include <rtems/libio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "devfs.h"

int devFS_stat(
  rtems_filesystem_location_info_t *loc,
  struct stat                      *buf
)
{
  rtems_device_name_t *the_dev;

  the_dev = (rtems_device_name_t *)loc->node_access;

  /*
   *  stat() invokes devFS_evaluate_path() which checks that node_access
   *  is not NULL.  So this should NEVER be NULL unless someone breaks
   *  other code in this filesystem.
   */
  #if defined(RTEMS_DEBUG)
    if (!the_dev)
      rtems_set_errno_and_return_minus_one( EFAULT );
  #endif 

  buf->st_rdev  = rtems_filesystem_make_dev_t( the_dev->major, the_dev->minor );
  buf->st_mode = the_dev->mode;
  return 0;
}


