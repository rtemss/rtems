/*
 *  $Id: getgid.c,v 1.3 2010/08/03 15:46:52 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/userenv.h>

/*
 *  4.2.1 Get Real User, Effective User, Ral Group, and Effective Group IDs,
 *        P1003.1b-1993, p. 84
 */
gid_t getgid( void )
{
  return _POSIX_types_Gid;
}
