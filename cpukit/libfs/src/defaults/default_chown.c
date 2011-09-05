/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_chown.c,v 1.3 2010/06/29 19:37:28 jennifer Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/seterr.h>

int rtems_filesystem_default_chown(
 rtems_filesystem_location_info_t  *pathloc,       /* IN */
 uid_t                              owner,         /* IN */
 gid_t                              group          /* IN */
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}
