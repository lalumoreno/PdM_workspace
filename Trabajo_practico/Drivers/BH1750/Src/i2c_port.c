/*
 * i2c_port.c
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "i2c_port.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

/* Private variables----------------------------------------------------------*/
static I2C_HandleTypeDef hi2c;


/**
 * @brief  I2C protocol initialization.
 * @retval True on success, False otherwise
 */
bool_t i2c_init(){

	hi2c.Instance = I2C1; //SDA-CN7:PB9 SCL-CN7:PB8
	hi2c.Init.ClockSpeed = 100000;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.OwnAddress1 = 0;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.OwnAddress2 = 0;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c) != HAL_OK)
	{
		return false;
	}

	/** Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	{
		return false;
	}

	/** Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c, 0) != HAL_OK)
	{
		return false;
	}

	return true;

}

/**
 * @brief  I2C Write Master to Slave
 * @param devAdd: Device Address
 * @param cmd: pointer to the instruction to be sent
 * @param size: size of the instruction
 * @retval True on success, False otherwise
 */
bool_t i2c_master_write(uint16_t devAdd, uint8_t *cmd, uint16_t size) {

	if (HAL_I2C_Master_Transmit(&hi2c, devAdd, cmd,  1, HAL_MAX_DELAY) != HAL_OK) {
		return false;
	}

	return true;
}

/**
 * @brief  I2C Read Slave from Master
 * @param devAdd: Device Address
 * @param cmd: pointer to the array to store data
 * @param size: size of the data read
 * @retval True on success, False otherwise
 */
bool_t i2c_master_read(int16_t devAdd, uint8_t *pData, uint16_t size){

	if (HAL_I2C_Master_Receive(&hi2c, devAdd, pData, size, HAL_MAX_DELAY) != HAL_OK){
		return false;
	}

	return true;
}
