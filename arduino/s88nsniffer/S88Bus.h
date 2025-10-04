#pragma once
#include <Arduino.h>
#include "Config.h"

struct Frame {
  uint8_t  vals[Config::N_MELDERS];
  uint16_t len;
  uint32_t id;
};

class S88Bus {
public:
  void begin();
  void snapshot(Frame &dst);

private:
  static void onClockRise();
  static void onLoadRise();

  friend void ::ISR_CLOCK_Rise();
  friend void ::ISR_LOAD_Rise();
};

// Globale ISR-compatibele object
extern S88Bus S88;
