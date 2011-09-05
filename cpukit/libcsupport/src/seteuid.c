/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: seteuid.c,v 1.2 2010/08/03 15:56:25 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>

#include <rtems/userenv.h>

int seteuid( uid_t euid )
{
  _POSIX_types_Euid = euid;
  return 0;
}
