#include "UI.h"


static UI_STATE UI_state = STANDBY;
static UI_STATE UI_last_state = STANDBY;

UI_STATE UI_getState(void){
    return UI_state;
}

UI_STATE UI_getLastState(void){
    return UI_last_state;
}

void UI_setState(UI_STATE new_state){
    UI_last_state = UI_state;
    UI_state = new_state;
}

// fill OLED with new static state data when the state is switched
void UI_setup(void){
    switch(UI_state){
        case STANDBY:
            settingMenus_standbySetup();
            break;
        case MENU:
            navMenu_setup();
            break;
        case RUNNING:
            runningMenus_runningSetup();
            break;
        case ERROR:
            break;
        case SET_TEMPERATURE:
            settingMenus_temperatureSetup();
            break;
        case CHANGE_UNITS:
            settingMenus_changeUnitsSetup();
            break;
        case LIMIT_CURRENT:
            settingMenus_currentSetup();
            break;
        case ABOUT:
            settingMenus_aboutSetup();
            break;
        case DEMO_MODE_TOGGLE:
            settingMenus_demoModeToggleSetup();
            break;
        case START:
            settingMenus_startSetup();
            break;
    }
}

// when in a UI state, this handles reading encoder input, updating only the
// needed info on the OLED, and moving to the next UI state
void UI_handleStateInput(UI_STATE exit_state, void (*ui_update)(int16_t)){
    static bool pressed = false; // Value to keep track of button state, avoids blocking
    if(!BUTTON_GetValue()){ // button press means move to different UI state
        pressed = true;
    } else if(BUTTON_GetValue() && pressed == true){ // wait for button to be released
        UI_updateEEPROM();
        UI_setState(exit_state); // set state
        UI_setup(); // populate OLED to match state
        pressed = false;
    } else {
        (*ui_update)(encoderControl_getMoves());
    }
    

}

//Check if current value is different than what is in EEPROM
void UI_updateEEPROM(void){
    if(settings_getValue(SETTINGS_LAST_TEMP) != settingMenus_getTargetTemp()){
        setting_writeValue(SETTINGS_LAST_TEMP, settingMenus_getTargetTemp());
    }
    if(settings_getValue(SETTINGS_CURRENT_LIMIT) != settingMenus_getCurrentLimit()){
        setting_writeValue(SETTINGS_CURRENT_LIMIT, settingMenus_getCurrentLimit());
    }
    if(settings_getValue(SETTINGS_TEMP_UNIT) != settingMenus_getTempUnit()){
        setting_writeValue(SETTINGS_TEMP_UNIT, settingMenus_getTempUnit());
    }
    if(settings_getValue(SETTINGS_DEMO_MODE) != settingMenus_getDemoMode()){
        setting_writeValue(SETTINGS_DEMO_MODE, settingMenus_getDemoMode());
    }
}