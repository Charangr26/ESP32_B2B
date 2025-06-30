#include <Arduino.h>

void SelfDeletingTask(void *pvParameters)
{
  while(1)
  {
    Serial.println("I'm doing something Important");
    vTaskDelay(3000/portTICK_PERIOD_MS);
    Serial.println("Now I'm deleting myself");
    vTaskDelete(NULL);
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(SelfDeletingTask,"Delete task",1000,NULL,1,NULL);
}

void loop() {
}