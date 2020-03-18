#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "GpioManager.h"

class DisplayManager
{
public:
    void DisplayInit(U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C *_u8g2, GpioManager *gpioManager);
    void DrawSplashScreen(const char *version);
    void DrawWifiConnection(char *SSID);
    void DrawWaitCard();
    void DrawCardInfo(char *id, char *name);
    void DrawWifiError();
    void DrawNTPError();
private:
    U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C *u8g2;
    GpioManager *gpioMan;
};
