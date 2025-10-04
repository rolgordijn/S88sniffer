#include <Arduino.h>
#include "Config.h"
#include "S88Bus.h"
#include "MelderManager.h"
#include "Relay.h"

MelderManager melders;
Relay relay1("relay1", Config::RELAY1_PIN, Config::RELAY1_SET, Config::RELAY1_RESET);
Relay relay2("relay2", Config::RELAY2_PIN, Config::RELAY2_SET, Config::RELAY2_RESET);

void setup() {

  Serial.begin(115200);
  while (!Serial) {}
  
  Serial.println(F("S88 sniffer"));

  S88.begin();
  melders.begin();
  relay1.begin();
  relay2.begin();
}

void loop() {
  static uint32_t lastId = 0;
  Frame cur;

  S88.snapshot(cur);

  if (cur.id != lastId) {
    melders.updateFromFrame(cur);
    relay1.update(melders);
    relay2.update(melders);
    lastId = cur.id;
  }

  delay(1);
}
