/*
 * dimmer_system.h
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#ifndef API_INC_DIMMER__H_
#define API_INC_DIMMER__H_

/* Includes ------------------------------------------------------------------*/

#include "common.h"
#include "delay.h"


/* Exported types ------------------------------------------------------------*/

typedef enum {

	INIT,
	UPDATE_UI,
	READ_SENSOR,
	UPDATE_LAMP,
	READ_TERMINAL,
	SAVE_SETTINGS

} dimmerState_t;

typedef struct {

	delay_t timer;
	dimmerState_t state;
	uint16_t currentLx;
	uint16_t previousLx;
	uint32_t pwmPulse;

} dimmer_t;


/* Exported functions prototypes ---------------------------------------------*/

void dimmer_init();
void dimmer_run();
void dimmer_fsm_update();

#endif /* API_INC_DIMMER__H_ */
