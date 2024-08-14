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
#include "lamp.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Private define ------------------------------------------------------------*/
#define DIMMER_FSM_DELAY	180 // milliseconds

/* Private variables----------------------------------------------------------*/
static dimmer_t myDimmer;
static uint8_t sensor_data[2] = {0};

/* Private function prototypes -----------------------------------------------*/
static void dimmer_process(void);
static uint8_t dimmer_get_pulse();
static void dimmer_set_settings(ui_settings_t settings);
static void dimmer_error(uint8_t * pstring);

/**
 * @brief  Dimmer system initialization.
 * @retval None
 */
void dimmer_init(void){

	/* Initial configurations of the system */
	myDimmer.state = INIT;
	myDimmer.currentLx = 0;
	myDimmer.pwmPulse = 0;
	myDimmer.maxPulse = 199; // TODO import value of htim3.Init.Period;
	delay_init(&myDimmer.timer, DIMMER_FSM_DELAY);
	dimmer_set_settings(SETTINGS_OPTION_1);

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

	ui_print_start();

	myDimmer.state = UPDATE_UI;

}

/**
 * @brief  Dimmer finite state machine update
 * @retval None
 */
void dimmer_fsm_update(void){

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

/**
 * @brief  Execute action for each dimmer state
 * @retval None
 */
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
		// Combine MSB and LSB to get the data read from the sensor (2bytes)
		myDimmer.currentLx = (sensor_data[0] << 8) | sensor_data[1];
		break;

	case UPDATE_LAMP:
		myDimmer.pwmPulse = dimmer_get_pulse();
		lamp_set_pulse(myDimmer.pwmPulse);
		break;

	case READ_TERMINAL:
		uint8_t settings;
		settings = ui_menu();
		dimmer_set_settings(settings);
		break;

	default:
		break;

	}
}

/**
 * @brief  Calculate PWM pulse based on dimmer settings
 * @retval PWM Pulse
 */
uint8_t dimmer_get_pulse(){

	uint16_t lx = myDimmer.currentLx;

	if (lx > myDimmer.maxLx) {
		lx = myDimmer.maxLx;
	} else if (lx < myDimmer.minLx) {
		lx = myDimmer.minLx;
	}

	// Get the PWM pulse based on the inverse and linear relationship between lx and pwmPulse
	return myDimmer.maxPulse * (myDimmer.maxLx - lx) / (myDimmer.maxLx - myDimmer.minLx);
}

/**
 * @brief  Set dimmer system settings
 * @param settings: settings selected by the user
 * @retval None
 */
void dimmer_set_settings(ui_settings_t settings){

	//BH1750 returns Lx from 0 to 60000. Then three possible boundaries are established:
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

/**
 * @brief  Dimmer system error. Stop execution
 * @param pstring: error message to display
 * @retval None
 */
void dimmer_error(uint8_t * pstring){

	ui_print_error(pstring);

	/* Turn LED3 on to indicate error*/
	BSP_LED_On(LED3);
	while (1) {

	}
}
