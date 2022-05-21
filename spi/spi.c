#include "hardware/spi.h"
#include "hardware/dma.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20000

int main() {
  stdio_init_all();

  spi_inst_t *spix = spi0;
  
  printf("SPI start\n");
  // ~ 1 MHz transfer
  printf("Baud rate %d\n", spi_init(spix, 10000000));
  spi_set_format(spix, 8, 1, 1, SPI_MSB_FIRST);

  // 10...13 for spi1
  // 16...19 for spi0
  if (spix == spi0) {
    gpio_set_function(16, GPIO_FUNC_SPI);
    gpio_set_function(17, GPIO_FUNC_SPI);
    gpio_set_function(18, GPIO_FUNC_SPI);
    gpio_set_function(19, GPIO_FUNC_SPI);
  } else {
    gpio_set_function(10, GPIO_FUNC_SPI);
    gpio_set_function(11, GPIO_FUNC_SPI);
    gpio_set_function(12, GPIO_FUNC_SPI);
    gpio_set_function(13, GPIO_FUNC_SPI);
  }    
    
  spi_set_slave(spix, true);

  uint8_t buffer[BUFFER_SIZE], buffer2[BUFFER_SIZE];
  for (int j = 0; j < BUFFER_SIZE; j++) {
    buffer[j] = 0xff;
  }
  for (int cycle = 0;;cycle++) {
    // set up buffer for next cycle
    for (int j = 0; j < BUFFER_SIZE; j++) {
      buffer[j] = (cycle + j) % 0x100;
    }
    int nn = spi_write_read_blocking(spix, buffer, buffer2, BUFFER_SIZE);
    printf("Cycle: %d N: %d\n", cycle, nn);
  }

  return 0;
}
