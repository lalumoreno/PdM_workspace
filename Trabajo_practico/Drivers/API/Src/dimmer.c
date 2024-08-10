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

/* Private define ------------------------------------------------------------*/
#define DIMMER_FSM_DELAY	180 // milliseconds

/* Private variables----------------------------------------------------------*/
dimmer_t myDimmer;
uint8_t sensor_data[2] = {0};

/* Private function prototypes -----------------------------------------------*/
void dimmer_error(uint8_t * pstring);
void dimmer_get_pwm();
void dimmer_process();
void dimmer_update_settings(ui_settings_t settings);

/**
 * @brief  Dimmer system initialization.
 * @retval None
 */
void dimmer_init(){

	/* Initial configurations of the system */
	myDimmer.state = INIT;
	myDimmer.currentLx = 0;
	myDimmer.pwmPulse = 0;
	myDimmer.maxPulse = 199; // TODO import value of htim3.Init.Period;
	dimmer_update_settings(SETTINGS_OPTION_1);
	delay_init(&myDimmer.timer, DIMMER_FSM_DELAY);

	/* Initialize peripherals */
	BSP_LED_Init(LED3);

	/* Initialize User Interface */
	if (!ui_init(&myDimmer)) {
		dimmer_error((uint8_t *)"[DIMMER] Error UI Init\n\r");
	}

	/* Initialize BH1750 sensor */
	if ( !bh1750_init()) {
		dimmer_error((uint8_t *)"[DIMMER] Error BH1750 Sensor Init \n\r");
	}

	/* Initialize PWM pulse */
	if( !lamp_init()) {
		dimmer_error((uint8_t *)"[DIMMER] Error PWM Init\n\r");
	}

	ui_start();

	myDimmer.state = UPDATE_UI;

}

void dimmer_error(uint8_t * pstring){

	ui_print_error(pstring);

	/* Turn LED2 on */
	BSP_LED_On(LED3);
	while (1) {

	}
}

void dimmer_fsm_update(){

	if(delay_read(&myDimmer.timer)) {

		switch (myDimmer.state) {

		case UPDATE_UI:
			if (ui_menu_key()) {
				myDimmer.state = READ_TERMINAL;
			} else {
				myDimmer.state = READ_SENSOR;
			}
			break;

		case READ_SENSOR:
			if (ui_menu_key()) {
				myDimmer.state = READ_TERMINAL;
			} else {
				myDimmer.state = UPDATE_LAMP;
			}
			break;

		case UPDATE_LAMP:
			if (ui_menu_key()) {
				myDimmer.state = READ_TERMINAL;
			} else {
				myDimmer.state = UPDATE_UI;
			}
			break;

		case READ_TERMINAL:
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

		if ( !bh1750_read(sensor_data, 2)){
			dimmer_error((uint8_t *)"[DIMMER] Error reading BH1750 sensor \r\n");
		}

		myDimmer.previousLx = myDimmer.currentLx;
		myDimmer.currentLx = (sensor_data[0] << 8) | sensor_data[1]; // Combine MSB and LSB

		break;

	case UPDATE_LAMP:

		dimmer_get_pwm();
		lamp_set_pulse(myDimmer.pwmPulse);

		break;

	case READ_TERMINAL:
		uint8_t settings;
		settings = ui_menu();
		dimmer_update_settings(settings);
		break;

	default:
		break;

	}
}

void dimmer_get_pwm(){

	uint16_t lx = myDimmer.currentLx;

	if (lx > myDimmer.maxLx) {
		lx = myDimmer.maxLx;
	} else if (lx < myDimmer.minLx) {
		lx = myDimmer.minLx;
	}

	// Calcular el PWM en función de la relación inversa entre lx y pwmPulse
	myDimmer.pwmPulse = myDimmer.maxPulse * (myDimmer.maxLx - lx) / (myDimmer.maxLx - myDimmer.minLx);
}

void dimmer_update_settings(ui_settings_t settings){

	//BH1750 gives lx from 0 to 60000
	switch (settings) {

	case SETTINGS_OPTION_1:
		myDimmer.minLx = 0;
		myDimmer.maxLx = 2000;
		break;

	case SETTINGS_OPTION_2:
		myDimmer.minLx = 2001;
		myDimmer.maxLx = 20000;
		break;

	case SETTINGS_OPTION_3:
		myDimmer.minLx = 20001;
		myDimmer.maxLx = 60000;
		break;

	default:
		break;
	}

}
