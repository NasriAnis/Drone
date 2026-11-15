#include <stdint.h>
#include "driver/i2c_master.h"

#define MPU_ADDR 0x68
#define MPU_PWR_MGMT_1 0x6b
#define MPU_ACCEL_XOUT  0x3B

typedef struct {
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t gx;
	int16_t gy;
	int16_t gz;
} Cords;
extern Cords cords;
extern Cords cords_error;

void print_cords();
Cords *mpu_init();
void mpu_read_cords(Cords *cords);