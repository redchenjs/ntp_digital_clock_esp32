/*
 * seg.h
 *
 *  Created on: 2020-07-22 22:13
 *      Author: Jack Chen <redchenjs@live.com>
 */

#ifndef INC_BOARD_SEG_H_
#define INC_BOARD_SEG_H_

#include <stdint.h>

extern void seg_set_col(bool val);
extern void seg_set_num(uint8_t dig, uint8_t num);
extern void seg_set_idle(void);

extern void seg_init(void);

#endif /* INC_BOARD_SEG_H_ */
