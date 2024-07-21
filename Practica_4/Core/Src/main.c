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
#include "API_debounce.h"
#include "stm32f4xx_nucleo_144.h"
#include "API_delay.h"

/* Private defines ---------------------------------------------------------*/
#define DEBOUNCE_DURATION	50

/* Private variables ---------------------------------------------------------*/
const uint32_t TIEMPOS[]={100, 500};
const uint8_t MAXSEQ = sizeof(TIEMPOS) / sizeof(uint32_t);

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void buttonPressed(void);
void buttonReleased(void);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  Turn on led if button pressed
 * @retval None
 */
void buttonPressed() {
	BSP_LED_On(LED1);
}

/**
 * @brief  Turn on led if button released
 * @retval None
 */
void buttonReleased() {
	BSP_LED_Off(LED1);
}

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

	/* Initialize LED1, LED2 and BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);

	/* Initialize Timers */
	delay_t timerDebounce;
	delay_t timerLED;

	delayInit(&timerDebounce, DEBOUNCE_DURATION);

	uint32_t index = 0;
	delayInit(&timerLED, TIEMPOS[index]);

	/* Initialize FSM */
	debounceFSM_init();

	while (1) {

		// Debounce timer
		if (delayRead(&timerDebounce)) {
			debounceFSM_update(BSP_PB_GetState(BUTTON_USER));
		}

		//Toggle LED
		if (delayRead(&timerLED)) {
			BSP_LED_Toggle(LED2);
		}

		//Check if the button is pressed and do something
		if (debounceFSM_isButtonDown()) {

			//Punto 1
			buttonPressed();

			//Punto 2
			index = (index + 1) % MAXSEQ;
			delayWrite(&timerLED, TIEMPOS[index]);

		} else {
			buttonReleased();
		}
	}

	return 0;
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

