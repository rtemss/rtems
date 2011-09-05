/*
 *  COPYRIGHT (c) 2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: default_close.c,v 1.2 2010/09/27 12:32:40 sh Exp $
 */

#include <rtems/libio.h>

int rtems_filesystem_default_close(
  rtems_libio_t *iop
)
{
  return 0;
}
