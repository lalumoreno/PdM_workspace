/*
 * dimmer_system.c
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

#include "dimmer_system.h"
#include "ui.h"
#include "bh1750.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DIMMER_FSM_DELAY	1000 // 1 second

/* Private variables----------------------------------------------------------*/
dimmerSysConfig_t mySystem; //Or send as paramter in each function
uint8_t data[2] = {0};

void systemError();

/* System initialization */
void dimmerSys_Init(){

	BSP_LED_Init(LED3);

	delayInit(&mySystem.timer, DIMMER_FSM_DELAY);

	mySystem.state = UPDATE_UI;

	/*Initial configurations of the system*/
	mySystem.sensorRead = 0;
	mySystem.pwmWrite = 0;
	mySystem.relation = 50;

	//Init UART and others i2c pwm
	//Initialize User Interface
	if (!uiInit(&mySystem)){
		systemError();
	}

	//int ret = sensorInit();
	if ( !sensorInit()){
		printf("sensorInit Error \r\n");
		systemError();
	}

	printf("sensorInit Ok \r\n");
}

void systemError(){
	/* Turn LED2 on */
	BSP_LED_On(LED3);
	while (1) {

	}
}

//add parameters
void systemConfigUpdate(){

}

//System update
void dimmerSys_Update(/*user input*/){
	if(delayRead(&mySystem.timer)) {

		switch (mySystem.state) {

		case UPDATE_UI:
			if (false) { //configmenu user input()
				mySystem.state = READ_TERMINAL;
			} else {
				mySystem.state = READ_SENSOR;
			}
			break;

		case READ_SENSOR:
			if (false) { //configmenu user input()
				mySystem.state = READ_TERMINAL;
			} else {
				mySystem.state = PROCESS_DATA;
			}
			break;

		case PROCESS_DATA:
			if (false) { //configmenu user input()
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

		if ( !sensorReadtemp(&data, 2)){
			printf("sensorReadtemp Error \r\n");
			systemError();
		}

		uint16_t lux = (data[0] << 8) | data[1]; // Combine MSB and LSB
		printf("sensorReadtemp Ok %d \r\n", lux);
		//printf("sensorReadtemp Ok %x \r\n", data);
		//mySystem.sensorRead = data;

		break;

	case PROCESS_DATA:
		//printf("PROCESS_DATA \r\n");
		//call pwm_update();
		break;

	case READ_TERMINAL:
		//printf("READ_TERMINAL \r\n");
		//call ui_read();
		break;

	case PROCESS_TERMINAL:
		//printf("READ_TERMINAL \r\n");
		//call systemConfig_update()
		break;

	default:
		break;

	}
}
