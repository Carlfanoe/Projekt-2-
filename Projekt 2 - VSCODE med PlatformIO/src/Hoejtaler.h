#include <Arduino.h>

class Hoejtaler{
private:
    int pin_;
public:
    Hoejtaler(int pin);
    void tune(int frequency, int duration);
};