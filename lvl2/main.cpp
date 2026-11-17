#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <cstdint>
#include <pico/time.h>

constexpr uint32_t SIO_B = 0xd0000000;
constexpr uint32_t GPIO_OE_SET_OFFSET = 0x024;
constexpr uint32_t GPIO_OUT_SET_OFFSET = 0x014;
constexpr uint32_t GPIO_OUT_CLR_OFFSET = 0x018;

int main() {
  const uint32_t PIN_MASK = (1u << 14) | (1u << 15) | (1u << 16) | (1u << 17);

  volatile uint32_t *oe_set =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OE_SET_OFFSET);
  volatile uint32_t *out_set =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_SET_OFFSET);
  volatile uint32_t *out_clr =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_CLR_OFFSET);

  gpio_init_mask(PIN_MASK);
  *oe_set = PIN_MASK;

  uint32_t currentLed = (1u << 14);

  while (true) {
    *out_clr = PIN_MASK;
    sleep_ms(1000);
    *out_set = currentLed;
    sleep_ms(1000);
    currentLed <<= 1;
    if (currentLed > (1u << 17)) {
      currentLed = (1u << 14);
    }
  }
}
