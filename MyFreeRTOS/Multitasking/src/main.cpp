#include <Arduino.h>
#define LED 2
void TaskBlinkLED(void*pvParameters)
{
  pinMode(LED,OUTPUT);

  while(1)
  {
    digitalWrite(LED,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(LED,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}
void TaskSerialPrint(void *pvParameters)
{
  while(1)
  {
    Serial.println("Hello ESP 32");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  xTaskCreate(
    TaskBlinkLED,
    "Blink Led",
    1000,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    TaskSerialPrint,
    "Print message",
    1000,
    NULL,
    1,
    NULL
  );
}

void loop() {
}