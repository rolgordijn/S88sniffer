#include "MelderManager.h"

void MelderManager::begin() {
  for (uint16_t i = 0; i < Config::N_MELDERS; i++) {
    melders[i] = {0,0,0,0,false};
  }
}

void MelderManager::printChange(uint16_t idx, uint8_t val, uint32_t tMs) {
  Serial.print('['); Serial.print(tMs); Serial.print(" ms] melder ");
  Serial.print(idx); Serial.print(" -> ");
  Serial.println(val ? "X" : ".");
}

void MelderManager::updateFromFrame(const Frame &f) {
  const uint32_t now = millis();
  const uint16_t maxN = (f.len > Config::N_MELDERS) ? Config::N_MELDERS : f.len;

  for (uint16_t i = 0; i < Config::N_MELDERS; i++) {
    uint8_t raw = (i < maxN) ? f.vals[i] : 0;
    Melder &m = melders[i];

    if (!m.initialized) {
      m = {raw, raw, now, now, true};
      printChange(i, m.stable, now);
      continue;
    }

    if (raw != m.lastRaw) {
      m.lastRaw = raw;
      m.lastRawChangeMs = now;
    }

    if (raw != m.stable && (now - m.lastRawChangeMs) >= Config::DEBOUNCE_MS) {
      m.stable = raw;
      m.lastStableChangeMs = now;
      printChange(i, m.stable, now);
    }
  }
}
