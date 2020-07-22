/*
 * os.h
 *
 *  Created on: 2018-03-04 20:07
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_CORE_OS_H_
#define INC_CORE_OS_H_

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

typedef enum wifi_event_group_bits {
    WIFI_RDY_BIT = BIT0,
} wifi_event_group_bits_t;

typedef enum user_event_group_bits {
    NTP_RUN_BIT = BIT0,
    NTP_RDY_BIT = BIT1,

    MAN_RUN_BIT = BIT2,
} user_event_group_bits_t;

extern EventGroupHandle_t wifi_event_group;
extern EventGroupHandle_t user_event_group;

extern void os_init(void);

#endif /* INC_CORE_OS_H_ */
