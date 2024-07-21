/*
 * API_debounce.h
 *
 *  Created on: Jul 11, 2024
 *      Author: laura
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
typedef bool bool_t;

/* Exported functions prototypes ---------------------------------------------*/
void debounceFSM_init(void);
void debounceFSM_update(bool_t button);
bool_t debounceFSM_isButtonDown();

#ifdef __cplusplus
}
#endif

#endif /* API_INC_API_DEBOUNCE_H_ */
