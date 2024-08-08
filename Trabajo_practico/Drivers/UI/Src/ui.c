/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#include <uart_port.h>
#include "ui.h"

void ui_print_settings(dimmer_t * sys);

bool_t ui_init(dimmer_t * sys) {

	if(!uart_init()){
		//Error in initialization
		return false;
	}

	uart_send_string((uint8_t *)"********************************************** \r\n");
	uart_send_string((uint8_t *)"Trabajo Practico CESE \r\n");
	uart_send_string((uint8_t *)"Autor: Laura Moreno \r\n\n");
	uart_send_string((uint8_t *)"********************************************** \r\n");
	uart_send_string((uint8_t *)"Dimer automatico \r\n");
	uart_send_string((uint8_t *)"********************************************** \r\n");

	ui_print_settings(sys);
	//uartSendString("Dimer automatico \n"); timestamp y datos?

	uart_read_it();

	return true;
}

void ui_update(dimmer_t * sys) {
	//TODO Check if initialized
	//uartSendString("Dimer automatico \n"); timestamp y datos?
	if(sys->currentLx != sys->previousLx) {
		//Only print if there was a change in lx
		printf("* Sensor read: %d PWM Write: %d \r\n", sys->currentLx, sys->pwmPulse);
	}

}

void ui_menu() {

//	UART_Read_IT();
}

void ui_settings_save(){

}

void ui_print_settings(dimmer_t * sys){
	uart_send_string((uint8_t *)"System configuration: \r\n");
	uart_send_string((uint8_t *)"Sensor Read \r\n");
	printf("Sensor read: %d \r\n", sys->currentLx);
	printf("PWM Write: %d \r\n", sys->pwmPulse);
}
