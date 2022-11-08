#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
    
//If defined, telemetry will be sent via UART
#define DEBUG_TELEMETRY 
    
//If defined, debug messages will be sent via UART
#define DEBUG_PRINT
    
//If defined, UI will show error messages
#define UI_ERRORS
    
//Lowest allowed temperature in demo mode
#define DEMO_TEMP_LIMIT_LOW 5

//Lowest allowed temperature in not demo mode
#define TEMP_LIMIT_LOW -20
    
//Maximum allowed temperature to set
#define TEMP_LIMIT_MAX 25
    
//Minimum Heatsink Temperature (to be considered connected)
#define TEMP_NTC_HOT_OPEN 15
    
//Minimum Heatsink Temperature (to be considered connected)
#define TEMP_NTC_COLD_OPEN 40
    
//Temperature to throw an error at
#define TEMP_LIMIT_SAFETY_MARGIN 5
    
//Minimum Current Limit
#define CURRENT_LIMIT_MIN 1
    
//Maximum Current Limit
#define CURRENT_LIMIT_MAX 10
        
//Max Temperature before 100% Fan Speed
#define HEATSINK_TEMP_FAN_MAX 60
    
//Base Temperature for Fan Speed Calculations
#define HEATSINK_TEMP_FAN_MIN 28
    
//Min Fan Speed (1 degree per C above)
#define HEATSINK_TEMP_SLOPE 40

//Pre-Computed DAC Constant (Current per bit)
#define DAC_FORMULA_CONSTANT 0.1
    
//Current Limit (100s of mA)
#define CURRENT_LIMIT 60
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

