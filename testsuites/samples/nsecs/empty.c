/*  COPYRIGHT (c) 1989-2007.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: empty.c,v 1.3 2011/02/22 10:54:32 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* put here hoping it won't get inlined */
void dummy_function_empty_body_to_force_call(void) {}

