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
#ifdef CFG_USE_RTOS_MAIN_TASK
#define TASK_MAIN_DELAY_MS    (100 / portTICK_PERIOD_MS)
static xTaskHandle s_TaskMain_Handle;
#endif

#ifdef CFG_USE_RTOS_WIFI_TASK
#define TASK_WIFI_DELAY_MS    (1000 / portTICK_PERIOD_MS)
static xTaskHandle s_xTaskWiFi_Handle;
static bool s_led_val = true;
static bool s_wifi_enable = false;
#endif

// -----------------------------------------------------------
// [Static]

#ifdef CFG_USE_RTOS_MAIN_TASK
static void _vTaskMain(void *p_param)
{
    while (1)
    {
        digitalWrite(OB_LED_PIN, s_led_val ? HIGH : LOW);
        s_led_val = !s_led_val;
        vTaskDelay(TASK_MAIN_DELAY_MS / portTICK_PERIOD_MS);
    }
}
#endif

#ifdef CFG_USE_RTOS_WIFI_TASK
/**
 * @brief FreeRTOS WiFiタスク
 * @param p_parameter (未使用)
 */
void _vTaskWiFi(void *p_parameter)
{
    while (1)
    {
        Serial.printf("WiFi SSID: %s\r\n", MY_WIFI_SSID);
        Serial.printf("WiFi Password: %s\r\n", MY_WIFI_PASSWORD);

        app_wifi_init(MY_WIFI_SSID, MY_WIFI_PASSWORD);

        Serial.printf("WiFi IP: %s\r\n", WiFi.localIP().toString().c_str());
        Serial.printf("WiFi RSSI: %d dBm\r\n", WiFi.RSSI());

        Serial.printf("RTC Sync Start\r\n");
        app_wifi_ntp_sync();

        Serial.printf("WiFi Disconnected\r\n");
        app_wifi_disconnet();

        Serial.printf("WiFi Task Suspend! GoodBye zzz\r\n");
        vTaskSuspend(NULL);
    }
}
#endif
// -----------------------------------------------------------
// [API]

void app_rtos_init(void)
{
#ifdef CFG_USE_RTOS_MAIN_TASK
    xTaskCreatePinnedToCore(_vTaskMain,    // コールバック関数ポインタ
                            "vTaskMain",  // タスク名
                            4096,         // スタック
                            NULL,         // パラメータ
                            0,            // 優先度(0～7、7が最優先)
                            &s_TaskMain_Handle, // ハンドル
                            0);
#endif

#ifdef CFG_USE_RTOS_WIFI_TASK
    xTaskCreatePinnedToCore(_vTaskWiFi,    // コールバック関数ポインタ
                            "vTaskWiFi",  // タスク名
                            8192,         // スタック
                            NULL,         // パラメータ
                            6,            // 優先度(0～7、7が最優先)
                            &s_xTaskWiFi_Handle, // ハンドル
                            0);
#endif
}