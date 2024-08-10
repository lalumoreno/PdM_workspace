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

typedef enum {

	SETTINGS_OPTION_1,
	SETTINGS_OPTION_2,
	SETTINGS_OPTION_3,

}ui_settings_t;

bool_t ui_init(dimmer_t * sys);
void ui_update(dimmer_t * sys); //receive Sensor read and pwm
bool_t ui_menu_key();
void ui_settings_save();
ui_settings_t ui_menu();
void ui_start();

#endif /* UI_INC_UI_H_ */
