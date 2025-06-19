#include <Arduino.h>
#define led 18
#define freq 5000
#define res 8
#define pwm_ch 0

void setup() {
  ledcSetup(pwm_ch,freq,res);
  ledcAttachPin(led,pwm_ch);
}

void loop() {
  for(int i=0;i<=255;i++)
  {
    ledcWrite(pwm_ch,i);
    delay(15);
  }

  for(int i=255;i>=0;i--)
  {
    ledcWrite(pwm_ch,i);
    delay(15);
  }
}