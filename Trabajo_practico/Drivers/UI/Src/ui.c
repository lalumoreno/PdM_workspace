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

void ui_print_settings(dimmer_t * sys);

bool_t ui_init(dimmer_t * sys) {

	myUi.menuKey = false;
	myUi.initialized = false;

	if(!uart_init()){
		//Error in initialization
		return false;
	}

	myUi.initialized = true;

	uart_send_string((uint8_t *)"********************************************** \r\n");
	uart_send_string((uint8_t *)"Trabajo Practico CESE \r\n");
	uart_send_string((uint8_t *)"Autor: Laura Moreno \r\n\n");
	uart_send_string((uint8_t *)"********************************************** \r\n");
	uart_send_string((uint8_t *)"Dimer automatico \r\n");
	uart_send_string((uint8_t *)"********************************************** \r\n");

	ui_print_settings(sys);
	//uartSendString("Dimer automatico \n"); timestamp y datos?

	uart_read_it(); //Enable reading

	return true;
}

void ui_update(dimmer_t * sys) {
	//TODO Check if initialized
	//uartSendString("Dimer automatico \n"); timestamp y datos?
	if(sys->currentLx != sys->previousLx) {
		//Only print if there was a change in lx
		printf("* Sensor read: %d PWM Write: %ld \r\n", sys->currentLx, sys->pwmPulse);
	}

}

bool_t ui_menu_key() {

	uint8_t c = uart_get_last_char();
	//uart_get_last_char(&c);

	//uart_send_string(&c);
	// Check if received character is 'M'
	if (c == 'M') {
		// Handle the key press event
		uart_send_string((uint8_t *)"Key 'M' Pressed!\r\n");
		return true;
	}

	return false;
}

bool_t ui_menu_settings(){

	uart_send_string((uint8_t *)"Menu de configuracion: \r\n");
	uart_send_string((uint8_t *)"Seleccione la relacion que desea manejar: \r\n");
	uart_send_string((uint8_t *)"Presione C \r\n");

	uint8_t c = uart_get_last_char();

	// Check if received character is 'C'
	while ( c != 'C') {
		// Handle the key press event
		c = uart_get_last_char();
		//uart_send_string((uint8_t *)"Key 'C' Pressed!\r\n");
		//return true;
	}

	uart_send_string((uint8_t *)"Fuera del menu \r\n");
	return true;

}

void ui_settings_save(){

}

void ui_print_settings(dimmer_t * sys){
	uart_send_string((uint8_t *)"System configuration: \r\n");
	uart_send_string((uint8_t *)"Sensor Read \r\n");
	printf("Sensor read: %d \r\n", sys->currentLx);
	printf("PWM Write: %ld \r\n", sys->pwmPulse);
}
