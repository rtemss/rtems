/**
 * @file
 *
 * @ingroup lpc32xx_nand_mlc
 *
 * @brief NAND MLC controller API.
 */

/*
 * Copyright (c) 2010-2011 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * Copyright (c) 2011 Stephan Hoffmann <sho@reLinux.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef LIBBSP_ARM_LPC32XX_NAND_MLC_H
#define LIBBSP_ARM_LPC32XX_NAND_MLC_H

#include <rtems.h>

#include <bsp/utility.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup lpc32xx_nand_mlc NAND MLC Controller
 *
 * @ingroup lpc32xx
 *
 * @brief NAND MLC Controller.
 *
 * Timing constraints:
 *
 * -# (WR_LOW + 1) / HCLK >= tWP
 * -# (WR_HIGH - WR_LOW) / HCLK >= tWH
 * -# (WR_LOW + 1) / HCLK + (WR_HIGH - WR_LOW) / HCLK >= tWC
 * -# (RD_LOW + 1) / HCLK >= tRP
 * -# (RD_LOW + 1) / HCLK >= tREA + tSU
 * -# (RD_HIGH - RD_LOW) / HCLK >= tREH
 * -# (RD_LOW + 1) / HCLK + (RD_HIGH - RD_LOW) / HCLK >= tRC
 * -# (RD_HIGH - RD_LOW) / HCLK + NAND_TA / HCLK >= tRHZ
 * -# BUSY_DELAY / HCLK >= max(tWB, tRB)
 * -# TCEA_DELAY / HCLK >= tCEA - tREA
 *
 * Known flash layouts (Format: SP = small pages, LP = large pages / address
 * cycles / pages per block):
 *
 * -# SP/3/32
 * -# SP/4/32
 * -# LP/4/64
 * -# LP/5/64
 * -# LP/5/128
 *
 * @{
 */

/**
 * @name MLC NAND Flash Dimensions
 *
 * @{
 */

#define MLC_SMALL_PAGE_SIZE 528
#define MLC_SMALL_DATA_SIZE 512
#define MLC_SMALL_SPARE_SIZE 16
#define MLC_SMALL_DATA_WORD_COUNT (MLC_SMALL_DATA_SIZE / 4)
#define MLC_SMALL_SPARE_WORD_COUNT (MLC_SMALL_SPARE_SIZE / 4)
#define MLC_SMALL_PAGES_PER_LARGE_PAGE 4
#define MLC_LARGE_PAGE_SIZE \
  (MLC_SMALL_PAGES_PER_LARGE_PAGE * MLC_SMALL_PAGE_SIZE)
#define MLC_LARGE_DATA_SIZE \
  (MLC_SMALL_PAGES_PER_LARGE_PAGE * MLC_SMALL_DATA_SIZE)
#define MLC_LARGE_SPARE_SIZE \
  (MLC_SMALL_PAGES_PER_LARGE_PAGE * MLC_SMALL_SPARE_SIZE)
#define MLC_LARGE_DATA_WORD_COUNT (MLC_LARGE_DATA_SIZE / 4)
#define MLC_LARGE_SPARE_WORD_COUNT (MLC_LARGE_SPARE_SIZE / 4)

/** @} */

/**
 * @name NAND Flash Clock Control Register (FLASHCLK_CTRL)
 *
 * @{
 */

#define FLASHCLK_IRQ_MLC BSP_BIT32(5)
#define FLASHCLK_MLC_DMA_RNB BSP_BIT32(4)
#define FLASHCLK_MLC_DMA_INT BSP_BIT32(3)
#define FLASHCLK_SELECT_SLC BSP_BIT32(2)
#define FLASHCLK_MLC_CLK_ENABLE BSP_BIT32(1)
#define FLASHCLK_SLC_CLK_ENABLE BSP_BIT32(0)

/** @} */

/**
 * @name MLC NAND Timing Register (MLC_TIME_REG)
 *
 * @{
 */

#define MLC_TIME_WR_LOW(val) BSP_FLD32(val, 0, 3)
#define MLC_TIME_WR_HIGH(val) BSP_FLD32(val, 4, 7)
#define MLC_TIME_RD_LOW(val) BSP_FLD32(val, 8, 11)
#define MLC_TIME_RD_HIGH(val) BSP_FLD32(val, 12, 15)
#define MLC_TIME_NAND_TA(val) BSP_FLD32(val, 16, 18)
#define MLC_TIME_BUSY_DELAY(val) BSP_FLD32(val, 19, 23)
#define MLC_TIME_TCEA_DELAY(val) BSP_FLD32(val, 24, 25)

/** @} */

/**
 * @name MLC NAND Lock Protection Register (MLC_LOCK_PR)
 *
 * @{
 */

#define MLC_UNLOCK_PROT 0xa25e

/** @} */

/**
 * @name MLC NAND Status Register (MLC_ISR)
 *
 * @{
 */

#define MLC_ISR_DECODER_FAILURE BSP_BIT32(6)
#define MLC_ISR_ERRORS_DETECTED BSP_BIT32(3)
#define MLC_ISR_ECC_READY BSP_BIT32(2)
#define MLC_ISR_CONTROLLER_READY BSP_BIT32(1)
#define MLC_ISR_NAND_READY BSP_BIT32(0)

/** @} */

/**
 * @name MLC NAND Controller Configuration Register (MLC_ICR)
 *
 * @{
 */

#define MLC_ICR_SOFT_WRITE_PROT BSP_BIT32(3)
#define MLC_ICR_LARGE_PAGES BSP_BIT32(2)
#define MLC_ICR_ADDR_WORD_COUNT_4_5 BSP_BIT32(1)
#define MLC_ICR_IO_BUS_16 BSP_BIT32(0)

/** @} */

/**
 * @name MLC NAND Auto Encode Register (MLC_ECC_AUTO_ENC)
 *
 * @{
 */

#define MLC_ECC_AUTO_ENC_PROGRAM BSP_BIT32(8)

/** @} */

#define MLC_BAD_BLOCK_MASK ((uint32_t) 0xff00)

/**
 * @brief Bad block mark.
 * 
 * We define our own bad block mark to be able to recognize the blocks that
 * have been marked bad during operation later.
 */
#define MLC_BAD_BLOCK_MARK ((uint32_t) 0xbadb)

/**
 * @brief The bytes 4 and 5 are reserved for bad block handling.
 */
#define MLC_RESERVED ((uint32_t) 0xffff)

/**
 * @name NAND Status Register
 *
 * @{
 */

#define NAND_STATUS_ERROR (1U << 0)
#define NAND_STATUS_READY (1U << 6)
#define NAND_STATUS_NOT_PROTECTED (1U << 7)

/** @} */

/**
 * @brief MLC NAND controller configuration.
 */
typedef struct {
  uint32_t flags;

  uint32_t block_count;

  /**
   * @brief Value for the MLC NAND Timing Register (MLC_TIME_REG).
   */
  uint32_t time;
} lpc32xx_mlc_config;

/**
 * @brief Selects small pages (512 Bytes user data and 16 Bytes spare data)
 * or large pages (2048 Bytes user data and 64 Bytes spare data).
 */
#define MLC_SMALL_PAGES 0x1U

/**
 * @Brief Selects 3/4 address cycles for small pages/large pages or 4/5
 * address cycles.
 */
#define MLC_MANY_ADDRESS_CYCLES 0x2U

/**
 * @brief Selects 64 or 128 pages per block in case of large pages.
 */
#define MLC_NORMAL_BLOCKS 0x4U

/**
 * @brief Initializes the MLC NAND controller according to @a cfg.
 */
void lpc32xx_mlc_init(const lpc32xx_mlc_config *cfg);

uint32_t lpc32xx_mlc_page_size(void);

uint32_t lpc32xx_mlc_pages_per_block(void);

uint32_t lpc32xx_mlc_block_count(void);

void lpc32xx_mlc_write_protection(
  uint32_t page_index_low,
  uint32_t page_index_high
);

void lpc32xx_mlc_read_id(uint8_t *id, size_t n);

/**
 * @brief Reads the page with index @a page_index.
 *
 * 32-bit reads will be performed.
 *
 * Bytes 7 to 15 of the spare area will contain the ECC.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_INVALID_ID Invalid @a page_index value.
 * @retval RTEMS_IO_ERROR Uncorrectable bit error.
 */
rtems_status_code lpc32xx_mlc_read_page(
  uint32_t page_index,
  uint32_t *data,
  uint32_t *spare
);

/**
 * @brief Erases the block with index @a block_index.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_INVALID_ID Invalid @a block_index value.
 * @retval RTEMS_IO_ERROR Erase error.
 */
rtems_status_code lpc32xx_mlc_erase_block(uint32_t block_index);

/**
 * @brief Erases the block with index @a block_index.
 *
 * In case of an erase error all pages and the spare areas of this block are
 * programmed with zero values.  This will mark the first and second page as
 * bad.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_INCORRECT_STATE The first or second page of this block is bad.
 * @retval RTEMS_INVALID_ID Invalid @a block_index value.
 * @retval RTEMS_IO_ERROR Erase error.
 */
rtems_status_code lpc32xx_mlc_erase_block_safe(uint32_t block_index);

/**
 * @brief Erases the block with index @a block_index.
 *
 * Variant of lpc32xx_mlc_erase_block_safe() with more parameters for
 * efficiency reasons.  The @a page_begin must be the index of the first page
 * of the block.  The @a page_end must be the page index of the last page of
 * the block plus one.
 */
rtems_status_code lpc32xx_mlc_erase_block_safe_3(
  uint32_t block_index,
  uint32_t page_begin,
  uint32_t page_end
);

/**
 * @brief Writes zero values to the pages specified by @a page_begin and
 * @a page_end.
 *
 * The data and spare area are cleared to zero.  This marks the pages as bad.
 */
void lpc32xx_mlc_zero_pages(uint32_t page_begin, uint32_t page_end);

/**
 * @brief Writes the page with index @a page_index.
 *
 * 32-bit writes will be performed.
 *
 * Bytes 7 to 15 of the spare area will be used for the automatically generated
 * ECC.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_INVALID_ID Invalid @a page_index value.
 * @retval RTEMS_IO_ERROR Write error.
 */
rtems_status_code lpc32xx_mlc_write_page_with_ecc(
  uint32_t page_index,
  const uint32_t *data,
  const uint32_t *spare
);

/**
 * @brief Writes @a src_size Bytes from @a src to the flash area specified by
 * @a block_begin and @a block_end.
 *
 * The @a page_buffer will be used as an intermediate buffer.
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_INVALID_ID Invalid @a block_begin or @a block_end value.
 * @retval RTEMS_IO_ERROR Too many bad blocks or source area too big.
 */
rtems_status_code lpc32xx_mlc_write_blocks(
  uint32_t block_begin,
  uint32_t block_end,
  const void *src,
  size_t src_size,
  uint32_t page_buffer [MLC_LARGE_DATA_WORD_COUNT]
);

/**
 * @brief Read blocks process function type.
 *
 * @see lpc32xx_mlc_read_blocks().
 *
 * @retval false Continue processing.
 * @retval true Stop processing.
 */
typedef bool (*lpc32xx_mlc_read_process)(
  void *process_arg,
  uint32_t page_index,
  uint32_t page_size,
  uint32_t page_data [MLC_LARGE_DATA_WORD_COUNT],
  uint32_t page_spare [MLC_LARGE_SPARE_WORD_COUNT]
);

/**
 * @brief Reads the pages of block @a block_begin up to and excluding
 * @a block_end.
 *
 * For each page @a process will be called with the @a process_arg parameter,
 * the page_index, the page data and the page spare.
 *
 * The @a page_buffer_0 and @a page_buffer_1 will be used as
 * intermediate buffers.
 */
rtems_status_code lpc32xx_mlc_read_blocks(
  uint32_t block_begin,
  uint32_t block_end,
  lpc32xx_mlc_read_process process,
  void *process_arg,
  uint32_t page_buffer_0 [MLC_LARGE_DATA_WORD_COUNT],
  uint32_t page_buffer_1 [MLC_LARGE_DATA_WORD_COUNT]
);

static inline bool lpc32xx_mlc_is_bad_page(const uint32_t *spare)
{
  return (spare [1] & MLC_BAD_BLOCK_MASK) != MLC_BAD_BLOCK_MASK;
}

static inline void lpc32xx_mlc_set_bad_page(uint32_t *spare)
{
  spare [1] = MLC_BAD_BLOCK_MARK;
}

static inline void lpc32xx_mlc_set_reserved(uint32_t *spare)
{
  spare [1] = MLC_RESERVED;
}

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_LPC32XX_NAND_MLC_H */
