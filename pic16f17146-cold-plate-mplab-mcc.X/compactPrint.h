#ifndef COMPACTPRINT_H
#define	COMPACTPRINT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    //Sends a string of text to the UART with no newline appended
    void compactPrint_sendStringLiteral(const char* str);
    
    //Sends a string of text to the UART with a newline appended.
    void compactPrint_sendStringWithNewline(const char* str);
    
    //Sends Debug Telemetry to the UART
    void compactPrint_sendDebugTelemetry(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* COMPACTPRINT_H */

