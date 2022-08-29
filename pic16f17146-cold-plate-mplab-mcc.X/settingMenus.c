#include <math.h>

#include "settingMenus.h"
#include "config.h"

// STANDBY OLED FUNTIONS

// set static elements on the STANDBY scene
void settingMenus_standbySetup(void){
    OLED_clear();

    OLED_command(line_address[0]); // define DDRAM address to update RAM for display line #1
    OLED_writeString("   The Cold Plate");

    OLED_command(line_address[2]);
    OLED_writeString("  Plate Temp: ");
    
    if(settingMenus_getDemoMode()){
        OLED_command(line_address[3]);
        OLED_writeString("   Demo Mode On     ");
    }
    
    settingMenus_standbyUpdate(0);
}

// update dynamic elements on the STANDBY scene
void settingMenus_standbyUpdate(int16_t moves){
    char temp_buff[4];
    OLED_command(line_address[2] + 14);
    sprintf(temp_buff, "%d", tempMonitor_getLastColdTemp());
    OLED_writeString(temp_buff);
    OLED_data(0b00000000); // degrees symbol
    OLED_writeString("C ");
    
}


// SET TEMPERATURE FUNCTIONS
static int8_t target_temp = 0; // set function to read EEPROM


// set static elements in the scene
void settingMenus_temperatureSetup(void){
    char disp_string[20];
    
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("Set Temperature (");
    OLED_data(0b00000000);
    OLED_writeString("C)");
    
    OLED_command(line_address[2]);
    OLED_writeString("  Min   Set   Max  ");
    
    OLED_command(line_address[3]);
    sprintf(disp_string, "  %d          %d", (bool)settings_getSetting(SETTINGS_DEMO_MODE) ? DEMO_TEMP_LIMIT_LOW : TEMP_LIMIT_LOW, TEMP_LIMIT_MAX);
    OLED_writeString(disp_string);

    OLED_command(line_address[3]+8);
    sprintf(disp_string, "%3d", target_temp);
    OLED_writeString(disp_string);
    #ifdef DEBUG_PRINT
    printf("Target temp setup: %d\r\n", target_temp);
#endif
}

// update necessary elements
void settingMenus_temperatureUpdate(int16_t moves){
    char disp_string[20];
    
    // keeps target temp within in + max temp range
    int8_t min_temp = settings_getSetting(SETTINGS_DEMO_MODE) ? DEMO_TEMP_LIMIT_LOW : TEMP_LIMIT_LOW;
    target_temp = (target_temp+moves <= min_temp) ? min_temp : (target_temp+moves >= TEMP_LIMIT_MAX) ? TEMP_LIMIT_MAX : (int8_t)(target_temp + moves);
    
    sprintf(disp_string, "%3d", target_temp);
        #ifdef DEBUG_PRINT
    printf("Target temp update: %d\r\n", target_temp);
        #endif
    OLED_command(line_address[3]+8);
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
static uint8_t current_limit = CURRENT_LIMIT_MIN*10; // actual limit is divided by 10
void settingMenus_currentSetup(void){
    current_limit = settings_getSetting(SETTINGS_CURRENT_LIMIT);
       
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString(" Set Current Limit");
    
    OLED_command(line_address[1]);
    OLED_writeString("       (Amps)");
    
    OLED_command(line_address[2]);
    OLED_writeString("  Min   Set   Max  ");
    
    char disp_string[20];
    sprintf(disp_string, "  %3.1f   %3.1f   %3.1f", (float)CURRENT_LIMIT_MIN, (float)current_limit/10.0, (float)CURRENT_LIMIT_MAX);

    OLED_command(line_address[3]);
    OLED_writeString(disp_string);
}

void settingMenus_currentUpdate(int16_t moves){
    int8_t current_adjustment = (int8_t)(moves*5); // each move is 0.1 A.
    int8_t new_limit = current_limit + current_adjustment;
    current_limit = (new_limit <= CURRENT_LIMIT_MIN*10) ? (uint8_t)CURRENT_LIMIT_MIN*10 : (new_limit >= CURRENT_LIMIT_MAX*10) ? (uint8_t)CURRENT_LIMIT_MAX*10 : (uint8_t)new_limit;
    
    char disp_string[4];

    OLED_command(line_address[3]+8);

    sprintf(disp_string, "%3.1f ", (float)current_limit/10.0);
    OLED_writeString(disp_string);
    
}

uint8_t settingMenus_getCurrentLimit(void){
    return current_limit;
}

void settingMenus_setCurrentLimit(uint8_t limit){
    current_limit = limit;
}

// CHANGE UNITS
char temp_unit = 'C';

void settingMenus_changeUnitsSetup(void){

    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("   Set units to:");
    
    OLED_command(line_address[2]);

    if(temp_unit == 'C'){
        OLED_writeString("      Celsius   ");
    } else if(temp_unit == 'F'){
        OLED_writeString("     Fahrenheit ");
    }
    
}

void settingMenus_changeUnitsUpdate(int16_t moves){
    moves = moves % 2;
    if(moves){
        temp_unit = (temp_unit == 'C') ? 'F' : 'C';
        OLED_command(line_address[2]);
        if(temp_unit == 'C'){
            OLED_writeString("      Celsius   ");
        } else if(temp_unit == 'F'){
            OLED_writeString("     Fahrenheit ");
        }
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
    
    OLED_command(line_address[0]);
    OLED_writeString("    Version 1.0");
    
    OLED_command(line_address[1]);
    OLED_writeString("   Developed By:");
    
    OLED_command(line_address[2]);
    OLED_writeString("   Robert Perkel");
    
    OLED_command(line_address[3]);
    OLED_writeString("    Josh Booth");
}

void settingMenus_aboutUpdate(int16_t moves){}


// START
void settingMenus_startSetup(void){

    
    OLED_clear();
    
    OLED_command(line_address[3]);
    OLED_writeString("   Push to start");
    
    OLED_command(line_address[0]);
    OLED_writeString("Target Temp: ");
    
    char disp_string[20];
    sprintf(disp_string, "%4d", (int8_t)settings_getSetting(SETTINGS_LAST_SET_TEMP));
    OLED_writeString(disp_string);
    
    OLED_data(0b00000000);
    OLED_writeString("C");
    
    OLED_command(line_address[1]);
    OLED_writeString("Current lim: ");
    uint8_t currLim = settings_getSetting(SETTINGS_CURRENT_LIMIT);
    uint8_t wholeNumber = 0;
    
    while (currLim >= 10)
    {
        currLim -= 10;
        wholeNumber++;
    }
    
    sprintf(disp_string, "%u.%u A", wholeNumber, currLim);
    OLED_writeString(disp_string);

}

void settingMenus_startUpdate(int16_t moves){
    if(moves < 0){ // return to menu if rotary encoder is turned
        UI_setState(MENU);
        UI_setup();
    }
}

#define PASSCODE 636
bool demo_mode = 0;

// DEMO MODE
void settingMenus_demoModeToggleSetup(void){
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("     Enter code:");
    
    OLED_command(line_address[1]);
    OLED_writeString("      0   0   0     ");
    
    OLED_command(line_address[3]);
    OLED_writeString("  Next digit in: ");
    
}

void settingMenus_demoModeToggleUpdate(int16_t moves){
    char disp_buff[20];
    static int8_t value[3] = {0,0,0};
    static uint8_t counter_seconds = 0;
    static uint8_t index = 0;
    static bool passcodeEntered = false;
    int8_t countdown_seconds = 4;
    if(!passcodeEntered){
        // adjust shown value
        value[index]=(value[index]+moves)%10; // take to 1 digit
        value[index] = (value[index] < 0) ? value[index]+10 : value[index]; // implement digit wrap-around

        if(counter_seconds >= countdown_seconds*10){
            if(index >= 2){ // value has been set
                // compare value && turn on demo mode
                OLED_command(line_address[2]);
                if(((value[0]*100)+(value[1]*10)+value[2]) == PASSCODE){
                    // toggle demo mode
                    if(settings_getSetting(SETTINGS_DEMO_MODE)){
                        OLED_writeString(" Demo Mode Disabled  ");
                        settingMenus_setDemoMode(0);
                    } else {
                        OLED_writeString(" Demo Mode Enabled  ");
                        settingMenus_setDemoMode(1);
                    }
                    passcodeEntered = true;
                    OLED_command(line_address[3]);
                    OLED_clear_line();
                    
                } else {
                    OLED_writeString(" Incorrect passcode ");
                }
                //OLED_command(line_address[3]);
                //OLED_clear_line();
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
            OLED_command(line_address[1]);
            sprintf(disp_buff, "      %d   %d   %d     ", value[0], value[1], value[2]);
            OLED_writeString(disp_buff);
        
            OLED_command(line_address[3]+17);
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
    settingMenus_setCurrentLimit(settings_getSetting(SETTINGS_CURRENT_LIMIT));
    settingMenus_setTempUnit((char)settings_getSetting(SETTINGS_TEMP_UNIT));
    settingMenus_setDemoMode((bool)settings_getSetting(SETTINGS_DEMO_MODE));
}