#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
    
//EEPROM Version ID
#define COMPILED_EEPROM_VERSION 0x02
    
typedef enum{
    SETTINGS_EEPROM_VERSION = 0, SETTINGS_LAST_TEMP, SETTINGS_CURRENT_LIMIT,
            SETTINGS_TEMP_UNIT, SETTINGS_DEMO_MODE
} UserSetting;    
    
    //Init Settings (Check for validity)
    void settings_init(void);

    //Erases EEPROM and writes default values in
    void settings_writeDefaults(void);

    //Returns true if the settings are valid
    bool settings_isValid(void);
    
    //Returns the value at [READ]
    uint8_t settings_getValue(UserSetting read);
    
    //Writes [VALUE] to [WRITE]
    void setting_writeValue(UserSetting write, uint8_t value);

#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

