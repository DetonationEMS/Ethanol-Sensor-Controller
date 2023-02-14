#include <Arduino.h>
#include "definitions.h"

// Pins
extern const uint8_t sensorInput;
extern const uint8_t ethonolOutput; // OCR2A
extern const uint8_t tempOutput;    // OCR2B

// Constants
const unsigned int SERIALINTERVAL = 1000; // Serial delay in ms
const unsigned int OUTPUTDELAY = 1000;    // Output delay in ms

// Global variables
float Hz;              // Frequency
uint32_t tempWidth;    // Temperature pulse width in us = lowTime
uint32_t highTime;     // Temperature pulse high time in us
uint32_t lowTime;      // Temperature pulse low time in us
uint32_t prevInterval; // Store previous millis()

void sampleFuel()
{

  unsigned long tempPulse;

  lowTime = 0;
  highTime = 0;

  tempPulse = pulseInLong(sensorInput, HIGH, 2000000);
  if (tempPulse > highTime)
  {
    highTime = tempPulse;
  }

  tempPulse = pulseInLong(sensorInput, LOW, 2000000); // Low should only be 1ms to 5ms
  if (tempPulse > lowTime)
  {
    lowTime = tempPulse;
  }

  if (highTime + lowTime != 0)
  {
    Hz = ((1.0 / double(highTime + lowTime)) * 1000000.0);
  }
  else
    Hz = 0;

  tempWidth = lowTime;
}

void outputPWM()
{

  static unsigned long serialPrev;
  static unsigned long outputPrev;
  byte constrHz = round(constrain(Hz, 50, 150));               // Constrain Hz to valuid values
  unsigned int constrWidth = constrain(tempWidth, 1000, 5000); // Constrain pulse width to valid values
  int ethOutPWM = round(((2.55 * constrHz) - 127.5));          // Scale for ethanol PWM output
  int tempOutPWM = round(((0.06375 * constrWidth) - 63.75));   // Scale for temperature PWM output

  if (millis() - outputPrev >= OUTPUTDELAY)
  {
    outputPrev += OUTPUTDELAY;

    analogWrite(ethonolOutput, ethOutPWM);
    analogWrite(tempOutput, tempOutPWM);
  }

  if (millis() - serialPrev >= SERIALINTERVAL)
  { // Uncomment for serial debugging
    serialPrev += SERIALINTERVAL;
    Serial.print(highTime);
    Serial.println(" us high");
    Serial.print(lowTime);
    Serial.println(" us low (tempWidth)");
    Serial.print(constrWidth);
    Serial.println(" us constrWidth");
    Serial.print(Hz);
    Serial.println(" Hz");
    Serial.print(constrHz);
    Serial.println(" constrHz");
    Serial.print(tempOutPWM);
    Serial.println(" /255 temp pwm");
    Serial.print(ethOutPWM);
    Serial.println(" /255 eth pwm");
    Serial.println();
  }
}