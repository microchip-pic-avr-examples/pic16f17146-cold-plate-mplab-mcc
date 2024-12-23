#include "settings.h"
#include "mcc_generated_files/system/system.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "config.h"
#include "defaults.h"
#include "compactPrint.h"

static uint8_t settingsCache[SETTINGS_CRC];
static bool writeFail = false;

//Init Settings (Check for validity)
void settings_init(void)
{
    //Setup CRC for 8-bit operations
    CRCCON0bits.EN = 0;
    CRCCON2bits.DLEN = 7;
    CRCCON0bits.EN = 1;
    
    uint8_t memVersion = settings_getSettingFromEEPROM(SETTINGS_EEPROM_VERSION);
        
    //Check for valid EEPROM markers
    if (memVersion != COMPILED_EEPROM_VERSION)
    {
        //Invalid EEPROM
        settings_writeDefaults();
#ifdef DEBUG_PRINT
        compactPrint_sendStringWithNewline("EEPROM Version ID: INVALID");
#endif
    }
    else
    {
#ifdef DEBUG_PRINT
        compactPrint_sendErrorCode("EEPROM Version ID: ", memVersion);
#endif
        
        uint8_t checksum = settings_verifyCRC();

        compactPrint_sendStringLiteral("User Settings Checksum: ");
        //Verify checksum
        if (checksum != 0x00)
        {
            //Failed CRC
#ifdef DEBUG_PRINT
            compactPrint_sendStringWithNewline("BAD");
#endif
            settings_writeDefaults();
        }
        else
        {
#ifdef DEBUG_PRINT
            compactPrint_sendStringWithNewline("OK");
#endif
        }
    }
    
#ifdef DEBUG_PRINT
    if (writeFail)
    {
        compactPrint_sendStringWithNewline("EEPROM Write Failure");
    }
#endif

    
    
    //Load the settings
    settings_loadFromEEPROM();
}

void settings_loadFromEEPROM()
{
    //Load all data
    for (uint8_t i = 0; i < SETTINGS_CRC; i++)
    {
        settingsCache[i] = eeprom_read(i);
    }
}

//Erases EEPROM and writes default values in
void settings_writeDefaults(void)
{
#ifdef DEBUG_PRINT
    compactPrint_sendStringWithNewline("Resetting EEPROM Settings");
#endif
    
    //Write Defaults
    settings_writeValue(SETTINGS_UNUSED, 0xFF);
    settings_writeValue(SETTINGS_TEMP_UNIT, DEFAULT_TEMP_UNIT);
    settings_writeValue(SETTINGS_MAX_INT_TEMP, DEFAULT_MAX_INT_SETTING);
    settings_writeValue(SETTINGS_MAX_HEATSINK_TEMP, DEFAULT_MAX_HOT_SETTINGS);
    settings_writeValue(SETTINGS_DEMO_MODE, DEFAULT_DEMO_MODE);
    settings_writeValue(SETTINGS_LAST_SET_TEMP, DEFAULT_LAST_TEMP_SETTING);
    settings_writeValue(SETTINGS_HYSTER_OVER, DEFAULT_TEMP_HYSTER_OVER);
    settings_writeValue(SETTINGS_HYSTER_UNDER, DEFAULT_TEMP_HYSTER_UNDER);
    settings_writeValue(SETTINGS_SHOW_ICONS, DEFAULT_SHOW_ICONS);
    
    //Write EEPROM Version ID
    settings_writeValue(SETTINGS_EEPROM_VERSION, COMPILED_EEPROM_VERSION);

    if (!writeFail)
    {
        //Calculate new checksum
        uint8_t newChecksum = settings_calculateCRC();

        //Write the new CRC Value
        settings_writeValue(SETTINGS_CRC, newChecksum);
    }
}

//Returns true if an EEPROM write failed
bool settings_didWriteFail(void)
{
    return writeFail;
}

//Clears the flag for EEPROM write failure
void settings_clearWriteFail(void)
{
    writeFail = false;
}

//Runs a CRC and returns the checksum
uint8_t settings_calculateCRC(void)
{
    //Setup access to the output
    CRCCON0bits.SETUP = 0b00;
    
    //Clear Output and set SEED value
    CRCOUT = 0xFF;
    
    //Configure EEPROM Scan Range
    CRC_SetScannerAddressLimit(SETTINGS_EEPROM_START, SETTINGS_EEPROM_STOP);
    
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
    CRC_SetScannerAddressLimit(SETTINGS_EEPROM_START, SETTINGS_EEPROM_STOP + 1);
    
    //Start CRC Scanner
    CRC_StartScanner();
    
    //Wait for the scanner...
    while (CRC_IsScannerBusy());
    
    //We already set the setup bits to access CRCOUT
    return CRCOUTL;
}

//Returns the value at [READ]
uint8_t settings_getSettingFromEEPROM(UserSetting setting)
{
    return eeprom_read(setting);
}

//Returns the cached value
uint8_t settings_getSetting(UserSetting setting)
{
    if (setting >= SETTINGS_CRC)
    {
        return 0x00;
    }
    
    return settingsCache[setting];
}

//Writes a setting to memory and updates the checksum.
void settings_writeSetting(UserSetting setting, uint8_t value)
{
    if (setting >= SETTINGS_CRC)
    {
        return;
    }
    
    settingsCache[setting] = value;
    
    //Write the setting to memory
    settings_writeValue(setting, value);
    
    //Write the CRC Value
    settings_writeValue(SETTINGS_CRC, settings_calculateCRC());
}

//Writes [VALUE] to [WRITE]
bool settings_writeValue(UserSetting setting, uint8_t value)
{
    if (setting > SETTINGS_CRC)
    {
        writeFail = true;
        return false;
    }
    
    //Cache in RAM
    settingsCache[setting] = value;
    
    //Write to EEPROM
    eeprom_write(setting, value);
    
    //Verify write
    if (settings_getSettingFromEEPROM(setting) != value)
    {
        //Write Failure
        writeFail = true;
        return false;
    }
    return true;
}

//Write the CRC value with new values from EEPROM
void settings_writeCRC(void)
{
    //Write the CRC Value
    settings_writeValue(SETTINGS_CRC, settings_calculateCRC());
}