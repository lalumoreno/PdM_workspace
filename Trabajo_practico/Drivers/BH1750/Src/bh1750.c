/*
 * bh1750.c
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#include "bh1750.h"
#include "i2c_port.h"

#define ADDRESS 0x23

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

//uint8_t address receive as parameter
bool_t sensorInit(){

	if(!i2cInit()) {
		return false;
	}

	return sensorPowerOn();
}

bool_t sensorPowerOn(){

	return i2CMasterWrite(ADDRESS, POWER_ON, 1);
}

bool_t sensorSendAddress(){

	//	return i2CMasterWrite((uint8_t *)ADDRESS, 1);
}

bool_t sensorReadtemp(){
/*
	if (!sensorSendAddress()){
		return false;
	}
*/
	if(!i2CMasterWrite(ADDRESS, CONTINUOUS_HIGH_RES_MODE, 1)){
		return false;
	}

	uint8_t data[16];
	return i2CMasterRead(ADDRESS, data, 16);

}

void sensorRead(){


}

void sensorWrite() {

	//i2CWriteToMaster();
}
