#include "peltierControl.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"
#include "utility.h"

#define FET_PWM_DISABLE_PERIOD_INT() do { PIR3bits.PWM1PIF = 0; PIE3bits.PWM1PIE = 0; } while (0)
#define FET_PWM_ENABLE_PERIOD_INT() do { PIR3bits.PWM1PIF = 0; PIE3bits.PWM1PIE = 1; } while (0)

//State machine for DAC updates
enum CurrentLimitState {
    CURRENT_LIMIT_NO_CHANGE = 0, CURRENT_LIMIT_SET_DAC, CURRENT_LIMIT_SETTLE
};

static enum CurrentLimitState dacUpdateState = CURRENT_LIMIT_NO_CHANGE;
static uint8_t newDACValue = 0;

//Init the Peltier Current Controller
void peltierControl_init(void)
{    
    //Disable Period Interrupt for PWM
    FET_PWM_DISABLE_PERIOD_INT();
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

//This function directly modifies the current threshold in the loop.
void peltierControl_adjustThreshold(void)
{
    switch (dacUpdateState)
    {
        case CURRENT_LIMIT_SET_DAC:
        {
            //Set OPAMP to Output VDD
            OPA1_SetSoftwareOverride(0b10);
            
            //Update DAC Value
            DAC2_SetOutput(newDACValue);
            
            //Update State
            dacUpdateState = CURRENT_LIMIT_SETTLE;            
            break;
        }
        case CURRENT_LIMIT_SETTLE:
        {            
            //Release OPAMP
            OPA1_SetSoftwareOverride(0b00);
            
            //Update State
            dacUpdateState = CURRENT_LIMIT_NO_CHANGE;
            
            //Disable Period Interrupts
            FET_PWM_DISABLE_PERIOD_INT();
            break;
        }
        case CURRENT_LIMIT_NO_CHANGE:
        default:
        {
            //Update State
            dacUpdateState = CURRENT_LIMIT_NO_CHANGE;
            
            //Disable Period Interrupts
            FET_PWM_DISABLE_PERIOD_INT();
        }
    }
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
    newDACValue = lim;
    dacUpdateState = CURRENT_LIMIT_SET_DAC;
    FET_PWM_ENABLE_PERIOD_INT();
}

//Returns the error code from the Peltier regulator. Does NOT clear the error
uint8_t peltierControl_getError(void)
{
    return PELTIER_ERROR_NONE;
}

