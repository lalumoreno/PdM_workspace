/*
 * API_uart.h
 *
 *  Created on: Jul 29, 2024
 *      Author: laura
 */

#ifndef UI_INC_UART_PORT_H_
#define UI_INC_UART_PORT_H_

#include "common.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"


bool_t uart_init();
bool_t uart_send_string(uint8_t * pstring);
void uart_receive_string(uint8_t * pstring, uint16_t size);
void uart_read_it(void);

#endif /* UI_INC_UART_PORT_H_ */
