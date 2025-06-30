#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

typedef struct struct_message {
  float temperature;
  float humidity;
} struct_message;

struct_message incomingData;

// ESP8266 Sender MAC Address
uint8_t senderMac[] = {0x84, 0xF3, 0xEB, 0xE1, 0x61, 0xBA};

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
  Serial.printf("Received => Temp: %.2f°C, Hum: %.2f%%\n", incomingData.temperature, incomingData.humidity);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.printf("T %.2f C", incomingData.temperature);

  display.setCursor(0, 30);
  display.printf("H %.2f %%", incomingData.humidity);
  display.display();
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common OLED I2C addr
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }
  display.clearDisplay();
  display.display();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing here; everything happens in callback.
}