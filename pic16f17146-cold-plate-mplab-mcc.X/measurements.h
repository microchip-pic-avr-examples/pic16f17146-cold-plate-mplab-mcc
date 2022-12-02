#ifndef MEASUREMENTS_H
#define	MEASUREMENTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
        
    //Initializes the Measurement State Machine + Setups for Temperature Measurements
    void Measurements_init(void);
    
    //Runs a state machine to measure temperature
    void Measurements_runStateMachine(void);
    
    //Starts a temperature conversion for the Cold Plate NTC
    void Measurements_sampleCold(void);
    
    //Starts a temperature conversion for the heatsink NTC
    void Measurements_sampleHot(void);
    
    //Starts a temperature conversion using the internal temp sensor
    void Measurements_sampleIntTemp(void);
    
    //Measures current through the loop
    void Measurements_sampleCurrent(void);
        
    //Load Results for the ADC
    void Measurements_loadResults(void);
    
    //Prints raw values to UART
    void Measurements_printRawValues(void);
    
    //Returns the last cold plate temperature
    int8_t Measurements_getLastColdTemp(void);
    
    //Returns the raw cold value from the ADC
    uint16_t Measurements_getRawColdValue(void);
    
    //Returns the last heatsink temperature
    int8_t Measurements_getLastHotTemp(void);
    
    //Returns the raw hot value from the ADC
    uint16_t Measurements_getRawHotValue(void);

    //Returns the last internal temperature
    int8_t Measurements_getLastIntTemp(void);
    
    //Returns the raw INT value from the ADC
    uint16_t Measurements_getRawIntValue(void);
    
    //Returns the last current through the loop (in 100s of mA)
    uint8_t Measurements_getLastCurrent(void);
    
    //Returns the raw current value from the ADC
    uint16_t Measurements_getRawCurrentValue(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TEMPMONITOR_H */

