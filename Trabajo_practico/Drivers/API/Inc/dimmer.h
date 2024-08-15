/*
 * dimmer_system.h
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#ifndef API_INC_DIMMER__H_
#define API_INC_DIMMER__H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "delay.h"

/* Public types ------------------------------------------------------------*/
typedef bool bool_t;

/* Exported types ------------------------------------------------------------*/

// States of Finite State Machine
typedef enum {

	INIT,
	UPDATE_UI,
	READ_SENSOR,
	UPDATE_LAMP,
	READ_TERMINAL

} dimmerState_t;

// Dimmer system structure
typedef struct {

	delay_t timer;
	dimmerState_t state;
	uint16_t currentLx;
	uint16_t previousLx;
	uint8_t pwmPulse;
	uint16_t minLx;
	uint16_t maxLx;
	uint8_t maxPulse;

} dimmer_t;


/* Public functions prototypes ---------------------------------------------*/

void dimmer_init(void);
void dimmer_fsm_update(void);

#endif /* API_INC_DIMMER__H_ */
