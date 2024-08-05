/*
 * API_uart.c
 *
 *  Created on: Jul 29, 2024
 *      Author: laura
 */

#include <string.h>
#include <uart_port.h>

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

void uartErrorHandler(void);

UART_HandleTypeDef huart;

/**
 * @brief  Initialize UART protocol
 * @retval True if success, false otherwise
 */
bool_t uartInit(){

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
bool_t uartSendString(uint8_t * pstring){

	if(pstring == NULL) {
		uartErrorHandler();
	}

	if (HAL_UART_Transmit(&huart, pstring, strlen((const char*)pstring), HAL_MAX_DELAY) != HAL_OK){
		return false;
	}

	return true;

}

void uartPrintf(){

	printf("Hello World\n");

}

/**
 * @brief Prints only some bytes of a string
 * @param String to print and numbers of bytes to print
 * @retval None
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	if(pstring == NULL) {
		uartErrorHandler();
	}

	HAL_UART_Transmit(&huart, pstring, size, HAL_MAX_DELAY);
}

/**
 * @brief Receives a string
 * @param Pointer to the buffer received and size of the buffer
 * @retval None
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size) {
	if(pstring == NULL) {
		uartErrorHandler();
	}

	HAL_UART_Receive(&huart, pstring, size, HAL_MAX_DELAY);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void uartErrorHandler(void)
{
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
}


PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
