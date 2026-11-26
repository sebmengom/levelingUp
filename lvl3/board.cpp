#include "board.h"
#include <cstdint>

volatile uint32_t *out_xor =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_XOR);

volatile uint32_t *oe_set =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OE_SET_OFFSET);

Heartbeat::Heartbeat(uint pin) {
  mask = 1u << pin;
  gpio_init_mask(mask);
  *oe_set = mask;
}

void Heartbeat::tick() {
  if (get_absolute_time() - lastChange > 1000000) {
    *out_xor = mask;
    lastChange = get_absolute_time();
  }
}

void initPins(const uint pins[], int count) {
  uint32_t mask = 0;
  for (int i = 0; i < count; i++) {
    mask |= 1u << pins[i];
  }
  gpio_init_mask(mask);
  *oe_set = mask;
}

void adcStart(uint adcPin, uint inputPin) {
  if (adcPin > 28 || adcPin < 26) {
    std::cout << "Enter a valid pin!" << '\n';
    return;
  }
  if (inputPin > 3) {
    std::cout << "Invalid input pin!" << '\n';
    return;
  }

  adc_gpio_init(adcPin);
  adc_select_input(inputPin);
};
