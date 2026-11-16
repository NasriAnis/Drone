#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "mpu.h"
#include "i2c.h"
#include "motors.h"

void app_main(void)
{
	printf("ESP32-S3 Drone Controler\n");

	i2c_init();
	Cords *cords = mpu_init();
	motors_init();

	while (1) {
		mpu_read_cords(cords);
		print_cords();
	}
}
