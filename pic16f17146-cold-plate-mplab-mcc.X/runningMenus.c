#include "runningMenus.h"
#include "peltierControl.h"

void runningMenus_runningSetup(void){     
    OLED_clear();
    
    OLED_command(line_address[0]+3);
    OLED_writeString("Plate:");
    
    OLED_command(line_address[1]);
    OLED_writeString("Heatsink:");

    OLED_command(line_address[2]+5);
    OLED_writeString("MCU:");
    
    OLED_command(line_address[3]);
    OLED_writeString("Fan RPMs:");
    
}

void runningMenus_runningUpdate(int16_t moves){
    char disp_buff[20];

    // update current Plate Temperature
    OLED_command(line_address[0]+9);
    sprintf(disp_buff, "%3d/%3d", dispTemp(tempMonitor_getLastColdTemp()), dispTemp(settingMenus_getTargetTemp()));
    OLED_writeString(disp_buff);
    OLED_writeTempUnit();

    OLED_command(line_address[1]+9);
    sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastHotTemp()));
    OLED_writeString(disp_buff);
    OLED_writeTempUnit();

    // MCU Temp
    OLED_command(line_address[2]+9);
    sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastIntTemp()));
    OLED_writeString(disp_buff);
    OLED_writeTempUnit();
            
    OLED_command(line_address[3]+10);
    sprintf(disp_buff, "%4d, %4d", fanControl_getFan1RPM(), fanControl_getFan2RPM());
    OLED_writeString(disp_buff);
}


void runningMenus_errorSetup(void){
    OLED_clear();
    OLED_command(line_address[0]+2);
    OLED_writeString("Not Cool - Error");
    
    OLED_command(line_address[3]+3);
    OLED_writeString("Push to clear");
}

void runningMenus_errorUpdate(int16_t moves){
    OLED_command(line_address[2]);
    switch(peltierControl_getError()){
        case PELTIER_FAN1_ERROR:
            OLED_writeSpaces(1);
            OLED_writeString("Fan 1 Not Running");
            break;
        case PELTIER_HEATSINK_OVERHEAT:
            OLED_writeString("Heatsink Overheated");
            break;
        case PELTIER_INT_OVERHEAT:
            OLED_writeSpaces(3);
            OLED_writeString("MCU Overheated");
            break;
        case PELTIER_POWER_ERROR:
            OLED_writeString("Peltier Power Error");
            break;
    }

}