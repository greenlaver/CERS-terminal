#include "NetworkManager.h"

void NetworkManager::NetworkInit(GpioManager *gpioManager, DisplayManager *displayManager)
{
    gpioMan = gpioManager;
    displayMan = displayManager;
    EEPROM.begin(sizeof(WIFI_CONFIG));

    // Store Dummy Wifi Settings
    storeWifiConfig(WIFI_CONFIG{"SSID", "PASS", "ntp.nict.jp"});
    // Read Wifi settings from EEPROM
    loadWifiConfig(&wifi_config);
}

void NetworkManager::connectWifi()
{
    // Try to connect Wifi
    uint32_t check_count = 0;
    WiFi.begin(wifi_config.ssid, wifi_config.pass);
    
    Serial.print("Connecting to ");
    Serial.print(wifi_config.ssid);
    gpioMan->setLEDColor(GpioManager::Color::GREEN, 500);
    displayMan->DrawWifiConnection(wifi_config.ssid);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        if (check_count % 50 == 0) Serial.print(".");
        
        check_count++;
        delay(10);
    }

    Serial.println("done.");
    gpioMan->setLEDColor(GpioManager::Color::GREEN, 0);
}

void NetworkManager::setupNTP()
{
    const long gmtOffset_sec = 9 * 3600;
    const int daylightOffset_sec = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, wifi_config.ntps);
}

bool NetworkManager::getNTPTime(char *str_dt, uint8_t str_c)
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return false;

    strftime(str_dt, str_c,
        "%Y-%m-%dT%H:%M:%S+09:00", &timeinfo);
    
    Serial.print("[Info] Current Time : ");
    Serial.println(str_dt);

    return true;
}

void NetworkManager::loadWifiConfig(WIFI_CONFIG *buf)
{
    EEPROM.get<WIFI_CONFIG>(0, *buf);
}

void NetworkManager::storeWifiConfig(WIFI_CONFIG buf)
{
    EEPROM.put<WIFI_CONFIG>(0, buf);
    EEPROM.commit();
}
