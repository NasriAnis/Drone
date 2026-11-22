#define WIFI_MODE WIFI_MODE_STA
#define WIFI_IF WIFI_IF_STA

enum device {
	drone, controler
};

// reading are written in % and can be nagative
// for example : up_down = -50% mean joystick down 50%
// 				 up_down = 100% mean joystick up 100%
// One easy way to thing about it is when pushed to the
// joystick VCC it go + and to GND it go -
typedef struct {
	int up_down, rotate, left_right, forward_rear;
} Message;
extern Message controler_readings;

void comunication_init(enum device dev);
void controler_send_readings();
void print_controller_data();