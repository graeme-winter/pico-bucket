#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "blink.pio.h"

int main() {

    static const uint led_pin = 25;
    static const float pio_freq = 2000;

    PIO pio = pio0;

    uint sm = pio_claim_unused_sm(pio, true);

    uint offset = pio_add_program(pio, &blink_program);

    float div = (float)clock_get_hz(clk_sys) / pio_freq;

    blink_program_init(pio, sm, offset, led_pin, div);

    pio_sm_set_enabled(pio, sm, true);

    while (true) {
        sleep_ms(1000);
    }
}


