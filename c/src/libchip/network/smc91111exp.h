/*
 *  $Id: smc91111exp.h,v 1.4 2011/08/30 13:16:35 sh Exp $
 */

#ifndef _SMC91111_EXP_H_
#define _SMC91111_EXP_H_

#include <bsp.h>

typedef struct scmv91111_configuration {
  void                     *baseaddr;
  unsigned int              vector;
  unsigned int              pio;
  unsigned int              ctl_rspeed;
  unsigned int              ctl_rfduplx;
  unsigned int              ctl_autoneg;
#ifdef BSP_FEATURE_IRQ_EXTENSION
  const char *              info;
  rtems_option              options;
  rtems_interrupt_handler   interrupt_wrapper;
  void *                    arg;
#endif
} scmv91111_configuration_t;

#endif  /* _SMC_91111_EXP_H_ */


