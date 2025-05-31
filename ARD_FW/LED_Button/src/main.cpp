#include <Arduino.h>
#define led1 12
#define led2 14
#define led3 27
#define sw1 5
#define sw2 18
#define sw3 19


void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(sw1,INPUT);
  pinMode(sw2,INPUT);
  pinMode(sw3,INPUT);
  //Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(sw1) == HIGH)
  {
    //Serial.println("BUTTON1 HIGH");
    digitalWrite(led1,HIGH);
  }
  if(digitalRead(sw1) == LOW)
  {
    //Serial.println("BUTTON1 LOW");
    digitalWrite(led1,LOW);
  }

  if(digitalRead(sw2) == HIGH)
  {
    digitalWrite(led2,HIGH);
  }
  if(digitalRead(sw2) == LOW)
  {
    digitalWrite(led2,LOW);
  }

  if(digitalRead(sw3) == HIGH)
  {
    digitalWrite(led3,HIGH);
  }
  if(digitalRead(sw3) == LOW)
  {
    digitalWrite(led3,LOW);
  }
}