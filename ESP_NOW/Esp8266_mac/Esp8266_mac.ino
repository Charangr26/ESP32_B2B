#include <ESP8266WiFi.h>

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  Serial.println("Mac Address = ");
  Serial.print(WiFi.macAddress());
}

void loop(){
}