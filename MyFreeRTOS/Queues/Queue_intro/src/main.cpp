#include <Arduino.h>
QueueHandle_t queue;

void SendCommand(void *pvParameters){
  unsigned int count = 0;
  while(1){
    count++;
    xQueueSend(queue,&count,portMAX_DELAY);
    Serial.println("Sent : "+String(count));
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void ReceiveCommand(void *pvParameters){
  unsigned int receive = 0;
  while(1)
  {
    if(xQueueReceive(queue,&receive,portMAX_DELAY)==pdTRUE){
      Serial.println("Receive = "+String(receive));
    }
  }
}

void setup() {
  Serial.begin(115200);
  queue = xQueueCreate(5,sizeof(int));

  if(queue == NULL)
  {
    Serial.println("Queue is not created");
    while(1);
  }

  xTaskCreate(SendCommand,"Send message",1000,NULL,1,NULL);
  xTaskCreate(ReceiveCommand,"Receive Message",1000,NULL,1,NULL);
}

void loop() {
}