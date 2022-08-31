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
#include "utility.h"
    
// STANDBY
void settingMenus_standbySetup(void);
void settingMenus_standbyUpdate(int16_t moves);

// TEMPERATURE
void settingMenus_temperatureSetup(void);
void settingMenus_temperatureUpdate(int16_t moves);

// temp getters
int8_t settingMenus_getTargetTemp(void);
void settingMenus_setTargetTemp(int8_t temp);

// LIMIT CURRENT
void settingMenus_currentSetup(void);
void settingMenus_currentUpdate(int16_t moves);
// current limit getter
uint8_t settingMenus_getCurrentLimit(void);
void settingMenus_setCurrentLimit(uint8_t limit);

// CHANGE UNITS
void settingMenus_changeUnitsSetup(void);
void settingMenus_changeUnitsUpdate(int16_t moves);

char settingMenus_getTempUnit(void);
void settingMenus_setTempUnit(char unit);

// ABOUT
void settingMenus_aboutSetup(void);
void settingMenus_aboutUpdate(int16_t moves);

// START
void settingMenus_startSetup(void);
void settingMenus_startUpdate(int16_t moves);

// DEMO MODE
void settingMenus_demoModeToggleSetup(void);
void settingMenus_demoModeToggleUpdate(int16_t moves);

bool settingMenus_getDemoMode(void);
void settingMenus_setDemoMode(bool mode);

void settingMenus_populateSettings(void);

void settingMenus_showAdvancedSetup(void);
void settingMenus_showAdvancedUpdate(int16_t moves);

bool settingMenus_getShowAdvanced(void);
void settingMenus_setShowAdvanced(bool showAdvanced);


#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGSMENUS_H */

