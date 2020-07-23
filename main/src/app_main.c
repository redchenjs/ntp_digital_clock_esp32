/*
 * app_main.c
 *
 *  Created on: 2018-03-11 15:57
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include "core/os.h"
#include "core/app.h"

#include "chip/nvs.h"
#include "chip/wifi.h"

#include "board/seg.h"

#include "user/ntp.h"
#include "user/man.h"

static void core_init(void)
{
    app_print_info();

    os_init();
}

static void chip_init(void)
{
    nvs_init();

    wifi_init();
}

static void board_init(void)
{
    seg_init();
}

static void user_init(void)
{
    ntp_init();

    man_init();
}

int app_main(void)
{
    core_init();

    chip_init();

    board_init();

    user_init();

    return 0;
}
