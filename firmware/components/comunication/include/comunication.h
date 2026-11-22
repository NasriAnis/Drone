#define WIFI_MODE WIFI_MODE_STA
#define WIFI_IF WIFI_IF_STA

enum device {
	drone, controler
};

typedef struct {
	int up, down, right, left, forward, rear;
} Message;
extern Message controler_readings;

void comunication_init(enum device dev);
void controler_send_readings();
void print_controller_data();