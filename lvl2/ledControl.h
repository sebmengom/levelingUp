#pragma once

#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <bitset>
#include <iostream>

constexpr uint32_t SIO_B = 0xd0000000;
constexpr uint32_t GPIO_OE_SET_OFFSET = 0x024;
constexpr uint32_t GPIO_OUT_SET_OFFSET = 0x014;
constexpr uint32_t GPIO_OUT_CLR_OFFSET = 0x018;
constexpr uint32_t GPIO_OUT_XOR = 0x01c;
constexpr uint32_t GPIO_IN_STATE = 0x004;

class LedControl {
private:
  const uint32_t COUNTER_MASK =
      (1u << 14) | (1u << 15) | (1u << 16) | (1u << 17);

  const uint32_t XOR_MASK = (1u << 18);

  volatile uint32_t *oe_set =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OE_SET_OFFSET);
  volatile uint32_t *out_set =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_SET_OFFSET);
  volatile uint32_t *out_clr =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_CLR_OFFSET);
  volatile uint32_t *out_xor =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_OUT_XOR);

  volatile uint32_t *in =
      reinterpret_cast<volatile uint32_t *>(SIO_B + GPIO_IN_STATE);

  const uint32_t PIN_MASK = XOR_MASK | COUNTER_MASK;
  uint32_t lecture{};

public:
  LedControl();
  void looper(int &counter);
  void xorBlinker();
};
