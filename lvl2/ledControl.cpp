#include "ledControl.h"

LedControl::LedControl() {
  gpio_init_mask(PIN_MASK);
  *oe_set = PIN_MASK;
}
void LedControl::looper(int &counter) {
  while (true) {
    xorBlinker();
    *out_clr = COUNTER_MASK;
    sleep_ms(1000);
    *out_set = counter << 14;

    sleep_ms(1000);
    counter++;
    if (counter > 15) {
      counter = 0;
    }
    lecture = (*in >> 14) & 0xF;

    std::cout << std::bitset<4>(lecture) << '\n';
  }
}

void LedControl::xorBlinker() { *out_xor = XOR_MASK; }
