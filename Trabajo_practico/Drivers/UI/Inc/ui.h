/*
 * ui.h
 *
 *  Created on: Aug 3, 2024
 *      Author: laura
 */

#ifndef UI_INC_UI_H_
#define UI_INC_UI_H_

#include "common.h"
#include "dimmer_system.h"

bool_t uiInit();
void uiClear();
void uiUpdate(dimmerSysConfig_t * sys); //receive Sensor read and pwm
void uiConfigMenu();
void uiConfigSave();
void uiPrintConfig(dimmerSysConfig_t * sys);

#endif /* UI_INC_UI_H_ */
