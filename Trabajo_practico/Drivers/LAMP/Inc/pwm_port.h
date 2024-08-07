/*
 * pwm_port.h
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

#ifndef LAMP_INC_PWM_PORT_H_
#define LAMP_INC_PWM_PORT_H_

#include "common.h"

void MX_TIM3_Init(void);
void PWMStart();
uint32_t PWMChange(uint32_t pulse);

#endif /* LAMP_INC_PWM_PORT_H_ */
