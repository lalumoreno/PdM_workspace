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
#include <stdbool.h>
#include <stdint.h>
#include <stdbool.h>

/* Public types ------------------------------------------------------------*/
typedef bool bool_t;
typedef uint32_t tick_t; 	//4 bytes

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;


/* Public functions prototypes ---------------------------------------------*/

bool_t delay_init(delay_t *delay, tick_t duration);
bool_t delay_read(delay_t *delay);
bool_t delay_write(delay_t *delay, tick_t duration);

#ifdef __cplusplus
}
#endif

#endif /* API_INC_DELAY_H_ */
