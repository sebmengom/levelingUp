#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "starter.h"
#include <cstdint>
#include <iostream>
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>

constexpr uint32_t GPIO_OUT_SET_OFFSET = 0x014;
constexpr uint32_t GPIO_OUT_CLR_OFFSET = 0x018;

volatile uint32_t *out_set =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_SET_OFFSET);
volatile uint32_t *out_clr =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_CLR_OFFSET);

const uint32_t COUNTER_MASK = (1u << 14) | (1u << 15) | (1u << 16) | (1u << 17);

int main() {
  stdio_init_all();
  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);
  uint pins[4] = {14, 15, 16, 17};
  initPins(pins, 4);
  Heartbeat hb{18};
  int ledsOn{};
  absolute_time_t lastChangeCounter{};

  while (true) {
    hb.tick();

    if (get_absolute_time() - lastChangeCounter > 25000) {
      uint16_t raw = adc_read();
      float voltage = raw * 3.3 / 4096;
      ledsOn = raw / 819;
      if (ledsOn > 4) {
        ledsOn = 4;
      }
      uint32_t strip = (1 << ledsOn) - 1;

      *out_clr = COUNTER_MASK;
      *out_set = strip << 14;

      std::cout << voltage << '\n';
      lastChangeCounter = get_absolute_time();
    }
  }
}
