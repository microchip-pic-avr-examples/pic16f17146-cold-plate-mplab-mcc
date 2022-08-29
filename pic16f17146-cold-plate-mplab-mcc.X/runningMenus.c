#include "runningMenus.h"

void runningMenus_runningSetup(void){     
    OLED_clear();
    
    OLED_command(line_address[0]);
    OLED_writeString("Plate Temp:");
    runningMenus_runningUpdate(0);
}

void runningMenus_runningUpdate(int16_t moves){
    enum RUNNING_MSGS {NEW_STATS1, STATS1, NEW_STATS2, STATS2};
    static enum RUNNING_MSGS msg = NEW_STATS2;
    static int8_t counter10s = 0;
    char disp_buff[20];
    switch(msg){
        case NEW_STATS1: // change the few static elements
            // update to avg current
            OLED_command(line_address[1]);
            OLED_writeString("Avg. current:       ");
            
            
            // update fan number
            OLED_command(line_address[2]);
            OLED_writeString("Fan RPMs:           ");

            OLED_command(line_address[3]);
            OLED_writeString("   Push to cancel   ");

            msg = STATS1;
            // fall through execution to update STATS1
        case STATS1: // only update changing values
            // FAN 1 RPM
            OLED_command(line_address[2]+10);
            sprintf(disp_buff, "%d, %d", fanControl_getFan1RPM(), fanControl_getFan2RPM());
            OLED_writeString(disp_buff);

            // Avg. Current
            OLED_command(line_address[1]+17);
            //sprintf(disp_buff, "4%d", getCurrent()); // TODO: replace with current reading function
            OLED_writeString("5 A");
            
            break;
        case NEW_STATS2:
            // update fan number
            OLED_command(line_address[1]);
            OLED_writeString("Heatsink Temp:");
            
            // update to hot temp
            OLED_command(line_address[2]+5);
            OLED_writeString("MCU Temp:");
            
            OLED_command(line_address[3]+2);
            OLED_writeString("Status: Running");
            
            msg = STATS2;
            // fall through execution to update STATS2
        case STATS2:
            // Heatsink temp
            OLED_command(line_address[1]+14);
            sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastHotTemp()));
            OLED_writeString(disp_buff);
            OLED_writeTempUnit();
            
            // MCU Temp
            OLED_command(line_address[2]+14);
            sprintf(disp_buff, "%4d", dispTemp(tempMonitor_getLastIntTemp()));
            OLED_writeString(disp_buff);
            OLED_writeTempUnit();
            break;
    }
    // update current Plate Temperature
    OLED_command(line_address[0]+12);
    sprintf(disp_buff, "%d/%d", dispTemp(tempMonitor_getLastColdTemp()), dispTemp(settingMenus_getTargetTemp()));
    OLED_writeString(disp_buff);
    
    OLED_command(line_address[0]+18);
    OLED_writeTempUnit();
    
    // cycles the stats every 10 seconds
    if(counter10s >= 100){
        msg = (msg == STATS1) ? NEW_STATS2 : NEW_STATS1;        
        counter10s = 0;
    } else {
        counter10s++;
    }
    
}
