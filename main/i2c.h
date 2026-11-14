#include "stdint.h"
#include "driver/i2c_master.h"

#define I2C_TIMEOUT_MS  100

#define I2C_SDA_IO 9
#define I2C_SCL_IO 8

typedef struct {
	i2c_master_bus_handle_t bus;
	i2c_master_dev_handle_t mpu;
} I2CState;
extern I2CState i2c_state;

i2c_master_bus_handle_t  i2c_init();
i2c_master_dev_handle_t i2c_add_device(uint16_t i2c_device_addr, i2c_master_bus_handle_t handle);
esp_err_t reg_write(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t val);
esp_err_t reg_read(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t *buf, size_t len);