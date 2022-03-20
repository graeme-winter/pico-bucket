cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/pi/C/pico/pico-sdk")

include(pico_sdk_import.cmake)

project(pio_blink C CXX ASM)

pico_sdk_init()

add_executable(pio_blink pio_blink.c)

pico_generate_pio_header(pio_blink ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

pico_set_program_name(pio_blink "pio_blink")
pico_set_program_version(pio_blink "0.1")

pico_enable_stdio_uart(pio_blink 1)
pico_enable_stdio_usb(pio_blink 0)

target_link_libraries(pio_blink pico_stdlib hardware_pio)

pico_add_extra_outputs(pio_blink)

