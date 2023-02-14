/*********************************
* Standalone Engine Simulator
* Aaron S. (Detonation) 2023
*
* https://www.DetonationEMS.com
* https://github.com/DetonationEMS
**********************************
  DESCRIPTION
  ====================
  Small simple code for reading ethanol content sensors.
  The information can be displayed or sent as a sent as a 0-5v output.

Credits:
Reference Code written by: pabohoney1
Original code & documents - /reference-documents
(https://www.audizine.com/forum/showthread.php/797848-DIY-Arduino-Ethanol-Content-Analyzer)

*/

#include <Arduino.h>
#include "main.h"
#include "timers.h"

#if defined(NANO_328)   // Tons of room left for more features
const uint8_t LED = 13; // Internal LED but can also connect external
const uint8_t sensorInput = 8;
const uint8_t ethonolOutput = 11; // OCR2A
const uint8_t tempOutput = 3;     // OCR2B
#endif                            // end core

#if defined(NANO_168)   // Closing in on Flash size.
const uint8_t LED = 13; // Internal LED but can also connect external
const uint8_t sensorInput = 8;
const uint8_t ethonolOutput = 11; // OCR2A
const uint8_t tempOutput = 3;     // OCR2B
#endif                            // end core

#if defined(ATTINY)      // Closing in on Flash size.
const uint8_t LED = PB3; // PB1 is internal LED, needs to be used for OCR
const uint8_t sensorInput = PB2;
const uint8_t ethonolOutput = PB0; // OCR0A
const uint8_t tempOutput = PB1;    // OCR0B
#endif                             // end core

#if defined(ATTINY88)   // PINS ARE NOT TESTED PROBABLY WRONG!!!
const uint8_t LED = 13; // internal LED, needs to be used for OCR
const uint8_t sensorInput = 8;
const uint8_t ethonolOutput = 9; // OCR1A
const uint8_t tempOutput = 10;   // OCR1B
#endif                           // end core

void setup()
{
  loadDisplay(); // Setup Display for selected board
  initBoard();   // Setup Timers for selected board
  // Serial.begin(9600); // Uncomment for serial debugging
  // while (!Serial)
  pinMode(sensorInput, INPUT);
  pinMode(ethonolOutput, OUTPUT);
  pinMode(tempOutput, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  sampleFuel();    // Get data from Sensor
  outputPWM();     // Calculate and Send PWM data
  conversions();   // Convert data for Display
  errorHandling(); // Controls LED output

  drawScreen(); // Load the display (if any)
}