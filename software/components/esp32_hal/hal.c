#include <stdint.h>

#include "board.h"
#include "freertos/FreeRTOS.h"

#include "driver/spi_master.h"
#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "rom/ets_sys.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "hal.h"

static const char *TAG = "HAL";

static i2c_master_bus_handle_t bus_handle;
static i2c_master_bus_config_t i2c_mst_config;
static i2c_device_config_t i2c_dev_cfg;
static i2c_master_dev_handle_t i2c_dev_handle;

void hal_init(){

    ESP_LOGI(TAG, "Initializing I2C");

    //configure and register an i2c port as a master
    i2c_mst_config = (i2c_master_bus_config_t){
        .i2c_port = I2C_NUM_0,
        .sda_io_num = SOIL_SDA,
        .scl_io_num = SOIL_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    //configure and register the soil sensor as a device
    i2c_dev_cfg = (i2c_device_config_t){
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = STEMMA_SENSOR_ADDR,
        .scl_speed_hz = I2C_FREQ,
    };
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &i2c_dev_cfg, &i2c_dev_handle));
}


void hal_delay_us(uint32_t us){
    ets_delay_us(us);
}

void hal_delay_ms(uint32_t ms){
    vTaskDelay(pdMS_TO_TICKS(ms));
}

uint32_t hal_get_time_ms(){

    return (uint32_t)(esp_timer_get_time() / 1000);
}

// send an buffer to i2c device (imu) no timeout
void hal_i2c_write(uint8_t *buf, uint16_t size){
    i2c_master_transmit(i2c_dev_handle, buf, size, -1);
}

void hal_i2c_mem_write(uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *buf, uint16_t size){
    uint8_t mem_addr_buf[2] = { (uint8_t)(mem_addr >> 8), (uint8_t)mem_addr};
    i2c_master_transmit_multi_buffer_info_t mem_write_buffer[2] = {
        {.write_buffer = mem_addr_buf, .buffer_size = mem_addr_size},
        {.write_buffer = buf, .buffer_size = size}
    };
    i2c_master_multi_buffer_transmit(i2c_dev_handle, mem_write_buffer, 2, -1);
}

//recieve from i2c device no timeout
void hal_i2c_read(uint8_t *buf, uint16_t size){
    i2c_master_receive(i2c_dev_handle, buf, size, -1 );
}

// read from memmory address on i2c device. up to
void hal_i2c_mem_read(uint16_t mem_addr, uint16_t mem_addr_size, uint8_t *buf, uint16_t buf_size){
    uint8_t mem_addr_buf[2] = { (uint8_t)(mem_addr >> 8), (uint8_t)mem_addr};
    i2c_master_transmit_receive(i2c_dev_handle, mem_addr_buf, mem_addr_size, buf, buf_size, -1);
}
