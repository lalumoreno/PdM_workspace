/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#include <stdio.h>
#include "uart_port.h"
#include "ui.h"

typedef struct {

	bool_t menuKey;
	bool_t initialized;

} ui_t;

ui_t myUi;

bool_t ui_init(dimmer_t * sys) {

	myUi.menuKey = false;
	myUi.initialized = false;

	if(!uart_init()){
		//Error in initialization
		return false;
	}

	myUi.initialized = true;

	uart_read_it(); //Enable reading// return false

	uart_send_string((uint8_t *)"\r\n\n\nDimmer init ... \r\n");

	return true;
}

void ui_update(dimmer_t * sys) {
	//TODO Check if initialized

	if(sys->currentLx != sys->previousLx) {
		//Only print if there was a change in lx
		// Calcular el ciclo de trabajo en porcentaje
		uint16_t duty_cycle = sys->pwmPulse * 100 / sys->maxPulse;
		printf("* Sensor: %d lx - PWM duty cycle: %ld %% \r\n", sys->currentLx, duty_cycle);
	}

}

void ui_print_error(uint8_t * pstring) {

	uart_send_string(pstring);

}

void ui_start(){

	uart_send_string((uint8_t *)"\r\nDimmer running ... \r\n\n");
	uart_send_string((uint8_t *)"Press M to open User Menu \r\n\n");

}

bool_t ui_menu_key() {

	uint8_t c = uart_get_last_char();

	if (c == 'M') {
		return true;
	}

	return false;
}

ui_settings_t ui_menu(){

	uint8_t c;

	uart_send_string((uint8_t *)"********************************************** \r\n");
	uart_send_string((uint8_t *)"Please select the desired sensitivity level for the Lamp: \r\n");
	uart_send_string((uint8_t *)"1. Low sensitivity \r\n");
	uart_send_string((uint8_t *)"2. Medium sensitivity \r\n");
	uart_send_string((uint8_t *)"3. High sensitivity \r\n");
	uart_send_string((uint8_t *)"********************************************** \r\n");

	//TODO Add timer to go back to main screen

	//System is blocked unitl a setting is selected
	while ( true ) {

		c = uart_get_last_char();

		switch( c ) {

		case '1':
			return SETTINGS_OPTION_1;
			break;

		case '2':
			return SETTINGS_OPTION_2;
			break;

		case '3':
			return SETTINGS_OPTION_3;
			break;

		default:
			break;
		}
	}
}

void ui_settings_save(){

}
