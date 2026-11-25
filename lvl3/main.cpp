#include "board.h"
#include "potTracker.h"
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>

int main() {
  stdio_init_all();
  adc_init();
  uint pins[8] = {14, 15, 16, 17, 19, 10, 11, 12};
  initPins(pins, 8);
  Heartbeat hb{18};
  PotTracker pot{26, 0, "pot", 1};
  PotTracker ldr{27, 1, "ldr", 0};
  PotTracker tempSensor{28, 2, "temp", 0};

  while (true) {
    hb.tick();
    pot.potLevel();
    ldr.potLevel();
    tempSensor.potLevel();
  }
}
