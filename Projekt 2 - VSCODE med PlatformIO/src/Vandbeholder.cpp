#include "Vandbeholder.h"

Vandbeholder::Vandbeholder(
    int trigPin,
    int echoPin,
    int threshold,
    int filledDistance,
    int emptyDistance
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
    long duration = pulseIn(echoPin_, HIGH, 100000); // 100ms timeout

    // Calculating the distance
    long distance = duration * 0.034 / 2; // Centimeters
    return TranslateToPercentage(distance);
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

int Vandbeholder::TranslateToPercentage(long distance)
{
    int percentFull = (
        (
            1 - (
                (static_cast<long>(emptyDistance_ - distance))
                / (static_cast<long>(emptyDistance_ - filledDistance_))
                )
            )
        * 100
        );
    return constrain(percentFull, 0, 100);
}
