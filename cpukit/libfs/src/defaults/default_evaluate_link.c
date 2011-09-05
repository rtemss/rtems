/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_evaluate_link.c,v 1.2 2010/08/27 06:42:46 sh Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/seterr.h>

int rtems_filesystem_default_evaluate_link(
  rtems_filesystem_location_info_t *pathloc,     /* IN/OUT */
  int                               flags        /* IN     */
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}

