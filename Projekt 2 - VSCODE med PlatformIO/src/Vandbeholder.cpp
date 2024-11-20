#include "Vandbeholder.h"

Vandbeholder::Vandbeholder(
    int trigPin,
    int echoPin,
    int filledDistance,
    int emptyDistance
)
    :   trigPin_(trigPin),
        echoPin_(echoPin),
        filledDistance_(filledDistance),
        emptyDistance_(emptyDistance)
{
    Serial.println("Initializing ultrasonic sensor...");
    InitializeSensor();
    //Serial.println("Ultrasonic sensor initialized..."); //Uncommenting this breaks the system???
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
    long duration = pulseIn(echoPin_, HIGH);

    // Calculating the distance
    int distance = duration * 0.034 / 2; // Centimeters

    return TranslateToPercentage(distance);
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
            (static_cast<float>(emptyDistance_) - distance)
            / (static_cast<float>(emptyDistance_ - filledDistance_))
        )
        * 100
    );
    int clampedPercentage = constrain(percentFull, 0, 100);
    return clampedPercentage;
}





// Vandbeholder::Vandbeholder(int trigPin, int echoPin)
//     :   trigPin_(trigPin),
//         echoPin_(echoPin)
// {
//     InitializeSensor();
// }

// int Vandbeholder::ReadWaterLevel() {
//     // Clears the trigPin
//     WritePORTA(trigPin_, false);
//     _delay_us(2);

//     // Sets the trigPin on HIGH state for 10 micro seconds
//     WritePORTA(trigPin_, true);
//     _delay_us(10);
//     WritePORTA(trigPin_, false);

//     // Reads the echoPin, returns the sound wave travel time in microseconds
//     long duration = pulseIn(23, HIGH); // Fix this

//     // Calculating the distance
//     int distance = duration * 0.034 / 2; // Centimeters

//     return distance;
// }

// void Vandbeholder::InitializeSensor()
// {
//     DDRA |= (1 << trigPin_);  // Set trigPin as output
// 	DDRA &= ~(1 << echoPin_); // Set echoPin as input
// }

// bool Vandbeholder::ReadPINA(int pin)
// {
//     bool pinState = false;
// 	if (pin <= 7) {
// 		unsigned char mask = (1 << pin);
// 		pinState = (PINA & mask);
// 	}
// 	return pinState;
// }

// void Vandbeholder::WritePORTA(int pin, bool state)
// {
//     if (pin <= 7) {
// 		unsigned char mask = (1 << pin);
// 		if (state) PORTA |= mask;
// 		else PORTA &= ~mask;
// 	}
// }