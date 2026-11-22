#include <stdint.h>
#include "driver/i2c_master.h"

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