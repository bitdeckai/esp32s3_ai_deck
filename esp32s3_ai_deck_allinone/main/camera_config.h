#pragma once
#include "esp_camera.h"

//WROVER-KIT PIN Map
#define CAM_PIN_PWDN    -1 //power down is not used
#define CAM_PIN_RESET   -1 //software reset will be performed
#define CAM_PIN_XCLK    15
#define CAM_PIN_SIOD    4
#define CAM_PIN_SIOC    5

#define CAM_PIN_D7      16
#define CAM_PIN_D6      17
#define CAM_PIN_D5      18
#define CAM_PIN_D4      12
#define CAM_PIN_D3      10
#define CAM_PIN_D2      8
#define CAM_PIN_D1      9
#define CAM_PIN_D0      11
#define CAM_PIN_VSYNC   6
#define CAM_PIN_HREF    7
#define CAM_PIN_PCLK    13

//
#define PWDN_GPIO_NUM    CAM_PIN_PWDN
#define RESET_GPIO_NUM   CAM_PIN_RESET
#define XCLK_GPIO_NUM    CAM_PIN_XCLK
#define SIOD_GPIO_NUM    CAM_PIN_SIOD
#define SIOC_GPIO_NUM    CAM_PIN_SIOC

#define Y9_GPIO_NUM      CAM_PIN_D7
#define Y8_GPIO_NUM      CAM_PIN_D6
#define Y7_GPIO_NUM      CAM_PIN_D5
#define Y6_GPIO_NUM      CAM_PIN_D4
#define Y5_GPIO_NUM      CAM_PIN_D3
#define Y4_GPIO_NUM      CAM_PIN_D2
#define Y3_GPIO_NUM      CAM_PIN_D1
#define Y2_GPIO_NUM      CAM_PIN_D0
#define VSYNC_GPIO_NUM   CAM_PIN_VSYNC
#define HREF_GPIO_NUM    CAM_PIN_HREF
#define PCLK_GPIO_NUM    CAM_PIN_PCLK

static inline camera_config_t camera_default_config(void)
{
    camera_config_t config = {
        .pin_pwdn       = PWDN_GPIO_NUM,
        .pin_reset      = RESET_GPIO_NUM,
        .pin_xclk       = XCLK_GPIO_NUM,
        .pin_sscb_sda   = SIOD_GPIO_NUM,
        .pin_sscb_scl   = SIOC_GPIO_NUM,

        .pin_d7 = Y9_GPIO_NUM,
        .pin_d6 = Y8_GPIO_NUM,
        .pin_d5 = Y7_GPIO_NUM,
        .pin_d4 = Y6_GPIO_NUM,
        .pin_d3 = Y5_GPIO_NUM,
        .pin_d2 = Y4_GPIO_NUM,
        .pin_d1 = Y3_GPIO_NUM,
        .pin_d0 = Y2_GPIO_NUM,

        .pin_vsync = VSYNC_GPIO_NUM,
        .pin_href  = HREF_GPIO_NUM,
        .pin_pclk  = PCLK_GPIO_NUM,

        .xclk_freq_hz = 20000000,
        .ledc_timer   = LEDC_TIMER_0,
        .ledc_channel = LEDC_CHANNEL_0,

        .pixel_format = PIXFORMAT_JPEG,//YUV422,GRAYSCALE,RGB565,JPEG
        .frame_size   = FRAMESIZE_UXGA,//QQVGA-UXGA, For ESP32, do not use sizes above QVGA when not JPEG. The performance of the ESP32-S series has improved a lot, but JPEG mode always gives better frame rates.
        .jpeg_quality = 12,
        .fb_count     = 2,
        .grab_mode = CAMERA_GRAB_WHEN_EMPTY//CAMERA_GRAB_LATEST. Sets when buffers should be filled
    };
    return config;
}
