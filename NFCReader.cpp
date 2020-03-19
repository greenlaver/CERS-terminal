#include "NFCReader.h"

void NFCReader::NFCInit(GpioManager *gpioManager, DisplayManager *displayManager)
{
  gpioMan = gpioManager;
  displayMan = displayManager;

  // Init NFC reader
  if (!HkNfcRw::open())
  {
    // Show Error
    Serial.println("[Error] NFC Reader Init Failed.");
    while (true)
      ;
  }
  Serial.println("[ OK ] RC-S620S Connected.");

  HkNfcF::setServiceCode(NFC_SERVICE_CODE);
  clearStudentInfo();
  is_detected = false;
}

void NFCReader::resetNFC()
{
  HkNfcRw::reset();
}

bool NFCReader::readCard()
{
  // Card Polling
  if (!pollingCard())
  {
    is_detected = false;
    return false;
  }

  // Work only first detection
  if (!is_detected)
  {
    clearStudentInfo();

    if (!readIDFromCard(student_info.id))
    {
      return false;
    }
    if (!readNameFromCard(student_info.name))
    {
      return false;
    }

    is_detected = true;

    printStudentInfo();
  }
  else
  {
    return false;
  }

  return true;
}

void NFCReader::printStudentInfo()
{
  char str_sjis[(NAME_MAX_LENGTH * 3) + 1];
  strcpy(str_sjis, student_info.name);
  convertSjis2UTF8(NAME_MAX_LENGTH, str_sjis, student_info.name);

  Serial.print("[Info] Student ID   : ");
  Serial.println(student_info.id);
  Serial.print("[Info] Student Name : ");
  Serial.println(student_info.name);

  displayMan->DrawCardInfo(student_info.id, student_info.name);
}

bool NFCReader::pollingCard()
{
  // Detect NFC Felica
  return HkNfcF::polling(NFC_SYSTEM_CODE);
}

bool NFCReader::readIDFromCard(char *str_id)
{
  uint8_t buf[16];

  // Read Student ID
  if (!HkNfcF::read(buf, 0x00))
  {
    return false;
  }
  for (int i = 0; i < ID_MAX_LENGTH; i++)
  {
    str_id[i] = buf[2 + i];
    if (!isDigit(str_id[i]))
      return false;
  }

  return true;
}

bool NFCReader::readNameFromCard(char *str_name)
{
  uint8_t buf[16];

  // Read Student Name
  if (!HkNfcF::read(buf, 0x01))
  {
    return false;
  }
  for (int i = 0; i < NAME_MAX_LENGTH; i++)
  {
    str_name[i] = buf[i];
  }

  return true;
}

void NFCReader::clearStudentInfo()
{
  for (int i = 0; i < ID_MAX_LENGTH; i++)
  {
    student_info.id[i] = 0x00;
  }
  for (int i = 0; i < NAME_MAX_LENGTH; i++)
  {
    student_info.name[i] = 0x00;
  }
}
