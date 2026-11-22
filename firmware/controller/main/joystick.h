#define JOYSTICK_ADC             ADC_UNIT_1
#define JOYSTICK1_UP_DOWN_CH     0
#define JOYSTICK1_ROTATE_CH      1
#define JOYSTICK2_ADV_REAR_CH    2
#define JOYSTICK2_RIGHT_LEFT_CH  3

void write_reading(int up, int down, int left, int right, int forward, int rear);
void joystick_read();