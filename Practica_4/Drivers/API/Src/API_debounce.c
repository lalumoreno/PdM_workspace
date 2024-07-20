/*
 * API_debounce.c
 *
 *  Created on: Jul 18, 2024
 *      Author: laura
 */

#include "API_debounce.h"

// Enum privado
typedef enum{

	BUTTON_UP,  // Estado: inicial (no presionado)
	BUTTON_FALLING,  // Estado: siendo presionado
	BUTTON_DOWN, // Estado: totalmente presionado
	BUTTON_RAISING, // Estado: se suelta el botón

} debounceState_t;

// Variable global privado
bool_t button_pressed;

// Variable global privada (con static)
static debounceState_t estadoActual;

bool_t isButtonDown() {

	if (estadoActual == BUTTON_DOWN) {

		return true;

	} else {

		return false;

	}

}

void debounceFSM_init(void){

	estadoActual = BUTTON_UP;

}

void writeKey() {

	button_pressed = true;

}

bool_t readKey() {

	if (button_pressed) {

		button_pressed = false;

		return true;

	}

	return button_pressed;

}

void debounceFSM_update(void) {

	switch(estadoActual) {

	case BUTTON_UP:

		estadoActual = BUTTON_FALLING;
		break;

	case BUTTON_FALLING:

		if (readKey()) {

			estadoActual = BUTTON_DOWN;

		} else {

			estadoActual = BUTTON_UP;

		}

		break;

	case BUTTON_RAISING:

		if (!readKey()) {

			estadoActual = BUTTON_UP;

		} else {

			estadoActual = BUTTON_DOWN;

		}

		break;

	case BUTTON_DOWN:

		estadoActual = BUTTON_RAISING;

		break;

	default:

		debounceFSM_init();

		break;

	}

}



