#include <Arduino.h>

uint16_t duty;     // Duty cycle (0.0-100.0)
float period;      // Store period time here (eg.0.0025 s)
float temperature; // Store fuel temperature here
uint16_t celsTemp; // Store C temp
uint16_t fahrTemp; // Store F temp
uint8_t ethanol;   // Store ethanol percentage here

extern uint32_t highTime;
extern uint32_t lowTime;

void conversions()
{
  // Calculate ethanol percentage.
  if (Hz > 50) // Avoid dividing by zero
  {
    ethanol = Hz - 50;
  }
  else
  {
    ethanol = 0;
  }

  if (ethanol > 99) // Avoid overflow in PWM
  {
    ethanol = 99;
  }

  duty = ((100 * (highTime / (double(lowTime + highTime))))); // Calculate duty cycle (integer extra decimal)
  float T = (float(1.0 / float(Hz)));                         // Calculate total period time
  float period = float(100 - duty) * T;                       // Calculate the active period time (100-duty)*T
  float temp2 = float(10) * float(period);                    // Convert ms to whole number
  temperature = ((40.25 * temp2) - 81.25);                    // Calculate temperature for display (1ms = -40, 5ms = 80)
  celsTemp = int(temperature);                                // Celsius temp as float
  fahrTemp = ((temperature * 1.8) + 32);                      // Fahrenheit temp as float
}