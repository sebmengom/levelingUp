// Mac-side comparison for the lvl1 sizeof experiment.
// Build: clang++ -std=c++17 sizes.cpp -o sizes && ./sizes
#include <cstdint>
#include <iostream>
#include <limits>

struct dataHolder {
  int64_t current{0};
  unsigned dataSize{0};
  int64_t sum{0};
  int64_t min = std::numeric_limits<int64_t>::max();
  int64_t max = std::numeric_limits<int64_t>::min();
  bool isNegative = false;
};

int main() {
  dataHolder stats;
  std::cout << "stats: " << sizeof(stats)
            << " current: " << sizeof(stats.current)
            << " isNegative: " << sizeof(stats.isNegative)
            << " dataSize: " << sizeof(stats.dataSize)
            << " max: " << sizeof(stats.max) << " min: " << sizeof(stats.min)
            << " sum: " << sizeof(stats.sum) << '\n';

  std::cout << "char: " << sizeof(char) << " short: " << sizeof(short)
            << " int: " << sizeof(int) << " long: " << sizeof(long)
            << " long long: " << sizeof(long long)
            << " void*: " << sizeof(void *) << '\n';
}
