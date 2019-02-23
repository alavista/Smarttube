#include "Identifier.h"
#include "Arduino.h"
#define MAX_NUM_TUBES 32

Identifier::Identifier(int analogInputPin) {
    this->analogInputPin = analogInputPin;
    pinMode(this->analogInputPin, INPUT);
}

int Identifier::getID() {
    return analogRead(this->analogInputPin)/MAX_NUM_TUBES;
}