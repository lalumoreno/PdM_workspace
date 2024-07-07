/*
 * API_delay.h
 *
 *  Created on: Jul 4, 2024
 *      Author: Laura Moreno
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef API_API_DELAY_H_
#define API_API_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/

typedef uint32_t tick_t; 	//4 bytes
typedef bool bool_t;		//1 byte

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/* Exported functions prototypes ---------------------------------------------*/

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
bool_t delayIsRunning(delay_t * delay);
void delayErrorHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* API_API_DELAY_H_ */
