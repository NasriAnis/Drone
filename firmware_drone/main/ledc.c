#include "driver/ledc.h"
#include "hal/ledc_types.h"

#include "ledc.h"

ledc_timer_config_t ledc_init_timer(){
	ledc_timer_config_t ledc_timer = {
		.speed_mode = LEDC_LOW_SPEED_MODE,
		.duty_resolution = LEDC_TIMER_10_BIT, // frequency × 2^resolution  ≤  clock
		.freq_hz = LEDC_FREQ_HZ,
		.timer_num = TIMER, // same timer for the 4 motors
		.clk_cfg = LEDC_AUTO_CLK,
	};
	ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
	return ledc_timer;
}

void ledc_init_pin(int pin, ledc_channel_t channel){
	ledc_channel_config_t ledc_config = {
		.gpio_num = pin,
		.channel = channel, // different channels so each motor has his own PWM output
		.speed_mode = LEDC_LOW_SPEED_MODE,
		.timer_sel = TIMER, // same timer for the 4 motors
		.duty       = 0, // start off
		.hpoint     = 0,
	};
	ESP_ERROR_CHECK(ledc_channel_config(&ledc_config));
}