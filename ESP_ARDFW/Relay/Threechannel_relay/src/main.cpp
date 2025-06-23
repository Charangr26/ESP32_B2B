#include <Arduino.h>
#define in1 5
#define in2 17
#define in3 16

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
}

void loop() {
  digitalWrite(in1,LOW);
  delay(1000);
  digitalWrite(in1,HIGH);
  delay(1000);

  digitalWrite(in2,LOW);
  delay(1000);
  digitalWrite(in2,HIGH);
  delay(1000);

  digitalWrite(in3,LOW);
  delay(1000);
  digitalWrite(in3,HIGH);
  delay(1000);
}