#ifndef CURRENTSENSE_H
#define	CURRENTSENSE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
      
    typedef enum {
        UNITY = 0, GAIN_2, GAIN_4, GAIN_8, GAIN_16
    } CurrentSenseGain;
    
    //Init Current Sense System
    void currentSense_init(void);
    
    //Runs current sense - self calibration
    //Blocking Code - only run on startup
    void currentSense_selfTest(void);
    
    //Calibrates the gain of the OPAMP
    //Blocking Code - only run on startup
    void currentSense_gainSelfTest(void);
        
    //Sets the current range for the program
    void currentSense_setCurrentLimits(void);
    
    //Sets the gain of the current sense amplifier
    void currentSense_setConfiguration(CurrentSenseGain gain);
    
    //Gets the gain configuration of the amplifier
    CurrentSenseGain currentSense_getConfiguration(void);
    
    //Sets the boolean for overcurrent events
    void currentSense_setOvercurrentEvent(void);
    
    //Returns true if an overcurrent event was detected
    bool currentSense_hasOvercurrentOccurred(void);
    
    //Returns true if gain is within tolerance
    bool currentSense_isGainOK(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* CURRENTSENSE_H */

