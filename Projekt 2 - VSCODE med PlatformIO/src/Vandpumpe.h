#include <Arduino.h>

class Vandpumpe{
private:
    const int pumpPin;
public:
    Vandpumpe(int pin);

    void InitPump();
    void PumpWater(int duration_ms);
};