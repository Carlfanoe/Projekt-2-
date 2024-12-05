#include "Vandbeholder.h"

Vandbeholder::Vandbeholder(
    int trigPin,
    int echoPin,
    int threshold,
    float filledDistance,
    float emptyDistance
)
    : trigPin_(trigPin),
    echoPin_(echoPin),
    threshold_(threshold),
    filledDistance_(filledDistance),
    emptyDistance_(emptyDistance)
{
    InitializeSensor();
}

int Vandbeholder::ReadWaterLevel() {
    // Trigger the sensor
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_, LOW);

    // Read the echo
    long duration = pulseIn(echoPin_, HIGH, 50000); // 50 ms timeout

    if (duration == 0) {
        // Handle timeout (no echo received)
        return 0; // Or an error code/value indicating a problem
    }

    // Calculate distance and percentage
    float distance = duration * 0.034 / 2; // Centimeters
    //Serial.println(distance);
    int percentage = TranslateToPercentage(distance);
    return percentage;
}

int Vandbeholder::GetThreshold()
{
    return threshold_;
}

void Vandbeholder::InitializeSensor()
{
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

int Vandbeholder::TranslateToPercentage(float distance)
{
    int percentFull = (
        (
            1 - (
                    (emptyDistance_ - distance)
                    / (emptyDistance_ - filledDistance_)
                )
            )
        * 100
        );
    return constrain(percentFull, 0, 100); // percentFull;
}