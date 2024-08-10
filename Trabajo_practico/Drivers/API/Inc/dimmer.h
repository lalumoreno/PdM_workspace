/*
 * dimmer_system.h
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#ifndef API_INC_DIMMER__H_
#define API_INC_DIMMER__H_

/* Includes ------------------------------------------------------------------*/
#include "delay.h"


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

void dimmer_init();
void dimmer_fsm_update();

#endif /* API_INC_DIMMER__H_ */
