/**
 * @file
 *
 * @ingroup mpc83xx
 *
 * @brief Source for BSP startup code.
 */

/*
 * Copyright (c) 2008
 * Embedded Brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * rtems@embedded-brains.de
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 * $Id: bspstart.c,v 1.32 2011/06/07 13:34:30 sh Exp $
 */

#include <libchip/serial.h>

#include <libcpu/powerpc-utility.h>

#include <bsp.h>
#include <bsp/vectors.h>
#include <bsp/bootcard.h>
#include <bsp/irq-generic.h>
#include <bsp/u-boot.h>

/* Configuration parameters for console driver, ... */
unsigned int BSP_bus_frequency;

/* Configuration parameters for clock driver, ... */
uint32_t bsp_clicks_per_usec;

/* Default decrementer exception handler */
static int mpc83xx_decrementer_exception_handler( BSP_Exception_frame *frame, unsigned number)
{
  ppc_set_decrementer_register(UINT32_MAX);

  return 0;
}

void BSP_panic(char *s)
{
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);

  printk("%s PANIC %s\n", rtems_get_version_string(), s);

  while (1) {
    /* Do nothing */
  }
}

void _BSP_Fatal_error(unsigned n)
{
  rtems_interrupt_level level;

  rtems_interrupt_disable( level);

  printk( "%s PANIC ERROR %u\n", rtems_get_version_string(), n);

  while (1) {
    /* Do nothing */
  }
}

void bsp_start( void)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  unsigned long i = 0;

  ppc_cpu_id_t myCpu;
  ppc_cpu_revision_t myCpuRevision;

  uintptr_t interrupt_stack_start = (uintptr_t) bsp_interrupt_stack_start;
  uintptr_t interrupt_stack_size = (uintptr_t) bsp_interrupt_stack_size;

  /*
   * Get CPU identification dynamically. Note that the get_ppc_cpu_type() function
   * store the result in global variables so that it can be used latter...
   */
  myCpu = get_ppc_cpu_type();
  myCpuRevision = get_ppc_cpu_revision();

  /* Basic CPU initialization */
  cpu_init();

  /*
   * Enable instruction and data caches. Do not force writethrough mode.
   */

#if BSP_INSTRUCTION_CACHE_ENABLED
  rtems_cache_enable_instruction();
#endif

#if BSP_DATA_CACHE_ENABLED
  rtems_cache_enable_data();
#endif

  /*
   * This is evaluated during runtime, so it should be ok to set it
   * before we initialize the drivers.
   */

  /* Initialize some device driver parameters */

#ifdef HAS_UBOOT
  BSP_bus_frequency = bsp_uboot_board_info.bi_busfreq;
  bsp_clicks_per_usec = bsp_uboot_board_info.bi_busfreq / 4000000;
#else /* HAS_UBOOT */
  BSP_bus_frequency = BSP_CLKIN_FRQ * BSP_SYSPLL_MF / BSP_SYSPLL_CKID;
  bsp_clicks_per_usec = BSP_bus_frequency / 4000000;
#endif /* HAS_UBOOT */

  /* Initialize some console parameters */
  for (i = 0; i < Console_Port_Count; ++i) {
    Console_Port_Tbl [i].ulClock = BSP_bus_frequency;

    #ifdef HAS_UBOOT
      Console_Port_Tbl [i].pDeviceParams =
        (void *) bsp_uboot_board_info.bi_baudrate;
    #endif
  }

  /* Initialize exception handler */
  sc = ppc_exc_initialize(
    PPC_INTERRUPT_DISABLE_MASK_DEFAULT,
    interrupt_stack_start,
    interrupt_stack_size
  );
  if (sc != RTEMS_SUCCESSFUL) {
    BSP_panic("cannot initialize exceptions");
  }

  /* Install default handler for the decrementer exception */
  sc = ppc_exc_set_handler( ASM_DEC_VECTOR, mpc83xx_decrementer_exception_handler);
  if (sc != RTEMS_SUCCESSFUL) {
    BSP_panic("cannot install decrementer exception handler");
  }

  /* Initalize interrupt support */
  sc = bsp_interrupt_initialize();
  if (sc != RTEMS_SUCCESSFUL) {
    BSP_panic("cannot intitialize interrupts\n");
  }

#ifdef SHOW_MORE_INIT_SETTINGS
  printk("Exit from bspstart\n");
#endif
}
