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
bool_t ui_menu_key();
void ui_settings_save();
bool_t ui_menu_settings();

#endif /* UI_INC_UI_H_ */
