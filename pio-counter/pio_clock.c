#include <stdio.h>

#include "clock.pio.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

int main() {

  static const uint pin = 17;

  PIO pio = pio0;

  uint sm = pio_claim_unused_sm(pio, true);

  uint offset = pio_add_program(pio, &clock_program);

  clock_program_init(pio, sm, offset, pin);

  pio_sm_set_enabled(pio, sm, true);

  while (true) {
    printf("%d\n", pio_sm_get_blocking(pio, sm));
  }
}
