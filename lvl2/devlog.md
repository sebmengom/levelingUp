# Devlog LVL2

## What I did:
 I developed a binary counter for the Raspberry Pi Pico WH, using memory addresses instead of the gpio_put function. I used constant expressions to log the addresses of different registers that I got from the datasheet. Then I created a pin mask to initialize the pins I used for the task, in this case the pins were 14, 15, 16, and 17. Then I proceeded to make 3 different volatile pointers in order to point at different registers inside of the memory, all of them use the constant SIO_B + the register to point at the address. After initializing all pins, I flipped the pin mask pins into output mode by writing on the oe_set address. Then came the logic inside of the while loop: first it turns off all the LEDs that were on by clearing all of the pins in output mode, sleeps, and writes the binary value of the current counter value shifted by 14 bits inside of the out_set register address, sleeps, increases the counter, and checks if the counter is over 15. It can't go over 15 since that is the max number that can be represented with 4 LEDs. On top of the counter, a fifth LED on GP18 blinks using the `GPIO_OUT_XOR` register, and every loop the program reads `GPIO_IN`, keeps bits 14 to 17 and prints them in binary over USB.

## Circuit:
The circuit was pretty simple, just 4 LEDs connected normally, while their positive leg was plugged to the different GPIO pins I used, these being 14, 15, 16, and 17, as I mentioned previously. Later I added a fifth LED on GP18 for the XOR blink. Every LED has its own 220 Ω resistor.


## Bugs I found:

### 1. `PIN_MASK += 14` on a `const`
- **Symptom:** compile error, assignment to a read-only variable.
- **Cause:** `PIN_MASK` is `const`, so it can't change after it's created. The idea was also wrong: `+= 14` adds 14 to the number (`0b1` + 14 = 15 = `0b1111`, pins 0 to 3). It doesn't move a bit to pin 14.
- **Fix:** build the mask once with shifts and OR: `(1u << 14) | (1u << 15) | (1u << 16) | (1u << 17)`.

### 2. Init mask with only one pin
- **Symptom:** only the GP14 LED worked. The other three stayed off.
- **Cause:** the mask passed to `gpio_init_mask` had only bit 14, so GP15 to GP17 were never connected to SIO. Writing their bits in `OUT_SET` did nothing.
- **Fix:** pass the full `PIN_MASK` to `gpio_init_mask` and to `oe_set`.

### 3. Flashing an old `.uf2`
- **Symptom:** changed the code, flashed, and the Pico behaved exactly like before.
- **Cause:** copied the `.uf2` without rebuilding first, so it was the old firmware.
- **Fix:** always run `make` (or `make flash`) before copying.

### 4. First counter didn't count
- **Symptom:** no LEDs turned on.
- **Cause:** three mistakes left over from the chase code: `counter << 1` shifted only 1 place (pins 1 to 4, nothing connected); `counter <<= 1` doubled instead of adding 1 (1, 2, 4, 8...); and past 15 the `if` did `counter++` instead of going back to 0, so it kept growing.
- **Fix:** `counter << 14` to land on GP14 to GP17, `counter++` to count, and `counter = 0` when it passes 15, so it always fits in 4 bits.


## Experiments:

| Experiment | What I expected | What happened |
|---|---|---|
| `GPIO_OUT_XOR` (0x01c) toggle on GP18, same mask every loop, while the counter runs on GP14–17 | It would blink, because nothing else touches GP18 and XOR flips its current state every write. | 2 s on, 2 s off (4 s total, one flip per loop with my two `sleep_ms(1000)`). The counter kept working normally. |
| Read `GPIO_IN` (0x004): `(*in >> 14) & 0xF`, printed over USB | It would print the binary of what's at that address. | `std::cout` printed it in decimal, so I used `std::bitset<4>` to see the bits. The printed binary matched the LEDs on GP14–17 every time. |


## What I learned:
 I learned a lot during this mini project. I had no idea that you could tell the compiler, trust me I know that this is going to be used, and you can do that by using the volatile qualifier. I also became familiar with bit shifting for the first time. At first the concept was pretty difficult and weird, since I had no idea what I was supposed to do, but with research I found out how and why we do it. It was simpler than I thought. It was just basically, we are going to write N number inside of this address, but in order for the LEDs to turn on we have to write the value from position 14 to 17, so you write the value AND shift it by 14, to fill the used bits, which if I am not mistaken, there is only 30 usable values inside most of the registers since a couple of them are already reserved.

I also learned about the registers that control the pins:
- **`GPIO_OUT` saves the state.** I had no idea the Pico could save the current state of the pins. `GPIO_OUT` is a register with 32 boxes (30 of them have a pin, GP0 to GP29). A 1 puts 3.3 V on the pin, a 0 puts 0 V, and it stays like that until something changes it. `OUT_SET`, `OUT_CLR` and `OUT_XOR` don't save anything. They are doors that change the boxes of `GPIO_OUT`.
- **`OE_SET` turns pins into outputs.** Every pin starts as an input that only listens. `OE_SET` puts the pins in my mask in output mode. GP18 never turned on until I added it to `PIN_MASK`.
- **Writing vs reading a register.** Writing is `*pointer = value` (the `*` on the left). Reading is `value = *pointer` (the `*` on the right). `GPIO_IN` contains the 0s and 1s of the real state of every pin right now.
- **Getting just my 4 bits.** `>> 14` shifts everything 14 boxes to the right and the boxes 0 to 13 fall off. `& 0xF` is a filter that keeps boxes 0 to 3 and cuts off the rest (like the GP18 bit).
- **Why the XOR register is useful.** I send the same mask every time and the chip flips the pin by itself, so I don't need a variable, an `if`, or extra operations to remember if the LED is on.

# NEXT: LVL3
