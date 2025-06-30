#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct struct_message {
  char msg[32];
} struct_message;

struct_message incomingData;

void OnDataRecv(uint8_t *mac, uint8_t *incomingDataBytes, uint8_t len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
  Serial.print("Received: ");
  Serial.println(incomingData.msg);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}