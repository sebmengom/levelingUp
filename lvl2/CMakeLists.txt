cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico_w)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fno-exceptions -fno-rtti)

include(pico_sdk_import.cmake)

project(lvl2 C CXX ASM)

pico_sdk_init()

add_executable(lvl2 main.cpp ledControl.cpp)

target_link_libraries(lvl2 pico_stdlib)

pico_enable_stdio_usb(lvl2 1)

pico_enable_stdio_uart(lvl2 0)

pico_add_extra_outputs(lvl2)

add_custom_target(flash COMMAND cp $<TARGET_FILE_DIR:lvl2>/lvl2.uf2 /Volumes/RPI-RP2/ DEPENDS lvl2 COMMENT "Flashing lvl2")
