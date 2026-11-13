# levelingUp

Learning embedded C++ on a Raspberry Pi Pico WH (RP2040), from the fundamentals up to my own RTOS.
Every level is a project I build myself. Each folder has its own `devlog.md` with what I built, the bugs I found, and what I learned.

## Progress

| Level | Project | Fundamentals | Status |
|---|---|---|---|
| [0](lvl0/) | Tick counter over USB | Toolchain, CMake from scratch, build vs. run time | ✅ Done |
| [1](lvl1/) | Serial calculator | Fixed-width types, overflow, signed/unsigned, `char` as a number, `struct`, pass by value / `&` / `const&`, `constexpr` |  ✅ Done|
| 2 | Binary counter on 4 LEDs (registers, no `gpio_put`) | Bitwise ops, memory-mapped I/O, reading the datasheet. Ohm's law, LED resistors | ⬜ |
| 3 | Pico voltmeter (pot + photoresistor) | ADC, non-blocking timing. Voltage dividers, pull-ups | ⬜ |
| 4 | Combination lock with 4 buttons | State machines, `enum class`. RC hardware debounce | ⬜ |
| 5 | Reaction-time game with IRQs | Interrupts, `volatile`, shared data | ⬜ |
| 6 | Buzzer melody + servo | Timers, PWM math. Powering loads safely | ⬜ |
| 7 | 4-digit 7-segment display via 74HC595 | Shift registers, SPI, multiplexing | ⬜ |
| 8 | Measuring the stack | Stack vs. heap vs. static, `.map` file, linker | ⬜ |
| 🏁 | Temperature station (LM35 + display + alarm) | Everything above, combined | ⬜ |
| → | **My own RTOS** | Scheduler, context switching | ⬜ |

## Hardware
- Raspberry Pi Pico WH
- Inland Electronic Parts Pack (LEDs, resistors, buttons, pot, photoresistors, LM35, 74HC595, 7-seg displays, buzzers, servo, breadboard)

## Build & flash
Each level is its own CMake project:

```sh
cd lvlN && mkdir -p build && cd build
cmake ..
make
# BOOTSEL: hold the button, plug in the Pico, release
cp lvlN.uf2 /Volumes/RPI-RP2/
```

Serial output: `screen /dev/tty.usbmodemXXXX 115200` (exit with `Ctrl-A`, `K`, `y`).

`scratch/` holds small programs that run on the Mac, for comparing against the Pico.
