#include "comunication.h"
#include "adc.h"
#include "joystick.h"

void write_reading(int up, int down, int left, int right, int forward, int rear){
	controler_readings.up = up;
	controler_readings.down = down;
	controler_readings.left = left;
	controler_readings.right = right;
	controler_readings.forward = forward;
	controler_readings.rear = rear;
}

void joystick_read(){
	int up_down    = adc_read(JOYSTICK1_UP_DOWN_CH);
	int rotation   = adc_read(JOYSTICK1_ROTATE_CH);
	int adv_rear   = adc_read(JOYSTICK2_ADV_REAR_CH);
	int right_left = adc_read(JOYSTICK2_RIGHT_LEFT_CH);

	// scan the data and write accordingly to the structure
	// write_reading(int up, int down, int left, int right, int forward, int rear)
}

void init_joystick(){
	init_adc_unit(JOYSTICK_ADC);
	adc_config_chanel(JOYSTICK1_UP_DOWN_CH);
	adc_config_chanel(JOYSTICK1_ROTATE_CH);
	adc_config_chanel(JOYSTICK2_ADV_REAR_CH);
	adc_config_chanel(JOYSTICK2_RIGHT_LEFT_CH);
}