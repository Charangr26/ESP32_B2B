#include <ESP8266WiFi.h>
#include <espnow.h>
#include <DHT.h>

#define DHTPIN 2       // GPIO2 (D4)
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message sensorData;

// ESP32 Receiver MAC Address (ESP32 WROOM-32 Dev Kit)
uint8_t receiverMac[] = {0xF4, 0x65, 0x0B, 0x4A, 0x83, 0xE0};

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Send Status: ");
  Serial.println(sendStatus == 0 ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  dht.begin();

  if (esp_now_init() != 0) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_register_send_cb(OnDataSent);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT11 Read Failed");
    delay(2000);
    return;
  }

  sensorData.temperature = temp;
  sensorData.humidity = hum;

  esp_now_send(receiverMac, (uint8_t *)&sensorData, sizeof(sensorData));

  Serial.printf("Sent => Temp: %.2f°C, Hum: %.2f%%\n", temp, hum);
  delay(2000);
}
