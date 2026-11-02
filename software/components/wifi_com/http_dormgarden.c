#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "cJSON.h"
#include "wifi_com.h"



#include "esp_log.h"

#define SND_BUF_SIZE 1024
#define RES_BUF_SIZE 1024

#define WEB_HOST "10.24.125.12" // dormgarden server host ip
#define WEB_PORT "9147"
#define WEB_PATH "/plant_log"

//HTTP GET request
static const char *REQUEST = "POST " WEB_PATH " HTTP/1.0\r\n"
  "Host: " WEB_HOST ":" WEB_PORT "\r\n"
  "User-Agent: esp-idf/1.0 esp32\r\n";

#define CUR_TIME_STR_SIZE 256
#define CONTENT_LEN_STR_SIZE 64



void get_time_str(){

}


static const char *TAG = "HTTP Dormgarden";

int http_dormgarden_plant_log_post(const char* plant_name, uint16_t moisture_reading){
    char send_buf[SND_BUF_SIZE] = {0};
    char res_buf[RES_BUF_SIZE] = {0};
    char cur_time_str[CUR_TIME_STR_SIZE] = {0};
    char content_len_str[CONTENT_LEN_STR_SIZE] = {0};
    int body_len = 0;

    strncpy(send_buf, REQUEST, SND_BUF_SIZE);
    //get local time
    time_t current_time = time(NULL);
    struct tm *tm_local = localtime(&current_time);
    //hard code time offset
    strftime(cur_time_str,  sizeof(cur_time_str), "%Y-%m-%dT%H:%M:%S-05:00", tm_local);

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "device_id", 1);
    cJSON_AddStringToObject(json, "plant_name", plant_name);
    cJSON_AddStringToObject(json, "timestamp", cur_time_str);
    cJSON_AddNumberToObject(json, "moisture_reading", (double)moisture_reading);
    char *json_str = cJSON_Print(json);
    body_len = strlen(json_str);
    strcat(send_buf, "Content-Type: application/json\r\n");
    snprintf(content_len_str, CONTENT_LEN_STR_SIZE, "Content-Length: %d\r\n", body_len);
    strcat(send_buf, content_len_str);
    strcat(send_buf,"\r\n");
    strcat(send_buf, json_str);
    strcat(send_buf, "\r\n");
    ESP_LOGI(TAG, "%s", send_buf);
    wifi_http_request(WEB_HOST, WEB_PORT, send_buf, res_buf, RES_BUF_SIZE);
    ESP_LOGI(TAG, "%s", res_buf);
    return 0;
}
