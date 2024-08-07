/*
 * lamp.c
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

#include "pwm_port.h"

uint32_t pulse = 0 ;

void initLamp(){

	MX_TIM3_Init();
	PWMStart();

}

void lampChange() {

	pulse += 100;

	uint32_t out;
	out = PWMChange(pulse);
	pulse = out;
}


