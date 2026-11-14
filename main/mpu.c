#include <stdint.h>
#include <stdio.h>
#include "driver/i2c_master.h"
#include "driver/i2c_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "mpu.h"
#include "i2c.h"

Cords cords;

void print_cords(){
	printf("A: %6d %6d %6d | G: %6d %6d %6d\n", \
		cords.ax, cords.ay, cords.az, cords.gx, cords.gy, cords.gz);
}

void mpu_init(){
	i2c_state.mpu = i2c_add_device(MPU_ADDR, i2c_state.bus);
	vTaskDelay(pdMS_TO_TICKS(100));
	ESP_ERROR_CHECK(reg_write(i2c_state.mpu, MPU_PWR_MGMT_1, 0x00));   // wake up
}

void mpu_read_cords(){
	uint8_t raw[14];
	esp_err_t err = reg_read(i2c_state.mpu, MPU_ACCEL_XOUT, raw, sizeof(raw));
	if (err == ESP_OK) {
		cords.ax = (raw[0]  << 8) | raw[1];
		cords.ay = (raw[2]  << 8) | raw[3];
		cords.az = (raw[4]  << 8) | raw[5];
		cords.gx = (raw[8]  << 8) | raw[9];
		cords.gy = (raw[10] << 8) | raw[11];
		cords.gz = (raw[12] << 8) | raw[13];
	} else {
		printf("read failed: %s\n", esp_err_to_name(err));
	}
}