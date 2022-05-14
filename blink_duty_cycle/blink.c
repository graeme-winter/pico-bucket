/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "blink.pio.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq,
                       float duty);

int main() {
  setup_default_uart();

  // todo get free sm
  PIO pio = pio0;
  uint offset = pio_add_program(pio, &blink_program);
  printf("Loaded program at %d\n", offset);

  blink_pin_forever(pio, 0, offset, 25, 1000, 0.1);
  blink_pin_forever(pio, 1, offset, 14, 1000, 0.1);
}

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq,
                       float duty) {
  blink_program_init(pio, sm, offset, pin);

  printf("Blinking pin %d at %d Hz %f\n", pin, freq, duty);
  int count = (clock_get_hz(clk_sys) / freq);
  int nn = count * duty;

  pio->txf[sm] = (count - nn) - 3;

  // copy 32 bits from OSR to ISR
  pio_sm_exec(pio, sm, pio_encode_pull(false, false));
  pio_sm_exec(pio, sm, pio_encode_out(pio_isr, 32));
  pio->txf[sm] = nn - 3;
  pio_sm_set_enabled(pio, sm, true);
}
