#ifndef PELTIERCONTROL_H
#define	PELTIERCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdbool.h>
#include <stdint.h>
    
    //Peltier Error Codes
    typedef enum {
        PELTIER_ERROR_NONE = 0, PELTIER_FAN1_ERROR, 
        PELTIER_OVERCURRENT_ERROR, PELTIER_POWER_ERROR,
        PELTIER_GAIN_ERROR,
        PELTIER_INT_OVERHEAT, PELTIER_HEATSINK_OVERHEAT, 
        PELTIER_SENSE_HOT_OPEN, PELTIER_SENSE_COLD_OPEN, 
        PELTIER_PLATE_TEMP_LIMIT
    } PeltierError;
    
    //Peltier States
    typedef enum {
        PELTIER_STATE_DISABLED = 0, PELTIER_STATE_STARTUP, PELTIER_STATE_AT_TEMP, PELTIER_STATE_COOLING
    } PeltierState;
        
    //Init the Peltier Current Controller
    void peltierControl_init(void);
    
    //This function is used to check for faults and to adjust the regulator. 
    //If this function is not called, the device will RESET.
    //ONLY CALL THIS FUNCTION FROM MAIN
    void peltierControl_periodicCheck(void);
    
    //Returns the current state of the Peltier
    PeltierState peltierControl_getState(void);
    
    //This function directly modifies the current threshold in the loop.
    //DO NOT CALL DIRECTLY
    void peltierControl_adjustThreshold(void);
    
    //Attempt to start the Peltier Regulator
    void peltierControl_start(void);
    
    //Stop the Peltier Regulator
    void peltierControl_stop(void);
    
    //Stops the Peltier without any prints
    //Only called from ISRs
    void peltierControl_fastStop(void);
    
    //Set the max current through the loop
    //void peltierControl_setMaxCurrent(uint8_t lim);
    
    //Returns the error code from the Peltier regulator. Does NOT clear the error
    PeltierError peltierControl_getError(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PELTIERCONTROL_H */

