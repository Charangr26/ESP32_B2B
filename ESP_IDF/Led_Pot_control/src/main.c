#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "esp_log.h"

#define ADC_CHANNEL ADC1_CHANNEL_6 // GPIO34
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0
#define LEDC_MODE LEDC_HIGH_SPEED_MODE
#define LED_GPIO 18

void app_main() {
    // 1. Configure ADC to read from potentiometer
    adc1_config_width(ADC_WIDTH_BIT_12); // 12-bit resolution: values from 0 to 4095
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11); // Wider voltage range

    // 2. Configure LED PWM controller
    ledc_timer_config_t ledc_timer = {
        .duty_resolution = LEDC_TIMER_8_BIT, // 8-bit PWM (0–255)
        .freq_hz = 5000,                     // 5 kHz PWM frequency
        .speed_mode = LEDC_MODE,
        .timer_num = LEDC_TIMER
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_CHANNEL,
        .duty       = 0,
        .gpio_num   = LED_GPIO,
        .speed_mode = LEDC_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER
    };
    ledc_channel_config(&ledc_channel);

    while (1) {
        // 3. Read ADC value from potentiometer
        int adc_reading = adc1_get_raw(ADC_CHANNEL);

        // 4. Map ADC (0–4095) to PWM duty (0–255)
        int pwm_duty = (adc_reading * 255) / 4095;

        // 5. Set LED brightness
        ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, pwm_duty);
        ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);

        vTaskDelay(pdMS_TO_TICKS(50)); // Small delay (50ms)
    }
}
