/*
 * clk.c
 *
 *  Created on: 2020-07-15 18:14
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <time.h>

#include "esp_log.h"
#include "esp_task.h"

#include "core/os.h"
#include "board/seg.h"

#define TAG "clk"

static time_t now = 0;
static struct tm timeinfo = {0};

static bool col_val = false;

static void tim_task(void *pvParameter)
{
    portTickType xLastWakeTime;

    while (1) {
        xLastWakeTime = xTaskGetTickCount();

        time(&now);
        localtime_r(&now, &timeinfo);

        seg_set_col(col_val = !col_val);

        vTaskDelayUntil(&xLastWakeTime, 500 / portTICK_RATE_MS);
    }
}

static void seg_task(void *pvParameter)
{
    vTaskDelay(500 / portTICK_RATE_MS);

    while (1) {
        seg_set_num(1, timeinfo.tm_hour / 10);
        vTaskDelay(1 / portTICK_RATE_MS);

        seg_set_num(2, timeinfo.tm_hour % 10);
        vTaskDelay(1 / portTICK_RATE_MS);

        seg_set_num(3, timeinfo.tm_min / 10);
        vTaskDelay(1 / portTICK_RATE_MS);

        seg_set_num(4, timeinfo.tm_min % 10);
        vTaskDelay(1 / portTICK_RATE_MS);
    }
}

static void clk_task(void *pvParameter)
{
    xEventGroupWaitBits(
        user_event_group,
        NTP_SYNC_RUN_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );
    xTaskCreatePinnedToCore(tim_task, "timT", 1280, NULL, ESP_TASK_TIMER_PRIO, NULL, 0);

    xEventGroupWaitBits(
        user_event_group,
        NTP_SYNC_SET_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );
    xTaskCreatePinnedToCore(seg_task, "segT", 1280, NULL, ESP_TASK_PRIO_MAX, NULL, 1);

    ESP_LOGI(TAG, "started.");

    vTaskDelete(NULL);
}

void clk_init(void)
{
    xTaskCreatePinnedToCore(clk_task, "clkT", 1280, NULL, 5, NULL, 0);
}
