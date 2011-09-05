/* irq.c
 *
 *  Copyright (c) 2010 Sebastien Bourdeauducq
 *
 *  The license and distribution terms for this file may be
 *  found in found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: irq.c,v 1.1 2011/08/01 13:48:39 joel Exp $
 */

#include <bsp.h>
#include <rtems/score/cpu.h>
#include <bsp/irq.h>
#include <bsp/irq-generic.h>

rtems_status_code bsp_interrupt_facility_initialize(void)
{
  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_vector_enable(rtems_vector_number vector)
{
  lm32_interrupt_unmask(1 << vector);
  return RTEMS_SUCCESSFUL;
}

rtems_status_code bsp_interrupt_vector_disable(rtems_vector_number vector)
{
  lm32_interrupt_mask(1 << vector);
  return RTEMS_SUCCESSFUL;
}

void bsp_interrupt_handler_default(rtems_vector_number vector)
{
  printk("spurious interrupt: %u\n", vector);
}
