/*
 * ui.h
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#ifndef UI_INC_UI_H_
#define UI_INC_UI_H_

#include "common.h"
#include "dimmer.h"

bool_t ui_init(dimmer_t * sys);
void ui_update(dimmer_t * sys); //receive Sensor read and pwm
void ui_menu();
void ui_settings_save();

#endif /* UI_INC_UI_H_ */
