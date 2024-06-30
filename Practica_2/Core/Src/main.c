/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Private define ------------------------------------------------------------*/
#define TIMER_DURATION	100 //100ms

/* Private variables ---------------------------------------------------------*/
uint32_t cycle_counter[] = {5, 5, 5};	// Number of times that the cycle must be repeated
uint32_t time_frame[] = {1000, 200, 100}; // Time frame in milliseconds
uint32_t work_cycle[] = {50, 50, 50}; // Work cycle in percentage (Ex: 50%)
const uint8_t MAXSEQ = sizeof(work_cycle) / sizeof(uint32_t);

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
tick_t getCycleDuration(uint8_t i);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  The application entry point.
 * @retval 0 on success
 */
int main(void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize BSP Led for LED1 and LED2 */
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);

	/* Initialize timer for point 2 */
	delay_t timer;
	delayInit(&timer, TIMER_DURATION);

	/* Initialize timer for point 3 */
	delay_t timer_2;
	uint8_t index = 0;
	uint8_t counter = 0;
	tick_t timer2_duration = getCycleDuration(index);
	delayInit(&timer_2, timer2_duration);

	/* Infinite loop */
	while (1)
	{
		// 2. Solution point 2
		if (delayRead(&timer)) {
			//Change LED status
			BSP_LED_Toggle(LED1);
		}

		// 3. Solution point 3
		if (delayRead(&timer_2)) {
			//Change LED status
			BSP_LED_Toggle(LED2);
			counter++; //Increase counter

			// Move to next sequence if cycle_counter is completed
			if (counter >= cycle_counter[index]*2) {
				index = (index < MAXSEQ - 1) ? index + 1 : 0; //Increase index or back to 0
				timer2_duration = getCycleDuration(index);
				delayWrite(&timer_2, timer2_duration);// Set new timer duration
				counter = 0; // Reset counter
			}
		}

	}

	return 0;

}

/**
 * @brief  Get correct cycle duration according to work_cycle percentage
 * @param  i: index to the work_cycle and time_frame array
 * @retval duration in milliseconds
 */
tick_t getCycleDuration(uint8_t i) {
	if(i < 0 || i > MAXSEQ){
		Error_Handler();
	}

	return work_cycle[i] * time_frame[i] / 100;
}

/**
 * @brief  Initialize timer
 * @param  delay: pointer to timer structure
 * @param  duration: duration of the timer in milliseconds
 * @retval None
 */
void delayInit(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		Error_Handler();
		return;
	}

	//Initialize delay structure
	delay->startTime = 0;
	delay->duration = duration;
	delay->running = false;
}

/**
 * @brief  Read if the timer is expired
 * @param  delay: pointer to timer structure
 * @retval True if the duration of the timer expired
 */
bool_t delayRead(delay_t *delay){

	if(delay == NULL) {
		Error_Handler();
	}

	if(delay->running){
		tick_t currentTime = HAL_GetTick();
		tick_t diff = currentTime - delay->startTime;

		if (diff >= delay->duration) {
			delay->running = false;
			return true;
		}

	} else {
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	return false;
}

/**
 * @brief  Write timer duration
 * @param  delay: pointer to timer structure
 * @param  duration: duration of the timer in milliseconds
 * @retval None
 */
void delayWrite(delay_t *delay, tick_t duration){

	if(delay == NULL) {
		Error_Handler();
	}

	delay->duration = duration;
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
}
