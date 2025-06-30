#include <Arduino.h>

// Define states
enum State { OFF, ON, BLINKING };
State currentState = OFF;

// Pins
const int ledPin = 2;
const int buttonPin = 4;

// Blinking
unsigned long previousMillis = 0;
const long blinkInterval = 500;

// Debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool lastButtonState = HIGH;
bool buttonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        switch (currentState) {
          case OFF:
            currentState = ON;
            break;
          case ON:
            currentState = BLINKING;
            break;
          case BLINKING:
            currentState = OFF;
            break;
        }
      }
    }
  }
  lastButtonState = reading;

  switch (currentState) {
    case OFF:
      digitalWrite(ledPin, LOW);
      break;
    case ON:
      digitalWrite(ledPin, HIGH);
      break;
    case BLINKING:
      if (millis() - previousMillis >= blinkInterval) {
        previousMillis = millis();
        int ledState = digitalRead(ledPin);
        digitalWrite(ledPin, !ledState);
      }
      break;
  }
}
