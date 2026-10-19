#include <stdio.h>
#include <stdint.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "hal.h"
#include "ada_soil_sensor.h"


void app_main(void)
{
    hal_init();
    while(1){
        uint16_t moisture = 0;
        ada_soil_sensor_read_moisture(&moisture);
        printf("Moisture: %u\n", moisture);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}
