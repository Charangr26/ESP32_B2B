#include <Arduino.h>

HardwareSerial MySerial(1);  // Use UART1

void setup() {
    Serial.begin(115200); // Monitor on USB
    MySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17
    delay(1000);
}

void loop() {
    MySerial.println("Hello from ESP32 via UART!");
    Serial.println("ESP32 Sent: Hello to ESP8266");
    delay(1000);
}