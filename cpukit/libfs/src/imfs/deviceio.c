/*
 *  IMFS Device Node Handlers
 *
 *  This file contains the set of handlers used to map operations on
 *  IMFS device nodes onto calls to the RTEMS Classic API IO Manager.
 *
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: deviceio.c,v 1.24 2010/07/15 08:10:47 sh Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include <rtems/libio.h>
#include <rtems/devfs.h>

#include "imfs.h"

/*
 *  device_open
 *
 *  This handler maps an open() operation onto rtems_io_open().
 */

int device_open(
  rtems_libio_t *iop,
  const char    *pathname,
  uint32_t       flag,
  uint32_t       mode
)
{
  rtems_libio_open_close_args_t  args;
  rtems_status_code              status;
  IMFS_jnode_t                  *the_jnode;

  the_jnode  = iop->pathinfo.node_access;

  args.iop   = iop;
  args.flags = iop->flags;
  args.mode  = mode;

  status = rtems_io_open(
    the_jnode->info.device.major,
    the_jnode->info.device.minor,
    (void *) &args
  );

  return rtems_deviceio_errno( status );
}

/*
 *  device_close
 *
 *  This handler maps a close() operation onto rtems_io_close().
 */

int device_close(
  rtems_libio_t *iop
)
{
  rtems_libio_open_close_args_t  args;
  rtems_status_code              status;
  IMFS_jnode_t                  *the_jnode;

  the_jnode = iop->pathinfo.node_access;

  args.iop   = iop;
  args.flags = 0;
  args.mode  = 0;

  status = rtems_io_close(
    the_jnode->info.device.major,
    the_jnode->info.device.minor,
    (void *) &args
  );

  IMFS_check_node_remove( the_jnode );

  return rtems_deviceio_errno( status );
}

/*
 *  device_read
 *
 *  This handler maps a read() operation onto rtems_io_read().
 */

ssize_t device_read(
  rtems_libio_t *iop,
  void          *buffer,
  size_t         count
)
{
  rtems_libio_rw_args_t   args;
  rtems_status_code       status;
  IMFS_jnode_t           *the_jnode;

  the_jnode = iop->pathinfo.node_access;

  args.iop         = iop;
  args.offset      = iop->offset;
  args.buffer      = buffer;
  args.count       = count;
  args.flags       = iop->flags;
  args.bytes_moved = 0;

  status = rtems_io_read(
    the_jnode->info.device.major,
    the_jnode->info.device.minor,
    (void *) &args
  );

  if ( status )
    return rtems_deviceio_errno(status);

  return (ssize_t) args.bytes_moved;
}

/*
 *  device_write
 *
 *  This handler maps a write() operation onto rtems_io_write().
 */

ssize_t device_write(
  rtems_libio_t *iop,
  const void    *buffer,
  size_t         count
)
{
  rtems_libio_rw_args_t   args;
  rtems_status_code       status;
  IMFS_jnode_t           *the_jnode;

  the_jnode = iop->pathinfo.node_access;

  args.iop         = iop;
  args.offset      = iop->offset;
  args.buffer      = (void *) buffer;
  args.count       = count;
  args.flags       = iop->flags;
  args.bytes_moved = 0;

  status = rtems_io_write(
    the_jnode->info.device.major,
    the_jnode->info.device.minor,
    (void *) &args
  );

  if ( status )
    return rtems_deviceio_errno(status);

  return (ssize_t) args.bytes_moved;
}

/*
 *  device_ioctl
 *
 *  This handler maps an ioctl() operation onto rtems_io_ioctl().
 */

int device_ioctl(
  rtems_libio_t *iop,
  uint32_t       command,
  void          *buffer
)
{
  rtems_libio_ioctl_args_t  args;
  rtems_status_code         status;
  IMFS_jnode_t             *the_jnode;

  args.iop     = iop;
  args.command = command;
  args.buffer  = buffer;

  the_jnode = iop->pathinfo.node_access;

  status = rtems_io_control(
    the_jnode->info.device.major,
    the_jnode->info.device.minor,
    (void *) &args
  );

  if ( status )
    return rtems_deviceio_errno(status);

  return args.ioctl_return;
}

/*
 *  device_lseek
 *
 *  This handler eats all lseek() operations and does not create
 *  an error. It assumes all devices can handle the seek. The
 *  writes fail.
 */

rtems_off64_t device_lseek(
  rtems_libio_t *iop,
  rtems_off64_t  offset,
  int            whence
)
{
  return offset;
}

/*
 *  device_stat
 *
 *  The IMFS_stat() is used.
 */

/*
 *  device_rmnod
 *
 *  The IMFS_rmnod() is used.
 */

int device_ftruncate(
  rtems_libio_t *iop,
  rtems_off64_t  length
)
{
  return 0;
}
