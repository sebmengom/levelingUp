cmake_minimum_required(VERSION 3.13...3.27)

set(PICO_BOARD pico_w)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-fno-exceptions -fno-rtti)

include(pico_sdk_import.cmake)

project(lvl3 C CXX ASM)

pico_sdk_init()

add_executable(lvl3 main.cpp board.cpp potTracker.cpp)

target_link_libraries(lvl3 pico_stdlib hardware_adc)

pico_enable_stdio_usb(lvl3 1)

pico_enable_stdio_uart(lvl3 0)

pico_add_extra_outputs(lvl3)

add_custom_target(flash COMMAND cp $<TARGET_FILE_DIR:lvl3>/lvl3.uf2 /Volumes/RPI-RP2/ DEPENDS lvl3 COMMENT "Flashing lvl3")
