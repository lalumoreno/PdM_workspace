/*
 * dimmer_system.h
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#ifndef INC_DIMMER_SYSTEM_H_
#define INC_DIMMER_SYSTEM_H_

#include "common.h"
#include "API_delay.h"

typedef enum {

	UPDATE_UI,
	READ_SENSOR,
	PROCESS_DATA,
	READ_TERMINAL,
	PROCESS_TERMINAL

} dimmerSysState_t;

typedef struct {

	uint32_t relation;
	uint32_t sensorRead;
	uint32_t pwmWrite;
	delay_t timer;
	dimmerSysState_t current_state;

} dimmerSysConfig_t;

void dimmerSys_Init();
void dimmerSys_Update();
void dimmerSys_Process();

#endif /* INC_DIMMER_SYSTEM_H_ */
