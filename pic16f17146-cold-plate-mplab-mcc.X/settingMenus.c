#include "settingMenus.h"

// STANDBY OLED FUNTIONS

// set static elements on the STANDBY scene
void settingMenus_standbySetup(void){
    OLED_clear();

    OLED_command(line_address[0]); // define DDRAM address to update RAM for display line #1
    OLED_writeString("   The Cold Plate");

    OLED_command(line_address[2]);
    OLED_writeString("  Plate Temp: ");
}

// update dynamic elements on the STANDBY scene
void settingMenus_standbyUpdate(void){
    char temp_buff[4];
    OLED_command(line_address[2] + 14);
    sprintf(temp_buff, "%d", tempMonitor_getLastColdTemp());
    OLED_writeString(temp_buff);
    OLED_data(0b00000000); // degrees symbol
    OLED_writeString("C");
    
}


// SET TEMPERATURE FUNCTIONS
static int8_t target_temp = 0; // set function to read EEPROM
static int8_t min_temp, max_temp = 0;

void settingMenus_temperatureSetup(void){
    target_temp = tempMonitor_getLastColdTemp(); // read EEPROM to get this value
    min_temp = settingMenus_getMinTemp(); // TODO replace with function to get min allowed temp
    max_temp = settingMenus_getMaxTemp();
    
    char disp_string[20];
    sprintf(disp_string, "  %d          %d", min_temp, max_temp);
    
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("Set Temperature (");
    OLED_data(0b00000000);
    OLED_writeString("C)");
    
    OLED_command(line_address[2]);
    OLED_writeString("  Min   Set   Max  ");
    
    OLED_command(line_address[3]);
    OLED_writeString(disp_string);
    
    OLED_command(line_address[3]+8);
    sprintf(disp_string, "%3d", target_temp);
    OLED_writeString(disp_string);
}

void settingMenus_temperatureUpdate(int16_t moves){
    // keeps target temp within in + max temp range
    target_temp = (target_temp+moves <= settingMenus_getMinTemp()) ? settingMenus_getMinTemp() : (target_temp+moves >= settingMenus_getMaxTemp()) ? settingMenus_getMaxTemp() : target_temp+moves;
    settingMenus_setTargetTemp(target_temp); // save new target temperature
    
    char disp_string[20];
    sprintf(disp_string, "%3d", target_temp);
    
    OLED_command(line_address[3]+8);
    OLED_writeString(disp_string);
}

void settingMenus_setTargetTemp(int8_t temp){
    target_temp = temp;
}

int8_t settingMenus_getTargetTemp(void){
    return target_temp;
}

void settingMenus_setMinTemp(int8_t temp){
    min_temp = temp;
}

int8_t settingMenus_getMinTemp(void){
    return -5;
}

void settingMenus_setMaxTemp(int8_t temp){
    max_temp = temp;
}

int8_t settingMenus_getMaxTemp(void){
    return 100;
}

// CHANGE UNITS
static float current_limit = 5;
static float max_current_limit = 0;

void settingMenus_currentSetup(void){
    current_limit = settingMenus_getCurrentLimit();
    max_current_limit = settingMenus_getMaxCurrentLimit(); // TODO: replace with EEPROM function
       
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString(" Set Current Limit");
    
    OLED_command(line_address[1]);
    OLED_writeString("       (Amps)");
    
    OLED_command(line_address[2]);
    OLED_writeString("    Set      Max    ");
    
    char disp_string[20];
    sprintf(disp_string, "    %3.1f      %3.1f", current_limit, max_current_limit);
    
    OLED_command(line_address[3]);
    OLED_writeString(disp_string);
}

void settingMenus_currentUpdate(int16_t moves){
    float current_adjustment = moves*0.5; // each move is 0.1 A.
    float new_limit = settingMenus_getCurrentLimit() + current_adjustment;
    new_limit = (new_limit <= 0) ? 0 : (new_limit >= settingMenus_getMaxCurrentLimit()) ? settingMenus_getMaxCurrentLimit() : new_limit;
    settingMenus_setCurrentLimit(new_limit);
    
    char disp_string[4];
    sprintf(disp_string, "%3.1f ", new_limit);
    
    OLED_command(line_address[3]+4);
    OLED_writeString(disp_string);
    
}

void settingMenus_setCurrentLimit(float limit){
    current_limit = limit;
}

float settingMenus_getCurrentLimit(void){
    return current_limit;
}

void settingMenus_setMaxCurrentLimit(float limit){
    max_current_limit = limit;
}

float settingMenus_getMaxCurrentLimit(void){
    return 10;
}

// CHANGE UNITS
bool is_celsius = true;
void settingMenus_changeUnitsSetup(void){
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("   Set units to:");
    
    OLED_command(line_address[2]);
    settingMenus_setIsCelsius(settingMenus_getIsCelsius());
    if(is_celsius){
        OLED_writeString("      Celsius   ");
    } else{
        OLED_writeString("     Fahrenheit ");
    }
    
}

void settingMenus_changeUnitsUpdate(int16_t moves){
    moves = moves % 2;
    if(moves){
        settingMenus_setIsCelsius(!settingMenus_getIsCelsius());
        OLED_command(line_address[2]);
        if(is_celsius){
            OLED_writeString("      Celsius   ");
        } else{
            OLED_writeString("     Fahrenheit ");
        }
    }
}

bool settingMenus_getIsCelsius(void){
    return is_celsius;
}

void settingMenus_setIsCelsius(bool celsius){
    is_celsius = celsius;
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

void settingMenus_aboutUpdate(void){}


// START
void settingMenus_startSetup(void){
    // get temp
    
    // get current
    
    OLED_clear();
    
    OLED_command(line_address[3]);
    OLED_writeString("   Push to start");
    
    OLED_command(line_address[0]);
    OLED_writeString("Target Temp: ");
    
    char disp_string[20];
    sprintf(disp_string, "%4d", settingMenus_getTargetTemp());
    OLED_writeString(disp_string);
    
    OLED_data(0b00000000);
    OLED_writeString("C");
    
    OLED_command(line_address[1]);
    OLED_writeString("Current lim: ");
    sprintf(disp_string, "%4.1f A", settingMenus_getCurrentLimit());
    OLED_writeString(disp_string);

}

void settingMenus_startUpdate(int16_t moves){
    if(moves < 0){
        UI_setState(MENU);
        UI_setup();
    }
}

#define PASSCODE 636
bool passcodeEntered = false;

// DEMO MODE
void settingMenus_demoModeToggleSetup(void){
    
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("     Enter code:");
    
    OLED_command(line_address[1]);
    OLED_writeString("      0   0   0     ");
    
    OLED_command(line_address[3]);
    OLED_writeString("  Next digit in: 5  ");
    
    passcodeEntered = false;
}

void settingMenus_demoModeToggleUpdate(int16_t moves){
    char disp_buff[20];
    static int8_t value[3] = {0,0,0};
    static uint8_t counter5s = 0;
    static uint8_t index = 0;
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
                    // TODO: check if DEMO mode is enabled, and enable or disable it

                    OLED_writeString(" Demo Mode Enabled  ");
                    // TODO: enable demo mode
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