#include "potTracker.h"
#include "board.h"
#include <hardware/adc.h>
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
    adc_read();
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
    } else if (type == "ldr") {
      if (raw < 1900) {
        *out_clr = LDR_MASK;
        *out_set = 1u << 19;
      } else {
        *out_clr = LDR_MASK;
      }
    } else if (type == "temp") {
      int mV = (raw * 3300) / 4095;
      int celsius = (mV / 10) - 6;
      if (celsius <= 19) {
        *out_clr = TEMP_MASK;
        *out_set = 1u << 10;
      } else if (celsius >= 22) {
        *out_clr = TEMP_MASK;
        *out_set = 1u << 11;
      } else {
        *out_clr = TEMP_MASK;
        *out_set = 1u << 12;
      }
    }
    std::cout << type << ": " << raw << '\n';
    lastChangeCounter = get_absolute_time();
  }
}
