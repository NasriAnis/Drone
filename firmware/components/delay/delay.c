#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "include/delay.h"

void delay(int delay_ms){
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}