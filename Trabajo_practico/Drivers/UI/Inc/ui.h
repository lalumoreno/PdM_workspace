/*
 * ui.h
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#ifndef UI_INC_UI_H_
#define UI_INC_UI_H_

/* Includes ------------------------------------------------------------------*/
#include "dimmer.h"

/* Public types ------------------------------------------------------------*/
typedef enum {

	SETTINGS_OPTION_1,
	SETTINGS_OPTION_2,
	SETTINGS_OPTION_3,

}ui_settings_t;

/* Public functions prototypes ---------------------------------------------*/
bool_t ui_init(dimmer_t * sys);
void ui_update(dimmer_t * sys);
bool_t ui_menu_key(void);
ui_settings_t ui_menu(void);
void ui_print_start(void);
void ui_print_error(uint8_t * pstring);

#endif /* UI_INC_UI_H_ */
