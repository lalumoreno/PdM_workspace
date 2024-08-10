/*
 * lamp.c
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

#include "pwm_port.h"

bool_t lamp_init(){

	pwm_init();
	pwm_start();

}

void lamp_set_pulse(uint32_t pulse) {

	pwm_update(pulse);

}


