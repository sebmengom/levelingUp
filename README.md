# levelingUp

Learning embedded C++ on a Raspberry Pi Pico WH (RP2040), from the fundamentals up to my own RTOS.
Every level is a project I build myself. Each folder has its own `devlog.md` with what I built, the bugs I found, and what I learned.

## Progress

| Level | Project | Fundamentals | C++ | Status |
|---|---|---|---|---|
| [0](lvl0/) | Tick counter over USB | Toolchain, CMake from scratch, build vs. run time | `main`, `stdio`, `sleep_ms` | ✅ Done |
| [1](lvl1/) | Serial calculator | Fixed-width types, overflow, signed/unsigned, `char` as a number | `struct`, pass by value / `&` / `const&`, `constexpr` | ✅ Done |
| [2](lvl2/) | Binary counter on 4 LEDs + XOR blink + `GPIO_IN` readback (registers, no `gpio_put`) | Bitwise ops (`\|` `&` `^` `<<` `>>`), memory-mapped I/O, SET/CLR/XOR, `GPIO_OE`, `GPIO_IN`, reading the datasheet. Ohm's law, LED resistors | pointers, `volatile`, `reinterpret_cast`, `std::bitset` | ✅ Done |
| 2.5 | Refactor lvl2 | Same hardware, cleaner code | `class`, constructors, `private` | ⬜ Next |
| 3 | Pico voltmeter (pot + photoresistor) | ADC, non-blocking timing. Voltage dividers, pull-ups | more classes, `namespace` | ⬜ |
| 4 | Combination lock with 4 buttons | State machines. RC hardware debounce | `enum class`, `switch` | ⬜ |
| 5 | Reaction-time game with IRQs | Interrupts, shared data | passing functions (callbacks) | ⬜ |
| 6 | Buzzer melody + servo | Timers, PWM math. Powering loads safely | | ⬜ |
| 7 | 4-digit 7-segment display via 74HC595 | Shift registers, SPI, multiplexing | `std::array`, templates | ⬜ |
| 8 | Measuring the stack | `.map` file, linker | stack vs. heap vs. static | ⬜ |
| 🏁 | Temperature station (LM35 + display + alarm) | Everything above, combined | | ⬜ |
| → | **My own RTOS** | Scheduler, context switching | | ⬜ |

## Hardware
- Raspberry Pi Pico WH
- Inland Electronic Parts Pack (LEDs, resistors, buttons, pot, photoresistors, LM35, 74HC595, 7-seg displays, buzzers, servo, breadboard)

## Build & flash
Each level is its own CMake project:

```sh
cd lvlN && mkdir -p build && cd build
cmake ..
# BOOTSEL: hold the button, plug in the Pico, release
make flash      # builds, then copies lvlN.uf2 to /Volumes/RPI-RP2/
```

Serial output: `screen /dev/tty.usbmodemXXXX 115200` (exit with `Ctrl-A`, `K`, `y`).

`scratch/` holds small programs that run on the Mac, for comparing against the Pico.
