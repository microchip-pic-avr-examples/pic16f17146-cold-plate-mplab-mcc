#include "runningMenus.h"

void runningMenus_runningSetup(void){ 
    
    char disp_buff[20];
    
    OLED_clear();
    
    OLED_command(line_address[0]);
    
    OLED_writeString("Fan RPMs: ");
    sprintf(disp_buff, "%d, %d", fanControl_getFan1RPM(), fanControl_getFan1RPM());
    OLED_writeString(disp_buff);
    
    OLED_command(line_address[1]);
    //sprintf(disp_buff, "4%dA", getCurrent()); // TODO: get current function
    OLED_writeString("Avg. current: ");

    OLED_command(line_address[1]+17);
    strcpy(disp_buff, "5 A"); // TODO: remove
    OLED_writeString(disp_buff);
    
    OLED_command(line_address[2]);
    OLED_writeString("Plate temp:");
    
    OLED_command(line_address[3]);
    OLED_writeString("  Status: Running   ");
    
}

void runningMenus_runningUpdate(void){
    enum RUNNING_MSGS {NEW_STATS1, STATS1, NEW_STATS2, STATS2};
    static enum RUNNING_MSGS msg = STATS1;
    static int8_t counter10s = 0;
    char disp_buff[20];
    switch(msg){
        case NEW_STATS1: // change the few static elements
            // update fan number
            OLED_command(line_address[0]);
            OLED_writeString("Fan RPMs:           ");
            
            // update to avg current
            OLED_command(line_address[1]);
            OLED_writeString("Avg. current:       ");
            
            OLED_command(line_address[3]);
            OLED_writeString("  Status: Running   ");
            
            msg = STATS1;
            // fall through execution to update STATS1
        case STATS1: // only update changing values
            // FAN 1 RPM
            OLED_command(line_address[0]+10);
            sprintf(disp_buff, "%d, %d", fanControl_getFan1RPM(), fanControl_getFan1RPM());
            OLED_writeString(disp_buff);

            // Avg. Current
            OLED_command(line_address[1]+17);
            //sprintf(disp_buff, "4%d", getCurrent()); // TODO: replace with current reading function
            strcpy(disp_buff, "5 A"); // TODO: remove
            OLED_writeString(disp_buff);
            
            break;
        case NEW_STATS2:
            // update fan number
            OLED_command(line_address[0]);
            OLED_writeString("Heatsink Temp:      ");
            
            // update to hot temp
            OLED_command(line_address[1]);
            OLED_writeString("     MCU Temp:      ");
            
            OLED_command(line_address[3]);
            OLED_writeString("   Push to cancel   ");
            
            msg = STATS2;
            // fall through execution to update STATS2
        case STATS2:
            // Heatsink temp
            OLED_command(line_address[0]+14);
            sprintf(disp_buff, "%4d", tempMonitor_getLastHotTemp());
            OLED_writeString(disp_buff);
            OLED_data(0b00000000); // degrees symbol
            OLED_writeString("C");
            
            // MCU Temp
            OLED_command(line_address[1]+14);
            sprintf(disp_buff, "%4d", tempMonitor_getLastIntTemp());
            OLED_writeString(disp_buff);
            OLED_data(0b00000000); // degrees symbol
            OLED_writeString("C");
            break;
    }
    // update current Plate Temperature
    OLED_command(line_address[2]+12);
    sprintf(disp_buff, "%d/%d", tempMonitor_getLastColdTemp(), settingMenus_getTargetTemp());
    OLED_writeString(disp_buff);
    OLED_data(0b00000000); // degrees symbol
    OLED_writeString("C");
    
    // cycles the stats every 10 seconds
    if(counter10s >= 100){
        msg = (msg == STATS1) ? NEW_STATS2 : NEW_STATS1;        
        counter10s = 0;
    } else {
        counter10s++;
    }
    
}