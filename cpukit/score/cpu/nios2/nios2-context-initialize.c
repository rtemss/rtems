/*
 * Copyright (c) 2011 embedded brains GmbH
 *
 * Copyright (c) 2006 Kolja Waschk (rtemsdev/ixo.de)
 *
 * COPYRIGHT (c) 1989-2006
 * On-Line Applications Research Corporation (OAR).
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 * $Id: nios2-context-initialize.c,v 1.2 2011/09/02 07:52:30 sh Exp $
 */

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include <string.h>

#include <rtems/score/cpu.h>
#include <rtems/score/nios2-utility.h>

void _CPU_Context_Initialize(
  Context_Control *context,
  void *stack_area_begin,
  size_t stack_area_size,
  uint32_t new_level,
  void (*entry_point)( void ),
  bool is_fp
)
{
  uint32_t stack = (uint32_t) stack_area_begin + stack_area_size - 4;

  memset(context, 0, sizeof(*context));

  context->fp = stack;
  context->status = _Nios2_ISR_Set_level( new_level, NIOS2_STATUS_PIE );
  context->sp = stack;
  context->ra = (uint32_t) entry_point;
}
