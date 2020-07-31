/*
 * seg.c
 *
 *  Created on: 2020-07-22 22:13
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "esp_log.h"

#include "driver/gpio.h"

#define TAG "seg"

static const uint8_t num_k[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

void seg_set_col(bool val)
{
    gpio_set_level(CONFIG_SEG_COL_A_PIN, val);
}

void seg_set_num(uint8_t dig, uint8_t num)
{
    gpio_set_level(CONFIG_SEG_DIG1_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_DIG2_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_DIG3_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_DIG4_A_PIN, 0);

    gpio_set_level(CONFIG_SEG_A_K_PIN,  num_k[num] & 0x01);
    gpio_set_level(CONFIG_SEG_B_K_PIN,  num_k[num] & 0x02);
    gpio_set_level(CONFIG_SEG_C_K_PIN,  num_k[num] & 0x04);
    gpio_set_level(CONFIG_SEG_D_K_PIN,  num_k[num] & 0x08);
    gpio_set_level(CONFIG_SEG_E_K_PIN,  num_k[num] & 0x10);
    gpio_set_level(CONFIG_SEG_F_K_PIN,  num_k[num] & 0x20);
    gpio_set_level(CONFIG_SEG_G_K_PIN,  num_k[num] & 0x40);
    gpio_set_level(CONFIG_SEG_DP_K_PIN, num_k[num] & 0x80);

    if (num == 1 || num == 7) {
        switch (dig) {
            case 1:
                gpio_set_drive_capability(CONFIG_SEG_DIG1_A_PIN, GPIO_DRIVE_CAP_DEFAULT);
                break;
            case 2:
                gpio_set_drive_capability(CONFIG_SEG_DIG2_A_PIN, GPIO_DRIVE_CAP_DEFAULT);
                break;
            case 3:
                gpio_set_drive_capability(CONFIG_SEG_DIG3_A_PIN, GPIO_DRIVE_CAP_DEFAULT);
                break;
            case 4:
                gpio_set_drive_capability(CONFIG_SEG_DIG4_A_PIN, GPIO_DRIVE_CAP_DEFAULT);
                break;
            default:
                break;
        }
    } else {
        switch (dig) {
            case 1:
                gpio_set_drive_capability(CONFIG_SEG_DIG1_A_PIN, GPIO_DRIVE_CAP_3);
                break;
            case 2:
                gpio_set_drive_capability(CONFIG_SEG_DIG2_A_PIN, GPIO_DRIVE_CAP_3);
                break;
            case 3:
                gpio_set_drive_capability(CONFIG_SEG_DIG3_A_PIN, GPIO_DRIVE_CAP_3);
                break;
            case 4:
                gpio_set_drive_capability(CONFIG_SEG_DIG4_A_PIN, GPIO_DRIVE_CAP_3);
                break;
            default:
                break;
        }
    }

    gpio_set_level(CONFIG_SEG_DIG1_A_PIN, dig == 1);
    gpio_set_level(CONFIG_SEG_DIG2_A_PIN, dig == 2);
    gpio_set_level(CONFIG_SEG_DIG3_A_PIN, dig == 3);
    gpio_set_level(CONFIG_SEG_DIG4_A_PIN, dig == 4);
}

void seg_set_idle(bool val)
{
    gpio_set_level(CONFIG_SEG_DIG1_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_DIG2_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_DIG3_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_DIG4_A_PIN, 0);

    if (val) {
        gpio_set_drive_capability(CONFIG_SEG_A_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_B_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_C_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_D_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_E_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_F_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_G_K_PIN,  GPIO_DRIVE_CAP_DEFAULT);
        gpio_set_drive_capability(CONFIG_SEG_DP_K_PIN, GPIO_DRIVE_CAP_DEFAULT);
    } else {
        gpio_set_drive_capability(CONFIG_SEG_A_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_B_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_C_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_D_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_E_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_F_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_G_K_PIN,  GPIO_DRIVE_CAP_3);
        gpio_set_drive_capability(CONFIG_SEG_DP_K_PIN, GPIO_DRIVE_CAP_3);
    }

    gpio_set_level(CONFIG_SEG_A_K_PIN,  1);
    gpio_set_level(CONFIG_SEG_B_K_PIN,  1);
    gpio_set_level(CONFIG_SEG_C_K_PIN,  1);
    gpio_set_level(CONFIG_SEG_D_K_PIN,  1);
    gpio_set_level(CONFIG_SEG_E_K_PIN,  1);
    gpio_set_level(CONFIG_SEG_F_K_PIN,  1);
    gpio_set_level(CONFIG_SEG_G_K_PIN,  0);
    gpio_set_level(CONFIG_SEG_DP_K_PIN, 1);

    gpio_set_level(CONFIG_SEG_DIG1_A_PIN, 1);
    gpio_set_level(CONFIG_SEG_DIG2_A_PIN, 1);
    gpio_set_level(CONFIG_SEG_DIG3_A_PIN, 1);
    gpio_set_level(CONFIG_SEG_DIG4_A_PIN, 1);
}

void seg_init(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = BIT64(CONFIG_SEG_DIG1_A_PIN) | BIT64(CONFIG_SEG_DIG2_A_PIN) |
                        BIT64(CONFIG_SEG_DIG3_A_PIN) | BIT64(CONFIG_SEG_DIG4_A_PIN) |
                        BIT64(CONFIG_SEG_COL_A_PIN)  | BIT64(CONFIG_SEG_COL_K_PIN)  |
                        BIT64(CONFIG_SEG_A_K_PIN)    | BIT64(CONFIG_SEG_B_K_PIN)    |
                        BIT64(CONFIG_SEG_C_K_PIN)    | BIT64(CONFIG_SEG_D_K_PIN)    |
                        BIT64(CONFIG_SEG_E_K_PIN)    | BIT64(CONFIG_SEG_F_K_PIN)    |
                        BIT64(CONFIG_SEG_G_K_PIN)    | BIT64(CONFIG_SEG_DP_K_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = false,
        .pull_down_en = false,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&io_conf);

    gpio_set_level(CONFIG_SEG_COL_A_PIN, 0);
    gpio_set_level(CONFIG_SEG_COL_K_PIN, 0);
    gpio_set_drive_capability(CONFIG_SEG_COL_A_PIN, GPIO_DRIVE_CAP_1);
    gpio_set_drive_capability(CONFIG_SEG_COL_K_PIN, GPIO_DRIVE_CAP_1);

    seg_set_idle(true);

    ESP_LOGI(TAG, "initialized.");
}
