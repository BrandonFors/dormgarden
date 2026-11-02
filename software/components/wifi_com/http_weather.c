#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "cJSON.h"
#include "wifi_com.h"

#include "esp_log.h"

#define RES_BUF_SIZE 1024

#define WEB_HOST "api.open-meteo.com"
#define WEB_PORT "80"
#define WEB_PATH "/v1/forecast?latitude=41.67&longitude=-86.25&current_weather=true"

//HTTP GET request
static const char *REQUEST = "GET " WEB_PATH " HTTP/1.0\r\n"
  "Host: " WEB_HOST ":" WEB_PORT "\r\n"
  "User-Agent: esp-idf/1.0 esp32\r\n"
  "\r\n";

static const char *TAG = "HTTP Weather";

int parse_weather_json(const char *json_str) {
  cJSON *root = cJSON_Parse(json_str);
  if (root == NULL) {
    ESP_LOGE(TAG, "Failed to parse JSON");
    return -100;
  }

  cJSON *current_weather = cJSON_GetObjectItem(root, "current_weather");
  if (current_weather != NULL) {
    cJSON *temp_item = cJSON_GetObjectItem(current_weather, "temperature");
    if (cJSON_IsNumber(temp_item)) {
      // ESP_LOGI(TAG, "Outside Temperature: %.1f°C", temp_item->valuedouble);
      cJSON_Delete(root);
      return (int)round(temp_item->valuedouble);
    }
  }
  return -100;

}

int http_weather_get_temp(){
    char res_buf[RES_BUF_SIZE] = {0};
    wifi_http_request(WEB_HOST, WEB_PORT, REQUEST, res_buf, RES_BUF_SIZE);
    char *json_body = strstr(res_buf, "\r\n\r\n");
    int temp_result = 0;
    if (json_body != NULL) {
      json_body += 4;  // Skip past \r\n\r\n
      temp_result = parse_weather_json(json_body);
    }


    if(temp_result == -100){
      return -100;
    }
    return temp_result;
}
