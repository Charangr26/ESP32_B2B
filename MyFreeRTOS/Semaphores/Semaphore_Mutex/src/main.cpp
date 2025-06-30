#include <Arduino.h>
SemaphoreHandle_t SerialSemaphore;

void TaskA(void *pvparameters){
  while(1){
    if(xSemaphoreTake(SerialSemaphore,portMAX_DELAY)==pdTRUE){
      Serial.println("Task A is running");
      vTaskDelay(100/portTICK_PERIOD_MS);
      xSemaphoreGive(SerialSemaphore);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void TaskB(void *pvparameters){
  while(1){
    if(xSemaphoreTake(SerialSemaphore,portMAX_DELAY)==pdTRUE){
      Serial.println("Task B is running");
      vTaskDelay(100/portTICK_PERIOD_MS);
      xSemaphoreGive(SerialSemaphore);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  SerialSemaphore = xSemaphoreCreateMutex();

  xTaskCreate(TaskA,"Task A",1000,NULL,1,NULL);
  xTaskCreate(TaskB,"Task B",1000,NULL,1,NULL);
}

void loop() {
}