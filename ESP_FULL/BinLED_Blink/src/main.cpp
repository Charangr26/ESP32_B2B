#include <Arduino.h>
#define led1 12
#define led2 14
#define led3 27

void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Red LED Glows");
  digitalWrite(led1,HIGH);
  delay(1000);
  Serial.println("Red LED Stops");
  digitalWrite(led1,LOW);
  delay(1000);
  Serial.println("Yellow LED Glows");
  digitalWrite(led2,HIGH);
  delay(1000);
  Serial.println("Yellow LED Stops");
  digitalWrite(led2,LOW);
  delay(1000);
  Serial.println("Green LED Glows");
  digitalWrite(led3,HIGH);
  delay(1000);
  Serial.println("Green LED Stops");
  digitalWrite(led3,LOW);
  delay(1000);
}