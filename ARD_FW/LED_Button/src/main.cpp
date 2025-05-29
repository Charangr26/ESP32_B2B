#include <Arduino.h>
#define led1 12
#define led2 14
#define led3 27
#define sw1 32
#define sw2 33
#define sw3 34


void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(sw3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sw1) == HIGH)
  {
    digitalWrite(led1,HIGH);
  }
  else if(digitalRead(sw1) == LOW)
  {
    digitalWrite(led1,LOW);
  }

  if(digitalRead(sw2) == HIGH)
  {
    digitalWrite(led2,HIGH);
  }
  else if(digitalRead(sw2) == LOW)
  {
    digitalWrite(led2,LOW);
  }

  if(digitalRead(sw3) == HIGH)
  {
    digitalWrite(led3,HIGH);
  }
  else if(digitalRead(sw3) == LOW)
  {
    digitalWrite(led3,LOW);
  }
}