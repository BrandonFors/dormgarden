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

#define SLEEP_PERIOD_MS 1800000 // 30 minutes
#define SNTP_SYNC_WAIT_MS 60000

#define NUM_SAMPLES 30
#define SAMPLE_PERIOD_MS 5000


void app_main(void)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(SLEEP_PERIOD_MS);

    my_hal_init();
    wifi_com_init();
    esp_netif_sntp_sync_wait(pdMS_TO_TICKS(SNTP_SYNC_WAIT_MS)); // wait a minute for sntp sync
    xLastWakeTime = xTaskGetTickCount();
    while(1){
        uint16_t moisture = 0;
        uint32_t moisture_sum = 0;
        uint16_t samples_taken = 0;
        while(samples_taken < NUM_SAMPLES){
            ada_soil_sensor_read_moisture(&moisture);
            moisture_sum += moisture;
            samples_taken++;
            printf("Moisture sample: %u\n", moisture);
            vTaskDelay(pdMS_TO_TICKS(SAMPLE_PERIOD_MS));
        }
        moisture = moisture_sum / NUM_SAMPLES;
        printf("Moisture AVG: %u\n", moisture);
        http_dormgarden_plant_log_post("Tradescantia",moisture);
        // implement using sleep later
        vTaskDelayUntil(&xLastWakeTime, xFrequency); // wake up every ~30 minutes
    }
}
