#include "compactPrint.h"

#include <xc.h>
#include "mcc_generated_files/system/system.h"
#include "fanControl.h"
#include "tempMonitor.h"
#include "settings.h"
#include "peltierControl.h"

//Sends a string of text to the UART with no newline appended
void compactPrint_sendStringLiteral(const char* str)
{
    uint8_t index = 0;
    while (str[index] != '\0')
    {
        if (UART1_IsTxReady())
        {
            UART1_Write(str[index]);
            index++;
        }
    }
    
    //Wait for TX
    while (!UART1_IsTxDone());
}

//Sends a string of text to the UART with a newline appended.
void compactPrint_sendStringWithNewline(const char* str)
{
    compactPrint_sendStringLiteral(str);
    compactPrint_sendStringLiteral("\r\n");
}

//Sends a string + error code with a newline appended.
void compactPrint_sendErrorCode(const char* str, uint8_t err)
{
    char buffer[4];
    
    //Send string
    compactPrint_sendStringLiteral(str);
    
    //Print Value
    compactPrint_convertUint8ToString(&buffer[0], err);
    compactPrint_sendStringWithNewline(buffer);
}

//Converts a duty cycle to a string
char* compactPrint_convertUint8ToString(char* str, uint8_t value)
{
    uint8_t divisor = 100;
    
    uint8_t index = 0, counter;
    bool hasStarted = false;
    while (divisor != 1)
    {
        //Reset iterative subtraction counter
        counter = 0;        
        while (divisor <= value)
        {
            //We started printing!
            hasStarted = true;
            
            //Subtract!
            value -= divisor;
            
            //Increment counter
            counter++;
        }
        
        if (hasStarted)
        {
            //We already printed a value!
            str[index] = '0' + counter;
            index++;
        }
        else
        {
            //Haven't printed anything, so leave it blank
            str[index] = ' ';
        }
        
        divisor /= 10;
    }
    
    //Last digit is always printed
    str[index] = value + '0';
    str[index + 1] = '\0';
    return (str + index + 1);
}

//Converts the value to a string. String contents are overwritten
char* compactPrint_convertUint16ToString(char* str, uint16_t value)
{
    uint16_t divisor = 10000;
    
    uint8_t index = 0, counter;
    bool hasStarted = false;
    while (divisor != 1)
    {
        //Reset iterative subtraction counter
        counter = 0;        
        while (divisor <= value)
        {
            //We started printing!
            hasStarted = true;
            
            //Subtract!
            value -= divisor;
            
            //Increment counter
            counter++;
        }
        
        if (hasStarted)
        {
            //We already printed a value!
            str[index] = '0' + counter;
            index++;
        }
        else
        {
            //Haven't printed anything, so leave it blank
            str[index] = ' ';
        }
        
        divisor /= 10;
    }
    
    //Last digit is always printed
    str[index] = value + '0';
    str[index + 1] = '\0';
    return (str + index + 1);
}

//Converts a temperature to a string with sign + unit
void compactPrint_convertTempToString(char* str, int8_t temp, char unit)
{
    uint8_t unsignTemp;
    
    if (temp < 0)
    {
        unsignTemp = temp * -1;
        str[0] = '-';
    }
    else
    {
        unsignTemp = temp;
        str[0] = '+';
    }
    
    //Convert temp to string
    char* end = compactPrint_convertUint8ToString((str + 1), unsignTemp);
    
    //Append unit
    *end = unit;
    *(end + 1) = '\0';
}

//Converts a duty cycle to a string
void compactPrint_convertDutyCycleToString(char* str, uint8_t duty)
{
    char* end = compactPrint_convertUint8ToString(str, duty);
    *end = '%';
    *(end + 1) = '\0';
}

//Sends Debug Telemetry to the UART
void compactPrint_sendDebugTelemetry(void)
{
    //Buffer for RPM/Temp/Etc...
    char buffer[6];
    
    //Print Fan 1 RPM
    compactPrint_sendStringLiteral("Fan 1 RPM: ");
    compactPrint_convertUint16ToString(buffer, fanControl_getFan1RPM());
    compactPrint_sendStringWithNewline(buffer);

    //Print Fan 2 RPM
    compactPrint_sendStringLiteral("Fan 2 RPM: ");
    compactPrint_convertUint16ToString(buffer, fanControl_getFan2RPM());
    compactPrint_sendStringWithNewline(buffer);

    //Print Cold Plate Temperature
    compactPrint_sendStringLiteral("Cold Plate Temp: ");
    compactPrint_convertTempToString(buffer, tempMonitor_getLastColdTemp(), settings_getSetting(SETTINGS_TEMP_UNIT));
    compactPrint_sendStringWithNewline(buffer);
    
    //Print Heatsink Temperature
    compactPrint_sendStringLiteral("Heatsink Temp: ");
    compactPrint_convertTempToString(buffer, tempMonitor_getLastHotTemp(), settings_getSetting(SETTINGS_TEMP_UNIT));
    compactPrint_sendStringWithNewline(buffer);

    //Print MCU Temperature
    compactPrint_sendStringLiteral("Int Temp: ");
    compactPrint_convertTempToString(buffer, tempMonitor_getLastIntTemp(), settings_getSetting(SETTINGS_TEMP_UNIT));
    compactPrint_sendStringWithNewline(buffer);
    
    //Print Duty Cycle
    compactPrint_sendStringLiteral("Average Duty Cycle: ");
    compactPrint_convertDutyCycleToString(buffer, peltierControl_getAverageDutyCycle());
    compactPrint_sendStringWithNewline(buffer);
}
