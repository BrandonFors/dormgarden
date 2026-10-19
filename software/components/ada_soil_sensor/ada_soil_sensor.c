#include <stdint.h>
#include "ada_soil_sensor.h"
#include "hal.h"

static const char *TAG = "ADA_SOIL_SENSOR";


void ada_soil_sensor_init()
{
    // do nothing
}

void ada_soil_sensor_read_moisture(uint16_t *moisture_value)
{
    uint8_t read_buf[2] = {0};
    uint16_t moisture_reg = (STEMMA_MOISTURE_BASE_REG << 8) | STEMMA_MOISTURE_FUNC_REG;
    hal_i2c_mem_read(moisture_reg, 2, read_buf, 2);
    *moisture_value = ((uint16_t)read_buf[0] << 8) | read_buf[1];
}

void ada_soil_read_temperature(float *temperature_value)
{
    uint8_t read_buf[4] = {0};
    uint16_t temp_reg = (STEMMA_TEMP_BASE_REG << 8) | STEMMA_TEMP_FUNC_REG;
    hal_i2c_mem_read(temp_reg, 2, (uint8_t *)read_buf, 4);
    int32_t raw_temp = ((uint32_t)read_buf[0] << 24) | ((uint32_t)read_buf[1] << 16) | ((uint32_t)read_buf[2] << 8) | read_buf[3];
    *temperature_value = (1.0 / (1UL << 16)) * raw_temp;
}
