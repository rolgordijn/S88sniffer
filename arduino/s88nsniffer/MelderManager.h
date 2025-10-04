#pragma once
#include "Config.h"
#include "S88Bus.h"

struct Melder {
  uint8_t  stable;
  uint8_t  lastRaw;
  uint32_t lastRawChangeMs;
  uint32_t lastStableChangeMs;
  bool     initialized;
};

class MelderManager {
public:
  void begin();
  void updateFromFrame(const Frame &f);
  bool state(uint16_t idx) const { return (idx < Config::N_MELDERS) ? melders[idx].stable : 0; }

private:
  Melder melders[Config::N_MELDERS];
  void printChange(uint16_t idx, uint8_t val, uint32_t tMs);
};
