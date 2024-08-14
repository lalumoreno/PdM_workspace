/*
 * pwm_port.c
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

#include "stm32f4xx_hal.h"
#include "pwm_port.h"

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

TIM_HandleTypeDef htim3;

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
bool_t pwm_init(void)
{

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 180-1;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 10000-1;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		return false;
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		return false;
	}

	if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
	{
		return false;
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		return false;
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		return false;
	}

	HAL_TIM_MspPostInit(&htim3);

	return true;
}

bool_t pwm_start() {

	if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3) != HAL_OK){
		return false;
	}

	return true;
}

uint32_t pwm_update(uint32_t pulse) {

	if (pulse > htim3.Init.Period) {
		pulse = htim3.Init.Period;
	}

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pulse);

	return pulse;
}
