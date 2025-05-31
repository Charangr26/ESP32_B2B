#include<Arduino.h>
#define LED_PIN 17             // Use a real GPIO pin (PWM-capable)
#define POTENTIOMETER_PIN 34   // Use ADC-capable GPIO

void setup() {
  ledcSetup(0, 5000, 8);            // Channel 0, 5kHz, 8-bit resolution
  ledcAttachPin(LED_PIN, 0);       // Attach channel 0 to LED_PIN
  Serial.begin(115200);
}

void loop() {
  int potentiometerValue = analogRead(POTENTIOMETER_PIN);  // 0 to 4095
  int brightness = potentiometerValue / 16;  // Convert to 0–255
  ledcWrite(0, brightness);  // Set PWM brightness
  Serial.printf("Pot value %d, Brightness %d\n",potentiometerValue,brightness);
  delay(10);
}
