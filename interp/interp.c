#include "hardware/interp.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
  stdio_init_all();

  interp_config cfg = interp_default_config();
  interp_set_config(interp0, 0, &cfg);

  interp0->accum[0] = 0;
  interp0->base[0] = 1;

  while (true) {
    for (int j = 0; j < 1000000; j++) {
      interp0->pop[0];
    }
    printf("%d\n", interp0->pop[0]);
  }

  return 0;
}
