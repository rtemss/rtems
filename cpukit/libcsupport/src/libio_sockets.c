/*
 *  This file contains the support infrastructure used to manage the
 *  table of integer style file descriptors used by the socket calls.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: libio_sockets.c,v 1.16 2010/07/15 08:10:47 sh Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/libio_.h>
#include <rtems/seterr.h>

/*
 * Convert an RTEMS file descriptor to a BSD socket pointer.
 */

struct socket *rtems_bsdnet_fdToSocket(
  int fd
)
{
  rtems_libio_t *iop;

  /* same as rtems_libio_check_fd(_fd) but different return */
  if ((uint32_t)fd >= rtems_libio_number_iops) {
    errno = EBADF;
    return NULL;
  }
  iop = &rtems_libio_iops[fd];

  /* same as rtems_libio_check_is_open(iop) but different return */
  if ((iop->flags & LIBIO_FLAGS_OPEN) == 0) {
    errno = EBADF;
    return NULL;
  }

  if (iop->data1 == NULL)
    errno = EBADF;
  return iop->data1;
}

/*
 * Create an RTEMS file descriptor for a socket
 */

int rtems_bsdnet_makeFdForSocket(
  void *so,
  const rtems_filesystem_file_handlers_r *h
)
{
  rtems_libio_t *iop;
  int fd;

  iop = rtems_libio_allocate();
  if (iop == 0)
      rtems_set_errno_and_return_minus_one( ENFILE );

  fd = iop - rtems_libio_iops;
  iop->flags |= LIBIO_FLAGS_WRITE | LIBIO_FLAGS_READ;
  iop->data0 = fd;
  iop->data1 = so;
  iop->pathinfo.handlers = h;
  iop->pathinfo.ops = &rtems_filesystem_operations_default;
  return fd;
}
