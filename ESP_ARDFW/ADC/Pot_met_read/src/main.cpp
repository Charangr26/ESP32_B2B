#include <Arduino.h>
#define potpin 34

int potval = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  potval = analogRead(potpin);
  Serial.println(potval);
  delay(500);
}
