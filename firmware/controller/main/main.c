#include "comunication.h"
#include "joystick.h"

enum device CONTROLER = controler;

void app_main(void)
{
	comunication_init(CONTROLER);
	init_joystick();

	while (1) {
		joystick_read();

		// logs
		// print_controller_data();

		controler_send_readings();
	}
}