#pragma once
#include <Arduino.h>

namespace Config {
  constexpr uint8_t CLOCK_PIN = 2;
  constexpr uint8_t LOAD_PIN  = 3;
  constexpr uint8_t DATA_PIN  = 4;

  constexpr uint16_t N_MELDERS = 40;
  constexpr uint16_t DEBOUNCE_MS = 30;

  constexpr uint8_t RELAY1_PIN   = A0;
  constexpr uint16_t RELAY1_SET  = 13;
  constexpr uint16_t RELAY1_RESET= 11;

  constexpr uint8_t RELAY2_PIN   = A1;
  constexpr uint16_t RELAY2_SET  = 25;
  constexpr uint16_t RELAY2_RESET= 34;
}
