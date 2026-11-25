#pragma once
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <iostream>
#include <pico/time.h>
#include <pico/types.h>

constexpr uint32_t SIO_B = 0xd0000000;
constexpr uint32_t GPIO_OUT_XOR = 0x01c;
const uint32_t XOR_MASK = (1u << 18);
constexpr uint32_t GPIO_OE_SET_OFFSET = 0x024;

class Heartbeat {
private:
  uint32_t mask{};
  absolute_time_t lastChange{};

public:
  Heartbeat(uint pin);
  void tick();
};

void initPins(const uint pins[], int count);

void adcStart(uint adcPin, uint inputPin);
