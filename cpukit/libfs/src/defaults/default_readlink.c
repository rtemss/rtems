/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_readlink.c,v 1.3 2010/07/03 19:13:25 joel Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/seterr.h>

ssize_t rtems_filesystem_default_readlink(
 rtems_filesystem_location_info_t  *loc,     /* IN  */
 char                              *buf,     /* OUT */
 size_t                            bufsize
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}
