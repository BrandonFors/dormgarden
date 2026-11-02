#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "hal.h"
#include "ada_soil_sensor.h"
#include "wifi_com.h"
#include "http_weather.h"
#include <time.h>

void app_main(void)
{
    my_hal_init();
    wifi_com_init();
    while(1){
        uint16_t moisture = 0;
        ada_soil_sensor_read_moisture(&moisture);
        printf("Moisture: %u\n", moisture);

        int temp = http_weather_get_temp();

        printf("Temp: %d\n", temp);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }

}
