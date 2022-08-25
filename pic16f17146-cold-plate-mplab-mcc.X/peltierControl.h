#ifndef PELTIERCONTROL_H
#define	PELTIERCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    typedef enum {
        PELTIER_ERROR_NONE = 0, PELTIER_FAN1_ERROR, 
        PELTIER_POWER_ERROR, PELTIER_INT_OVERHEAT, PELTIER_HEATSINK_OVERHEAT, 
        PELTIER_PLATE_SATURATION
    } PeltierError;
    
    //Max Duty Cycle Allowed
#define PELTIER_MAX_DUTY_CYCLE 75
    
    //Init the Peltier Current Controller
    void peltierControl_init(void);
    
    //Performs a self-test of the Peltier element. This function will block when executing. 
    bool peltierControl_selfTest(void);
        
    //This function is used to check for faults and to adjust the regulator. 
    //If this function is not called, the device will RESET.
    //ONLY CALL THIS FUNCTION FROM MAIN
    void peltierControl_periodicCheck(void);
    
    //Calculates the average duty cycle
    //CALL EVERY 10ms
    void peltierControl_calculateDutyCycle(void);
    
    //Calculate the average duty cycle of the PWM
    uint8_t peltierControl_getAverageDutyCycle(void);
    
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
    PeltierError peltierControl_getError(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PELTIERCONTROL_H */

