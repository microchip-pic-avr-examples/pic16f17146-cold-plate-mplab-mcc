#ifndef UI_H
#define	UI_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum {STANDBY, MENU, RUNNING, ERROR, START, SET_TEMPERATURE, CHANGE_UNITS, LIMIT_CURRENT, ABOUT, DEMO_MODE_TOGGLE} UI_STATE;

#include "stdbool.h"
#include "mcc_generated_files/system/system.h"
#include <xc.h>
#include "settingMenus.h"
#include "encoderControl.h"
#include "navMenu.h"
#include "runningMenus.h"
    
UI_STATE UI_getState(void);
void UI_setState(UI_STATE new_state);
UI_STATE UI_getLastState(void);
void UI_setup(void);
void UI_handleStateInput(UI_STATE exit_state, void (*ui_update)(int16_t));

    
#ifdef	__cplusplus
}
#endif

#endif	/* UI_H */

