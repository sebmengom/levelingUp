#include "potTracker.h"
#include "board.h"
#include <string>

volatile uint32_t *out_set =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_SET_OFFSET);
volatile uint32_t *out_clr =
    reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_CLR_OFFSET);

PotTracker::PotTracker(uint adcPin, uint inputPin, std::string inputType,
                       bool barStatus) {
  pin = adcPin;
  input = inputPin;
  adcStart(pin, input);
  type = inputType;
  showBar = barStatus;
}
void PotTracker::potLevel() {

  if (get_absolute_time() - lastChangeCounter > 25000) {
    adc_select_input(input);
    uint16_t raw = adc_read();
    float voltage = raw * 3.3 / 4096;
    if (showBar) {
      ledsOn = raw / 819;
      if (ledsOn > 4) {
        ledsOn = 4;
      }
      uint32_t strip = (1u << ledsOn) - 1;

      *out_clr = COUNTER_MASK;
      *out_set = strip << 14;
    }
    std::cout << type << ": " << voltage << '\n';
    lastChangeCounter = get_absolute_time();
  }
}
