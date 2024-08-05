/*
 * API_uart.h
 *
 *  Created on: Jul 29, 2024
 *      Author: laura
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

typedef bool bool_t;		//1 byte

bool_t uartInit();
bool_t uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartPrintf();
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif /* API_INC_API_UART_H_ */
