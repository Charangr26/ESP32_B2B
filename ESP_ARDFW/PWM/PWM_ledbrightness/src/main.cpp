#include <Arduino.h>
#define led 18

void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
  for(int dutycycle=0;dutycycle<=255;dutycycle++)
  {
    analogWrite(led,dutycycle);
    delay(15);
  }

  for(int dutycycle=255;dutycycle>=0;dutycycle--)
  {
    analogWrite(led,dutycycle);
    delay(15);
  }
}
