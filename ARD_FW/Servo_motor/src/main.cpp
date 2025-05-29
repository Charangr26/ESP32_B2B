#include <Arduino.h>
#include <ESP32Servo.h>
#define SERVO_PIN 13

Servo myServo;

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);          // Standard 50Hz servo
  myServo.attach(SERVO_PIN, 500, 2400); // Attach to pin, min/max pulse width in microseconds
  Serial.println("ESP32 Servo Ready");
}

void loop() 
{
  for (int pos = 0; pos <= 180; pos++) 
  {
    myServo.write(pos);
    delay(15);
  }
  delay(500);

  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    delay(15);
  }
  delay(500);
}
