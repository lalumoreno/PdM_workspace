/*
 * API_debounce.c
 *
 *  Created on: Jul 18, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "API_debounce.h"
#include "API_uart.h"
#include "API_delay.h"

#define DEBOUNCE_DURATION	50

/* Private variables ---------------------------------------------------------*/
typedef enum{

	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,

} debounceState_t;

static debounceState_t state;
static bool_t button_pressed;
static delay_t timer;

/* Private function prototypes -----------------------------------------------*/
bool_t debounceFSM_readKey();

/**
 * @brief  Initialize debouncer
 * @retval None
 */
void debounceFSM_init() {

	delayInit(&timer, DEBOUNCE_DURATION);

	state = BUTTON_UP;
	button_pressed = false;

}

/**
 * @brief  Get if button is down
 * @retval True if button is down
 */
bool_t debounceFSM_isButtonDown() {

	return (state == BUTTON_DOWN);
}

/**
 * @brief  Get value of button_pressed
 * @retval True if button is pressed
 */
bool_t debounceFSM_readKey() {

	if (button_pressed) {
		button_pressed = false;
		return true;
	}

	return button_pressed;
}

/**
 * @brief  Update debounce FSM and set new state according with transitions
 * @param receive if the current value of the USER_BUTTON GPIO read from HAL
 * @retval None
 */
void debounceFSM_update(bool_t button ) {

	if (delayRead(&timer)) {
		button_pressed = button;

		switch(state) {

		case BUTTON_UP:
			if (debounceFSM_readKey()) {
				state = BUTTON_FALLING;
			}
			break;

		case BUTTON_FALLING:
			if (debounceFSM_readKey()) {
				state = BUTTON_DOWN;
				uartSendString((uint8_t*)"Flanco descendente detectado \r\n");
			} else {
				state = BUTTON_UP;
			}
			break;

		case BUTTON_DOWN:
			if (!debounceFSM_readKey()) {
				state = BUTTON_RAISING;
			}
			break;

		case BUTTON_RAISING:
			if (!debounceFSM_readKey()) {
				uartSendString((uint8_t*)"Flanco ascendente detectado \r\n");
				state = BUTTON_UP;
			} else {
				state = BUTTON_DOWN;
			}
			break;

		default:
			debounceFSM_init();
			break;
		}
	}
}
