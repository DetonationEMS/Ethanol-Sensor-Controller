#include <Arduino.h>

extern const uint8_t LED; // Internal LED but can also connect external

const uint8_t FASTBLINK = 250;   // Fast blink delay in ms
const uint16_t SLOWBLINK = 1000; // Slow blink delay in ms

void errorHandling()
{
  byte constrHzError = round(constrain(Hz, 0, 255));
  static bool ledState;
  static unsigned long prevBlink;

  if (constrHzError >= 50 && constrHzError <= 150) // No error no blinky
  {
    digitalWrite(LED, LOW);
  }
  if (constrHzError <= 0) // If sensor is not connected LED will stay illuminated
  {
    digitalWrite(LED, HIGH);
  }
  if (constrHzError > 0 && constrHzError < 50 && millis() - prevBlink >= SLOWBLINK) // If sensor detects contaminated fuel it will blink slowly
  {
    ledState = (ledState == LOW) ? HIGH : LOW;
    digitalWrite(LED, ledState);
    prevBlink += SLOWBLINK;
  }
  if (constrHzError > 150 && millis() - prevBlink >= FASTBLINK) // If sensor detects water in fuel it will blink fast
  {
    ledState = (ledState == LOW) ? HIGH : LOW;
    digitalWrite(LED, ledState);
    prevBlink += FASTBLINK;
  }
}