/**
 * @file
 *
 * @ingroup libcsupport
 *
 * @brief rtems_heap_extend() implementation.
 */

/*
 * Copyright (c) 2011 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 * $Id: rtems_heap_extend.c,v 1.1 2011/02/17 14:17:09 sh Exp $
 */

#if HAVE_CONFIG_H
  #include "config.h"
#endif

#ifdef RTEMS_NEWLIB
#include "malloc_p.h"

rtems_status_code rtems_heap_extend(
  void *area_begin,
  uintptr_t area_size
)
{
  bool ok = _Protected_heap_Extend(RTEMS_Malloc_Heap, area_begin, area_size);

  if (ok) {
    return RTEMS_SUCCESSFUL;
  } else {
    return RTEMS_INVALID_ADDRESS;
  }
}
#endif /* RTEMS_NEWLIB */
