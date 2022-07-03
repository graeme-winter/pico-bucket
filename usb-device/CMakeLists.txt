cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/pi/C/pico/pico-sdk")

include(pico_sdk_import.cmake)

project(usbd C CXX ASM)

pico_sdk_init()

add_executable(usbd dev_lowlevel.c)

pico_set_program_name(usbd "usbd")
pico_set_program_version(usbd "0.1")

pico_enable_stdio_uart(usbd 1)
pico_enable_stdio_usb(usbd 0)

target_link_libraries(usbd pico_stdlib)

target_link_libraries(usbd hardware_irq hardware_resets)

pico_add_extra_outputs(usbd)
