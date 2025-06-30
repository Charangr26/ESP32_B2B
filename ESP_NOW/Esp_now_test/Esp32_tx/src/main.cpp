#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

uint8_t receiverMac[] = {0x84, 0xF3, 0xEB, 0xE1, 0x61, 0xBA};

typedef struct struct_message {
  char msg[32];
} struct_message;

struct_message myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Delivery Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_add_peer(&peerInfo)) {
    Serial.println("Peer added");
  }

  strcpy(myData.msg, "Hello from ESP32!");
}

void loop() {
  esp_now_send(receiverMac, (uint8_t *)&myData, sizeof(myData));
  delay(2000);
}