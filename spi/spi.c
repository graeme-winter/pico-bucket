#include "hardware/spi.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
  stdio_init_all();

  printf("SPI start\n");
  // 1MHz transfer
  spi_init(spi1, 1e6);

  gpio_set_function(10, GPIO_FUNC_SPI);
  gpio_set_function(11, GPIO_FUNC_SPI);
  gpio_set_function(12, GPIO_FUNC_SPI);

  // grab unused dma channel for sending data
  const uint32_t dma_tx = dma_claim_unused_channel(true);

  static uint16_t buffer[BUFFER_SIZE];

  for (uint16_t j = 0; j < BUFFER_SIZE; j++) {
    buffer[j] = j;
  }

  dma_channel_config config = dma_channel_get_default_config(dma_tx);
  channel_config_set_transfer_data_size(&config, DMA_SIZE_16);
  channel_config_set_dreq(&config, spi_get_dreq(spi_default, true));
  dma_channel_configure(dma_tx, &config, &spi_get_hw(spi_default)->dr, txbuf,
                        BUFFER_SIZE, false);
  printf("DMA start\n");
  dma_channel_start(dma_tx);
  printf("Waiting for DMA completion\n");
  dma_channel_wait_for_finish_blocking(dma_tx);
  printf("DMA finished\n");

  // clean up
  dma_channel_unclaim(dma_tx);
  return 0;
}
