#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
    
//If defined, telemetry will be sent via UART (Global Enable)
#define DEBUG_TELEMETRY 
    
//If defined, debug messages will be sent via UART
#define DEBUG_PRINT
    
//If defined, raw ADC readings will be sent via UART
//#define DEBUG_RAW_VALUES
    
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
    
//Max Temperature before 100% Fan Speed
#define HEATSINK_TEMP_FAN_MAX 60
    
//Base Temperature for Fan Speed Calculations
#define HEATSINK_TEMP_FAN_MIN 28
    
//Min Fan Speed (1 degree per C above)
#define HEATSINK_TEMP_SLOPE 40
        
//Peltier Current Limit (100s of mA)
#define PELTIER_CURRENT_MAX 100

//Minimum Peltier current for detection
#define PELTIER_CURRENT_MIN 10
    
//Defines the gain the system is in
#define SYSTEM_GAIN GAIN_8
    
//Allowed error margin for gain (+/-)
#define GAIN_TOLERANCE 0.25
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

