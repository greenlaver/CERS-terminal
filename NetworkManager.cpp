#include "NetworkManager.h"

void NetworkManager::NetworkInit(GpioManager *gpioManager, DisplayManager *displayManager)
{
    gpioMan = gpioManager;
    displayMan = displayManager;
    EEPROM.begin(sizeof(WIFI_CONFIG));

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
        if (check_count % 50 == 0)
            Serial.print(".");

        check_count++;
        delay(10);
    }

    Serial.println("done.");
    gpioMan->setLEDColor(GpioManager::Color::GREEN, 0);
}

bool NetworkManager::post(bool is_in, NFCReader::StudentInfo _info, char *_dt)
{
    HTTPClient http;
    DynamicJsonDocument doc(1024);
    char buffer[1024];

    // Json Data
    doc["id"] = _info.id;
    doc["name"] = _info.name;
    doc["mode"] = is_in ? "enter" : "leave";
    doc["acceptedAt"] = _dt;
    // Json Serialize
    serializeJson(doc, buffer, sizeof(buffer));
    Serial.println(buffer);

    // HTTP POST
    http.begin(wifi_config.apis);
    http.addHeader("Content-Type", "application/json");
    int status_code = http.POST((uint8_t *)buffer, strlen(buffer));
    Serial.print("[info] HTTP Status Code : ");
    Serial.print(status_code);

    http.end();
    
    if (status_code != 201)
    {
        displayMan->DrawPOSTError(status_code);
        gpioMan->ringBuzzer(2000);

        return false;
    }
    
    gpioMan->ringBuzzer(100);

    return true;
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
    if (!getLocalTime(&timeinfo))
        return false;

    strftime(str_dt, str_c,
             "%Y-%m-%dT%H:%M:%S+09:00", &timeinfo);

    // Serial.print("[Info] Current Time : ");
    // Serial.println(str_dt);

    return true;
}

void NetworkManager::enterConfigMode()
{
    displayMan->DrawSetupMode();
    loadWifiConfig(&wifi_config);

    while (true)
    {
        Serial.println("=== SetupMode ===");
        Serial.println("[ Current Settings ]");
        Serial.printf(" * SSID : '%s'\n", wifi_config.ssid);
        Serial.printf(" * PASS : '******'\n");
        Serial.printf(" * NTP  : '%s'\n", wifi_config.ntps);
        Serial.printf(" * API  : '%s'\n", wifi_config.apis);
        Serial.println("");

        Serial.print("Would you like to change settings? [y/n] : ");
        char ret[2];
        readUARTnoTimeout(ret, 1, true);
        if (ret[0] != 'y' && ret[0] != 'Y')
            continue;

        Serial.println();
        Serial.print("SSID > ");
        readUARTnoTimeout(wifi_config.ssid, SSID_MAX_LEN, true);

        Serial.println();
        Serial.print("PASS > ");
        readUARTnoTimeout(wifi_config.pass, PASS_MAX_LEN, true);

        Serial.println();
        Serial.print("NTP  > ");
        readUARTnoTimeout(wifi_config.ntps, NTPS_MAX_LEN, true);

        Serial.println();
        Serial.print("API  > ");
        readUARTnoTimeout(wifi_config.apis, APIS_MAX_LEN, true);

        break;
    }

    storeWifiConfig(wifi_config);

    Serial.println();
    Serial.println("[OK] Settings were saved. Please switch CONF-SW.");
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

void NetworkManager::readUARTnoTimeout(char *buf, int max_length, bool repeat)
{
    int i = 0;
    char my_buf[max_length + 1];

    while (true)
    {
        if (Serial.available() > 0)
        {
            my_buf[i] = Serial.read();

            if (i >= max_length || my_buf[i] == '\n')
            {
                my_buf[i] = '\0';
                break;
            }
            else
            {
                if (repeat)
                    Serial.print(my_buf[i]);
            }

            i++;
        }
    }

    strcpy(buf, my_buf);
}
