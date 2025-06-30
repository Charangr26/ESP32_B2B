#include <Arduino.h>
#define led1 0
#define led2 2

void HighPriorityTask(void *pvParameters){
  pinMode(led1,OUTPUT);

  while(1)
  {
    digitalWrite(led1,!(digitalRead(led1)));
    //vTaskDelay(500/portTICK_PERIOD_MS);
    //digitalWrite(led1,LOW);
    //vTaskDelay(500/portTICK_PERIOD_MS);
  }
}

void LowPriorityTask(void *pvParameters){
  pinMode(led2,OUTPUT);

  while(1)
  {
    digitalWrite(led2,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(led2,LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    HighPriorityTask,
    "High priority",
    1000,
    NULL,
    2,
    NULL,
    1
  );

    xTaskCreatePinnedToCore(
    LowPriorityTask,
    "Low priority",
    1000,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
}