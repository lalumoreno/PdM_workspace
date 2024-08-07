/*
 * pwm_port.h
 *
 *  Created on: Aug 7, 2024
 *      Author: laura
 */

#ifndef LAMP_INC_PWM_PORT_H_
#define LAMP_INC_PWM_PORT_H_

#include <common.h>

void pwm_init(void);
void pwm_start();
uint32_t pwm_update(uint32_t pulse);

#endif /* LAMP_INC_PWM_PORT_H_ */
