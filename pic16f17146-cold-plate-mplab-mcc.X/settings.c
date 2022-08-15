#include "settings.h"
#include "mcc_generated_files/nvm/nvm.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

//Init Settings (Check for validity)
void settings_init(void)
{
    if (!settings_isValid())
    {
        //Invalid EEPROM
        settings_writeDefaults();
        printf("EEPROM not valid - resetting.\r\n");
    }
}

//Erases EEPROM and writes default values in
void settings_writeDefaults(void)
{
    //Write Defaults
    setting_writeValue(SETTINGS_LAST_TEMP, DEFAULT_TEMPERATURE_SETTING);
    setting_writeValue(SETTINGS_CURRENT_LIMIT, DEFAULT_CURRENT_LIMIT);
    
    //Write EEPROM Version ID Last
    setting_writeValue(SETTINGS_EEPROM_VERSION, COMPILED_EEPROM_VERSION);
}


//Returns true if the settings are valid
bool settings_isValid(void)
{
    if (settings_getValue(SETTINGS_EEPROM_VERSION) != COMPILED_EEPROM_VERSION)
    {
        //Invalid EEPROM
        return false;
    }
    return true;
}

//Returns the value at [READ]
uint8_t settings_getValue(UserSetting setting)
{
    return EEPROM_Read(setting);
}

//Writes [VALUE] to [WRITE]
void setting_writeValue(UserSetting setting, uint8_t value)
{
    EEPROM_Write(setting, value);
}
