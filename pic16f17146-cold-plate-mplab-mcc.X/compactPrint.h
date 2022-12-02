#ifndef COMPACTPRINT_H
#define	COMPACTPRINT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
    
    //Sends a string of text to the UART with no newline appended
    void compactPrint_sendStringLiteral(const char* str);
    
    //Sends a string of text to the UART with a newline appended.
    void compactPrint_sendStringWithNewline(const char* str);
    
    //Sends a string + error code with a newline appended.
    void compactPrint_sendErrorCode(const char* str, uint8_t err);
        
    //Converts a duty cycle to a string
    //Requires up-to 4 positions "255" + [NULL]
    //Returns the location of the NULL character
    char* compactPrint_convertUint8ToString(char* str, uint8_t value);
    
    //Converts the value to a string. String contents are overwritten
    //Requires up-to 6 positions "65535" + [NULL]
    //Returns the location of the NULL character
    char* compactPrint_convertUint16ToString(char* str, uint16_t value);
    
    //Converts a temperature to a string with sign + unit
    //Requires up-to 5 positions "+127" + [NULL]
    void compactPrint_convertTempToString(char* str, int8_t temp, char unit);
    
    //Converts a duty cycle to a string
    //Requires up-to 5 positions "100%" + [NULL]
    void compactPrint_convertCurrentToString(char* str, uint8_t duty);
    
    //Sends Debug Telemetry to the UART
    void compactPrint_sendDebugTelemetry(void);
    
    //Sends Raw ADC values to the UART
    void compactPrint_sendRawADCValues(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* COMPACTPRINT_H */

