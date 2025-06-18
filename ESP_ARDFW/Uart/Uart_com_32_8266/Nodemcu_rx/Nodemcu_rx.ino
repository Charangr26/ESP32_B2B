#include <SoftwareSerial.h>

SoftwareSerial mySerial(D2, D1); // RX, TX (ESP8266: D2 is GPIO4, D1 is GPIO5)

void setup() {
  Serial.begin(115200);    // USB Serial Monitor
  mySerial.begin(9600);    // UART from ESP32
}

void loop() {
  if (mySerial.available()) {
    String msg = mySerial.readStringUntil('\n');
    Serial.println("Received: " + msg); // Print received UART message to serial monitor
  }
}
