#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>

constexpr uint32_t SIO_B = 0xd0000000;
constexpr uint32_t GPIO_OE_SET_OFFSET = 0x024;
constexpr uint32_t GPIO_OUT_SET_OFFSET = 0x014;
constexpr uint32_t GPIO_OUT_CLR_OFFSET = 0x018;
constexpr uint32_t GPIO_OUT_XOR = 0x01c;
constexpr uint32_t GPIO_IN_STATE = 0x004;

int main() {
  stdio_init_all();
  sleep_ms(1000);

  const uint32_t COUNTER_MASK =
      (1u << 14) | (1u << 15) | (1u << 16) | (1u << 17);

  const uint32_t XOR_MASK = (1u << 18);

  const uint32_t PIN_MASK = COUNTER_MASK | XOR_MASK;
  volatile uint32_t *oe_set =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OE_SET_OFFSET);
  volatile uint32_t *out_set =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_SET_OFFSET);
  volatile uint32_t *out_clr =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_CLR_OFFSET);
  volatile uint32_t *out_xor =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_XOR);

  volatile uint32_t *in =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_IN_STATE);

  gpio_init_mask(PIN_MASK);
  *oe_set = PIN_MASK;

  uint32_t counter = 0;
  volatile uint32_t lecture{};
  while (true) {
    *out_clr = COUNTER_MASK;
    sleep_ms(1000);
    *out_set = counter << 14;
    *out_xor = XOR_MASK;
    sleep_ms(1000);
    counter++;
    if (counter > 15) {
      counter = 0;
    }
    lecture = (*in >> 14) & 0xF;

    std::cout << std::bitset<4>(lecture) << '\n';
  }
}
