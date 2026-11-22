#include "driver/i2c_master.h"

#include "i2c.h"
#include "settings.h"

I2CState i2c_state;

i2c_master_bus_handle_t  i2c_init(){
	i2c_master_bus_config_t i2c_mst_config = {
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.i2c_port = I2C_NUM_0, // chip internal
		.scl_io_num = I2C_SCL_IO,
		.sda_io_num = I2C_SDA_IO,
		.glitch_ignore_cnt = 7,
		.flags.enable_internal_pullup = true,
	};

	i2c_master_bus_handle_t bus_handle;
	ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
	i2c_state.bus = bus_handle;
	return bus_handle;
}

i2c_master_dev_handle_t i2c_add_device(uint16_t i2c_device_addr, i2c_master_bus_handle_t handle){
	i2c_device_config_t mpu_config = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = i2c_device_addr,
		.scl_speed_hz = 100000,
	};

	i2c_master_dev_handle_t dev_handle;
	ESP_ERROR_CHECK(i2c_master_bus_add_device(handle, &mpu_config, &dev_handle));
	return dev_handle;
}

esp_err_t reg_write(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t val) {
	uint8_t data[2] = { reg, val };
	return i2c_master_transmit(dev, data, sizeof(data), I2C_TIMEOUT_MS);
}

esp_err_t reg_read(i2c_master_dev_handle_t dev, uint8_t reg, uint8_t *buf, size_t len) {
	return i2c_master_transmit_receive(dev, &reg, 1, buf, len, I2C_TIMEOUT_MS);
}