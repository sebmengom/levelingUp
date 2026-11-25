#include "potTracker.h"
#include "board.h"

volatile uint32_t *out_set =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_SET_OFFSET);
volatile uint32_t *out_clr =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_CLR_OFFSET);

PotTracker::PotTracker(uint adcPin, uint inputPin) {
  pin = adcPin;
  input = inputPin;
  adcStart(pin, input);
}
void PotTracker::potLevel() {

  if (get_absolute_time() - lastChangeCounter > 25000) {
    uint16_t raw = adc_read();
    adc_select_input(input);
    float voltage = raw * 3.3 / 4096;
    ledsOn = raw / 819;
    if (ledsOn > 4) {
      ledsOn = 4;
    }
    uint32_t strip = (1u << ledsOn) - 1;

    *out_clr = COUNTER_MASK;
    *out_set = strip << 14;

    std::cout << voltage << '\n';
    lastChangeCounter = get_absolute_time();
  }
}
