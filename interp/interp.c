#include "hardware/interp.h"
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
  volatile uint32_t count = 0;
  absolute_time_t t0, t1;

  stdio_init_all();

  // interpolator configuration
  interp_config cfg = interp_default_config();
  interp_set_config(interp0, 0, &cfg);

  while (true) {
    register int x;
    interp0->accum[0] = 0;
    interp0->base[0] = 1;
    t0 = time_us_32();
    for (int j = 0; j < 125000000; j++) {
      x = interp0->pop[0];
    }
    t1 = time_us_32();
    printf("%d %d\n", x, t1 - t0);
  }

  return 0;
}
