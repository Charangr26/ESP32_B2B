#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define red GPIO_NUM_4
#define yellow GPIO_NUM_0
#define green GPIO_NUM_2
#define button1 GPIO_NUM_27
#define button2 GPIO_NUM_14
#define button3 GPIO_NUM_12

void app_main() 
{
    gpio_set_direction(red,GPIO_MODE_OUTPUT);
    gpio_set_direction(yellow,GPIO_MODE_OUTPUT);
    gpio_set_direction(green,GPIO_MODE_OUTPUT);

    gpio_set_direction(button1,GPIO_MODE_INPUT);
    gpio_set_direction(button2,GPIO_MODE_INPUT);
    gpio_set_direction(button3,GPIO_MODE_INPUT);

    gpio_set_pull_mode(button1, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(button2, GPIO_PULLDOWN_ONLY);
    gpio_set_pull_mode(button3, GPIO_PULLDOWN_ONLY);

    while(1)
    {
        int state1 = gpio_get_level(button1);
        int state2 = gpio_get_level(button2);
        int state3 = gpio_get_level(button3);

        if(state1 == 1){
            gpio_set_level(red,1);
            printf("Button pressed RED ON\n");
        }

        if(state2 == 1){
            gpio_set_level(yellow,1);
            printf("Button pressed YELLOW ON\n");
        }

        if(state3 == 1){
            gpio_set_level(green,1);
            printf("Button pressed GREEN ON\n");
        }

        if(state1 == 0){
            gpio_set_level(red,0);
            //printf("RED OFF\n");
        }

        if(state2 == 0){
            gpio_set_level(yellow,0);
            //printf("YELLOW OFF\n");
        }

        if(state3 == 0){
            gpio_set_level(green,0);
            //printf("GREEN OFF\n");
        }
        vTaskDelay(pdMS_TO_TICKS(100));
        printf("Button states: B1=%d B2=%d B3=%d\n", state1, state2, state3);

    }
}