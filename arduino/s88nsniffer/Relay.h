#pragma once
#include "Config.h"
#include "MelderManager.h"

class Relay {
public:
  Relay(const char* n, uint8_t pin, uint16_t setIdx, uint16_t resetIdx);
  void begin();
  void update(const MelderManager &mm);

private:
  const char* name;
  uint8_t pin;
  uint16_t setIdx, resetIdx;
  bool state;

  void printRelayChange(bool newState, uint32_t tMs, bool setActive, bool resetActive);
};
