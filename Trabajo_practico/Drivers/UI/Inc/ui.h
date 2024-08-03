/*
 * ui.h
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#ifndef UI_INC_UI_H_
#define UI_INC_UI_H_

//#include "port.h"

void uiInit();
void uiClear();
void uiUpdate(); //receive Sensor read and pwm
void uiConfigMenu();
void uiConfigSave();

#endif /* UI_INC_UI_H_ */
