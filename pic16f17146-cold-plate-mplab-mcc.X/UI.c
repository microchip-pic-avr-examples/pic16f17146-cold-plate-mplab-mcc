#include "UI.h"

//Current UI State
static UI_STATE UI_state = STANDBY;
//Signals the UI has entered a new state
static bool UI_new_state = true;
static bool UI_is_running = false;

UI_STATE UI_getState(void){
    return UI_state;
}

//UI State setter & flags a new state
void UI_setState(UI_STATE new_state){
    UI_state = new_state;
    UI_new_state = true;
    
    if(UI_state == STANDBY){
        UI_is_running = false;
        navMenu_changeStartOptions(true);
    } else if(UI_state == RUNNING){
        UI_is_running = true;
        navMenu_changeStartOptions(false);
    }
}

bool UI_isRunning(void){
    return UI_is_running;
}

//Updates the scene elements & sets a new scene if needed
void UI_refresh(void){
    if(UI_new_state){
        UI_setup();
        UI_new_state = false;
    }
    UI_update();
}

//Fill OLED with new static state data when the state is switched
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
        case ABOUT:
            settingMenus_aboutSetup();
            break;
        case DEMO_MODE_TOGGLE:
            settingMenus_demoModeToggleSetup();
            break;
        case START:
            settingMenus_startSetup();
            break;
        case SHOW_ADVANCED:
            settingMenus_showAdvancedSetup();
            break;
    }
}


//Update only the needed elements in a scene
void UI_update(void){
    UI_STATE returnState = STANDBY;
    
    switch(UI_state){
        case STANDBY:
        case RUNNING:
        case SET_TEMPERATURE:
        case CHANGE_UNITS:
        case ABOUT:
        case DEMO_MODE_TOGGLE:
        case SHOW_ADVANCED:
            returnState = MENU;
            break;
        case START:
            returnState = RUNNING;
            break;
        case MENU:
            returnState = navMenu_getSelected();
            break;
        case ERROR: // NO IMPLEMENTATION YET
            break;
    }
    
    static bool pressed = false; // Value to keep track of button state, avoids blocking
    if(!BUTTON_GetValue()){ // button press means move to different UI state
        pressed = true;
    } else if(BUTTON_GetValue() && pressed == true){ // wait for button to be released
        UI_setState(returnState); // set state
        UI_updateEEPROM();
        pressed = false;
    } else {
        switch(UI_state){
            case STANDBY:
                settingMenus_standbyUpdate(encoderControl_getMoves());
                break;
            case MENU:
                navMenu_update(encoderControl_getMoves());
                break;
            case RUNNING:
                runningMenus_runningUpdate(encoderControl_getMoves());
                break;
            case ERROR:
                break;
            case SET_TEMPERATURE:
                settingMenus_temperatureUpdate(encoderControl_getMoves());
                break;
            case CHANGE_UNITS:
                settingMenus_changeUnitsUpdate(encoderControl_getMoves());
                break;
            case ABOUT:
                settingMenus_aboutUpdate(encoderControl_getMoves());
                break;
            case DEMO_MODE_TOGGLE:
                settingMenus_demoModeToggleUpdate(encoderControl_getMoves());
                break;
            case START:
                settingMenus_startUpdate(encoderControl_getMoves());
                break;
            case SHOW_ADVANCED:
                settingMenus_showAdvancedUpdate(encoderControl_getMoves());
                break;
        }
    }
}

//Check if current value is different than what is in EEPROM
void UI_updateEEPROM(void){
    bool changed = false;
    if(settings_getSetting(SETTINGS_LAST_SET_TEMP) != (uint8_t)settingMenus_getTargetTemp())
    {
        settings_writeValue(SETTINGS_LAST_SET_TEMP, (uint8_t)settingMenus_getTargetTemp());
        changed = true;
    }
    
    if(settings_getSetting(SETTINGS_TEMP_UNIT) != settingMenus_getTempUnit())
    {
        settings_writeValue(SETTINGS_TEMP_UNIT, settingMenus_getTempUnit());
        changed = true;
    }
    
    if(settings_getSetting(SETTINGS_DEMO_MODE) != settingMenus_getDemoMode())
    {
        settings_writeValue(SETTINGS_DEMO_MODE, settingMenus_getDemoMode());
        changed = true;
    }
    
    if(changed)
    {
        settings_writeCRC();
    }
}