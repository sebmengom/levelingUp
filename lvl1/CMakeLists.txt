cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico_w)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fno-exceptions -fno-rtti)

include(pico_sdk_import.cmake)

project(lvl1 C CXX ASM)

pico_sdk_init()

add_executable(lvl1 main.cpp)

target_link_libraries(lvl1 pico_stdlib)

pico_enable_stdio_usb(lvl1 1)

pico_enable_stdio_uart(lvl1 0)

pico_add_extra_outputs(lvl1)

add_custom_target(flash COMMAND cp $<TARGET_FILE_DIR:lvl1>/lvl1.uf2 /Volumes/RPI-RP2/ DEPENDS lvl1 COMMENT "Flashing lvl1")
