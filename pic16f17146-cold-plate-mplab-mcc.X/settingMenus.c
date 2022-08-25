#include "settingMenus.h"

// STANDBY OLED FUNTIONS

// set static elements on the STANDBY scene
void settingMenus_standbySetup(void){
    OLED_clear();

    OLED_command(line_address[0]); // define DDRAM address to update RAM for display line #1
    OLED_writeString("   The Cold Plate");

    OLED_command(line_address[2]);
    OLED_writeString("  Plate Temp: ");
    
    if(settings_getValue(SETTINGS_DEMO_MODE)){
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
    sprintf(disp_string, "  %d          %d", settings_getValue(SETTINGS_DEMO_MODE) ? DEMO_TEMP_LIMIT_LOW : TEMP_LIMIT_LOW, TEMP_LIMIT_MAX);
    OLED_writeString(disp_string);
    
    OLED_command(line_address[3]+8);
    target_temp = settings_getValue(SETTINGS_LAST_TEMP); // read EEPROM to get this value
    sprintf(disp_string, "%3d", target_temp);
    OLED_writeString(disp_string);
}

// update necessary elements
void settingMenus_temperatureUpdate(int16_t moves){
    char disp_string[20];
    
    // keeps target temp within in + max temp range
    int8_t min_temp = settings_getValue(SETTINGS_DEMO_MODE) ? DEMO_TEMP_LIMIT_LOW : TEMP_LIMIT_LOW;
    target_temp = (target_temp+moves <= min_temp) ? min_temp : (target_temp+moves >= TEMP_LIMIT_MAX) ? TEMP_LIMIT_MAX : (int8_t)(target_temp + moves);
    
    sprintf(disp_string, "%3d", target_temp);
    
    OLED_command(line_address[3]+8);
    OLED_writeString(disp_string);
}

// getter for target temperature
int8_t settingMenus_getTargetTemp(void){
    return target_temp;
}


// CHANGE UNITS
static float current_limit = 0;
void settingMenus_currentSetup(void){
    current_limit = settings_getValue(SETTINGS_CURRENT_LIMIT);
       
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString(" Set Current Limit");
    
    OLED_command(line_address[1]);
    OLED_writeString("       (Amps)");
    
    OLED_command(line_address[2]);
    OLED_writeString("    Set      Max    ");
    
    char disp_string[20];
    sprintf(disp_string, "    %3.1f      %3.1f", current_limit, CURRENT_LIMIT_MAX);

    OLED_command(line_address[3]);
    OLED_writeString(disp_string);
}

void settingMenus_currentUpdate(int16_t moves){
    float current_adjustment = (float)(moves*0.5); // each move is 0.1 A.
    float new_limit = current_limit + current_adjustment;
    current_limit = (new_limit <= 0) ? 0 : (new_limit >= CURRENT_LIMIT_MAX) ? CURRENT_LIMIT_MAX : new_limit;
    
    char disp_string[4];
    sprintf(disp_string, "%3.1f ", current_limit);
    
    OLED_command(line_address[3]+4);
    OLED_writeString(disp_string);
    
}

float settingMenus_getCurrentLimit(void){
    return current_limit;
}

// CHANGE UNITS
uint8_t temp_unit = CELSIUS;
void settingMenus_changeUnitsSetup(void){
    temp_unit = settings_getValue(SETTINGS_TEMP_UNIT);
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("   Set units to:");
    
    OLED_command(line_address[2]);

    if(temp_unit == CELSIUS){
        OLED_writeString("      Celsius   ");
    } else if(temp_unit == FAHRENHEIT){
        OLED_writeString("     Fahrenheit ");
    }
    
}

void settingMenus_changeUnitsUpdate(int16_t moves){
    moves = moves % 2;
    if(moves){
        temp_unit = (temp_unit == CELSIUS) ? FAHRENHEIT : CELSIUS;
        OLED_command(line_address[2]);
        if(temp_unit == CELSIUS){
            OLED_writeString("      Celsius   ");
        } else if(temp_unit == FAHRENHEIT){
            OLED_writeString("     Fahrenheit ");
        }
    }
}

uint8_t settingMenus_getTempUnit(void){
    return temp_unit;
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
    sprintf(disp_string, "%4d", settings_getValue(SETTINGS_LAST_TEMP));
    OLED_writeString(disp_string);
    
    OLED_data(0b00000000);
    OLED_writeString("C");
    
    OLED_command(line_address[1]);
    OLED_writeString("Current lim: ");
    sprintf(disp_string, "%4.1f A", settings_getValue(SETTINGS_LAST_TEMP));
    OLED_writeString(disp_string);

}

void settingMenus_startUpdate(int16_t moves){
    if(moves < 0){ // return to menu if rotary encoder is turned
        UI_setState(MENU);
        UI_setup();
    }
}

#define PASSCODE 636
uint8_t demo_mode = 0;

// DEMO MODE
void settingMenus_demoModeToggleSetup(void){
    demo_mode = settings_getValue(SETTINGS_DEMO_MODE);
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("     Enter code:");
    
    OLED_command(line_address[1]);
    OLED_writeString("      0   0   0     ");
    
    OLED_command(line_address[3]);
    OLED_writeString("  Next digit in: 5  ");
    
}

void settingMenus_demoModeToggleUpdate(int16_t moves){
    char disp_buff[20];
    static int8_t value[3] = {0,0,0};
    static uint8_t counter5s = 0;
    static uint8_t index = 0;
    static bool passcodeEntered = false;
    if(!passcodeEntered){
        // adjust shown value
        value[index]=(value[index]+moves)%10; // take to 1 digit
        value[index] = (value[index] < 0) ? value[index]+10 : value[index]; // implement digit wrap-around

        if(counter5s >= 50){
            if(index >= 2){ // value has been set
                // compare value && turn on demo mode
                OLED_command(line_address[3]);
                if(((value[0]*100)+(value[1]*10)+value[2]) == PASSCODE){
                    // toggle demo mode
                    if(settings_getValue(SETTINGS_DEMO_MODE)){
                        OLED_writeString(" Demo Mode Disabled  ");
                        demo_mode = 0;
                    } else {
                        OLED_writeString(" Demo Mode Enabled  ");
                        demo_mode = 1;
                    }
                    // TODO: enable demo mode
                    passcodeEntered = true;
                    
                } else {
                    OLED_writeString(" Incorrect passcode ");
                }
                //OLED_command(line_address[3]);
                //OLED_clear_line();
                value[0] = 0;
                value[1] = 0;
                value[2] = 0;
                index = 0;
                passcodeEntered = true;
            } else {
                index++;
            }
            counter5s = 0;
        }


        // update time
        if(!passcodeEntered){
            
           // adjust time countdown
            OLED_command(line_address[1]);
            sprintf(disp_buff, "      %d   %d   %d     ", value[0], value[1], value[2]);
            OLED_writeString(disp_buff);
        
            OLED_command(line_address[3]+17);
            sprintf(disp_buff, "%d", 5-((int)counter5s/10));
            OLED_writeString(disp_buff);
        }

        counter5s++;
    } 
}

uint8_t settingMenus_getDemoMode(void){
    return demo_mode;
}