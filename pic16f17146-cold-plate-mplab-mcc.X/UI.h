#ifndef UI_H
#define	UI_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum {STANDBY, MENU, RUNNING, ERROR, SET_TEMPERATURE, CHANGE_UNITS, SHOW_ICONS, ABOUT, DEMO_MODE_TOGGLE} UI_STATE;

#include "stdbool.h"
#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "settingMenus.h"
#include "encoderControl.h"
#include "navMenu.h"
#include "runningMenus.h"
#include "peltierControl.h"
    
UI_STATE UI_getState(void);
void UI_setState(UI_STATE new_state);
bool UI_isRunning(void);
void UI_setup(void);
void UI_update(void);
void UI_handleStateInput(UI_STATE exit_state, void (*ui_update)(int16_t));
void UI_updateEEPROM(void);
void UI_refresh(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* UI_H */

