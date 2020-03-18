#include "GpioManager.h"
#include "NFCReader.h"
#include "NetworkManager.h"
#include "DisplayManager.h"

/// =======================================
///  UART Settings
/// =======================================
// Connected to PC via USB-Serial converter
#define UART0_BAUD 115200
// Connected to RC-S620/S NFC sensor
//        RX:IO16  TX:IO17
#define UART2_BAUD 115200

GpioManager gpioMan;
NFCReader nfcReader;
NetworkManager netMan;
DisplayManager dispMan;

char localtime_str[30];

void setup()
{
  Serial.begin(UART0_BAUD);
  Serial2.begin(UART2_BAUD);

  gpioMan.GpioInit();
  nfcReader.NFCInit(&gpioMan);
  netMan.NetworkInit(&gpioMan);
  dispMan.DisplayInit();

  Serial.println("COVID-19 NFC Program.");
  gpioMan.setLEDColor(GpioManager::Color::GREEN, 0);

  // Connect to Wifi
  netMan.connectWifi();
  netMan.setupNTP();
}

void loop()
{
  // New Arriving Card Process
  if (nfcReader.readCard())
  {
    gpioMan.setLEDColor(GpioManager::Color::GREEN, 50);

    // NTP
    if (!netMan.getNTPTime(localtime_str, 30)) showNTPError();

    gpioMan.ringBuzzer(100);
    gpioMan.setLEDColor(GpioManager::Color::GREEN, 0);
  }

  // Wifi Health Check
  if(WiFi.status() != WL_CONNECTED) {
    showWifiError();
    netMan.connectWifi();
  }
}

void showNTPError() {
  Serial.println("=== NTP FAILED. ===");
  gpioMan.ringBuzzer(2000);
}

void showWifiError(){
  Serial.println("=== Wifi Discon. ===");
  gpioMan.ringBuzzer(2000);
}
