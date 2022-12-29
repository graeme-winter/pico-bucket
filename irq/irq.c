#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"

// GPIO input

#define BTN0 11
#define BTN1 12
#define BTN2 13

volatile bool pressed[3] = {false, false, false};

// GPIO output

#define LED0 18
#define LED1 19
#define LED2 20

// IRQ handler

void __not_in_flash_func(irq_callback)(uint32_t gpio, uint32_t event) {
  pressed[gpio - BTN0] = true;
}

int main() {
  setup_default_uart();

  // set up all GPIO - input and output

  for (uint32_t btn = BTN0; btn <= BTN2; btn++) {
    gpio_init(btn);
    gpio_set_dir(btn, GPIO_IN);
    gpio_pull_down(btn);
  }

  for (uint32_t led = LED0; led <= LED2; led++) {
    gpio_init(led);
    gpio_set_dir(led, GPIO_OUT);
  }

  // set up interrupts - handler first then enable for others

  uint32_t mask = GPIO_IRQ_EDGE_FALL;
  gpio_set_irq_enabled_with_callback(BTN0, mask, true, &irq_callback);
  gpio_set_irq_enabled(BTN1, mask, true);
  gpio_set_irq_enabled(BTN2, mask, true);

  while (true) {
    uint32_t irq_flags = save_and_disable_interrupts();
    for (uint32_t btn = BTN0; btn <= BTN2; btn++) {
      if (pressed[btn - BTN0]) {
        gpio_xor_mask(1 << (btn + 7));
        pressed[btn - BTN0] = false;
      }
    }
    restore_interrupts(irq_flags);
    sleep_ms(10);
  }
}
