#include "settingMenus.h"
#include "config.h"

// SET TEMPERATURE FUNCTIONS
static int8_t target_temp = 0; // set function to read EEPROM
static char temp_unit = 'C';

// STANDBY OLED FUNTIONS
// set static elements on the STANDBY scene
void settingMenus_standbySetup(void){
    OLED_clear();

    OLED_command(line_address[0]); // define DDRAM address to update RAM for display line #1
    OLED_writeString("The Cold Plate:");

    OLED_command(line_address[1]);
    OLED_writeString("Target temp:");
    
    if(settingMenus_getDemoMode()){
        OLED_command(line_address[3]+4);
        OLED_writeString("Demo Mode On");
    }
    
}

// update dynamic elements on the STANDBY scene
void settingMenus_standbyUpdate(int16_t moves){
    char temp_buff[4];
    OLED_command(line_address[0] + 15);
    sprintf(temp_buff, "%3d", dispTemp(tempMonitor_getLastColdTemp()));
    OLED_writeString(temp_buff);
    OLED_writeTempUnit();
    
    OLED_command(line_address[1]+11);
    sprintf(temp_buff, "%3d", dispTemp(settingMenus_getTargetTemp()));
    OLED_writeString(temp_buff);
    OLED_writeTempUnit();
}

// set static elements in the scene
void settingMenus_temperatureSetup(void){
    char disp_string[20];
    
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("Set Temperature (");
    OLED_writeTempUnit();
    OLED_writeString(")");
    
    OLED_command(line_address[2]+2);
    OLED_writeString("Min");
    OLED_command(line_address[2]+8);
    OLED_writeString("Set");
    OLED_command(line_address[2]+14);
    OLED_writeString("Max");
    
    OLED_command(line_address[3]+2);
    sprintf(disp_string, "%d", settings_getSetting(SETTINGS_DEMO_MODE) ? dispTemp(DEMO_TEMP_LIMIT_LOW) : dispTemp(TEMP_LIMIT_LOW));
    OLED_writeString(disp_string);
    
    OLED_command(line_address[3]+14);
    sprintf(disp_string, "%d", dispTemp(TEMP_LIMIT_MAX));
    OLED_writeString(disp_string);
}

// update necessary elements
void settingMenus_temperatureUpdate(int16_t moves){
    char disp_string[20];
    
    // keeps target temp within in + max temp range
    int8_t min_temp = settings_getSetting(SETTINGS_DEMO_MODE) ? DEMO_TEMP_LIMIT_LOW : TEMP_LIMIT_LOW;
    target_temp = (target_temp+moves <= min_temp) ? min_temp : (target_temp+moves >= TEMP_LIMIT_MAX) ? TEMP_LIMIT_MAX : (int8_t)(target_temp + moves);
    
    sprintf(disp_string, "%3d", dispTemp(target_temp));
    OLED_command(line_address[3]+7);
    OLED_writeString(disp_string);
}

// getter for target temperature
int8_t settingMenus_getTargetTemp(void){
    return target_temp;
}
void settingMenus_setTargetTemp(int8_t temp){
    target_temp = temp;
}

// CHANGE UNITS

void settingMenus_changeUnitsSetup(void){
    OLED_clear();
    
    OLED_command(line_address[0]+3);
    OLED_writeString("Set units to:");    

}

void settingMenus_changeUnitsUpdate(int16_t moves){
    moves = moves % 2;
    if(moves){
        temp_unit = (temp_unit == 'C') ? 'F' : 'C';
    }
    
    OLED_command(line_address[2]+5);
    if(temp_unit == 'C'){
        OLED_writeString(" Celsius  ");
    } else if(temp_unit == 'F'){
        OLED_writeString("Fahrenheit");
    }
}

char settingMenus_getTempUnit(void){
    return temp_unit;
}

void settingMenus_setTempUnit(char unit){
    temp_unit = unit;
}


// ABOUT
void settingMenus_aboutSetup(void){
    OLED_clear();
    
    OLED_command(line_address[0]+4);
    OLED_writeString("Version 1.0");
    
    OLED_command(line_address[1]+3);
    OLED_writeString("Developed By:");
    
    OLED_command(line_address[2]+3);
    OLED_writeString("Robert Perkel");
    
    OLED_command(line_address[3]+4);
    OLED_writeString("Josh Booth");
}

void settingMenus_aboutUpdate(int16_t moves){
    if(moves < 0){ // return to menu if rotary encoder is turned
        UI_setState(MENU);
        UI_setup();
    }
}


// START
void settingMenus_startSetup(void){ 
    OLED_clear();
    
    OLED_command(line_address[3]+3);
    OLED_writeString("Push to start");
    
    OLED_command(line_address[0]);
    OLED_writeString("Target Temp: ");
    
    char disp_string[20];
    sprintf(disp_string, "%4d", dispTemp(target_temp));
    OLED_writeString(disp_string);
    
    OLED_writeTempUnit();

}

void settingMenus_startUpdate(int16_t moves){
    if(moves < 0){ // return to menu if rotary encoder is turned
        UI_setState(MENU);
        UI_setup();
    }
}

#define PASSCODE 636
bool demo_mode = 0;
static int8_t value[3] = {0,0,0};
static uint8_t counter_seconds = 0;
static uint8_t index = 0;
static bool passcodeEntered = false;

// DEMO MODE
void settingMenus_demoModeToggleSetup(void){

    value[0] = 0;
    value[1] = 0;
    value[2] = 0;
    counter_seconds = 0;
    index = 0;
    passcodeEntered = false;
    
    OLED_clear();
    
    OLED_command(line_address[0]+5);
    OLED_writeString("Enter code:");
    
    OLED_command(line_address[1]+7);
    OLED_writeString("0");
    
    OLED_command(line_address[1]+10);
    OLED_writeString("0");
    
    OLED_command(line_address[1]+14);
    OLED_writeString("0");
    
    OLED_command(line_address[3]+1);
    if(settings_getSetting(SETTINGS_DEMO_MODE)){
        OLED_writeString("Demo Mode Enabled");
    } else{
        OLED_writeString("Demo Mode Disabled");
    }
    
    OLED_command(line_address[2]+2);
    OLED_writeString("Next digit in:");
    
}

void settingMenus_demoModeToggleUpdate(int16_t moves){
    char disp_buff[20];
    int8_t countdown_seconds = 4;
    if(!passcodeEntered){
        // adjust shown value
        value[index]=(value[index]+moves)%10; // take to 1 digit
        value[index] = (value[index] < 0) ? value[index]+10 : value[index]; // implement digit wrap-around

        if(counter_seconds >= countdown_seconds*10){
            if(index >= 2){ // value has been set
                // compare value && turn on demo mode
                OLED_command(line_address[3]+1);
                if(((value[0]*100)+(value[1]*10)+value[2]) == PASSCODE){
                    // toggle demo mode
                    if(settings_getSetting(SETTINGS_DEMO_MODE)){
                        OLED_writeString("Demo Mode Disabled");
                        settingMenus_setDemoMode(false);
                    } else {
                        OLED_writeString("Demo Mode Enabled ");
                        settingMenus_setDemoMode(true);
                    }
                    passcodeEntered = true;
                    OLED_command(line_address[2]);
                    OLED_clear_line();
                    
                } else {
                    OLED_writeString("Incorrect passcode ");
                }

                value[0] = 0;
                value[1] = 0;
                value[2] = 0;
                index = 0;
            } else {
                index++;
            }
            counter_seconds = 0;
        }

        // update time
        if(!passcodeEntered){
            
           // adjust time countdown
            OLED_command(line_address[1]+6);
            sprintf(disp_buff, "%d   %d   %d", value[0], value[1], value[2]);
            OLED_writeString(disp_buff);
        
            OLED_command(line_address[2]+17);
            sprintf(disp_buff, "%d", countdown_seconds-((int)counter_seconds/10));
            OLED_writeString(disp_buff);
        }
        counter_seconds++;
    } 
}

bool settingMenus_getDemoMode(void){
    return demo_mode;
}

void settingMenus_setDemoMode(bool mode){
    demo_mode = mode;
}

void settingMenus_populateSettings(void){
    settingMenus_setTargetTemp((int8_t)settings_getSetting(SETTINGS_LAST_SET_TEMP));
    settingMenus_setTempUnit((char)settings_getSetting(SETTINGS_TEMP_UNIT));
    settingMenus_setDemoMode((bool)settings_getSetting(SETTINGS_DEMO_MODE));
}
