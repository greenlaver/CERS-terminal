#include "DisplayManager.h"

void DisplayManager::DisplayInit(U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C *_u8g2, GpioManager *gpioManager)
{
    u8g2 = _u8g2;
    gpioMan = gpioManager;

    u8g2->begin();
    u8g2->enableUTF8Print();
}

void DisplayManager::DrawSplashScreen(const char *version)
{
    u8g2->setFont(u8g2_font_luBIS08_tf);
    u8g2->setFontDirection(0);
    u8g2->firstPage();
    do
    {
        u8g2->setCursor(0, 8);
        u8g2->print("Covid-19 Entrance");
        u8g2->setCursor(0, 18);
        u8g2->print("Recording System");
        u8g2->setCursor(35, 30);
        u8g2->print("Ver.");
        u8g2->setCursor(67, 30);
        u8g2->print(version);
    } while (u8g2->nextPage());

    delay(2000);
}

void DisplayManager::DrawWifiConnection(char *SSID)
{
    u8g2->setFont(u8g2_font_profont12_mf);
    u8g2->setFontDirection(0);
    u8g2->firstPage();
    do
    {
        u8g2->setCursor(0, 12);
        u8g2->print("Connecting Wifi");
        u8g2->setCursor(0, 26);
        u8g2->print(SSID);
    } while (u8g2->nextPage());
}

void DisplayManager::DrawWaitCard()
{
    u8g2->setFont(u8g2_font_b16_t_japanese3);
    u8g2->setFontDirection(0);
    u8g2->firstPage();
    do
    {
        u8g2->setCursor(32, 15);
        if(gpioMan->isInMode()) u8g2->print("入室受付");
        else u8g2->print("退室受付");
        u8g2->setCursor(16, 31);
        u8g2->print("学生証タッチ");
    } while (u8g2->nextPage());
}

void DisplayManager::DrawCardInfo(char *id, char *name)
{
    u8g2->setFont(u8g2_font_unifont_t_japanese1);
    u8g2->setFontDirection(0);
    u8g2->firstPage();
    do
    {
        u8g2->setCursor(16, 10);
        u8g2->print(id);
        u8g2->setCursor(0, 24);
        // sjis半角カナからUTF8全角カナへの変換実装が必要
        u8g2->print("ヤマダ　ハナコ");
    } while (u8g2->nextPage());
}

void DisplayManager::DrawWifiError()
{
    u8g2->setFont(u8g2_font_b16_t_japanese3);
    u8g2->setFontDirection(0);
    u8g2->firstPage();
    do
    {
        u8g2->setCursor(32, 15);
        u8g2->print("エラー");
        u8g2->setCursor(16, 31);
        u8g2->print("WiFi切断");
    } while (u8g2->nextPage());
}

void DisplayManager::DrawNTPError()
{
    u8g2->setFont(u8g2_font_b16_t_japanese3);
    u8g2->setFontDirection(0);
    u8g2->firstPage();
    do
    {
        u8g2->setCursor(32, 15);
        u8g2->print("エラー");
        u8g2->setCursor(16, 31);
        u8g2->print("NTP失敗");
    } while (u8g2->nextPage());
}
