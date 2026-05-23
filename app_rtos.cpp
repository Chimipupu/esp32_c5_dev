/**
 * @file app_rtos.cpp
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief FreeRTOS アプリ
 * @version 0.1
 * @date 2026-05-23
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "app_rtos.h"
#include "app_wifi.h"
#include "pcb_define.h"

// -----------------------------------------------------------
#if 0
#define TASK_MAIN_DELAY_MS    (100 / portTICK_PERIOD_MS)
static xTaskHandle s_TaskMain_Handle;
#endif

#if 1
#define TASK_WIFI_DELAY_MS    (1000 / portTICK_PERIOD_MS)
static xTaskHandle s_xTaskWiFi_Handle;
static bool s_led_val = true;
static bool s_wifi_enable = false;
#endif

// -----------------------------------------------------------
// [Static]

#if 0
static void _vTaskMain(void *p_param)
{
    while (1)
    {
        vTaskDelay(TASK_MAIN_DELAY_MS / portTICK_PERIOD_MS);
    }
}
#endif

#if 1
static void _vTaskWiFi(void *p_param)
{
    app_wifi_init(MY_WIFI_SSID, MY_WIFI_PASSWORD);
    s_wifi_enable = true;

    while (1)
    {
        app_wifi_main();
        digitalWrite(OB_LED_PIN, s_led_val ? HIGH : LOW);
        s_led_val = !s_led_val;
        vTaskDelay(TASK_WIFI_DELAY_MS / portTICK_PERIOD_MS);
    }
}
#endif
// -----------------------------------------------------------
// [API]

void app_rtos_init(void)
{
#if 0
    xTaskCreatePinnedToCore(_vTaskMain,    // コールバック関数ポインタ
                            "vTaskMain",  // タスク名
                            2048,         // スタック
                            NULL,         // パラメータ
                            0,            // 優先度(0～7、7が最優先)
                            &s_TaskMain_Handle, // ハンドル
                            0);
#endif

#if 1
    xTaskCreatePinnedToCore(_vTaskWiFi,    // コールバック関数ポインタ
                            "vTaskWiFi",  // タスク名
                            8192,         // スタック
                            NULL,         // パラメータ
                            6,            // 優先度(0～7、7が最優先)
                            &s_xTaskWiFi_Handle, // ハンドル
                            0);
#endif
}