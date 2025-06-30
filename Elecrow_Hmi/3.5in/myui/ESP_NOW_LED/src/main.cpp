#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

#define LED_PIN 2  // Use GPIO 2 (or change if needed)

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  String msg = "";
  for(int i=0; i<len; i++) {
    msg += (char)incomingData[i];
  }

  Serial.println("Received: " + msg);

  if (msg == "ON") {
    digitalWrite(LED_PIN, HIGH); // Turn LED ON
  } else if (msg == "OFF") {
    digitalWrite(LED_PIN, LOW);  // Turn LED OFF
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("ESP-NOW Receiver Ready.");
}

void loop() {
  // Nothing needed here
}