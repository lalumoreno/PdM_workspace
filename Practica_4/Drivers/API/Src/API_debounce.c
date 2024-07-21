/*
 * API_debounce.c
 *
 *  Created on: Jul 18, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include "API_debounce.h"

/* Private variables ---------------------------------------------------------*/
typedef enum{

	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,

} debounceState_t;

static debounceState_t state;
static bool_t button_pressed;

/* Private function prototypes -----------------------------------------------*/
bool_t debounceFSM_readKey();

/**
 * @brief  Initialize debouncer
 * @retval None
 */
void debounceFSM_init() {

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
 * @retval None
 */
void debounceFSM_update(bool_t button ) {

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
