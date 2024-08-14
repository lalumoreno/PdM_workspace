/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "uart_port.h"
#include "ui.h"
#include "delay.h"

/* Private define ------------------------------------------------------------*/
#define DIMMER_UI_DELAY	7000 // milliseconds

/* Private types ----------------------------------------------------------*/
typedef struct {

	bool_t menuKey;
	bool_t initialized;
	delay_t delay;

} ui_t;

/* Private variables----------------------------------------------------------*/
static ui_t myUi;

/**
 * @brief  User Interface initialization.
 * @param sys: pointer to dimmer system
 * @retval True on success, False otherwise
 */
bool_t ui_init(dimmer_t * sys) {

	myUi.menuKey = false;
	myUi.initialized = false;
	delay_init(&myUi.delay, DIMMER_UI_DELAY);

	if(!uart_init()){
		//Error in initialization
		return false;
	}

	myUi.initialized = true;

	uart_read_it(); //Enable reading// return false

	uart_send_string((uint8_t *)"\r\n\n\nDimmer init ... \r\n");

	return true;
}

/**
 * @brief  Update user interface message
 * @param sys: pointer to dimmer system
 * @retval None
 */
void ui_update(dimmer_t * sys) {

	//Print only if UI was successfully initialized
	if(myUi.initialized){

		//Print only if there was a change in lx to avoid duplicated lines
		if(sys->currentLx != sys->previousLx) {
			// Get duty cycle of PWM signal
			uint16_t duty_cycle = sys->pwmPulse * 100 / sys->maxPulse;
			printf("* Sensor: %d lx - PWM duty cycle: %d %% \r\n", sys->currentLx, duty_cycle);
		}
	}
}

/**
 * @brief Print string message in User Interface
 * @param pstring: pointer to string to print
 * @retval None
 */
void ui_print_string(uint8_t * pstring) {

	//Print only if UI was successfully initialized
	if(myUi.initialized) {
		uart_send_string(pstring);
	}

}

/**
 * @brief Print start messages in User Interface
 * @retval None
 */
void ui_print_start(){

	uart_send_string((uint8_t *)"\r\nDimmer running ... \r\n\n");
	uart_send_string((uint8_t *)"Press M to open User Menu \r\n\n");

}

/**
 * @brief Return if key to open menu was pressed
 * @retval True if M key was pressed, False otherwise
 */
bool_t ui_menu_key() {

	uint8_t c = uart_get_last_char();

	if (c == 'M') {
		return true;
	}

	return false;
}

/**
 * @brief Print User Menu in User Interface
 * @retval Settings option selected by the user
 */
ui_settings_t ui_menu(){

	uint8_t c;

	uart_send_string((uint8_t *)"********************************************** \r\n");
	uart_send_string((uint8_t *)"Please select the desired sensitivity level for the Lamp: \r\n");
	uart_send_string((uint8_t *)"1. Low sensitivity \r\n");
	uart_send_string((uint8_t *)"2. Medium sensitivity \r\n");
	uart_send_string((uint8_t *)"3. High sensitivity \r\n");
	uart_send_string((uint8_t *)"********************************************** \r\n");

	//Loop to get System is blocked unitl a setting is selected
	while ( true ) {

		if(delay_read(&myUi.delay)) {
			uart_clear_last_char();
			ui_print_string((uint8_t *)"[UI] User Menu Timeout \r\n");
			return SETTINGS_TIMEOUT;
		}

		c = uart_get_last_char();

		switch( c ) {

		case '1':
			ui_print_string((uint8_t *)"[UI] Settings option 1 selected \r\n");
			return SETTINGS_OPTION_1;
			break;

		case '2':
			ui_print_string((uint8_t *)"[UI] Settings option 2 selected \r\n");
			return SETTINGS_OPTION_2;
			break;

		case '3':
			ui_print_string((uint8_t *)"[UI] Settings option 3 selected \r\n");
			return SETTINGS_OPTION_3;
			break;

		default:
			break;
		}
	}
}
