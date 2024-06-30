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

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TICK_DURATION	100

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/


/**
 * @brief  The application entry point.
 * @retval int
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

	delay_t timer;
	delayInit(&timer, TICK_DURATION);

	uint32_t times [] = {5,5,5};
	uint32_t period[] = {1000,200,100};
	uint32_t workload[] = {50,50,50};
	delay_t timer_2;
	delayInit(&timer_2, 0);
	uint32_t i = 0;
	uint32_t t = 0;

	/* Infinite loop */
	while (1)
	{
		// 2. Toggle LED
		if (delayRead(&timer)) {
			//Change LED status
			BSP_LED_Toggle(LED1);
		}

		// 3.
		if (delayRead(&timer_2)) {
			//Change LED status
			BSP_LED_Toggle(LED2);
			t++;

			if (t >= times[i]*2) {
				uint32_t d = workload[i] * period[i] / 100;
				delayWrite(&timer_2, d);
				i = (i<2r) ? i+1 : 0;
				t = 0;
			}
		}

	}

}

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
