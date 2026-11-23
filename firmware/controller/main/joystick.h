// Data is from -1 to 1 with 0 meaning at rest
typedef struct {
	int up_down, rotate, right_left, forward_rear;
} joystick_at_rest;
extern joystick_at_rest joys_at_rest;

void write_reading(int up_down, int rotate, int right_left, int forward_rear);
void joystick_read();
void init_joystick();