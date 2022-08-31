#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

    

//Settings    
typedef enum{
    SETTINGS_EEPROM_VERSION = 0, SETTINGS_CURRENT_LIMIT, SETTINGS_TEMP_UNIT, SETTINGS_SHOW_ADVANCED,
            SETTINGS_MAX_INT_TEMP, SETTINGS_MAX_HEATSINK_TEMP, SETTINGS_DEMO_MODE, 
            SETTINGS_LAST_SET_TEMP,  SETTINGS_HYSTER_OVER, SETTINGS_HYSTER_UNDER,
            SETTINGS_CRC, 
} UserSetting;    
   
//Where to start scanning
#define SETTINGS_EEPROM_START (0xF000)

//Where to stop scanning
#define SETTINGS_EEPROM_STOP (SETTINGS_EEPROM_START + SETTINGS_CRC)
    
//EEPROM Version ID
#define COMPILED_EEPROM_VERSION 0x03
    
    //Init Settings (Check for validity)
    void settings_init(void);
    
    //Loads all settinsg from EEPROM
    void settings_loadFromEEPROM(void);

    //Erases EEPROM and writes default values in
    void settings_writeDefaults(void);

    //Returns true if the settings are valid
    bool settings_isValid(void);
    
    //Calculates the CRC and returns the checksum
    uint8_t settings_verifyCRC(void);
    
    //Runs a CRC and returns the checksum
    uint8_t settings_calculateCRC(void);
    
    //Returns the value at [READ]
    uint8_t settings_getSettingFromEEPROM(UserSetting setting);
    
    //Returns the cached value
    uint8_t settings_getSetting(UserSetting setting);
    
    //Writes a setting to memory and updates the checksum.
    void settings_writeSetting(UserSetting setting, uint8_t value);
    
    //Utility Function
    //Writes [VALUE] to [WRITE]. Does not update checksum
    void settings_writeValue(UserSetting setting, uint8_t value);

    //Write the CRC value with new values from EEPROM
    void settings_writeCRC(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

