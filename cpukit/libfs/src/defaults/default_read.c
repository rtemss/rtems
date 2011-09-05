/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_read.c,v 1.3 2010/07/03 19:13:25 joel Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/seterr.h>

ssize_t rtems_filesystem_default_read(
  rtems_libio_t *iop,
  void          *buffer,
  size_t         count
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}
