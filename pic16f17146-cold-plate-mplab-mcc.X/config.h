#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

//Lowest allowed temperature in demo mode
#define DEMO_TEMP_LIMIT_LOW 5

//Maximum allowed temperature to set
#define TEMP_LIMIT_MAX 25
    
//Minimum Current Limit
#define CURRENT_LIMIT_MIN 1
    
//Max Temperature before 100% Fan Speed
#define SAFETY_TEMP_MAX 70
    
//Default Settings - Used for resetting EEPROM
#define DEFAULT_TEMPERATURE_SETTING 10
#define DEFAULT_CURRENT_LIMIT 4
#define DEFAULT_TEMP_HYSTER 5
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

