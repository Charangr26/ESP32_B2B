#include <Arduino.h>
hw_timer_t *timer = NULL;
volatile bool ledState = false;
#define LED_PIN 2

void IRAM_ATTR onTimer() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 500000, true);
  timerAlarmEnable(timer);
}

void loop() {
  // Nothing to do here
}