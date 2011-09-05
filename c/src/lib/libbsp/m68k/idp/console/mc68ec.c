/*
 * mc68ec.c -- Low level support for the Motorola mc68ec0x0 board.
 *             Written by rob@cygnus.com (Rob Savoye)
 *
 *  $Id: mc68ec.c,v 1.6 2011/02/11 12:30:14 ralf Exp $
 */

#include "leds.h"

/*
 * rtems_bsp_delay -- delay execution. This is an ugly hack. It should
 *          use the timer, but I'm waiting for docs. (sigh)
 */
void rtems_bsp_delay(int num)
{
  while (num--)
    {
      __asm__ ("nop");
    }
}
