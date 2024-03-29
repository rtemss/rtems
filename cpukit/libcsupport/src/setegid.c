/*
 *  $Id: setegid.c,v 1.2 2010/08/03 15:56:25 ralf Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <unistd.h>

#include <rtems/system.h>
#include <rtems/score/object.h>
#include <rtems/seterr.h>
#include <rtems/userenv.h>

/*
 *  4.2.1 Get Real User, Effective User, Ral Group, and Effective Group IDs,
 *        P1003.1b-1993, p. 84
 */
int setegid(
  gid_t  gid
)
{
  _POSIX_types_Egid = gid;
  return 0;
}
