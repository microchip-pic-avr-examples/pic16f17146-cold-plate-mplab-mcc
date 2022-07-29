#ifndef TEMPMONITOR_H
#define	TEMPMONITOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
        
    //Initializes the Temperature Monitors
    void tempMonitor_init(void);
    
    //Runs a state machine to measure temperature
    void tempMonitor_runStateMachine(void);
    
    //Starts a temperature conversion for the Cold Plate NTC
    void tempMonitor_sampleCold(void);
    
    //Starts a temperature conversion for the heatsink NTC
    void tempMonitor_sampleHot(void);
    
    //Starts a temperature conversion using the internal temp sensor
    void tempMonitor_sampleIntTemp(void);
    
    //Loads results from the ADC. Results must be ready
    void tempMonitor_loadResults(void);
    
    //Returns the last cold plate temperature
    int8_t tempMonitor_getLastColdTemp(void);
    
    //Returns the last heatsink temperature
    int8_t tempMonitor_getLastHotTemp(void);
    
    //Returns the last internal temperature
    int8_t tempMonitor_getLastIntTemp(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TEMPMONITOR_H */

