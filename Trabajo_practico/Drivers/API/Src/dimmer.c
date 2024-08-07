/*
 * dimmer.c
 *
 *  Created on: Aug 2, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/

#include "dimmer.h"
#include "ui.h"
#include "bh1750.h"
#include "pwm_port.h"
#include "lamp.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */


/* Private typedef -----------------------------------------------------------*/



/* Private define ------------------------------------------------------------*/

#define DIMMER_FSM_DELAY	180 // milliseconds
#define MAX_LX				1000 //TODO add as configurable
#define MIN_LX				10 //TODO add as configurable


/* Private variables----------------------------------------------------------*/

dimmer_t myDimmer; //Or send as parameter in each function
uint8_t data[2] = {0};


void dimmer_error();
void dimmer_get_pwm();
void dimmer_process();

/* System initialization */
void dimmer_init(){

	BSP_LED_Init(LED3);

	delay_init(&myDimmer.timer, DIMMER_FSM_DELAY);

	myDimmer.state = INIT;

	/*Initial configurations of the system*/
	myDimmer.currentLx = 0;
	myDimmer.pwmPulse = 0;

	//Init UART and others i2c pwm
	//Initialize User Interface
	if (!ui_init(&myDimmer)){
		dimmer_error();
	}

	myDimmer.state = UPDATE_UI;

	//int ret = sensorInit();
	if ( !bh1750_init()){
		printf("sensorInit Error \r\n");
		dimmer_error();
	}

	printf("sensorInit Ok \r\n");

	lamp_init();

}

void dimmer_error(){
	/* Turn LED2 on */
	BSP_LED_On(LED3);
	while (1) {

	}
}

void dimmer_run(){
	dimmer_fsm_update();
}


void dimmer_fsm_update(/*user input*/){

	if(delay_read(&myDimmer.timer)) {

		switch (myDimmer.state) {

		case UPDATE_UI:
			if (false) { //configmenu user input()
				myDimmer.state = READ_TERMINAL;
			} else {
				myDimmer.state = READ_SENSOR;
			}
			break;

		case READ_SENSOR:
			if (false) { //configmenu user input()
				myDimmer.state = READ_TERMINAL;
			} else {
				myDimmer.state = UPDATE_LAMP;
			}
			break;

		case UPDATE_LAMP:
			if (false) { //configmenu user input()
				myDimmer.state = READ_TERMINAL;
			} else {
				myDimmer.state = UPDATE_UI;
			}
			break;

		case READ_TERMINAL:
			if (true) { //saveconfig user input()
				myDimmer.state = SAVE_SETTINGS;
			}
			break;

		case SAVE_SETTINGS:
			myDimmer.state = UPDATE_UI;
			break;

		default:
			myDimmer.state = UPDATE_UI;
			break;

		}

		dimmer_process();
	}
}

void dimmer_process() {

	switch (myDimmer.state) {

	case UPDATE_UI:
		ui_update(&myDimmer);
		break;

	case READ_SENSOR:

		//printf("READ_SENSOR \r\n");
		if ( !bh1750_read(data, 2)){
			printf("sensorReadtemp Error \r\n");
			dimmer_error();
		}

		myDimmer.previousLx = myDimmer.currentLx;
		myDimmer.currentLx = (data[0] << 8) | data[1]; // Combine MSB and LSB

		break;

	case UPDATE_LAMP:
		dimmer_get_pwm();
		lamp_set_pulse(myDimmer.pwmPulse);
		break;

	case READ_TERMINAL:
		//printf("READ_TERMINAL \r\n");
		//call ui_read();
		break;

	case SAVE_SETTINGS:
		//printf("READ_TERMINAL \r\n");
		//call systemConfig_update()
		break;

	default:
		break;

	}
}

void dimmer_get_pwm(){

	uint16_t lx = myDimmer.currentLx ;

	if (myDimmer.currentLx > MAX_LX){
		lx = MAX_LX;
	}

	myDimmer.pwmPulse = 999 - (lx - MIN_LX); //linear relation

	if (myDimmer.pwmPulse < 0) {
		myDimmer.pwmPulse = 0;
	}
}
