/*
 * dimmer_system.c
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#include "dimmer_system.h"
#include "ui.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DIMMER_FSM_DELAY	2000 // 2 second

/* Private variables----------------------------------------------------------*/
dimmerSysConfig_t mySystem; //Or send as paramter in each function

/* System initialization */
void dimmerSys_Init(){


	delayInit(&mySystem.timer, DIMMER_FSM_DELAY);

	mySystem.state = UPDATE_UI;

	/*Initial configurations of the system*/
	mySystem.sensorRead = 0;
	mySystem.pwmWrite = 0;
	mySystem.relation = 50;

	//Init UART and others i2c pwm
	//Initialize User Interface
	uiInit(&mySystem);

}

//add parameters
void systemConfigUpdate(){

}

//System update
void dimmerSys_Update(/*user input*/){
	if(delayRead(&mySystem.timer)) {

		switch (mySystem.state) {

		case UPDATE_UI:
			if (true) { //configmenu user input()
				mySystem.state = READ_TERMINAL;
			} else {
				mySystem.state = READ_SENSOR;
			}
			break;

		case READ_SENSOR:
			if (true) { //configmenu user input()
				mySystem.state = READ_TERMINAL;
			} else {
				mySystem.state = PROCESS_DATA;
			}
			break;

		case PROCESS_DATA:
			if (true) { //configmenu user input()
				mySystem.state = READ_TERMINAL;
			} else {
				mySystem.state = UPDATE_UI;
			}
			break;

		case READ_TERMINAL:
			if (true) { //saveconfig user input()
				mySystem.state = PROCESS_TERMINAL;
			}
			break;

		case PROCESS_TERMINAL:
			mySystem.state = UPDATE_UI;
			break;

		default:
			mySystem.state = UPDATE_UI;
			break;

		}

		dimmerSys_Process();
	}
}

void dimmerSys_Process() {

	switch (mySystem.state) {

	case UPDATE_UI:
		uiUpdate(&mySystem);
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
