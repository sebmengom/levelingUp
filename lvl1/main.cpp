#include <array>
#include <iostream>
#include <limits>
#include <pico/error.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>
constexpr unsigned MAGIC_NUMBER = 10;
int main() {
  stdio_init_all();
  int c{};
  int current{0};
  int dataSize{0};
  int data[1000]{};
  int sum{0};
  int min = std::numeric_limits<int>::max();
  double avg{0};
  int max = std::numeric_limits<int>::min();
  sleep_ms(10000);
  std::cout << "Enter a number, S to show stats or C to start over: " << '\n';
  while (true) {
    c = getchar_timeout_us(1000000);
    if (c == PICO_ERROR_TIMEOUT) {
      continue;
    } else if (c >= '0' && c <= '9') {
      current = current * MAGIC_NUMBER + (c - '0');
    } else if (c == '\r' || c == '\n') {
      if (dataSize == 999) {
        std::cout << "Array too big. Please restart program. \n";
        break;
      }
      data[dataSize] = current;
      if (current > max) {
        max = current;
      }
      if (current < min) {
        min = current;
      }
      sum += current;
      std::cout << current << '\n';
      current = 0;
      dataSize++;
    } else if (c == 's') {
      avg = static_cast<double>(sum) / dataSize;
      std::cout << "The Sum is: " << sum << " the average is: " << avg
                << " Size: " << dataSize << " Min: " << min << " Max: " << max
                << '\n';
    } else if (c == 'c') {
      current = 0;
      dataSize = 0;
      sum = 0;
      min = std::numeric_limits<int>::max();
      avg = 0;
      max = 0;
    }
  }
}
