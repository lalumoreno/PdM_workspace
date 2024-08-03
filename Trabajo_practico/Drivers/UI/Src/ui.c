/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#include "ui.h"
#include "API_uart.h"
//#include "port.h"

bool_t uiInit() {

	if(!uartInit()){
		//Error in initialization
		return false;
	}

	uartSendString((uint8_t *)"Trabajo Practico CESE \n");
	uartSendString((uint8_t *)"Autor: Laura Moreno \n\n");
	uartSendString((uint8_t *)"********************************************** \n");
	uartSendString((uint8_t *)"Dimer automatico \n");
	uartSendString((uint8_t *)"********************************************** \n");
	//uiPrintConfig(system_conig);
	//

	//uartSendString("Dimer automatico \n"); timestamp y datos?
}

void uiClear() {

}

//receive Sensor read and pwm
void uiUpdate() {
	//uartSendString("Dimer automatico \n"); timestamp y datos?
}

void uiConfigMenu() {

}

void uiConfigSave(){

}

void uiPrintConfig(dimmerSysConfig_t * sys){
	uartSendString((uint8_t *)"Configs \n");
}
