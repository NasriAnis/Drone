#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include "esp_log.h"

#include "mpu.h"
#include "i2c.h"
#include "settings.h"
#include "delay.h"

static const char *TAG = "drone";

Cords cords;
Cords cords_error;

void print_cords(void){
    ESP_LOGI(TAG, "+------+----------+----------+----------+");
    ESP_LOGI(TAG, "|      |    X     |    Y     |    Z     |");
    ESP_LOGI(TAG, "+------+----------+----------+----------+");
    ESP_LOGI(TAG, "| Acc  | %8.2f | %8.2f | %8.2f |", cords.ax, cords.ay, cords.az);
    ESP_LOGI(TAG, "| Gyro | %8.1f | %8.1f | %8.1f |", cords.gx, cords.gy, cords.gz);
    ESP_LOGI(TAG, "+------+----------+----------+----------+");
}

static void mpu_calibrate(void){
    memset(&cords_error, 0, sizeof(cords_error));
    Cords sum = {0};
    const int N = 200;

    for (int i = 0; i < N; i++) {
        mpu_read_cords(&cords);
        sum.ax += cords.ax;  sum.ay += cords.ay;  sum.az += cords.az;
        sum.gx += cords.gx;  sum.gy += cords.gy;  sum.gz += cords.gz;
        delay(5);
    }

    cords_error.ax = sum.ax / N;
    cords_error.ay = sum.ay / N;
    cords_error.az = sum.az / N - 1.0f;   // keep gravity: Z should read 1 g when flat
    cords_error.gx = sum.gx / N;
    cords_error.gy = sum.gy / N;
    cords_error.gz = sum.gz / N;
}

Cords *mpu_init(){
	i2c_state.mpu = i2c_add_device(MPU_ADDR, i2c_state.bus);
	delay(100);
	ESP_ERROR_CHECK(reg_write(i2c_state.mpu, MPU_PWR_MGMT_1, 0x00));   // wake up
	delay(10);
	mpu_calibrate();
	return &cords;
}

void mpu_read_cords(Cords *cords){
	uint8_t raw[14];
	esp_err_t err = reg_read(i2c_state.mpu, MPU_ACCEL_XOUT, raw, sizeof(raw));
	if (err == ESP_OK) {
		cords->ax = (int16_t)((raw[0]  << 8) | raw[1])  / ACCEL_SCALE - cords_error.ax;
		cords->ay = (int16_t)((raw[2]  << 8) | raw[3])  / ACCEL_SCALE - cords_error.ay;
		cords->az = (int16_t)((raw[4]  << 8) | raw[5])  / ACCEL_SCALE - cords_error.az;
		cords->gx = (int16_t)((raw[8]  << 8) | raw[9])  / GYRO_SCALE  - cords_error.gx;
		cords->gy = (int16_t)((raw[10] << 8) | raw[11]) / GYRO_SCALE  - cords_error.gy;
		cords->gz = (int16_t)((raw[12] << 8) | raw[13]) / GYRO_SCALE  - cords_error.gz;
	} else {
		printf("read failed: %s\n", esp_err_to_name(err));
	}
}