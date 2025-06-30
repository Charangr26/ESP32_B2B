#include <Arduino.h>
TaskHandle_t SuspendedTaskHandle;

void SuspendedTask(void *pvParameters){
  while(1)
  {
    Serial.println("I'm Running Now");
    vTaskSuspend(NULL);
    Serial.println("Back again!");
  }
}

void ControllerTask(void *pvParameters){
  while(1)
  {
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    Serial.println("Waking up the suspended task");
    vTaskResume(SuspendedTaskHandle);
  }
}


void setup() {
  Serial.begin(115200);
  xTaskCreate(SuspendedTask,"Susended Task",1000,NULL,1,&SuspendedTaskHandle);
  xTaskCreate(ControllerTask,"Control Task",1000,NULL,2,NULL);
}

void loop() {

}