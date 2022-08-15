#ifndef CURRENTSENSE_H
#define	CURRENTSENSE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
#include <stdint.h>
  
    typedef enum {
        UNITY = 0, GAIN_2, GAIN_4, GAIN_8, GAIN_16, MEASURE_GAIN_16
    } CURRENT_SENSE_GAIN;
    
    //Init Current Sense System
    void currentSense_init(void);
    
    //Runs current sense - self calibration
    //Blocking Code
    void currentSense_selfCalibrate(void);
    
    //Sets the gain of the current sense amplifier
    void currentSense_setConfiguration(CURRENT_SENSE_GAIN gain);
    
    //Prints OPAMP Calibration to UART
    void currentSense_printCalibration(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* CURRENTSENSE_H */

