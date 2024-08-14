/*
 * i2c_port.h
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#ifndef BH1750_INC_I2C_PORT_H_
#define BH1750_INC_I2C_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

/* Public types ------------------------------------------------------------*/
typedef bool bool_t;

/* Public functions prototypes ---------------------------------------------*/
bool_t i2c_init(void);
bool_t i2c_master_write(uint16_t devAdd, uint8_t *cmd, uint16_t size);
bool_t i2c_master_read(int16_t devAdd, uint8_t *pData, uint16_t size);

#endif /* BH1750_INC_I2C_PORT_H_ */
