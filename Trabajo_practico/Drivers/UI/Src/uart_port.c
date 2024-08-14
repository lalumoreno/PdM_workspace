/*
 * API_uart.c
 *
 *  Created on: Jul 29, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "uart_port.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

/* Private variables----------------------------------------------------------*/
static UART_HandleTypeDef huart;
static uint8_t received_char;
static uint8_t rx_buffer[1]; // Buffer to store received data

/* Private function prototypes -----------------------------------------------*/
void USART6_IRQHandler(void);

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
	return ch;
}

/**
 * @brief  Initialize UART protocol
 * @retval True if success, False otherwise
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
 * @param pstring: Pointer to string to print
 * @retval True if success, False otherwise
 */
bool_t uart_send_string(uint8_t * pstring){

	if(pstring == NULL) {
		return false;
	}

	if (HAL_UART_Transmit(&huart, pstring, strlen((const char*)pstring), HAL_MAX_DELAY) != HAL_OK){
		return false;
	}

	return true;

}

/**
 * @brief Prints only some bytes of a string
 * @param Pointer to string and numbers of bytes to print
 * @retval True if success, False otherwise
 */
bool_t uart_send_string_size(uint8_t * pstring, uint16_t size) {
	if(pstring == NULL) {
		return false;
	}

	if (HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY) != HAL_OK){
		return false;
	}

	return true;
}

/**
 * @brief Read UART on non-blocking mode and save data in rx_buffer
 * @retval True if success, False otherwise
 */
bool_t uart_read_it(void) {

	if (HAL_UART_Receive_IT(&huart, rx_buffer, sizeof(rx_buffer)) != HAL_OK) {
		return false;
	}

	return true;
}

/**
 * @brief Get last character received in UART buffer
 * @retval Last char received
 */
uint8_t uart_get_last_char() {

	return received_char;

}


/**
 * @brief Callback function called by HAL when UART data is received in non-blocking mode
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	//Filter to read only USART6
	if (huart->Instance == USART6) {
		// Store the received character
		received_char = rx_buffer[0];
	}

	uart_read_it();
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles USART global interrupt.
 */
void USART6_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart);
}

