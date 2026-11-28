# Devlog LVL3

## What I did:
Level 3 is the most complex level I have done. It has 4 red LEDs (GP14 to GP17) that show how much voltage the potentiometer is sending, like a battery bar. The number of LEDs on is the raw value divided by a quarter of the 4095 steps (`raw / 819`), capped at 4. Then I added a yellow LED (GP19) controlled by an LDR: it turns off when the raw value is 1900 or more, and on when it is less than that, so it works like a night light. Lastly I added an LM35 temperature sensor that controls 3 LEDs: green (GP10) when the temperature is 19 °C or less, yellow (GP11) between 19 and 22, and red (GP12) at 22 or more. A heartbeat LED on GP18 blinks every second.

All of this works with a scheduler: each task runs every certain amount of time (clock checks, no `sleep_ms`), so every process works properly and at the same time with no issues.

The three sensors use the same class, `PotTracker`. Each object gets its own ADC pin, its own input, a name (`"pot"`, `"ldr"`, `"temp"`) and a `showBar` flag, so only the pot draws the bar.

## Circuit:
- **Pot:** on GP26 (ADC input 0).
- **LDR:** a voltage divider. The LDR goes from 3V3 to the middle row, and a 10 kΩ resistor goes from the middle row to GND. The middle point goes to GP27 (ADC input 1). More light means the LDR's resistance drops, so it takes less of the 3.3 V and more voltage is left at the middle point.

```
3V3 ──[ LDR ]──┬──[ 10kΩ ]── GND
               │
             GP27 (ADC)
```

- **LM35:** +V on VBUS (pin 40), OUT on GP28 (ADC input 2), GND on its own GND pin of the Pico. It needs at least 4 V to work, so it goes on VBUS (5 V from USB) and not 3V3. The output is only 10 mV per °C, so it never goes over 1.5 V, which is safe for the ADC pin.

```
 5V (VBUS) ──► +V
 GP28 (ADC) ◄─ OUT     25 °C → 250 mV
 GND ────────► GND     (its own GND pin, not shared)
```

- Every LED has its own 220 Ω resistor.

## Bugs I found:

### 1. Pot never went above 2.1 V
- **Symptom:** the pot reading stopped at about 2.1 V.
- **Cause:** GP26 was inside the `initPins` array, so `OE_SET` made it an output. The Pico was pushing 0 V into the same pin the pot was pushing into. Two sources fighting drag the voltage down, and the extra current can damage the pin.
- **Fix:** took 26 out of `initPins` and used `adc_gpio_init(26)` instead. An ADC pin must never be an output.

### 2. Pot and LDR readings were mixed
- **Symptom:** the values printed as `pot` were the LDR's and the other way around.
- **Cause:** I called `adc_read()` before `adc_select_input()`. The ADC has one reader, so each object read the input the previous object had left selected.
- **Fix:** select first, then read. I also made the fix in the old file at first by mistake, so it didn't change anything until I edited the right file.

### 3. LM35 read about 7 °C too high and moved with the pot
- **Symptom:** the temperature went up and down when I turned the pot.
- **Cause:** the LM35 shared a GND wire with the pot and the LEDs. Every wire has a little resistance, and the current from the others made a small voltage on it (V = I × R). The LM35's ground sat a few mV above 0 V, so its output went up by the same amount and read hotter.
- **Fix:** gave the LM35 its own GND pin on the Pico.

### 4. Still about 6 °C high
- **Cause:** sensor error that was left after the ground fix.
- **Fix:** calibration. I compared it to the temperature in my city and subtracted the difference: `celsius = mV / 10 - 6`. It is an estimate, because the outside temperature isn't exactly the air at my desk. A real thermometer next to the sensor would be more exact.

## Experiments:

| Experiment | What I expected | What happened |
|---|---|---|
| Cover and uncover the LDR | | Covered: dropped from about 1.91 V to about 1.17 V, pretty fast. Uncovered: went back up, also super fast. |
| Heat and cool the LM35 | Touching it would heat it up. | Touching didn't work because my fingers were cold. Blowing warm air raised it (yellow/red), blowing cold air lowered it (green). |
| Read the ADC twice and keep the second | It would stop the values from getting mixed. | No change. The LM35 stayed high until I fixed the ground. |
| A: floating pin (unplug GP26) | | |
| B: LDR with 1 kΩ instead of 10 kΩ | | |
| C: internal temp sensor vs LM35 | | |

## What I learned:
- **ADC:** I finally understood how the ADC works and the rules behind it. It turns a voltage into a raw number from 0 to 4095. It has one reader: `adc_select_input` chooses which pin it listens to and `adc_read` listens, so always select first. An ADC pin must never be an output.
- **Formulas:** `mV = raw * 3300 / 4095` (multiply first so the integer division doesn't lose everything), and for the LM35 `°C = mV / 10`.
- **Circuits:** every day I learn more with practice. Voltage dividers, and why a shared ground can change a reading.
- **Classes:** with one class I created 3 different objects that each read their own sensor, instead of copying the same code 3 times. `lastChangeCounter` had to be a member so each object keeps its own last time safe. A `static` variable would be one copy shared by all the objects.

# NEXT: namespaces, experiments A/B/C, then LVL4
