#include "Vandpumpe.h"

Vandpumpe::Vandpumpe(int pin) : pin_(pin)
{
  InitPump();
}

void Vandpumpe::InitPump()
{
  pinMode(pin_, OUTPUT);
}

void Vandpumpe::PumpWater(int duration_ms)
{
  digitalWrite(pin_, HIGH); // Turn on the pump
  delay(duration_ms);       // Keep it on for the specified duration
  digitalWrite(pin_, LOW);  // Turn off the pump
}