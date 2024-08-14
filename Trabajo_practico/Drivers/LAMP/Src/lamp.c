/*
 * lamp.c
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include "lamp.h"

/**
 * @brief  Initialize lamp or LED
 * @retval True if success, False otherwise
 */
bool_t lamp_init(){

	if (pwm_init()) {
		//If PWM initialized, start pulse generation
		return pwm_start();
	}

	return false;
}

/**
 * @brief Change pulse of PWM signal for lamp or LED
 * @param pulse: pulse to set
 * @retval None
 */

void lamp_set_pulse(uint32_t pulse) {

	pwm_update(pulse);

}
