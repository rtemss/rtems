/*
 *  $Id: loop.h,v 1.3 2010/12/08 10:30:27 sh Exp $
 */

#ifndef _RTEMS_BSDNET_LOOP_H
#define _RTEMS_BSDNET_LOOP_H

#ifdef __cplusplus
extern "C" {
#endif

#define NLOOP 1

void rtems_bsdnet_initialize_loop(void);

#ifdef __cplusplus
}
#endif

#endif /* _RTEMS_BSDNET_LOOP_H */
