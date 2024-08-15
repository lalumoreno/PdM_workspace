/*
 * bh1750.h
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#ifndef BH1750_INC_BH1750_H_
#define BH1750_INC_BH1750_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/* Public types ------------------------------------------------------------*/
typedef bool bool_t;

/* Public functions prototypes ---------------------------------------------*/
bool_t bh1750_init(void);
bool_t bh1750_power_on(void);
bool_t bh1750_high_resolution(void);
bool_t bh1750_read(uint8_t *pData, uint16_t size);

#endif /* BH1750_INC_BH1750_H_ */
