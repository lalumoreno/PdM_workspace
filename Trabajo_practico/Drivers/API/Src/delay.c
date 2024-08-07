/*
 * API_delay.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Laura Moreno
 */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/* Private function prototypes -----------------------------------------------*/
void delay_error(void);

/**
 * @brief  Initialize timer
 * @param  delay: pointer to timer structure
 * @param  duration: duration of the timer in milliseconds
 * @retval None
 */
void delay_init(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		delay_error();
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
bool_t delay_read(delay_t *delay){

	if(delay == NULL) {
		delay_error();
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
void delay_write(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		delay_error();
	}

	delay->duration = duration;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void delay_error(void)
{
	while (1)
	{
	}
}
