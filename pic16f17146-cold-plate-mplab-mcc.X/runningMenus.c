#include "runningMenus.h"

void runningMenus_runningSetup(void){     
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("Plate Temp:");
    
    OLED_command(line_address[0]+18);
    OLED_writeTempUnit();
    
    OLED_command(line_address[1]);
    OLED_writeString("Heatsink Temp:");

    OLED_command(line_address[2]+5);
    OLED_writeString("MCU Temp:");
    
    OLED_command(line_address[3]);
    OLED_writeString("Fan RPMs:");
    
}

void runningMenus_runningUpdate(int16_t moves){
    char disp_buff[20];

    // update current Plate Temperature
    OLED_command(line_address[0]+11);
    sprintf(disp_buff, "%3d/%-3d", dispTemp(tempMonitor_getLastColdTemp()), dispTemp(settingMenus_getTargetTemp()));
    OLED_writeString(disp_buff);

    OLED_command(line_address[1]+14);
    sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastHotTemp()));
    OLED_writeString(disp_buff);
    OLED_writeTempUnit();

    // MCU Temp
    OLED_command(line_address[2]+14);
    sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastIntTemp()));
    OLED_writeString(disp_buff);
    OLED_writeTempUnit();
            
    OLED_command(line_address[3]+10);
    sprintf(disp_buff, "%4d, %4d", fanControl_getFan1RPM(), fanControl_getFan2RPM());
    OLED_writeString(disp_buff);
}
