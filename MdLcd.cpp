#include "MdLcd.h"
#include <M5Stack.h>

void MdLcd::displayJpgImage(const char* path)
{
    M5.Lcd.drawJpgFile(SD, path);
}

void MdLcd::displayJpgImageCoordinate(const char* path, uint16_t x, uint16_t y)
{
    M5.Lcd.drawJpgFile(SD, path, x, y);
}

void MdLcd::clearDisplay()
{
    M5.Lcd.clear();
}

void MdLcd::fillBackgroundWhite()
{
    M5.Lcd.fillScreen(0xFFFF);
}

void MdLcd::displayText(const char* text, int x, int y)
{
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextColor(0x0000, 0xFFFF);
    M5.Lcd.setTextSize(2);
    M5.Lcd.print(text);
}

void MdLcd::displayDateText(String text, int x, int y)
{
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextColor(0x0000, 0xFFFF);
    M5.Lcd.setTextSize(5);
    M5.Lcd.print(text);
}