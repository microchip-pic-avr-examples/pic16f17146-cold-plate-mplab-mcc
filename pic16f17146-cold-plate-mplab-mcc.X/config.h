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
    
//Sense Resistance
#define SENSE_RESISTANCE 0.01
    
//Resolution of the DAC (in terms of bits per volt)
//125 = 256 / 2.048V
#define DAC_CURRENT_RES 125

//Pre-Computed DAC Formula
#define DAC_FORMULA_CONSTANT ((DAC_CURRENT_RES * SENSE_RESISTANCE) / 10.0)
    
//Current Limit (100s of mA)
#define CURRENT_LIMIT 80
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

