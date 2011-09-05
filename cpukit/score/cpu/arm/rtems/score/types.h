/**
 * @file
 *
 * @ingroup ScoreCPU
 *
 * @brief ARM architecture types API.
 */

/*
 *  $Id: types.h,v 1.20 2010/07/29 17:51:31 joel Exp $
 *
 *  This include file contains type definitions pertaining to the
 *  arm processor family.
 *
 *  COPYRIGHT (c) 2000 Canon Research Centre France SA.
 *  Emmanuel Raguet, mailto:raguet@crf.canon.fr
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 */

#ifndef _RTEMS_SCORE_TYPES_H
#define _RTEMS_SCORE_TYPES_H

#include <rtems/score/basedefs.h>

#ifndef ASM

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ScoreCPU
 *
 * @{
 */

/*
 *  This section defines the basic types for this processor.
 */

typedef uint16_t         Priority_bit_map_Control;

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif
