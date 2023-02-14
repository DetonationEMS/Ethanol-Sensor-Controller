#include <Arduino.h>
#include "definitions.h"

#if defined(USE_TINY4K)
#include "fonts.h"

extern uint16_t celsTemp; // Store temp in celsius
extern uint16_t fahrTemp; // Store temp in fahrenheit.
extern uint8_t ethanol;   // Store ethanol percentage here

void drawScreen()
{
  oled.setFontX2Smooth(FONTBMSPA);
  oled.setCursor(0, 1);
  oled.print(F("ETH "));
  oled.print(ethanol);
  oled.print(F("% "));

  oled.setCursor(0, 5);
  oled.print("FT ");
  oled.print(fahrTemp);
  oled.print("F ");
}
#endif

#if defined(ADAFRUIT_GFX)
void drawScreen()
{
}
#endif