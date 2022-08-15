#ifndef SETTINGSMENUS_H
#define	SETTINGSMENUS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "navMenu.h"
#include "OLED.h"
#include "tempMonitor.h"
    
// STANDBY
void settingMenus_standbySetup(void);
void settingMenus_standbyUpdate(int16_t moves);

// TEMPERATURE
void settingMenus_temperatureSetup(void);
void settingMenus_temperatureUpdate(int16_t moves);

// temp setters and getters
void settingMenus_setTargetTemp(int8_t temp);
int8_t settingMenus_getTargetTemp(void);
void settingMenus_setTargetTemp(int8_t temp);
int8_t settingMenus_getTargetTemp(void);
void settingMenus_setMinTemp(int8_t temp);
int8_t settingMenus_getMinTemp(void);
void settingMenus_setMaxTemp(int8_t temp);
int8_t settingMenus_getMaxTemp(void);

// LIMIT CURRENT
void settingMenus_currentSetup(void);
void settingMenus_currentUpdate(int16_t moves);
void settingMenus_setCurrentLimit(float limit);
float settingMenus_getCurrentLimit(void);
void settingMenus_setMaxCurrentLimit(float limit);
float settingMenus_getMaxCurrentLimit(void);

// CHANGE UNITS
void settingMenus_changeUnitsSetup(void);
void settingMenus_changeUnitsUpdate(int16_t moves);
bool settingMenus_getIsCelsius(void);
void settingMenus_setIsCelsius(bool celsius);

// ABOUT
void settingMenus_aboutSetup(void);
void settingMenus_aboutUpdate(int16_t moves);

// START
void settingMenus_startSetup(void);
void settingMenus_startUpdate(int16_t moves);

// DEMO MODE
void settingMenus_demoModeToggleSetup(void);
void settingMenus_demoModeToggleUpdate(int16_t moves);

#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGSMENUS_H */

