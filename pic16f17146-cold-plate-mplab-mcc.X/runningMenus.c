#include "runningMenus.h"
#include "peltierControl.h"

void runningMenus_runningSetup(void){     
    OLED_clear();
    if(settingMenus_getShowIcons()){
        //Show icons
        OLED_command(line_address[0]+11);
        OLED_data(0b00000101);
        OLED_data(0b00000110);
        OLED_writeString(":");

        OLED_command(line_address[0]);
        OLED_writeString("Set:");

        OLED_command(line_address[1]+1);
        OLED_data(0b00000001);
        OLED_data(0b00000010);
        OLED_writeString(":");


        OLED_command(line_address[1]+11);
        OLED_data(0b00000011);
        OLED_data(0b00000100);
        OLED_writeString(":");


    } else {
        // Show text
    OLED_command(line_address[0]+3);
    OLED_writeString("Plate:");
    
    OLED_command(line_address[1]);
    OLED_writeString("Heatsink:");

    OLED_command(line_address[2]+5);
    OLED_writeString("MCU:");
    }
    
    OLED_command(line_address[3]);
    OLED_writeString("Fan RPMs:");
    
}

void runningMenus_runningUpdate(int16_t moves){
    char disp_buff[20];
    if(settingMenus_getShowIcons()){
        // Show icons
        // update current Plate Temperature
        OLED_command(line_address[0]+14);
        sprintf(disp_buff, "%3d", dispTemp(tempMonitor_getLastColdTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        OLED_command(line_address[0]+4);
        sprintf(disp_buff, "%3d", dispTemp(settingMenus_getTargetTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        // MCU Temp
        OLED_command(line_address[1]+4);
        sprintf(disp_buff, "%3d", dispTemp(tempMonitor_getLastIntTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        OLED_command(line_address[1]+14);
        sprintf(disp_buff, "%3d", dispTemp(tempMonitor_getLastHotTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

    } else {
        // Show text
        
        // update current Plate Temperature
        OLED_command(line_address[0]+9);
        sprintf(disp_buff, "%3d/%3d", dispTemp(tempMonitor_getLastColdTemp()), dispTemp(settingMenus_getTargetTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        OLED_command(line_address[1]+12);
        sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastHotTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();

        // MCU Temp
        OLED_command(line_address[2]+12);
        sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastIntTemp()));
        OLED_writeString(disp_buff);
        OLED_writeTempUnit();
    }
    
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
        case PELTIER_PLATE_TEMP_LIMIT:
            OLED_writeSpaces(2);
            OLED_writeString("Peltier Too Cold");
            OLED_command(line_address[1]);
            OLED_writeString(" Safety Shutdown:");
            break;
        case PELTIER_ERROR_NONE:
            break;
    }

}