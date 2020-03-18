#pragma once

#include <Arduino.h>

/// =======================================
///  GPIO Settings
/// =======================================
#define SW_MODE 12  // IN/OUT Mode SW
#define SW_CONF 13  // Configure Mode SW
#define LED_GRN 27  // Green LED
#define LED_RED 26  // Red LED
#define BUZ_PIN 32  // Buzzer

class GpioManager
{
  public:
    enum Color {
      None = 0b00,
      GREEN = 0b01,
      RED = 0b10,
      ORANGE = 0b11,
    };

    void GpioInit();
    void setLEDColor(Color color, uint16_t int_time);
    bool isInMode();
    bool isConfMode();
    void buzzerOn();
    void buzzerOff();
    void ringBuzzer(uint8_t bz_time);
  private:
    Color current_color;
};
