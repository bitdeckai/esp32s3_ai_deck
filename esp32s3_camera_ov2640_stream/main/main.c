#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"

#include "esp_camera.h"
#include "esp_http_server.h"

#include "camera_config.h"

static const char *TAG = "camera_server";

#define WIFI_SSID "HUAWEI-yang"
#define WIFI_PASS "justinlee"

static esp_err_t start_wifi(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = { 0 };
    strncpy((char*)wifi_config.sta.ssid, WIFI_SSID, sizeof(wifi_config.sta.ssid));
    strncpy((char*)wifi_config.sta.password, WIFI_PASS, sizeof(wifi_config.sta.password));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "wifi_init_sta finished.");

    ESP_ERROR_CHECK(esp_wifi_connect());
    return ESP_OK;
}

static esp_err_t stream_handler(httpd_req_t *req)
{
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=frame";
    static const char* _STREAM_BOUNDARY = "\r\n--frame\r\n";
    static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

    httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);

    while (true) {
        fb = esp_camera_fb_get();
        if (!fb) {
            ESP_LOGE(TAG, "Camera capture failed");
            res = ESP_FAIL;
            break;
        }

        size_t hlen = snprintf(NULL, 0, _STREAM_PART, fb->len);
        char *part_buf = malloc(hlen + 1);
        if (!part_buf) {
            esp_camera_fb_return(fb);
            res = ESP_ERR_NO_MEM;
            break;
        }
        snprintf(part_buf, hlen + 1, _STREAM_PART, fb->len);

        if (httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY)) != ESP_OK ||
            httpd_resp_send_chunk(req, part_buf, hlen) != ESP_OK ||
            httpd_resp_send_chunk(req, (const char *)fb->buf, fb->len) != ESP_OK) {
            free(part_buf);
            esp_camera_fb_return(fb);
            res = ESP_FAIL;
            break;
        }
        free(part_buf);
        esp_camera_fb_return(fb);
        vTaskDelay(pdMS_TO_TICKS(30));
    }
    return res;
}

static esp_err_t index_handler(httpd_req_t *req)
{
    const char* resp_str = "<html><body><img src=\"/stream\"/></body></html>";
    ESP_LOGI(TAG, "index_handler...");

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, resp_str, strlen(resp_str));
    return ESP_OK;
}

static httpd_handle_t start_http_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.stack_size = 8192;

    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t index_uri = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = index_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &index_uri);

        httpd_uri_t stream_uri = {
            .uri = "/stream",
            .method = HTTP_GET,
            .handler = stream_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &stream_uri);
    }
    return server;
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting...");

    ESP_ERROR_CHECK(start_wifi());

    camera_config_t config = camera_default_config();
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return;
    }

    start_http_server();
    ESP_LOGI(TAG, "Camera stream ready. Connect to http://<device_ip>/");
}
