#pragma once

#include <Arduino.h>

class InterruptGuard {
public:
  InterruptGuard() { noInterrupts(); }   // disable interrupts
  ~InterruptGuard() { interrupts(); }    // re-enable interrupts
};


