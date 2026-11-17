#include "comunication.h"
#include "joystick.h"

enum device cont = controler;

void app_main(void)
{
	comunication_init(cont);
	while (1) {
		write_reading(1, 2, 3, 4, 5, 6);
		controler_send_readings();
	}
}