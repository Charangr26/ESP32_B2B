#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#define red GPIO_NUM_4
#define yellow GPIO_NUM_0
#define green GPIO_NUM_2

void app_main() {
    gpio_set_direction(red,GPIO_MODE_OUTPUT);
    gpio_set_direction(yellow,GPIO_MODE_OUTPUT);
    gpio_set_direction(green,GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(red,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(red,0);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(yellow,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(yellow,0);
        vTaskDelay(pdMS_TO_TICKS(500));
        
        gpio_set_level(green,1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(green,0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
   
}