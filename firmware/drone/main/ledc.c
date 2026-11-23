#include "driver/ledc.h"
#include "hal/ledc_types.h"

#include "ledc.h"
#include "settings.h"

ledc_timer_config_t ledc_init_timer(){
	ledc_timer_config_t ledc_timer = {
		.speed_mode = LEDC_SPEED_MODE,
		.duty_resolution = LEDC_DUTY_RESOLUTION, // frequency × 2^resolution  ≤  clock
		.freq_hz = LEDC_FREQ_HZ,
		.timer_num = LEDC_TIMER, // same timer for the 4 motors
		.clk_cfg = LEDC_CLOCK_CFG,
	};
	ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
	return ledc_timer;
}

void ledc_init_pin(int pin, ledc_channel_t channel){
	ledc_channel_config_t ledc_config = {
		.gpio_num = pin,
		.channel = channel, // different channels so each motor has his own PWM output
		.speed_mode = LEDC_SPEED_MODE,
		.timer_sel = LEDC_TIMER, // same timer for the 4 motors
		.duty       = LEDC_START, // start off
		.hpoint     = LEDC_START,
	};
	ESP_ERROR_CHECK(ledc_channel_config(&ledc_config));
}