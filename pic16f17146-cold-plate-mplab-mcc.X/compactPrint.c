#include "compactPrint.h"

#include <xc.h>
#include "mcc_generated_files/system/system.h"

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

//Sends Debug Telemetry to the UART
void compactPrint_sendDebugTelemetry(void)
{
    
}
