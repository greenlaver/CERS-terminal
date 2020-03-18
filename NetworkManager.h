#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"
#include "GpioManager.h"

#define SSID_MAX_LEN 32
#define PASS_MAX_LEN 63
#define NTPS_MAX_LEN 128

class NetworkManager
{
public:
    struct WIFI_CONFIG
    {
        char ssid[SSID_MAX_LEN + 1];
        char pass[PASS_MAX_LEN + 1];
        char ntps[NTPS_MAX_LEN + 1];
    };

    void NetworkInit(GpioManager *gpioManager);
    void connectWifi();
    void setupNTP();
    bool getNTPTime(char *str_dt, uint8_t str_c);

private:
    WIFI_CONFIG wifi_config;
    GpioManager *gpioMan;

    void loadWifiConfig(WIFI_CONFIG *buf);
    void storeWifiConfig(WIFI_CONFIG buf);
};
