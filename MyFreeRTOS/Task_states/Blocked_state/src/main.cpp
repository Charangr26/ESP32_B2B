#include <Arduino.h>

void BlockedTask(void *pvParameters){
  while(1){
    Serial.println("I'm Running");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(BlockedTask,"Blocked task State",1000,NULL,1,NULL);
}

void loop() {
}