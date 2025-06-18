#include <Arduino.h>
HardwareSerial MySerial(1);

void setup() {
  Serial.begin(115200);
  MySerial.begin(9600, SERIAL_8N1, 16,17);
  delay(5000);
  Serial.println("Type Colour");
}

void loop() {
  if(Serial.available())
  {
    String input = Serial.readStringUntil('\n');
    MySerial.println(input);
    Serial.println("Sent : " +input);
  }
}
