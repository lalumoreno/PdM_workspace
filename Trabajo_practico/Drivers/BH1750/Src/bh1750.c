/*
 * bh1750.c
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#include "bh1750.h"
#include "i2c_port.h"

#define ADDRESS 0x23 << 1
#define BH1750_POWER_ON 0x01
#define BH1750_CONTINUOUS_HIGH_RES_MODE 0x10

typedef enum {
	// Power down
	POWER_DOWN = 0x00,
	// Power On
	POWER_ON = 0x01,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE = 0x10,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	CONTINUOUS_LOW_RES_MODE = 0x13,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE = 0x20,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE_2 = 0x21,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	ONE_TIME_LOW_RES_MODE = 0x23
}instruction_t;

bool_t sensorSendCmd(uint8_t cmd);


//uint8_t address receive as parameter
bool_t sensorInit(){

	if (i2cInit()) {

		if (sensorPowerOn()) {
			//HAL_Delay(10); // 10 ms delay
			return sensorSetHighResolution();
		}
	}

	return false;

}

bool_t sensorPowerOn(){

	return sensorSendCmd(BH1750_POWER_ON);

}

bool_t sensorSetHighResolution(){

	return sensorSendCmd(BH1750_CONTINUOUS_HIGH_RES_MODE);

}

bool_t sensorReadtemp(uint8_t *pData, uint16_t Size){

	 return i2CMasterRead(ADDRESS, pData, Size);
}

void sensorRead(){


}

bool_t sensorSendCmd(uint8_t cmd) {

	return i2CMasterWrite(ADDRESS, &cmd, 1);
}
