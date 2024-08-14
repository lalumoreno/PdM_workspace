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

bool_t uart_init(void);
bool_t uart_send_string(uint8_t * pstring);
bool_t uart_send_string_size(uint8_t * pstring, uint16_t size);
uint8_t uart_get_last_char(void);
bool_t uart_read_it(void);
void uart_clear_last_char(void);

#endif /* UI_INC_UART_PORT_H_ */
