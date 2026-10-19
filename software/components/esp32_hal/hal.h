#ifndef HAL_H
#define HAL_H
#include <stdint.h>

#define I2C_FREQ 100000

#define STEMMA_SENSOR_ADDR 0x36

void hal_init();

//General
void hal_delay_us(uint32_t us);
void hal_delay_ms(uint32_t ms);
uint32_t hal_get_time_ms();

// I2C
void hal_i2c_write(uint8_t *buf, uint16_t size);
void hal_i2c_mem_write(uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *buf, uint16_t size);
void hal_i2c_read(uint8_t *buf, uint16_t size);
void hal_i2c_mem_read(uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *buf, uint16_t buf_size);
#endif /* HAL_H */
