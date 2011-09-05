/**
 *  @file
 *
 *  LEON3 SMP Obtain CPU Core Number
 */

/*
 *  COPYRIGHT (c) 1989-2011.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: getcpuid.c,v 1.2 2011/06/29 15:12:08 joel Exp $
 */

int bsp_smp_processor_id(void)
{
  unsigned int id;
  __asm__ __volatile__( "rd     %%asr17,%0\n\t" : "=r" (id) : );

  return ((id >> 28) & 0xff);
}

