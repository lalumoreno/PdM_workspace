/*
 * dimmer_system.c
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#include "dimmer_system.h"
#include "API_delay.h"
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {

	UPDATE_UI,
	READ_SENSOR,
	PROCESS_DATA,
	READ_TERMINAL,
	PROCESS_TERMINAL

} systemState_t;

/* Private define ------------------------------------------------------------*/
#define FSM_DELAY	1000 // 1 second

/* Private variables----------------------------------------------------------*/
systemState_t current_state;
delay_t timer;


void systemFSMInit(){
	//System init
	delayInit(&timer, FSM_DELAY);
	current_state = UPDATE_UI;

	/*Initial configurations of the system*/
	//uint32_t relacion
	//Init UART and others i2c pwm
	uiInit();

}

//add parameters
void systemConfigUpdate(){

}

void systemFSMUpdate(/*user input*/){
//System update
	if(delayRead(&timer)) {

		switch (current_state) {

		case UPDATE_UI:
			if (true) { //configmenu user input()
				current_state = READ_TERMINAL;
			} else {
				current_state = READ_SENSOR;
			}
			break;

		case READ_SENSOR:
			if (true) { //configmenu user input()
				current_state = READ_TERMINAL;
			} else {
				current_state = PROCESS_DATA;
			}
			break;

		case PROCESS_DATA:
			if (true) { //configmenu user input()
				current_state = READ_TERMINAL;
			} else {
				current_state = UPDATE_UI;
			}
			break;

		case READ_TERMINAL:
			if (true) { //saveconfig user input()
				current_state = PROCESS_TERMINAL;
			}
			break;

		case PROCESS_TERMINAL:
			current_state = UPDATE_UI;
			break;

		default:
			current_state = UPDATE_UI;
			break;

		}

		systemFSMProcess();
	}
}

void systemFSMProcess() {

	switch (current_state) {

	case UPDATE_UI:
		//call ui_update();
		break;

	case READ_SENSOR:
		//call bh1750_read();
		break;

	case PROCESS_DATA:
		//call pwm_update();
		break;

	case READ_TERMINAL:
		//call ui_read();
		break;

	case PROCESS_TERMINAL:
		//call systemConfig_update()
		break;

	default:
		break;

	}
}
