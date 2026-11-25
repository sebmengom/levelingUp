#include "board.h"
#include "potTracker.h"
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>

int main() {
  stdio_init_all();
  adc_init();
  uint pins[4] = {14, 15, 16, 17};
  initPins(pins, 4);
  Heartbeat hb{18};
  PotTracker pot{26, 0, "pot", 1};
  PotTracker ldr{27, 1, "ldr", 0};

  while (true) {
    hb.tick();
    pot.potLevel();
    ldr.potLevel();
  }
}
