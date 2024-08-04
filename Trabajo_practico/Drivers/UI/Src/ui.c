/*
 * ui.c
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#include <uart_port.h>
#include "ui.h"
//#include "port.h"

bool_t uiInit() {

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
	//uiPrintConfig(system_conig);
	//

	//uartSendString("Dimer automatico \n"); timestamp y datos?
}

void uiClear() {

}

//receive Sensor read and pwm
void uiUpdate(dimmerSysConfig_t * sys) {
	//uartSendString("Dimer automatico \n"); timestamp y datos?
	uiPrintConfig(sys);
}

void uiConfigMenu() {

}

void uiConfigSave(){

}

void uiPrintConfig(dimmerSysConfig_t * sys){
	uartSendString((uint8_t *)"System configuration: \r\n");
	uartSendString((uint8_t *)"Sensor Read \r\n");
	uartPrintf();
	//uartSendString((uint8_t *)(sys->sensorRead + '0'));
	//uartSendString((uint8_t *)"\r\n");
	//Uart make string with arguments
	//uartSendString((uint8_t *)"Configs \n" , sys%);
}
