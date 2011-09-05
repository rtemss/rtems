/**
 * @file
 *
 * @ingroup lpc24xx_io
 *
 * @brief Input and output module.
 */

/*
 * Copyright (c) 2009-2011 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <bsp/io.h>
#include <bsp/system-clocks.h>

#define LPC24XX_PIN_SELECT(pin) (pin >> 4U)

#define LPC24XX_PIN_SELECT_SHIFT(pin) ((pin & 0xfU) << 1U)

#define LPC24XX_PIN_SELECT_MASK 0x3U

rtems_status_code lpc24xx_gpio_config(
  unsigned pin,
  lpc24xx_gpio_settings settings
)
{
  if (pin <= LPC24XX_IO_INDEX_MAX) {
    rtems_interrupt_level level;
    unsigned port = LPC24XX_IO_PORT(pin);
    unsigned bit = LPC24XX_IO_PORT_BIT(pin);
    unsigned select = LPC24XX_PIN_SELECT(pin);
    unsigned shift = LPC24XX_PIN_SELECT_SHIFT(pin);
    unsigned resistor = settings & LPC24XX_GPIO_RESISTOR_MASK;
    unsigned output = (settings & LPC24XX_GPIO_OUTPUT) != 0 ? 1U : 0U;

    /* Get resistor flags */
    switch (resistor) {
      case LPC24XX_GPIO_RESISTOR_PULL_UP:
      case LPC24XX_GPIO_RESISTOR_DEFAULT:
        resistor = 0x0U;
        break;
      case LPC24XX_GPIO_RESISTOR_NONE:
        resistor = 0x2U;
        break;
      case LPC24XX_GPIO_RESISTOR_PULL_DOWN:
        resistor = 0x3U;
        break;
      default:
        return RTEMS_INVALID_NUMBER;
    }

    rtems_interrupt_disable(level);

    /* Resistor */
    LPC24XX_PINMODE [select] =
      (LPC24XX_PINMODE [select] & ~(LPC24XX_PIN_SELECT_MASK << shift))
        | ((resistor & LPC24XX_PIN_SELECT_MASK) << shift);

    rtems_interrupt_flash(level);

    /* Input or output */
    LPC24XX_FIO [port].dir =
      (LPC24XX_FIO [port].dir & ~(1U << bit)) | (output << bit);

    rtems_interrupt_enable(level);
  } else {
    return RTEMS_INVALID_ID;
  }

  return RTEMS_SUCCESSFUL;
}

#define LPC24XX_MODULE_ENTRY(mod, pwr, clk, idx) \
  [mod] = { \
    .power = pwr, \
    .clock = clk, \
    .index = idx \
  }

typedef struct {
  unsigned char power : 1;
  unsigned char clock : 1;
  unsigned char index : 6;
} lpc24xx_module_entry;

static const lpc24xx_module_entry lpc24xx_module_table [] = {
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_ACF, 0, 1, 15),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_ADC, 1, 1, 12),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_BAT_RAM, 0, 1, 16),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_CAN_0, 1, 1, 13),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_CAN_1, 1, 1, 14),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_DAC, 0, 1, 11),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_EMC, 1, 0, 11),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_ETHERNET, 1, 0, 30),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_GPDMA, 1, 1, 29),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_GPIO, 0, 1, 17),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_I2C_0, 1, 1, 7),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_I2C_1, 1, 1, 19),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_I2C_2, 1, 1, 26),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_I2S, 1, 1, 27),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_LCD, 1, 0, 20),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_MCI, 1, 1, 28),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_PCB, 0, 1, 18),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_PWM_0, 1, 1, 5),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_PWM_1, 1, 1, 6),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_RTC, 1, 1, 9),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_SPI, 1, 1, 8),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_SSP_0, 1, 1, 21),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_SSP_1, 1, 1, 10),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_SYSCON, 0, 1, 30),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_TIMER_0, 1, 1, 1),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_TIMER_1, 1, 1, 2),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_TIMER_2, 1, 1, 22),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_TIMER_3, 1, 1, 23),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_UART_0, 1, 1, 3),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_UART_1, 1, 1, 4),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_UART_2, 1, 1, 24),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_UART_3, 1, 1, 25),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_USB, 1, 0, 31),
  LPC24XX_MODULE_ENTRY(LPC24XX_MODULE_WDT, 0, 1, 0)
};

static rtems_status_code lpc24xx_module_do_enable(
  lpc24xx_module module,
  lpc24xx_module_clock clock,
  bool enable
)
{
  rtems_interrupt_level level;
  bool has_power = false;
  bool has_clock = false;
  unsigned index = 0;

  if ((unsigned) module >= LPC24XX_MODULE_COUNT) {
      return RTEMS_INVALID_ID;
  }

  if ((clock & ~LPC24XX_MODULE_CLOCK_MASK) != 0U) {
    return RTEMS_INVALID_NUMBER;
  }

  has_power = lpc24xx_module_table [module].power;
  has_clock = lpc24xx_module_table [module].clock;
  index = lpc24xx_module_table [module].index;

  /* Enable or disable module */
  if (enable) {
    if (has_power) {
      rtems_interrupt_disable(level);
      PCONP |= 1U << index;
      rtems_interrupt_enable(level);
    }

    if (module != LPC24XX_MODULE_USB) {
      if (has_clock) {
        unsigned clock_shift = 2U * index;

        rtems_interrupt_disable(level);
        if (clock_shift < 32U) {
          PCLKSEL0 = (PCLKSEL0 & ~(LPC24XX_MODULE_CLOCK_MASK << clock_shift))
              | (clock << clock_shift);
        } else {
          clock_shift -= 32U;
          PCLKSEL1 = (PCLKSEL1 & ~(LPC24XX_MODULE_CLOCK_MASK << clock_shift))
              | (clock << clock_shift);
        }
        rtems_interrupt_enable(level);
      }
    } else {
      unsigned pllclk = lpc24xx_pllclk();
      unsigned usbsel = pllclk / 48000000U - 1U;

      if (usbsel > 15U || (usbsel % 2U != 1U) || (pllclk % 48000000U) != 0U) {
        return RTEMS_INCORRECT_STATE;
      }

      USBCLKCFG = usbsel;
    }
  } else {
    if (has_power) {
      rtems_interrupt_disable(level);
      PCONP &= ~(1U << index);
      rtems_interrupt_enable(level);
    }
  }

  return RTEMS_SUCCESSFUL;
}

rtems_status_code lpc24xx_module_enable(
  lpc24xx_module module,
  lpc24xx_module_clock clock
)
{
  return lpc24xx_module_do_enable(module, clock, true);
}

rtems_status_code lpc24xx_module_disable(
  lpc24xx_module module
)
{
  return lpc24xx_module_do_enable(module, 0U, false);
}

typedef rtems_status_code (*lpc24xx_pin_visitor)(
  volatile uint32_t *pinsel,
  uint32_t pinsel_mask,
  uint32_t pinsel_value,
  volatile uint32_t *fio_dir,
  uint32_t fio_bit
);

static rtems_status_code lpc24xx_pin_set_function(
  volatile uint32_t *pinsel,
  uint32_t pinsel_mask,
  uint32_t pinsel_value,
  volatile uint32_t *fio_dir,
  uint32_t fio_bit
)
{
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);
  *pinsel = (*pinsel & ~pinsel_mask) | pinsel_value;
  rtems_interrupt_enable(level);

  return RTEMS_SUCCESSFUL;
}

static rtems_status_code lpc24xx_pin_check_function(
  volatile uint32_t *pinsel,
  uint32_t pinsel_mask,
  uint32_t pinsel_value,
  volatile uint32_t *fio_dir,
  uint32_t fio_bit
)
{
  if ((*pinsel & pinsel_mask) == pinsel_value) {
    return RTEMS_SUCCESSFUL;
  } else {
    return RTEMS_IO_ERROR;
  }
}

static rtems_status_code lpc24xx_pin_set_input(
  volatile uint32_t *pinsel,
  uint32_t pinsel_mask,
  uint32_t pinsel_value,
  volatile uint32_t *fio_dir,
  uint32_t fio_bit
)
{
  rtems_interrupt_level level;

  rtems_interrupt_disable(level);
  *fio_dir &= ~fio_bit;
  *pinsel &= ~pinsel_mask;
  rtems_interrupt_enable(level);

  return RTEMS_SUCCESSFUL;
}

static rtems_status_code lpc24xx_pin_check_input(
  volatile uint32_t *pinsel,
  uint32_t pinsel_mask,
  uint32_t pinsel_value,
  volatile uint32_t *fio_dir,
  uint32_t fio_bit
)
{
  if ((*pinsel & pinsel_mask) == 0 && (*fio_dir & fio_bit) == 0) {
    return RTEMS_SUCCESSFUL;
  } else {
    return RTEMS_IO_ERROR;
  }
}

static const lpc24xx_pin_visitor lpc24xx_pin_visitors [] = {
  [LPC24XX_PIN_SET_FUNCTION] = lpc24xx_pin_set_function,
  [LPC24XX_PIN_CHECK_FUNCTION] = lpc24xx_pin_check_function,
  [LPC24XX_PIN_SET_INPUT] = lpc24xx_pin_set_input,
  [LPC24XX_PIN_CHECK_INPUT] = lpc24xx_pin_check_input
};

rtems_status_code lpc24xx_pin_config(
  const lpc24xx_pin_range *pins,
  lpc24xx_pin_action action
)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;

  if ((unsigned) action <= LPC24XX_PIN_CHECK_INPUT) {
    lpc24xx_pin_visitor visitor = lpc24xx_pin_visitors [action];
    lpc24xx_pin_range terminal = LPC24XX_PIN_TERMINAL;

    while (sc == RTEMS_SUCCESSFUL && pins->value != terminal.value) {
      uint32_t port = pins->fields.port;
      uint32_t index = pins->fields.index_begin;
      uint32_t last = pins->fields.index_last;
      uint32_t function = pins->fields.function;
      volatile uint32_t *fio_dir = &LPC24XX_FIO [port].dir;

      while (sc == RTEMS_SUCCESSFUL && index <= last) {
        uint32_t pin = LPC24XX_IO_INDEX_BY_PORT(port, index);
        uint32_t select = LPC24XX_PIN_SELECT(pin);
        uint32_t shift = LPC24XX_PIN_SELECT_SHIFT(pin);
        volatile uint32_t *pinsel = &LPC24XX_PINSEL [select];
        uint32_t pinsel_mask = LPC24XX_PIN_SELECT_MASK << shift;
        uint32_t pinsel_value = (function & LPC24XX_PIN_SELECT_MASK) << shift;
        uint32_t fio_bit = 1U << index;

        sc = (*visitor)(pinsel, pinsel_mask, pinsel_value, fio_dir, fio_bit);

        ++index;
      }

      ++pins;
    }
  } else {
    sc = RTEMS_NOT_DEFINED;
  }

  return sc;
}
