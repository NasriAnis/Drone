#include "driver/ledc.h"
#include "hal/ledc_types.h"

#define LEDC_FREQ_HZ 20000
#define TIMER LEDC_TIMER_0
#define PWM_MAX_DUTY  ((1 << 10) - 1)

ledc_timer_config_t ledc_init_timer();
void ledc_init_pin(int pin, ledc_channel_t channel);