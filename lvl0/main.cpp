#include <iostream>
#include <pico/stdlib.h>
int main() {
  stdio_init_all();
  int tick{0};
  while (true) {
    std::cout << "Tick " << tick << '\n';
    tick++;
    sleep_ms(1000);
  }
}
