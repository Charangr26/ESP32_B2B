#include <Arduino.h>

void RunningTask(void *pvParameters){
  while(1){
    Serial.println("I'm Running");
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(RunningTask,"Running task State",1000,NULL,1,NULL);
}

void loop() {
}