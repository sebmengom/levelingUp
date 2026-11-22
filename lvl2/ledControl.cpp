#include "ledControl.h"
#include <pico/time.h>
#include <pico/types.h>

LedControl::LedControl() {
  gpio_init_mask(PIN_MASK);
  *oe_set = PIN_MASK;
}
void LedControl::looper(int &counter) {
  while (true) {

    if (get_absolute_time() - LedControl::lastChangeHB > 1000000) {
      xorBlinker();
      *out_clr = COUNTER_MASK;
      LedControl::lastChangeHB = get_absolute_time();
    }

    if (get_absolute_time() - LedControl::lastChangeCounter > 1000000) {
      *out_set = counter << 14;
      counter++;
      if (counter > 15) {
        counter = 0;
      }
      lecture = (*in >> 14) & 0xF;

      std::cout << std::bitset<4>(lecture) << '\n';
      LedControl::lastChangeCounter = get_absolute_time();
    }
  }
}

void LedControl::xorBlinker() { *out_xor = XOR_MASK; }
