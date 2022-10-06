cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "/home/pi/C/pico/pico-sdk")

include(pico_sdk_import.cmake)

project(interp C CXX ASM)

pico_sdk_init()

add_executable(interp interp.c )

pico_set_program_name(interp "interp")
pico_set_program_version(interp "0.1")

pico_enable_stdio_uart(interp 1)
pico_enable_stdio_usb(interp 0)

target_link_libraries(interp pico_stdlib)

target_link_libraries(interp hardware_interp)

pico_add_extra_outputs(interp)

