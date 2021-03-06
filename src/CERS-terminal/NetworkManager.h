#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "time.h"
#include "GpioManager.h"
#include "DisplayManager.h"
#include "NFCReader.h"

#define SSID_MAX_LEN 32
#define PASS_MAX_LEN 63
#define NTPS_MAX_LEN 128
#define APIS_MAX_LEN 256

class NetworkManager
{
public:
    struct WIFI_CONFIG
    {
        char ssid[SSID_MAX_LEN + 1];
        char pass[PASS_MAX_LEN + 1];
        char ntps[NTPS_MAX_LEN + 1];
        char apis[APIS_MAX_LEN + 1];
    };

    void NetworkInit(GpioManager *gpioManager, DisplayManager *displayManager);
    void connectWifi();
    bool post(bool is_in, NFCReader::StudentInfo _info, char *_dt);
    void setupNTP();
    bool getNTPTime(char *str_dt, uint8_t str_c);
    void enterConfigMode();

private:
    WIFI_CONFIG wifi_config;
    GpioManager *gpioMan;
    DisplayManager *displayMan;

    void loadWifiConfig(WIFI_CONFIG *buf);
    void storeWifiConfig(WIFI_CONFIG buf);
    void readUARTnoTimeout(char *buf, int max_length, bool repeat);
};
