/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_lseek.c,v 1.2 2010/06/29 01:53:18 joel Exp $
 */

#include <rtems/libio.h>
#include <rtems/libio_.h>
#include <rtems/seterr.h>

rtems_off64_t rtems_filesystem_default_lseek(
  rtems_libio_t *iop,
  rtems_off64_t  length,
  int            whence
)
{
  rtems_set_errno_and_return_minus_one( ENOTSUP );
}
