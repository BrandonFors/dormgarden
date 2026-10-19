#ifndef ADAFRUIT_STEMMA_SOIL_SENSOR_H
#define ADAFRUIT_STEMMA_SOIL_SENSOR_H

#include <stdint.h>

#define STEMMA_MOISTURE_BASE_REG 0x0F
#define STEMMA_MOISTURE_FUNC_REG 0x10
#define STEMMA_TEMP_BASE_REG 0x00
#define STEMMA_TEMP_FUNC_REG 0x04

void ada_soil_sensor_init();
void ada_soil_sensor_read_moisture(uint16_t *moisture_value);
void ada_soil_read_temperature(float *temperature_value);


#endif // ADAFRUIT_STEMMA_SOIL_SENSOR_H
