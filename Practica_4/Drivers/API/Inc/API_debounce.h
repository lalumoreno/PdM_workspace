/*
 * API_debounce.h
 *
 *  Created on: Jul 11, 2024
 *      Author: laura
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_

#include <stdbool.h>

typedef bool bool_t;

void debounceFSM_init(void);
void debounceFSM_update(bool_t button);
bool_t debounceFSM_isButtonDown();

#endif /* API_INC_API_DEBOUNCE_H_ */
