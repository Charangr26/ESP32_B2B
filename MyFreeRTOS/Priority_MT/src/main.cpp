#include <Arduino.h>
#define LED 2

void TaskBlinkLED(void *pvParameters)
{
  pinMode(LED,OUTPUT);
  while(1)
  {
    digitalWrite(LED,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(LED,LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void TaskPrintMessage(void *pvParameters)
{
  while(1)
  {
    Serial.println("Hello Guru");
  vTaskDelay(1000/portTICK_PERIOD_MS); 
  // If you remove this delay, your led may stop blink. This is called task starvation
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
    TaskPrintMessage,
    "Print message",
    1000,
    NULL,
    2,
    NULL
  );
}

void loop() {
}