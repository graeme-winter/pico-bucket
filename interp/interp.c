#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/interp.h"
#include "hardware/dma.h"




int main()
{
    stdio_init_all();

    // Interpolator example code
    interp_config cfg = interp_default_config();
    // Now use the various interpolator library functions for your use case
    // e.g. interp_config_clamp(&cfg, true);
    //      interp_config_shift(&cfg, 2);
    // Then set the config 
    interp_set_config(interp0, 0, &cfg);


    puts("Hello, world!");

    return 0;
}
