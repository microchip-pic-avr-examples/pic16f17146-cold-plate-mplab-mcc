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
void UI_handleStateInput(UI_STATE exit_state, bool getEncoder, void (*ui_update)(int16_t)){
    if(!BUTTON_GetValue()){ // button press means move to different UI state
        while(!BUTTON_GetValue()); // wait for button to be released
        UI_setState(exit_state); // set state
        UI_setup(); // populate OLED
    } else if (getEncoder){
        (*ui_update)(encoderControl_getMoves());
    }

}