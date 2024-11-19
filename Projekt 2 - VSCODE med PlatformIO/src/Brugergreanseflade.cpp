#include "Brugergraenseflade.h"

bool Brugergraenseflade::IsMessageReady(){
return Serial.available();
}

String Brugergraenseflade::ReadMessage(){
if (Serial.available()) {
        String input = Serial.readStringUntil('\n'); // Read the full command
          input.trim(); // Remove leading/trailing whitespace
          input.toLowerCase(); // Convert to lowercase
          input.replace(" ", ""); // Remove all spaces
          return input;
    }
}

void Brugergraenseflade::SendMessage(String Message){
Serial.println(Message);
}