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

char localtime_str[30];

void loop()
{
  if (nfcReader.readCard())
  {
    // NTP
    if (netMan.getNTPTime(localtime_str, 30))
    {
      Serial.print("Current Time : ");
      Serial.println(localtime_str);
    }
    else
    {
      Serial.println("=== NTP FAILED. ===");
    }
  }
}
