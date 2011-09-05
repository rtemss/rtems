/*
 *  COPYRIGHT (c) 1989-2009.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: bspreset.c,v 1.2 2011/02/11 11:42:36 ralf Exp $
 */

#include <rtems.h>
#include <bsp/bootcard.h>
#include <bsp/swi.h>

void bsp_reset( void )
{
  __asm__ ("swi %a0" :: "i" (SWI_Exit));
}
