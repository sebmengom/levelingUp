#include <iostream>
#include <limits>
#include <pico/error.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>
constexpr unsigned MAX_ARRAY_SIZE = 5;

struct dataHolder {
  int current{0};
  unsigned dataSize{0};
  int data[MAX_ARRAY_SIZE]{};
  int sum{0};
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
};

void calculator(int input, dataHolder &currentStats);

void startOver(dataHolder &currentStats);

void showStats(const dataHolder &currentStats);

int main() {
  stdio_init_all();
  sleep_ms(10000);
  int input{};
  dataHolder stats;
  std::cout << "Enter a number, S to show stats or c to start over: " << '\n';
  while (true) {
    input = getchar_timeout_us(1000000);
    calculator(input, stats);
  }
}

void calculator(int input, dataHolder &currentStats) {
  if (input == PICO_ERROR_TIMEOUT) {
    return;

  } else if (input >= '0' && input <= '9') {
    int digit = input - '0';
    if (currentStats.current > (std::numeric_limits<int>::max() - digit) / 10) {
      std::cout << "Number exceeds numeric_limits, reseting to 0...\n";
      currentStats.current = 0;
    } else {
      currentStats.current = currentStats.current * 10 + digit;
    }
  } else if (input == '\r' || input == '\n') {
    if (currentStats.dataSize == MAX_ARRAY_SIZE) {
      std::cout << "Array too big. To clear the array press 'c'. \n";
      currentStats.current = 0;
      return;
    }
    if (currentStats.current == 0) {
      std::cout << "Please enter a number! \n";
    } else {
      currentStats.data[currentStats.dataSize] = currentStats.current;
      if (currentStats.current > currentStats.max) {
        currentStats.max = currentStats.current;
      }
      if (currentStats.current < currentStats.min) {
        currentStats.min = currentStats.current;
      }
      currentStats.sum += currentStats.current;
      std::cout << currentStats.current << '\n';
      currentStats.current = 0;
      currentStats.dataSize++;
    }
  } else if (input == 's') {

    showStats(currentStats);
  } else if (input == 'c') {
    startOver(currentStats);
  }
}

void startOver(dataHolder &currentStats) {
  std::cout << "Starting Over.... ";
  dataHolder newStats{};
  currentStats = newStats;
}

void showStats(const dataHolder &currentStats) {
  if (currentStats.dataSize == 0) {
    std::cout << "Enter numbers before checking stats! ";
  } else {
    double avg = static_cast<double>(currentStats.sum) / currentStats.dataSize;
    std::cout << "The Sum is: " << currentStats.sum
              << " the average is: " << avg
              << " Size: " << currentStats.dataSize
              << " Min: " << currentStats.min << " Max: " << currentStats.max
              << '\n';
  }
}
