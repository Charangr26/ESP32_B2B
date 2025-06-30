#include <Arduino.h>
SemaphoreHandle_t semaphore;

void TaskA(void *pvParameters){
  while(1){
    Serial.println("Giving permission to task B");
    xSemaphoreGive(semaphore);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void TaskB(void *pvParameters){
  while(1){
    if(xSemaphoreTake(semaphore,portMAX_DELAY)==pdTRUE){
      Serial.println("Got permission");
    }
  }
}

void setup() {
  Serial.begin(115200);
  semaphore=xSemaphoreCreateBinary();

  xTaskCreate(TaskA,"Task A",1000,NULL,1,NULL);
  xTaskCreate(TaskB,"Task B",1000,NULL,1,NULL);
}

void loop() {
}