cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/pi/C/pico/pico-sdk")

include(pico_sdk_import.cmake)

project(blink C CXX ASM)

pico_sdk_init()

add_executable(blink blink.c)

pico_generate_pio_header(blink ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

pico_set_program_name(blink "blink")
pico_set_program_version(blink "0.1")

pico_enable_stdio_uart(blink 1)
pico_enable_stdio_usb(blink 0)

target_link_libraries(blink pico_stdlib hardware_pio)

pico_add_extra_outputs(blink)

