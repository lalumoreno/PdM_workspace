/*
 * bh1750.h
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#ifndef BH1750_INC_BH1750_H_
#define BH1750_INC_BH1750_H_

#include <common.h>

bool_t bh1750_init();
bool_t bh1750_power_on();
bool_t bh1750_high_resolution();
bool_t bh1750_read(uint8_t *pData, uint16_t Size);

#endif /* BH1750_INC_BH1750_H_ */
