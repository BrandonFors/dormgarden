#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "hal.h"
#include "ada_soil_sensor.h"
#include "wifi_com.h"
#include "esp_netif_sntp.h"

#include "http_weather.h"
#include "http_dormgarden.h"
#include <time.h>

#define SLEEP_PERIOD_US 900000000 // 15 minutes
#define SLEEP_PERIOD_MS 900000 // 15 minutes
#define SNTP_SYNC_WAIT_MS 60000


void app_main(void)
{
    my_hal_init();
    wifi_com_init();
    esp_netif_sntp_sync_wait(pdMS_TO_TICKS(SNTP_SYNC_WAIT_MS)); // wait a minute for sntp sync
    while(1){
        uint16_t moisture = 0;
        ada_soil_sensor_read_moisture(&moisture);
        printf("Moisture: %u\n", moisture);
        http_dormgarden_plant_log_post("Tradescantia",moisture);
        // implement using sleep later
        vTaskDelay(pdMS_TO_TICKS(SLEEP_PERIOD_US)); // wake up every ~15 minutes
    }
}
