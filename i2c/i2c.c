#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/irq.h"

#define I2C0_SLAVE_ADDR 0x42

#define GPIO_SDA0 4
#define GPIO_SCK0 5 

uint8_t ram_addr;
uint8_t ram[256];

void i2c0_irq_handler() {
    uint32_t status = i2c0_hw->intr_stat;
    uint32_t value;

    /* Check to see if we have received data from the I2C master. */
    if (status & I2C_IC_INTR_STAT_R_RX_FULL_BITS) {
        /* Read the data (this will clear the interrupt). */
        value = i2c0_hw->data_cmd;

        /* Check if this is the first byte we have received. */
        if (value & I2C_IC_DATA_CMD_FIRST_DATA_BYTE_BITS) {
            ram_addr = (uint8_t)(value & I2C_IC_DATA_CMD_BITS);
        }
        else {
            /* If it is not the first byte, store the data in the RAM. */
            ram[ram_addr++] = (uint8_t)(value & I2C_IC_DATA_CMD_BITS);
        }
    }

    /* Check if the I2C master is requesting data from us. */
    if (status & I2C_IC_INTR_STAT_R_RD_REQ_BITS) {
        /* Write the data from the current address in RAM. */
        i2c0_hw->data_cmd = (uint32_t)(ram[ram_addr++]);

        /* Clear the interrupt. */
        i2c0_hw->clr_rd_req;
    }
}

int main() {
    stdio_init_all();

    i2c_init(i2c0, 100e3);
    i2c_set_slave_mode(i2c0, true, I2C0_SLAVE_ADDR);

    gpio_set_function(GPIO_SDA0, GPIO_FUNC_I2C);
    gpio_set_function(GPIO_SCK0, GPIO_FUNC_I2C);
    gpio_pull_up(GPIO_SDA0);
    gpio_pull_up(GPIO_SCK0);

    ram_addr = 0;

    /* Select the interrupts we want. */
    i2c0_hw->intr_mask = I2C_IC_INTR_MASK_M_RD_REQ_BITS
        | I2C_IC_INTR_MASK_M_RX_FULL_BITS;

    /* Set up the interrupt handler. */
    irq_set_exclusive_handler(I2C0_IRQ, i2c0_irq_handler);
    /* Enable I2C interrupts. */
    irq_set_enabled(I2C0_IRQ, true);

    while (true) {
        tight_loop_contents();
    }

    return 0;
}
