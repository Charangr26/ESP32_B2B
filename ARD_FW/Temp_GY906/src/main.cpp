#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  if (!mlx.begin()) {
    Serial.println("MLX90614 not found. Check wiring!");
    while (1);
  }
  Serial.println("MLX90614 Ready!");
}

void loop() {
  float ambient = mlx.readAmbientTempC();
  float object = mlx.readObjectTempC();

  Serial.print("Ambient Temp: ");
  Serial.print(ambient);
  Serial.print(" °C | Object Temp: ");
  Serial.print(object);
  Serial.println(" °C");

  delay(2000);
}