/*
 * API_uart.h
 *
 *  Created on: Jul 29, 2024
 *      Author: laura
 */

#ifndef UI_INC_UART_PORT_H_
#define UI_INC_UART_PORT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"

/* Public types ------------------------------------------------------------*/
typedef bool bool_t;

bool_t uart_init();
bool_t uart_send_string(uint8_t * pstring);
void uart_read_it(void);
uint8_t uart_get_last_char();

#endif /* UI_INC_UART_PORT_H_ */
