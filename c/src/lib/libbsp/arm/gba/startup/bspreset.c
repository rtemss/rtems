/*
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: bspreset.c,v 1.2 2011/02/11 11:42:34 ralf Exp $
 */

#include <bsp.h>
#include <gba.h>

void bsp_reset(void)
{
  __asm__ volatile ("ldr  r0, =_gba_reset");
  __asm__ volatile ("bx   r0");
}
