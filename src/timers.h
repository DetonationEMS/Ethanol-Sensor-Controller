#ifndef TIMERS_H
#define TIMERS_H
#include "main.h"

/* Timer setup for each available board */
#if defined(NANO_328) // Tons of room left for more features
void initBoard()
{
  cli();               // Disable interrupts
  TCCR2A = 0b10100001; // Fast PWM, non-inverting OCR2A & OCR2B
  TCCR2B = 0b00000001; // Timer = ~32kHz
  sei();               // Enable interrupts
}
#endif // end MCU

#if defined(NANO_168) // Closing in on Flash size.
void initBoard()
{
  cli();               // Disable interrupts
  TCCR2A = 0b10100001; // non-inverting OCR2A & OCR2B
  TCCR2B = 0b00000001; // Timer = ~32kHz
  sei();               // Enable interrupts
}
#endif // end MCU

#if defined(ATTINY)   
void initBoard()
{
  cli();               // Disable interrupts
  TCCR0A = 0b10100001; // non-inverting OCR0A & OCR0B
  TCCR0B = 0b00000001; // Timer = ~32kHz
  sei();               // Enable interrupts
}
#endif // end MCU

#if defined(ATTINY88) // ATTINY88 HAS NOT YET BEEN TESTED
void initBoard()
{
  cli();               // Disable interrupts
  TCCR1A = 0b10100001; // Fast PWM, non-inverting OCR1A & OCR1B
  TCCR1B = 0b00010001; // Timer = ~32kHz, set timer mode to fast PWM
  sei();               // Enable interrupts
}
#endif // end MCU

#endif // end file