/*
 * API_delay.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Laura Moreno
 */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"

/**
 * @brief  Initialize timer
 * @param  delay: pointer to timer structure
 * @param  duration: duration of the timer in milliseconds
 * @retval None
 */
void delayInit(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		delayErrorHandler();
		return;
	}

	//Initialize delay structure
	delay->startTime = 0;
	delay->duration = duration;
	delay->running = false;
}

/**
 * @brief  Read if the timer is expired
 * @param  delay: pointer to timer structure
 * @retval True if the duration of the timer expired
 */
bool_t delayRead(delay_t *delay){

	if(delay == NULL) {
		delayErrorHandler();
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
 * @retval None
 */
void delayWrite(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		delayErrorHandler();
	}

	delay->duration = duration;
}

/**
 * @brief  Get if the timer is running
 * @param  delay: pointer to timer structure
 * @retval True or False
 */
bool_t delayIsRunning(delay_t * delay) {

	if(delay == NULL) {
		delayErrorHandler();
	}

	return delay->running;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void delayErrorHandler(void)
{
	__disable_irq();
	while (1)
	{
	}
}
