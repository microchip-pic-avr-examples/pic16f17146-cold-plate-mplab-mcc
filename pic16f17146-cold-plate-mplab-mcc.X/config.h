#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
    
//If defined, telemetry will be sent via UART
#define DEBUG_TELEMETRY 
    
//If defined, PRINTF will send messages
#define DEBUG_PRINT
    
//Lowest allowed temperature in demo mode
#define DEMO_TEMP_LIMIT_LOW 5

//Lowest allowed temperature in not demo mode
#define TEMP_LIMIT_LOW -20
    
//Maximum allowed temperature to set
#define TEMP_LIMIT_MAX 25
    
//Temperature to throw an error at
#define TEMP_LIMIT_SAFETY_MARGIN 5
    
//Minimum Current Limit
#define CURRENT_LIMIT_MIN 1
    
//Maximum Current Limit
#define CURRENT_LIMIT_MAX 10
    
//Threshold to detect power
//~100mA per bit
#define POWER_DETECT_MINIMUM 10
    
//Max Temperature before 100% Fan Speed
#define HEATSINK_TEMP_FAN_MAX 60
    
//Sense Resistance
#define SENSE_RESISTANCE 0.01
    
//Resolution of the DAC (in terms of bits per volt)
//125 = 256 / 2.048V
#define DAC_CURRENT_RES 125

//Pre-Computed DAC Formula
#define DAC_FORMULA_CONSTANT ((DAC_CURRENT_RES * SENSE_RESISTANCE) / 10.0)
    
//8A Current Limit
#define POWER_LIMIT 80
            
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

