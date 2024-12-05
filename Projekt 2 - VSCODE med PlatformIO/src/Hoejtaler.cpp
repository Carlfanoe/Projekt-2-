#include "Hoejtaler.h"

Hoejtaler::Hoejtaler(int pin) : pin_(pin) {}

void Hoejtaler::tune(int frequency, int duration) {
  tone(pin_, frequency, duration); // Example using the built-in tone function
}