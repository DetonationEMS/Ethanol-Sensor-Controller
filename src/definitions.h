#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#if defined(USE_PULSE_IN_LONG)
uint32_t pulseInLong(uint8_t pin, uint8_t state, uint32_t timeout)
{
  uint32_t width = 0;
  uint32_t start = micros();
  // Wait for the pulse to start
  while (digitalRead(pin) != state)
  {
    if (micros() - start >= timeout)
      return 0;
  }
  // Measure the pulse width
  while (digitalRead(pin) == state)
  {
    width = micros() - start;
    if (width >= timeout)
      return 0;
  }
  return width;
}
#endif // END DEF

#if defined(USE_TINY4K)
#include "Tiny4kOLED.h"
void loadDisplay()
{
  // Setup OLED Display
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.clear();                // Clear Screen
  oled.on();                   // Turn on OLED Screen
                               // Shameless Logo implementation
  oled.setCursor(14, 3);       // Logo Location
  oled.print("DetonationEMS"); // Logo
  delay(2000);                 // Let Logo show for 2 seconds
  oled.clear();                // Clear Screen
}
#endif // end core

#if defined(ADAFRUIT_GFX)
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
void loadDisplay()
{
  Adafruit_SSD1306 display(OLED_RESET);
}
#endif

#if defined(NO_DISPLAY)
void loadDisplay()
{
  //do nothing
}
void drawScreen()
{
  // do nothing
}
#endif

#endif // END FILE