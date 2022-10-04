#include "hardware/interp.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include <stdio.h>

int main() {
  volatile uint32_t count = 0;
  absolute_time_t t0, t1;

  stdio_init_all();

  // interpolator configuration
  interp_config cfg = interp_default_config();
  interp_set_config(interp0, 0, &cfg);

  interp0->accum[0] = 0;
  interp0->base[0] = 1;

  // dma configuration
  uint32_t dma_a, dma_b;
  dma_channel_config dmc_a, dmc_b;

  channel_config_set_transfer_data_size(&dmc_a, DMA_SIZE_32);
  channel_config_set_read_increment(&dmc_a, false);
  channel_config_set_write_increment(&dmc_a, false);
  channel_config_set_chain_to(&dmc_a, dma_b);

  channel_config_set_transfer_data_size(&dmc_b, DMA_SIZE_32);
  channel_config_set_read_increment(&dmc_b, false);
  channel_config_set_write_increment(&dmc_b, false);
  channel_config_set_chain_to(&dmc_b, dma_a);

  dma_channel_configure(dma_a, &dmc_a, (volatile void *)&count,
                        (const volatile void *) &(interp0->pop[0]), 125000000, false);
  dma_channel_start(dma_a);
  dma_channel_wait_for_finish_blocking(dma_a);

  while (true) {
    printf("%d\n", count);
  }

  return 0;
}
