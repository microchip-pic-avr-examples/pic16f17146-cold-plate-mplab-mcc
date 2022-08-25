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
#include "settings.h"
#include "config.h"
    
// STANDBY
void settingMenus_standbySetup(void);
void settingMenus_standbyUpdate(int16_t moves);

// TEMPERATURE
void settingMenus_temperatureSetup(void);
void settingMenus_temperatureUpdate(int16_t moves);

// temp getters
int8_t settingMenus_getTargetTemp(void);

// LIMIT CURRENT
void settingMenus_currentSetup(void);
void settingMenus_currentUpdate(int16_t moves);
// current limit getter
float settingMenus_getCurrentLimit(void);

// CHANGE UNITS
void settingMenus_changeUnitsSetup(void);
void settingMenus_changeUnitsUpdate(int16_t moves);
uint8_t settingMenus_getTempUnit(void);

// ABOUT
void settingMenus_aboutSetup(void);
void settingMenus_aboutUpdate(int16_t moves);

// START
void settingMenus_startSetup(void);
void settingMenus_startUpdate(int16_t moves);

// DEMO MODE
void settingMenus_demoModeToggleSetup(void);
void settingMenus_demoModeToggleUpdate(int16_t moves);
uint8_t settingMenus_getDemoMode(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGSMENUS_H */

