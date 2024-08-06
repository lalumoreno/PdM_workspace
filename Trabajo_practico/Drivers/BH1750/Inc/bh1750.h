/*
 * bh1750.h
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#ifndef BH1750_INC_BH1750_H_
#define BH1750_INC_BH1750_H_

#include "common.h"

bool_t sensorInit();
void sensorRead();
void sensorWrite();
bool_t sensorSendAddress();
bool_t sensorPowerOn();

#endif /* BH1750_INC_BH1750_H_ */
