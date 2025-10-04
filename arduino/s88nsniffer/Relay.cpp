#include "Relay.h"

Relay::Relay(const char* n, uint8_t p, uint16_t s, uint16_t r)
  : name(n), pin(p), setIdx(s), resetIdx(r), state(false) {}

void Relay::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Relay::printRelayChange(bool newState, uint32_t tMs, bool setActive, bool resetActive) {
  Serial.print('['); Serial.print(tMs); Serial.print(" ms] ");
  Serial.print(name); Serial.print(" -> ");
  Serial.print(newState ? "ON" : "OFF"); Serial.print(" (");
  if (setActive && !resetActive) { Serial.print("SET "); Serial.print(setIdx); }
  else if (resetActive && !setActive) { Serial.print("RESET "); Serial.print(resetIdx); }
  else { Serial.print("set="); Serial.print(setActive); Serial.print(", reset="); Serial.print(resetActive); }
  Serial.println(")");
}

void Relay::update(const MelderManager &mm) {
  const uint32_t now = millis();
  const bool prev = state;

  bool setActive   = (setIdx   < Config::N_MELDERS) ? mm.state(setIdx)   : false;
  bool resetActive = (resetIdx < Config::N_MELDERS) ? mm.state(resetIdx) : false;

  if (setActive) state = true;
  if (resetActive) state = false;

  if (state != prev) {
    printRelayChange(state, now, setActive, resetActive);
  }

  digitalWrite(pin, state ? HIGH : LOW);
}
