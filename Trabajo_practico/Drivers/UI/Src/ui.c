/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#include <uart_port.h>
#include "ui.h"

bool_t uiInit(dimmerSysConfig_t * sys) {

	if(!uartInit()){
		//Error in initialization
		return false;
	}

	uartSendString((uint8_t *)"********************************************** \r\n");
	uartSendString((uint8_t *)"Trabajo Practico CESE \r\n");
	uartSendString((uint8_t *)"Autor: Laura Moreno \r\n\n");
	uartSendString((uint8_t *)"********************************************** \r\n");
	uartSendString((uint8_t *)"Dimer automatico \r\n");
	uartSendString((uint8_t *)"********************************************** \r\n");
	uiPrintConfig(sys);
	//

	//uartSendString("Dimer automatico \n"); timestamp y datos?
}

void uiClear() {

}

//receive Sensor read and pwm
void uiUpdate(dimmerSysConfig_t * sys) {
	//uartSendString("Dimer automatico \n"); timestamp y datos?
	printf("* Sensor read: %d PWM Write: %d \r\n", sys->sensorRead, sys->pwmWrite);
}

void uiConfigMenu() {

}

void uiConfigSave(){

}

void uiPrintConfig(dimmerSysConfig_t * sys){
	uartSendString((uint8_t *)"System configuration: \r\n");
	uartSendString((uint8_t *)"Sensor Read \r\n");
	printf("Sensor read: %d \r\n", sys->sensorRead);
	printf("PWM Write: %d \r\n", sys->pwmWrite);
	printf("Relation: %d \r\n", sys->relation);
}
