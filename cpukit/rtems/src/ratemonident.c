/*
 *  Rate Monotonic Manager -- Name to Id Lookup
 *
 *  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: ratemonident.c,v 1.12 2011/07/24 23:55:10 joel Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems/system.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/support.h>
#include <rtems/score/isr.h>
#include <rtems/score/object.h>
#include <rtems/rtems/ratemon.h>
#include <rtems/score/thread.h>

/*
 *  rtems_rate_monotonic_ident
 *
 *  This directive returns the system ID associated with
 *  the rate monotonic period name.
 *
 *  Input parameters:
 *    name - user defined period name
 *    id   - pointer to period id
 *
 *  Output parameters:
 *    *id              - region id
 *    RTEMS_SUCCESSFUL - if successful
 *    error code       - if unsuccessful
 */

rtems_status_code rtems_rate_monotonic_ident(
  rtems_name  name,
  rtems_id   *id
)
{
  Objects_Name_or_id_lookup_errors  status;

  status = _Objects_Name_to_id_u32(
    &_Rate_monotonic_Information,
    name,
    OBJECTS_SEARCH_LOCAL_NODE,
    id
  );

  return _Status_Object_name_errors_to_status[ status ];
}
