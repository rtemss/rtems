/*
 *  lchown() - POSIX 1003.1b 5.6.5 - Change Owner and Group of a File
 *             But Do Not Follow a Symlink
 *
 *  Written by: Vinu Rajashekhar <vinutheraj@gmail.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: lchown.c,v 1.1 2010/07/01 17:22:03 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/stat.h>

#include <rtems.h>

int _chown_helper( const char *path, uid_t owner, gid_t group, int follow_link);

int lchown(
  const char *path,
  uid_t       owner,
  gid_t       group
)
{
  return _chown_helper( path, owner, group, false );
}
