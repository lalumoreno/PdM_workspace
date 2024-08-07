/*
 * bh1750.c
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#include "bh1750.h"
#include "i2c_port.h"

#define BH1750_ADDRESS 0x23 << 1 //ADDR pin to GND

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
}command_t;

bool_t bh1750_send_cmd(uint8_t cmd);

//uint8_t address receive as parameter
bool_t bh1750_init(){

	if (i2c_init()) {

		if (bh1750_power_on()) {
			//HAL_Delay(10); // 10 ms delay
			return bh1750_high_resolution();
		}
	}

	return false;

}

bool_t bh1750_power_on(){

	return bh1750_send_cmd(POWER_ON);

}

bool_t bh1750_high_resolution(){

	return bh1750_send_cmd(CONTINUOUS_HIGH_RES_MODE);

}

bool_t bh1750_read(uint8_t *pData, uint16_t Size){

	 return i2c_master_read(BH1750_ADDRESS, pData, Size);
}

bool_t bh1750_send_cmd(uint8_t cmd) {

	return i2c_master_write(BH1750_ADDRESS, &cmd, 1);
}
