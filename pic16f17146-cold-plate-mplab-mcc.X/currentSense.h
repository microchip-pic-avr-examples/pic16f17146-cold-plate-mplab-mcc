#ifndef CURRENTSENSE_H
#define	CURRENTSENSE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
  
    typedef enum {
        UNITY = 0, GAIN_2, GAIN_4, GAIN_8, GAIN_16
    } CurrentSenseGain;
    
    //Init Current Sense System
    void currentSense_init(void);
    
    //Runs current sense - self calibration
    //Blocking Code - only run on startup
    void currentSense_selfCalibrate(void);
        
    //Sets the current limit of the demo
    //Units are 100s of mA (e.g.: 100mA = 1, 1A = 10, etc...)
    void currentSense_setCurrentLimit(uint8_t limit);
    
    //Sets the gain of the current sense amplifier
    void currentSense_setConfiguration(CurrentSenseGain gain);
    
#ifdef	__cplusplus
}
#endif

#endif	/* CURRENTSENSE_H */

