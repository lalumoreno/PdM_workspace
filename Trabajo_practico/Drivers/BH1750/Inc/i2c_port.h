/*
 * i2c_port.h
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#ifndef BH1750_INC_I2C_PORT_H_
#define BH1750_INC_I2C_PORT_H_

#include "stm32f4xx_hal.h"
#include "common.h"

bool_t i2cInit();
bool_t i2CSlaveWrite(uint8_t *pData, uint16_t Size);
bool_t i2cSlaveRead(uint8_t *pData, uint16_t Size);
bool_t i2CMasterRead(int16_t DevAddress, uint8_t *pData, uint16_t Size);
bool_t i2CMasterWrite(uint16_t DevAddress, uint8_t *cmd, uint16_t Size);

#endif /* BH1750_INC_I2C_PORT_H_ */
