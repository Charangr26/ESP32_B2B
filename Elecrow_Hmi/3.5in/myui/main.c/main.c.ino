#include <TFT_eSPI.h>
#include <Arduino.h>
#include <SPI.h>
#include <lvgl.h>
#include "ui.h"
#include <WiFi.h>
#include <esp_now.h>

/*** Display Settings ***/
#define CrowPanel_35
#if defined (CrowPanel_35)
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
uint16_t calData[5] = { 353, 3568, 269, 3491, 7 };
#endif

TFT_eSPI lcd = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * screenHeight / 13 ];

uint16_t touchX, touchY;

/*** ESP-NOW Settings ***/
uint8_t receiverMac[] = {0xF4, 0x65, 0x0B, 0x4A, 0x83, 0xE0};  // Replace this with your receiver's MAC
esp_now_peer_info_t peerInfo;

/*** Data Structure to Send ***/
typedef struct struct_message {
  char command[10];  // "ON" or "OFF"
} struct_message;

struct_message myData;

/* Display flush */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, w, h);
  lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
  lcd.endWrite();
  lv_disp_flush_ready(disp);
}

/* Touch read */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  bool touched = lcd.getTouch(&touchX, &touchY, 600);
  if (!touched) {
    data->state = LV_INDEV_STATE_REL;
  } else {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touchX;
    data->point.y = touchY;
  }
}

/*** Required for ui_events.c to send command ***/
struct_message getStructData() {
  return myData;
}
uint8_t* getReceiverMac() {
  return receiverMac;
}

/* Setup */
void setup() {
  Serial.begin(9600);

  pinMode(27, OUTPUT);
  digitalWrite(27, HIGH);

  lcd.begin();
  lcd.setRotation(1);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTouch(calData);
  delay(100);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, screenWidth * screenHeight / 13);
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_init();

  /*** ESP-NOW Init ***/
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  Serial.println("ESP-NOW Ready");
}

void loop() {
  lv_timer_handler();
  delay(5);
}
