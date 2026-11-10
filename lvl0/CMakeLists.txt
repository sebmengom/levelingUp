cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico_w)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fno-exceptions -fno-rtti)

include(pico_sdk_import.cmake)

project(lvl0 C CXX ASM)

pico_sdk_init()

add_executable(lvl0 main.cpp)

target_link_libraries(lvl0 pico_stdlib)

pico_enable_stdio_usb(lvl0 1)

pico_enable_stdio_uart(lvl0 0)

pico_add_extra_outputs(lvl0)

add_custom_target(flash COMMAND cp $<TARGET_FILE_DIR:lvl0>/lvl0.uf2 /Volumes/RPI-RP2/ DEPENDS lvl0 COMMENT "Flashing lvl0")
