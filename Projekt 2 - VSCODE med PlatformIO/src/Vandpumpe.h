#include <Arduino.h>

class Vandpumpe{
private:
    int pin_;
public:
    Vandpumpe(int pin);

    void InitPump();
    void PumpWater(int duration_ms);
};