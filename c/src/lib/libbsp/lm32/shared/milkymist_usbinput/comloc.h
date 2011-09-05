/*  comloc.h
 *
 *  Milkymist USB input devices driver for RTEMS
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: comloc.h,v 1.1 2011/08/01 13:48:40 joel Exp $
 *
 *  COPYRIGHT (c) 2010 Sebastien Bourdeauducq
 */

#ifndef __COMLOC_H_
#define __COMLOC_H_

#define COMLOCV(x)  (*(volatile unsigned char *)(x))

#define COMLOC_DEBUG_PRODUCE  COMLOCV(MM_SOFTUSB_DMEM_BASE+0x1000)
#define COMLOC_DEBUG(offset)  COMLOCV(MM_SOFTUSB_DMEM_BASE+0x1001+offset)
#define COMLOC_MEVT_PRODUCE COMLOCV(MM_SOFTUSB_DMEM_BASE+0x1101)
#define COMLOC_MEVT(offset) COMLOCV(MM_SOFTUSB_DMEM_BASE+0x1102+offset)
#define COMLOC_KEVT_PRODUCE	COMLOCV(MM_SOFTUSB_DMEM_BASE+0x1142)
#define COMLOC_KEVT(offset)	COMLOCV(MM_SOFTUSB_DMEM_BASE+0x1143+offset)

#endif /* __COMLOC_H_ */
