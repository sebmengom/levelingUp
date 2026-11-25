#pragma once
#include "board.h"
#include "hardware/adc.h"
#include <cstdint>
#include <iostream>
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>
#include <string>

constexpr uint32_t GPIO_OUT_SET_OFFSET = 0x014;
constexpr uint32_t GPIO_OUT_CLR_OFFSET = 0x018;
const uint32_t COUNTER_MASK = (1u << 14) | (1u << 15) | (1u << 16) | (1u << 17);
const uint32_t LDR_MASK = (1u << 19);
const uint32_t TEMP_MASK = (1u << 10) | (1u << 11) | (1u << 12);

class PotTracker {
private:
  uint pin{};
  absolute_time_t lastChangeCounter{};
  int ledsOn{0};
  uint input{};
  std::string type{};
  bool showBar{};

public:
  PotTracker(uint adcPin, uint inputPin, std::string type, bool showBar);
  void potLevel();
};
