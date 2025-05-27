#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SD.h>

// --- Pin Definitions ---
#define DHTPIN 4
#define DHTTYPE DHT11
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SD_CS         5     // SD Card Chip Select

// --- Initialize Objects ---
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
File logFile;

unsigned long startTime;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Mini Weather Station");
  display.display();
  delay(2000);

  // Initialize SD Card
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card initialization failed!");
    display.setCursor(0, 20);
    display.println("SD Init Failed!");
    display.display();
    while (true);  // Halt
  }
  Serial.println("SD Card ready.");

  // Create or open file
  if (!SD.exists("/weather_log.csv")) {
    logFile = SD.open("/weather_log.csv", FILE_WRITE);
    logFile.println("Time(s),Temperature(C),Humidity(%)");
    logFile.close();
  }

  startTime = millis();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  unsigned long currentTime = (millis() - startTime) / 1000;

  if (isnan(temp) || isnan(hum)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Serial Output
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C | Hum: ");
  Serial.print(hum);
  Serial.println(" %");

  // OLED Output
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Mini Weather Station");

  display.setCursor(0, 20);
  display.setTextSize(2);
  display.print("T:");
  display.print(temp);
  display.print("C");

  display.setCursor(0, 45);
  display.print("H:");
  display.print(hum);
  display.print("%");
  display.display();

  // SD Card Logging
  String dataString = String(currentTime) + "," + String(temp) + "," + String(hum);
  logFile = SD.open("/weather_log.csv", FILE_APPEND);
  if (logFile) {
    logFile.println(dataString);
    logFile.close();
  } else {
    Serial.println("Failed to open log file!");
  }

  delay(5000);  // Log every 5 seconds
}
