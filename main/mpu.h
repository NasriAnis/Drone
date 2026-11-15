#include <stdint.h>
#include "driver/i2c_master.h"

#define MPU_ADDR 0x68
#define MPU_PWR_MGMT_1 0x6b
#define MPU_ACCEL_XOUT  0x3B

#define ACCEL_SCALE 16384.0f   // ±2g
#define GYRO_SCALE  131.0f     // ±250 °/s

typedef struct {
	float ax;
	float ay;
	float az;
	float gx;
	float gy;
	float gz;
} Cords;
extern Cords cords;
extern Cords cords_error;

void print_cords();
Cords *mpu_init();
void mpu_read_cords(Cords *cords);