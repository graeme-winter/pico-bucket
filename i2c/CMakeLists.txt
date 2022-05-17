cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/pi/C/pico/pico-sdk")

include(pico_sdk_import.cmake)

project(i2c C CXX ASM)

pico_sdk_init()

add_executable(i2c i2c.c)

pico_set_program_name(i2c "i2c")
pico_set_program_version(i2c "0.1")

# stdout -> UART
pico_enable_stdio_uart(i2c 1)
pico_enable_stdio_usb(i2c 0)

target_link_libraries(i2c pico_stdlib)
target_link_libraries(i2c hardware_i2c)

pico_add_extra_outputs(i2c)
