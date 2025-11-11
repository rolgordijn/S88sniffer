#include "S88Bus.h"
#include "InterruptGuard.h"

static volatile Frame prevFrame = { {}, 0, 0};
static volatile uint8_t workVals[Config::N_MELDERS + 1];
static volatile uint16_t workLen = 0;

S88Bus S88;

void S88Bus::onClockRise() {
  if (workLen >= Config::N_MELDERS) return;
  workVals[workLen] = digitalRead(Config::DATA_PIN) ? 1 : 0;
  workLen++;
}

void S88Bus::onLoadRise() {
  uint16_t len = workLen;
  if (len > Config::N_MELDERS) len = Config::N_MELDERS;

  // Copy (len + 1) values from workVals[] to prevFrame.vals[]
  memcpy(prevFrame.vals, workVals, (len + 1) * sizeof(workVals[0]));

  prevFrame.len = len;
  prevFrame.id++;
  workLen = 1;
}

void S88Bus::begin() {
  pinMode(Config::CLOCK_PIN, INPUT);
  pinMode(Config::LOAD_PIN, INPUT);
  pinMode(Config::DATA_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(Config::CLOCK_PIN), onClockRise, RISING);
  attachInterrupt(digitalPinToInterrupt(Config::LOAD_PIN), onLoadRise, RISING);
}

bool S88Bus::snapshot(Frame &dst) {
  InterruptGuard interruptsDisabledInThisFunction;

  bool ret;

  if (prevFrame.len) {
    dst.id = prevFrame.id;
    dst.len = prevFrame.len > Config::N_MELDERS ? Config::N_MELDERS + 1 : prevFrame.len;

    // kopieer alleen de geldige bytes van vals[]
    memcpy(dst.vals, (const void *)prevFrame.vals, dst.len);
    ret = true;
  } else {
    ret = false;
  }

  return ret;
}
