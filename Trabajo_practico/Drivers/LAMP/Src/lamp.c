/*
 * lamp.c
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

#include "pwm_port.h"

void initLamp(){

	MX_TIM3_Init();
	PWMStart();

}

void lampChange(uint32_t pulse) {

	PWMChange(pulse);

}


