#ifndef PELTIERCONTROL_H
#define	PELTIERCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    typedef enum {
        PELTIER_ERROR_NONE = 0, PELTIER_FAN_ERROR, PELTIER_NO_POWER, PELTIER_OVERHEAT, PELTIER_PLATE_SATURATION
    } PELTIER_ERROR;
    
    //Max Duty Cycle Allowed
#define PELTIER_MAX_DUTY_CYCLE 75
    
    //Init the Peltier Current Controller
    void peltierControl_init(void);

    //Performs a self-calibration of the OPAMP. This function will block when executing. 
    void peltierControl_calibrateOPAMP(void);
    
    //Performs a self-test of the Peltier element. This function will block when executing. 
    bool peltierControl_selfTest(void);
        
    //This function is used to check for faults and to adjust the regulator. 
    //If this function is not called, the device will RESET.
    //ONLY CALL THIS FUNCTION FROM MAIN
    void peltierControl_periodicCheck(void);
    
    //Set the target temperature of the Cold Plate
    void peltierControl_setTargetTemp(int8_t target);
    
    //This function directly modifies the current threshold in the loop.
    //DO NOT CALL DIRECTLY
    void peltierControl_adjustThreshold(void);
    
    //Attempt to start the Peltier Regulator. Returns false if an error has occurred
    bool peltierControl_start(void);
    
    //Stop the Peltier Regulator
    void peltierControl_stop(void);
        
    //Set the max current through the loop
    void peltierControl_setMaxCurrent(uint8_t lim);
    
    //Returns the error code from the Peltier regulator. Does NOT clear the error
    uint8_t peltierControl_getError(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PELTIERCONTROL_H */

