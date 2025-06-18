#include <SoftwareSerial.h>
SoftwareSerial mySerial(D2,D1);
#define red D5
#define yellow D6
#define green D8

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
}

void loop() {

  if(mySerial.available())
  {
    String command = mySerial.readStringUntil('\n');
    command.trim();
    Serial.print(" Command = " + command);

    if(command == "red on") digitalWrite(D5,HIGH);

    if(command == "red off") digitalWrite(D5,LOW);
    
    if(command == "yellow on") digitalWrite(D6,HIGH);
  
    if(command == "yellow off") digitalWrite(D6,LOW);

    if(command == "green on") digitalWrite(D8,HIGH);

    if(command == "green off") digitalWrite(D8,LOW);
  }

}
