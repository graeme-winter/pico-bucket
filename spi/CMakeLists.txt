cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/pi/C/pico/pico-sdk")

include(pico_sdk_import.cmake)

project(spi C CXX ASM)

pico_sdk_init()

add_executable(spi spi.c)

pico_set_program_name(spi "spi")
pico_set_program_version(spi "0.1")

# stdout -> UART
pico_enable_stdio_uart(spi 1)
pico_enable_stdio_usb(spi 0)

target_link_libraries(spi pico_stdlib)
target_link_libraries(spi hardware_spi)
target_link_libraries(spi hardware_dma)

pico_add_extra_outputs(spi)
