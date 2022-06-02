#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"

#include "clock.pio.h"
#include "timer.pio.h"

int main() {
  setup_default_uart();

  const uint32_t output_pin = 16;
  const uint32_t input_pin = 17;

  // pio0 - input timer
  // pio1 - output clock

  uint32_t offset0 = pio_add_program(pio0, &clock_program);

  clock_program_init(pio0, 0, offset0, input_pin, 1);

  uint32_t offset1 = pio_add_program(pio1, &timer_program);

  timer_program_init(pio1, 0, offset1, output_pin, 125);

  pio1->txf[0] = 500000 - 3;

  pio_sm_set_enabled(pio1, 0, true);
  pio_sm_set_enabled(pio0, 0, true);

  while (true) {
    uint32_t ticks = pio_sm_get_blocking(pio0, 0) - 1;
    if (ticks & 0x80000000) {
      ticks = 5 * (0xffffffff - ticks);
      printf("High: %d\n", ticks);
    } else {
      ticks = 5 * (0x7fffffff - ticks);
      printf("Low:  %d\n", ticks);
    }
  }
}
