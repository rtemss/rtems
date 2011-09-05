/*
 *  Dummy version of BSD routine
 *
 *  $Id: issetugid.c,v 1.3 2010/07/01 15:37:48 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(RTEMS_NEWLIB) && !defined(HAVE_ISSETUGID)
int issetugid (void)
{
  return 0;
}
#endif
