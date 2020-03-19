#pragma once

#include <Arduino.h>
#include <HkNfcRw.h>
#include <HkNfcF.h>
#include "GpioManager.h"
#include "DisplayManager.h"
#include "SJIS2UTF8.h"

//  Student Info
#define ID_MAX_LENGTH 11
#define NAME_MAX_LENGTH 16

// NFC Service Code
#define NFC_SYSTEM_CODE 0xFF00
#define NFC_SERVICE_CODE 0x1A8B

class NFCReader
{
public:
  struct StudentInfo
  {
    char id[ID_MAX_LENGTH + 1];
    char name[(NAME_MAX_LENGTH * 3) + 1];
  };

  void NFCInit(GpioManager *gpioManager, DisplayManager *displayManager);
  void resetNFC();
  bool readCard();
  void printStudentInfo();

private:
  bool is_detected;
  StudentInfo student_info;
  GpioManager *gpioMan;
  DisplayManager *displayMan;

  bool pollingCard();
  bool readIDFromCard(char *str_id);
  bool readNameFromCard(char *str_name);
  void clearStudentInfo();
};
