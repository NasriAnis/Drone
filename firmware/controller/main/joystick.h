#define JOYSTICK_ADC             ADC_UNIT_1
#define JOYSTICK1_UP_DOWN_CH     0
#define JOYSTICK1_ROTATE_CH      1
#define JOYSTICK2_ADV_REAR_CH    2
#define JOYSTICK2_RIGHT_LEFT_CH  3

#define INVERSE_JOYSTICK 1

typedef struct {
	int up_down, rotate, right_left, forward_rear;
} joystick_at_rest;
extern joystick_at_rest joys_at_rest;

void write_reading(int up_down, int rotate, int right_left, int forward_rear);
void joystick_read();
void init_joystick();