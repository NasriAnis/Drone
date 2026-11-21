#include <stdio.h>

#include "mpu.h"
#include "i2c.h"
#include "motors.h"
#include "comunication.h"

enum device DRONE = drone;

void app_main(void)
{
	printf("ESP32-S3 Drone Controler\n");

	comunication_init(DRONE);
	i2c_init();
	Cords *cords = mpu_init();
	motors_init();

	while (1) {
		mpu_read_cords(cords);
		print_cords();
		print_controler_data();
	}
}
