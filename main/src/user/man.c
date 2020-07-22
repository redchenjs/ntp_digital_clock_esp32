/*
 * man.c
 *
 *  Created on: 2020-07-15 18:14
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <time.h>
#include <string.h>

#include "esp_log.h"

#include "core/os.h"
#include "board/seg.h"
#include "user/man.h"

#define TAG "man"

static time_t now = 0;
static struct tm timeinfo = {0};

static void seg_task(void *pvParameter)
{
    seg_set_idle(false);

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

static void man_task(void *pvParameter)
{
    portTickType xLastWakeTime;

    xEventGroupWaitBits(
        user_event_group,
        MAN_RUN_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );

    ESP_LOGI(TAG, "started.");

    xTaskCreatePinnedToCore(seg_task, "segT", 1280, NULL, 5, NULL, 1);

    while (1) {
        xLastWakeTime = xTaskGetTickCount();

        time(&now);
        localtime_r(&now, &timeinfo);

        vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_RATE_MS);
    }
}

void man_init(void)
{
    xTaskCreatePinnedToCore(man_task, "manT", 1280, NULL, 5, NULL, 0);
}
