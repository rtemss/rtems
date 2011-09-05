/*
 *  Device Operations Table for the IMFS
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_handlers_device.c,v 1.10 2010/07/01 20:18:40 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>

#include "imfs.h"

/*
 *  Handler table for IMFS device nodes
 */

const rtems_filesystem_file_handlers_r IMFS_device_handlers = {
  device_open,
  device_close,
  device_read,
  device_write,
  device_ioctl,
  device_lseek,
  IMFS_stat,
  IMFS_fchmod,
  device_ftruncate,
  rtems_filesystem_default_fpathconf,
  rtems_filesystem_default_fsync,
  rtems_filesystem_default_fdatasync,
  rtems_filesystem_default_fcntl,
  IMFS_rmnod
};
