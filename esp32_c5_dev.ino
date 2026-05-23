/**
 * @file esp32_c6_dev.ino
 * @author Chimipupu(https://github.com/Chimipupu)
 * @brief ESP32-C5 評価F/W @Arduino IDE用ファイル
 * @version 0.1
 * @date 2026-05-23
 * @copyright Copyright (c) 2026 Chimipupu All Rights Reserved.
 */

#include "pcb_define.h"
#include "app_rtos.h"
#include "app_memory.h"

void setup()
{
    // UART
    Serial.begin(UART_BAUD);

    // PSRAM初期化
    app_mem_psram_init();
    app_mem_info();

    // LED初期化
    pinMode(OB_LED_PIN, OUTPUT);
    digitalWrite(OB_LED_PIN, HIGH);

    // FreeRTOS初期化 & OS起動
    app_rtos_init();
}

void loop()
{
    // NOTE; Loopタスクはサスペンドで寝かせとく
    vTaskSuspend(NULL);
}