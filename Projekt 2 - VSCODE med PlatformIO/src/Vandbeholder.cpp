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
    // Clears the trigPin
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(echoPin_, HIGH, 50000); // 100ms timeout

    // Calculating the distance
    float distance = duration * 0.034 / 2; // Centimeters
    int percentage = TranslateToPercentage(distance);
    Serial.println(percentage);
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