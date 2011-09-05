/*
 *  Operations Table for Directories for the IMFS
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: imfs_handlers_directory.c,v 1.11 2010/08/25 09:37:48 sh Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <errno.h>

#include "imfs.h"

/*
 *  Set of operations handlers for operations on directories.
 */

const rtems_filesystem_file_handlers_r IMFS_directory_handlers = {
  imfs_dir_open,
  imfs_dir_close,
  imfs_dir_read,
  rtems_filesystem_default_write,
  rtems_filesystem_default_ioctl,
  imfs_dir_lseek,
  imfs_dir_fstat,
  IMFS_fchmod,
  rtems_filesystem_default_ftruncate,
  rtems_filesystem_default_fpathconf,
  rtems_filesystem_default_fsync,
  IMFS_fdatasync,
  rtems_filesystem_default_fcntl,
  imfs_dir_rmnod
};
