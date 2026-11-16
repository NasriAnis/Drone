#include "motors.h"
#include "ledc.h"

static const int motor_pins[NUM_MOTORS] = {MOTOR1, MOTOR2, MOTOR3, MOTOR4};
static const ledc_channel_t motor_ch[NUM_MOTORS] = {
    LEDC_CHANNEL_0, LEDC_CHANNEL_1, LEDC_CHANNEL_2, LEDC_CHANNEL_3
};

void motors_init(){
	ledc_init_timer();
	for (int i = 0; i<NUM_MOTORS; i++){
		ledc_init_pin(motor_pins[i], motor_ch[i]);
	}
}

void motor_set(int i, float speed)
{
    if (speed < 0.0f) speed = 0.0f;
    if (speed > 1.0f) speed = 1.0f;
    uint32_t duty = (uint32_t)(speed * PWM_MAX_DUTY);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, motor_ch[i], duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, motor_ch[i]);
}