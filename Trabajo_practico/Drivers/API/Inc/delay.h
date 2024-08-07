/*
 * API_delay.h
 *
 *  Created on: Jul 4, 2024
 *      Author: Laura Moreno
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef API_INC_DELAY_H_
#define API_INC_DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "common.h"
#include "stm32f4xx_hal.h"


/* Exported types ------------------------------------------------------------*/

typedef uint32_t tick_t; 	//4 bytes

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;


/* Exported functions prototypes ---------------------------------------------*/

void delay_init(delay_t *delay, tick_t duration);
bool_t delay_read(delay_t *delay);
void delay_write(delay_t *delay, tick_t duration);

#ifdef __cplusplus
}
#endif

#endif /* API_INC_DELAY_H_ */
