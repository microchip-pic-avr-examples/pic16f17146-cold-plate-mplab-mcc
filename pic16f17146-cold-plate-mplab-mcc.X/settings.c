#include "settings.h"
#include "mcc_generated_files/system/system.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"

//Init Settings (Check for validity)
void settings_init(void)
{
    //Setup CRC for 8-bit operations
    CRCCON0bits.EN = 0;
    CRCCON2bits.DLEN = 7;
    CRCCON0bits.EN = 1;
    
    
    uint8_t memVersion = settings_getSetting(SETTINGS_EEPROM_VERSION);
    
    //Check for valid EEPROM markers
    if (!memVersion)
    {
        //Invalid EEPROM
        settings_writeDefaults();
        printf("EEPROM Version ID Mismatch - Settings Reset.\r\n");
    }
    else
    {
        printf("EEPROM Version ID = 0x%x\r\n", memVersion);
        
        uint8_t checksum = settings_verifyCRC();
        //printf("CRC Checksum = 0x%x\r\n", checksum);

        //Verify checksum
        if (checksum != 0x00)
        {
            //Failed CRC
            printf("CRC Checksum failed validation - settings reset.\r\n");
            settings_writeDefaults();
        }
        else
        {
            printf("Memory Checksum OK.\r\n");
        }
    }
}

//Erases EEPROM and writes default values in
void settings_writeDefaults(void)
{
    printf("Clearing EEPROM Settings\r\n");
    
    //Write Defaults
    settings_writeValue(SETTINGS_LAST_SET_TEMP, DEFAULT_LAST_TEMP_SETTING);
    settings_writeValue(SETTINGS_CURRENT_LIMIT, DEFAULT_CURRENT_LIMIT);
    
    //Write EEPROM Version ID
    settings_writeValue(SETTINGS_EEPROM_VERSION, COMPILED_EEPROM_VERSION);

    //Calculate new checksum
    uint8_t newChecksum = settings_calculateCRC();
    
    printf("Calculated new checksum = 0x%x\r\n", newChecksum);
    
    //Write the new CRC Value
    settings_writeValue(SETTINGS_CRC, newChecksum);
}


//Returns true if the settings are valid
bool settings_isValid(void)
{
    if (settings_getSetting(SETTINGS_EEPROM_VERSION) != COMPILED_EEPROM_VERSION)
    {
        //Invalid EEPROM
        return false;
    }
    return true;
}

//Runs a CRC and returns the checksum
uint8_t settings_calculateCRC(void)
{
    //Setup access to the output
    CRCCON0bits.SETUP = 0b00;
    
    //Clear Output and set SEED value
    CRCOUT = 0xFF;
    
    //Configure EEPROM Scan Range
    //NOTE: Registers are flipped now - to be fixed
    CRC_SetScannerAddressLimit((SETTINGS_EEPROM_STOP - 1), SETTINGS_EEPROM_START);
    
    //Start CRC Scanner
    CRC_StartScanner();
    
    //Wait for the scanner...
    while (CRC_IsScannerBusy());
    
    //We already set the setup bits to access CRCOUT
    return CRCOUTL;
}

//Runs a CRC and returns the checksum
uint8_t settings_verifyCRC(void)
{   
    //Setup access to the output
    CRCCON0bits.SETUP = 0b00;
    
    //Clear Output and set SEED value
    CRCOUT = 0xFF;
    
    //Configure EEPROM Scan Range
    //NOTE: Registers are flipped now - to be fixed
    CRC_SetScannerAddressLimit((SETTINGS_EEPROM_STOP), SETTINGS_EEPROM_START);
    
    //Start CRC Scanner
    CRC_StartScanner();
    
    //Wait for the scanner...
    while (CRC_IsScannerBusy());
    
    //We already set the setup bits to access CRCOUT
    return CRCOUTL;
}

//Returns the value at [READ]
uint8_t settings_getSetting(UserSetting setting)
{
    return eeprom_read(setting);
}

//Writes a setting to memory and updates the checksum.
void settings_writeSetting(UserSetting setting, uint8_t value)
{
    //Write the setting to memory
    settings_writeValue(setting, value);
    
    //Write the CRC Value
    settings_writeValue(SETTINGS_CRC, settings_calculateCRC());
}

//Writes [VALUE] to [WRITE]
void settings_writeValue(UserSetting setting, uint8_t value)
{
    eeprom_write(setting, value);
}
