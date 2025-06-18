#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// HC-SR04 Pins
#define TRIG_PIN 13
#define ECHO_PIN 12

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Ultrasonic Distance");
  display.display();
  delay(2000);
}

float getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // speed of sound
  return distance;
}

void loop() {
  float distance_cm = getDistanceCM();
  float distance_inch = distance_cm / 2.54;

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.print(" cm | ");
  Serial.print(distance_inch);
  Serial.println(" inch");

  display.clearDisplay();
  display.setCursor(5, 0);
  display.setTextSize(1);
  display.println("Distance");

  display.setCursor(0, 20);
  display.setTextSize(2);
  display.print("CM:");
  display.print(distance_cm, 2);  // 2 decimal places

  display.setCursor(0, 35);
  display.print("IN:");
  display.print(distance_inch, 2);  // 2 decimal places

  display.display();

  delay(1000);
}