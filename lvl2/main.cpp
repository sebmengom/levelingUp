#include "ledControl.h"
#include <cstdint>
#include <iostream>
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>

int main() {
  stdio_init_all();
  sleep_ms(1000);
  int counter{0};
  LedControl controller{};
  std::cout << "Loaded..." << '\n';
  controller.looper(counter);
}
