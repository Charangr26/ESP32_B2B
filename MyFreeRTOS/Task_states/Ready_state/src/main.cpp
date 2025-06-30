#include <Arduino.h>

void HighPriorityTask(void *pvParameters){
  Serial.println("High Running");
  vTaskDelay(1000/portTICK_PERIOD_MS);
}

void LowPriorityTask(void *pvParameters){
  Serial.println("Low Running");
  vTaskDelay(1000/portTICK_PERIOD_MS);
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(HighPriorityTask,"High",1000,NULL,2,NULL);
  xTaskCreate(LowPriorityTask,"Low",1000,NULL,1,NULL);
}

void loop() {
}