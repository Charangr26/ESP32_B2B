#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2  // Built-in LED on many ESP32 dev boards

void app_main(void)
{
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);  // Set as output

    while (1) {
        gpio_set_level(LED_PIN, 1);  // LED ON
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_PIN, 0);  // LED OFF
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
