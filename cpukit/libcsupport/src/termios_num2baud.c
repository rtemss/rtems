/*
 *  COPYRIGHT (c) 1989-2008.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: termios_num2baud.c,v 1.4 2010/07/24 16:12:49 joel Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/termios.h>
#include <rtems/termiostypes.h>
#include <rtems/assoc.h>

extern rtems_assoc_t termios_assoc_table[];

int rtems_termios_number_to_baud(
  int32_t baud
)
{
  int termios_baud;

  termios_baud = rtems_assoc_remote_by_local( termios_assoc_table, baud );
  if ( termios_baud == 0 && baud != 0 )
    return -1;
  return termios_baud;
}
