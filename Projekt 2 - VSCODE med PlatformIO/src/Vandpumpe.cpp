#include "Vandpumpe.h"

Vandpumpe::Vandpumpe(int pin) : pumpPin(pin)
{
  InitPump();
}

void Vandpumpe::InitPump()
{
  pinMode(pumpPin, OUTPUT);
}

void Vandpumpe::PumpWater(int duration_ms)
{
  digitalWrite(pumpPin, HIGH);   // Turn on the pump
  delay(duration_ms);           // Keep it on for the specified duration
  digitalWrite(pumpPin, LOW);   // Turn off the pump
}