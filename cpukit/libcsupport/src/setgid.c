/*
 *  $Id: setgid.c,v 1.1 2010/08/03 15:46:52 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/userenv.h>

/*
 *
 *  4.2.2 Set User and Group IDs, P1003.1b-1993, p. 84
 */
int setgid(
  gid_t  gid
)
{
  _POSIX_types_Gid = gid;
  return 0;
}
