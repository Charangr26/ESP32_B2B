#include <Arduino.h>
#define LED1 2
#define LED2 13

void TaskDelay(void *pvParameters)
{
  pinMode(LED1,OUTPUT);

  while(1)
  {
    digitalWrite(LED1,HIGH);
    delay(1000);
    digitalWrite(LED1,LOW);
    delay(1000);
  }
}

void TaskvTaskDelay(void *pvParameters)
{
  pinMode(LED2,OUTPUT);

  while(1)
  {
    digitalWrite(LED2,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(LED2,LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup() {
  
  xTaskCreate(
    TaskDelay,
    "Delay op",
    1000,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    TaskvTaskDelay,
    "vTaskDelay op",
    1000,
    NULL,
    1,
    NULL
  );
}

void loop() {

}