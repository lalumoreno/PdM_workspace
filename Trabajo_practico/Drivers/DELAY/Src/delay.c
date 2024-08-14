/*
 * delay.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Laura Moreno
 */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "stm32f4xx_hal.h"

/**
 * @brief  Initialize non blocking timer
 * @param  delay: pointer to timer structure
 * @param  duration: duration of the timer in milliseconds
 * @retval True if success
 */
bool_t delay_init(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		return false;
	}

	//Initialize delay structure
	delay->startTime = 0;
	delay->duration = duration;
	delay->running = false;

	return true;
}

/**
 * @brief  Read if the timer is expired
 * @param  delay: pointer to timer structure
 * @retval True if the duration of the timer expired
 */
bool_t delay_read(delay_t *delay){

	if(delay == NULL) {
		return false;
	}

	if(delay->running){
		tick_t currentTime = HAL_GetTick();
		tick_t diff = currentTime - delay->startTime;

		if (diff >= delay->duration) {
			delay->running = false;
			return true;
		}

	} else {
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	return false;
}

/**
 * @brief  Write timer duration
 * @param  delay: pointer to timer structure
 * @param  duration: duration of the timer in milliseconds
 * @retval True if success
 */
bool_t delay_write(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		return false;
	}

	delay->duration = duration;

	return true;
}
