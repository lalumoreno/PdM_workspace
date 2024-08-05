/*
 * bh1750.c
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

#include "bh1750.h"

void sensorInit(){
	i2cInit();
}

void sensorRead(){


}

void sensorWrite() {

	i2CWriteToMaster();
}
