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

void debounceFSM_init() {

	state = BUTTON_UP;
	button_pressed = false;

}

bool_t debounceFSM_isButtonDown() {

	return (state == BUTTON_DOWN);
}

bool_t debounceFSM_readKey() {

	if (button_pressed) {
		button_pressed = false;
		return true;
	}

	return button_pressed;
}

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
