#include "comunication.h"
#include "joystick.h"

enum device CONTROLER = controler;

void app_main(void)
{
	comunication_init(CONTROLER);
	while (1) {
		// test reading
		write_reading(1, 2, 3, 4, 5, 6);
		controler_send_readings();
	}
}