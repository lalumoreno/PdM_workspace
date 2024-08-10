/*
 * API_uart.c
 *
 *  Created on: Jul 29, 2024
 *      Author: laura
 */

#include <string.h>
#include "uart_port.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

void uart_read_it(void);
void uart_error(void);

UART_HandleTypeDef huart;
uint8_t received_char;
uint8_t rx_buffer[1]; // Buffer to store received data

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

/**
 * @brief  Initialize UART protocol
 * @retval True if success, false otherwise
 */
bool_t uart_init(){

	huart.Instance = USART6; //TX-CN7:PC6 RX-CN7:PC7
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		return false;
	}

	return true;
}

/**
 * @brief Prints a whole string
 * @param String to print
 * @retval None
 */
bool_t uart_send_string(uint8_t * pstring){

	if(pstring == NULL) {
		uart_error();
	}

	if (HAL_UART_Transmit(&huart, pstring, strlen((const char*)pstring), HAL_MAX_DELAY) != HAL_OK){
		return false;
	}

	return true;

}

/**
 * @brief Prints only some bytes of a string
 * @param String to print and numbers of bytes to print
 * @retval None
 */
void uart_send_string_size(uint8_t * pstring, uint16_t size){
	if(pstring == NULL) {
		uart_error();
	}

	HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY);
}

void uart_read_it(void) {
	if (HAL_UART_Receive_IT(&huart, rx_buffer, sizeof(rx_buffer)) != HAL_OK) {
		// Receive Error
		uart_error();
	}
}

// Callback function called by HAL when data is received
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if (huart->Instance == USART6) {
		// Store the received character
		received_char = rx_buffer[0];
	}

	uart_read_it();
}

uint8_t uart_get_last_char() {

	return received_char;

}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles USART6 global interrupt.
 */
void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void uart_error(void)
{
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
}
