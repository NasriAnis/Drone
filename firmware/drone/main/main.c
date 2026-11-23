#include <stdio.h>

#include "mpu.h"
#include "i2c.h"
#include "motors.h"
#include "comunication.h"
#include "pid.h"

enum device DRONE = drone;

void app_main(void)
{
	printf("ESP32-S3 Drone Controler\n");

	comunication_init(DRONE);
	i2c_init();
	mpu_init();
	motors_init();

	while (1) {
		pid_correct();

		// logs
		// print_cords();
		// print_controller_data();
	}
}
