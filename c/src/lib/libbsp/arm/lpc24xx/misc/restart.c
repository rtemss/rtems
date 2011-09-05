/**
 * @file
 *
 * @ingroup lpc24xx
 *
 * @brief Restart implementation.
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
 * $Id: restart.c,v 1.1 2011/02/21 12:56:34 sh Exp $
 */

#include <rtems.h>

#include <bsp.h>

void bsp_restart(void *addr)
{
  ARM_SWITCH_REGISTERS;
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);

  asm volatile (
    ARM_SWITCH_TO_ARM
    "mov pc, %[addr]\n"
    ARM_SWITCH_BACK
    : ARM_SWITCH_OUTPUT
    : [addr] "r" (addr)
  );
}
