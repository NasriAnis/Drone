#include "comunication.h"
#include "adc.h"
#include "joystick.h"
#include "settings.h"
#include "delay.h"

joystick_at_rest joys_at_rest;

void write_reading(int up_down, int rotate, int left_right, int forward_rear){
	controler_readings.up_down = up_down;
	controler_readings.rotate = rotate;
	controler_readings.left_right = left_right;
	controler_readings.forward_rear = forward_rear;
}

int calc_joy_pecentage(int read_value, int max_value){
	if (max_value == 0){
		return 0;
	}
	return read_value / max_value;
}

void joystick_read(){
	int raw_up_down        = adc_read(JOYSTICK1_UP_DOWN_CH);
	int raw_rot            = adc_read(JOYSTICK1_ROTATE_CH);
	int raw_forward_rear   = adc_read(JOYSTICK2_ADV_REAR_CH);
	int raw_left_right     = adc_read(JOYSTICK2_RIGHT_LEFT_CH);

	int ud = calc_joy_pecentage(
		(raw_up_down - joys_at_rest.up_down) * INVERSE_JOYSTICK,
		joys_at_rest.up_down
	);
	int rot = calc_joy_pecentage(
		(raw_rot - joys_at_rest.rotate) * INVERSE_JOYSTICK,
		joys_at_rest.rotate
	);
	int fr = calc_joy_pecentage(
		(raw_forward_rear - joys_at_rest.forward_rear) * INVERSE_JOYSTICK,
		joys_at_rest.forward_rear
	);
	int lr = calc_joy_pecentage(
		(raw_left_right - joys_at_rest.right_left) * INVERSE_JOYSTICK,
		joys_at_rest.right_left
	);

	if (ud > 100)   ud  = 100;
	if (ud < -100)  ud  = -100;
	if (rot > 100)  rot = 100;
	if (rot < -100) rot = -100;
	if (fr > 100)   fr  = 100;
	if (fr < -100)  fr  = -100;
	if (lr > 100)   lr  = 100;
	if (lr < -100)  lr  = -100;

	write_reading(ud, rot, lr, fr);
}

void joystick_calibrate(){
	write_reading(0, 0, 0, 0);
	joys_at_rest.up_down        = adc_read(JOYSTICK1_UP_DOWN_CH);
	joys_at_rest.forward_rear   = adc_read(JOYSTICK2_ADV_REAR_CH);
	joys_at_rest.right_left     = adc_read(JOYSTICK2_RIGHT_LEFT_CH);
}

void init_joystick(){
	init_adc_unit(JOYSTICK_ADC);
	delay(10);
	adc_config_chanel(JOYSTICK1_UP_DOWN_CH);
	adc_config_chanel(JOYSTICK1_ROTATE_CH);
	adc_config_chanel(JOYSTICK2_ADV_REAR_CH);
	adc_config_chanel(JOYSTICK2_RIGHT_LEFT_CH);
	delay(10);
	joystick_calibrate();
}