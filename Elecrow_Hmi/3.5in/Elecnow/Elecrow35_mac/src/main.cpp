#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);  // Station mode (not Access Point)
  Serial.println("ESP32 MAC Address:");
  Serial.println(WiFi.macAddress()); // Print MAC
}

void loop() {
  // Nothing here
}
