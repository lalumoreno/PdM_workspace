/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#include "ui.h"
#include "API_uart.h"

void uiInit() {
	uartInit();
	uartSendString("Trabajo Practico CESE \n");
	uartSendString("Dimer automatico \n");
	//uartSendString("Dimer automatico \n"); timestamp y datos?
}

void uiClear() {

}

//receive Sensor read and pwm
void uiUpdate() {

}

void uiConfigMenu() {

}

void uiConfigSave(){

}
