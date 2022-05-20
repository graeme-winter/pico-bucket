#include "hardware/spi.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 64

int main() {
  stdio_init_all();

  printf("SPI start\n");
  // 1MHz transfer
  printf("Baud rate %d\n", spi_init(spi_default, 1000000));
  spi_set_format(spi_default, 8, 1, 1, SPI_MSB_FIRST);
  
  gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
  gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI);
  
  spi_set_slave(spi_default, true);
  // grab unused dma channel for sending data
  // const uint32_t dma_tx = dma_claim_unused_channel(true);

  static uint8_t buffer[BUFFER_SIZE];

  // read from channel
  printf("Reading\n");
  spi_read_blocking(spi_default, 0, buffer, BUFFER_SIZE);
  printf("First item: %d\n", buffer[0]);
  
  for (uint16_t j = 0; j < BUFFER_SIZE; j++) {
    buffer[j] = j % 0x100;
  }

  // dma_channel_config config = dma_channel_get_default_config(dma_tx);
  // channel_config_set_transfer_data_size(&config, DMA_SIZE_16);
  // channel_config_set_dreq(&config, spi_get_dreq(spi_default, true));
  // dma_channel_configure(dma_tx, &config, &spi_get_hw(spi_default)->dr, buffer,
  //                       BUFFER_SIZE, false);
  // printf("DMA start\n");
  // dma_channel_start(dma_tx);
  // printf("Waiting for DMA completion\n");
  // dma_channel_wait_for_finish_blocking(dma_tx);
  // printf("DMA finished\n");
  printf("Waiting for writable\n");
  while (!spi_is_writable(spi_default)) {
    tight_loop_contents();
  }
  printf("Write\n");
  int nn = spi_write_blocking(spi_default, buffer, BUFFER_SIZE);
  printf("Wrote %d bytes\n", nn);

  // clean up
  // dma_channel_unclaim(dma_tx);
  return 0;
}
