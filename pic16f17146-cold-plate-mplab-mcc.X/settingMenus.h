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


// CHANGE UNITS
void settingMenus_changeUnitsSetup(void);
void settingMenus_changeUnitsUpdate(int16_t moves);

char settingMenus_getTempUnit(void);
void settingMenus_setTempUnit(char unit);

// SHOW ICONS

void settingMenus_showIconsSetup(void);
void settingMenus_showIconsUpdate(int16_t moves);
bool settingMenus_getShowIcons(void);
void settingMenus_setShowIcons(bool showIcons);

// HYSTERESIS
void settingMenus_hysteresisSetup(void);
void settingMenus_hysteresisUpdate(int16_t moves);

// HYSTERESIS UNDER
void settingMenus_hysteresisOverSetup(void);
void settingMenus_hysteresisOverUpdate(int16_t moves);

int8_t settingMenus_getHysterOver(void);
void settingMenus_setHysterOver(int8_t newHysterOver);
int8_t settingMenus_getHysterUnder(void);
void settingMenus_setHysterUnder(int8_t newHysterUnder);



// ABOUT
void settingMenus_aboutSetup(void);
void settingMenus_aboutUpdate(int16_t moves);

// DEMO MODE
void settingMenus_demoModeToggleSetup(void);
void settingMenus_demoModeToggleUpdate(int16_t moves);

bool settingMenus_getDemoMode(void);
void settingMenus_setDemoMode(bool mode);

void settingMenus_populateSettings(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGSMENUS_H */

