/*
 * bh1750.c
 *
 *  Created on: Aug 4, 2024
 *      Author: laura
 */

/* Includes ------------------------------------------------------------------*/
#include "bh1750.h"
#include "i2c_port.h"


/* Private define ------------------------------------------------------------*/
#define BH1750_ADDRESS 0x23 << 1 //This is when ADDR pin is to GND


/* Private types ------------------------------------------------------------*/
//List of instructions for sensor BH1750
typedef enum {
	// Power down
	POWER_DOWN = 0x00,
	// Power On
	POWER_ON = 0x01,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE = 0x10,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	CONTINUOUS_LOW_RES_MODE = 0x13,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE = 0x20,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE_2 = 0x21,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	ONE_TIME_LOW_RES_MODE = 0x23
}command_t;


/* Private function prototypes -----------------------------------------------*/
static bool_t bh1750_send_cmd(uint8_t cmd);


/**
 * @brief  Sensor BH1750 initialization.
 * @retval True on success, False otherwise
 */
bool_t bh1750_init(){

	if (i2c_init()) {
		if (bh1750_power_on()) {
			// If power on, set continuous high resolution measurement for sensor BH1750
			return bh1750_high_resolution();
		}
	}

	return false;

}

/**
 * @brief  Send command or instruction to sensor BH1750
 * @param cmd: Instruction to send
 * @retval True on success, False otherwise
 */
bool_t bh1750_send_cmd(uint8_t cmd) {

	return i2c_master_write(BH1750_ADDRESS, &cmd, 1);
}

/**
 * @brief  Power on sensor BH1750
 * @retval True on success, False otherwise
 */
bool_t bh1750_power_on(){

	return bh1750_send_cmd(POWER_ON);

}

/**
 * @brief  Set continuous high resolution measurement for sensor BH1750
 * @retval True on success, False otherwise
 */
bool_t bh1750_high_resolution(){

	return bh1750_send_cmd(CONTINUOUS_HIGH_RES_MODE);

}

/**
 * @brief Read measurement of sensor BH1750
 * @param pData: pointer to array to store data
 * @param size: size of array
 * @retval True on success, False otherwise
 */
bool_t bh1750_read(uint8_t *pData, uint16_t size){

	return i2c_master_read(BH1750_ADDRESS, pData, size);
}
