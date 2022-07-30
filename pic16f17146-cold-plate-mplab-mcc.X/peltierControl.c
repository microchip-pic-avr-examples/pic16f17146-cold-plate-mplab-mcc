#include "peltierControl.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"
#include "utility.h"

//Init the Peltier Current Controller
void peltierControl_init(void)
{
    
}

//Performs a self-calibration of the OPAMP. This function will block when executing. 
void peltierControl_calibrateOPAMP(void)
{
    
}

//Performs a self-test of the Peltier element. This function will block when executing. 
bool peltierControl_selfTest(void)
{
    return false;
}

//This function is used to check for faults and to adjust the regulator. 
//If this function is not called, the device will RESET.
//ONLY CALL THIS FUNCTION FROM MAIN
void peltierControl_periodicCheck(void)
{
    //Clear the WWDT
    WWDT_reset();
}

//Set the target temperature of the Cold Plate
void peltierControl_setTargetTemp(int8_t target)
{
    
}

//Attempt to start the Peltier Regulator. Returns false if an error has occurred
bool peltierControl_start(void)
{
    //Enable WWDT
    WWDT_start();
    return false;
}

//Stop the Peltier Regulator
void peltierControl_stop(void)
{
    //Disable WWDT
    WWDT_stop();
}

//Set the max current through the loop
void peltierControl_setMaxCurrent(uint8_t lim)
{
    
}

//Returns the error code from the Peltier regulator. Does NOT clear the error
uint8_t peltierControl_getError(void)
{
    return PELTIER_ERROR_NONE;
}

