#include "driver/ledc.h"
#include "hal/ledc_types.h"

ledc_timer_config_t ledc_init_timer();
void ledc_init_pin(int pin, ledc_channel_t channel);