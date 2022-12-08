#include "peltierControl.h"

#include <xc.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"
#include "utility.h"
#include "fanControl.h"
#include "measurements.h"
#include "settings.h"
#include "config.h"
#include "currentSense.h"
#include "compactPrint.h"

#define PELTIER_ENABLE() FET_CONTROL_SetHigh()
#define PELTIER_DISABLE() FET_CONTROL_SetLow()

//Peltier State Machine
static PeltierState peltierState = PELTIER_STATE_DISABLED;

//Error for Peltier
static PeltierError error = PELTIER_ERROR_NONE;

//Init the Peltier Current Controller
void peltierControl_init(void)
{    
    //Turn off the FET
    PELTIER_DISABLE();
}

//This function is used to check for faults and to adjust the regulator. 
//If this function is not called, the device will RESET.
//ONLY CALL THIS FUNCTION FROM MAIN
void peltierControl_periodicCheck(void)
{    
    //Clear the WWDT
    WWDT_reset();    
    
    //Clear existing errors
    error = PELTIER_ERROR_NONE;
    
    if (fanControl_getFan1RPM() == 0)
    {
        //Fan Error!
        error = PELTIER_FAN1_ERROR;
    }
    if (Measurements_getLastHotTemp() > settings_getSetting(SETTINGS_MAX_HEATSINK_TEMP))
    {
        //Overheat - Heatsink
        error = PELTIER_HEATSINK_OVERHEAT;
    }
    if (Measurements_getLastHotTemp() < TEMP_NTC_HOT_OPEN)
    {
        //Possible bad NTC connection on the hot side
        //Usually appears as a really low temperature
        error = PELTIER_SENSE_HOT_OPEN;
    }
    if (Measurements_getLastIntTemp() > settings_getSetting(SETTINGS_MAX_INT_TEMP))
    {
        //Overheat - Int. Temperature
        error = PELTIER_INT_OVERHEAT;
    }
    if (Measurements_getLastColdTemp() < (TEMP_LIMIT_LOW))
    {
        //Overcooled - Cold Plate is below safe temperature
        error = PELTIER_PLATE_TEMP_LIMIT;
    }
    if (Measurements_getLastColdTemp() > TEMP_NTC_COLD_OPEN)
    {
        //Possible bad NTC connection on the cold side
        //This is likely a rare condition (expect overcool to detect this), but worth testing for
        error = PELTIER_SENSE_COLD_OPEN;
    }
    if (OVERCURRENT_CMP_GetOutputStatus())
    {
        //Overcurrent Error
        error = PELTIER_OVERCURRENT_ERROR;
        currentSense_setOvercurrentEvent();
    }
    if (!currentSense_isGainOK())
    {
        //Gain of OPAMP out of tolerance
        error = PELTIER_GAIN_ERROR;
    }

    int8_t stopTemp, startTemp, currentTemp;
    stopTemp = settings_getSetting(SETTINGS_LAST_SET_TEMP);
    startTemp = stopTemp;
    currentTemp = Measurements_getLastColdTemp();

    //Update fan speed based on temperature
    fanControl_updateSpeedFromTemp(Measurements_getLastHotTemp());
    
    //Setup Temperature Hysteresis
    stopTemp -= settings_getSetting(SETTINGS_HYSTER_OVER);
    startTemp += settings_getSetting(SETTINGS_HYSTER_UNDER);

    switch (peltierState)
    {
        case PELTIER_STATE_DISABLED:
        {
            //System is disabled
            break;
        }
        case PELTIER_STATE_STARTUP:
        {
            //Check to see if system is ready

            if (error != PELTIER_ERROR_NONE)
            {
                //Something went wrong
                peltierControl_stop();
            }
            else
            {
                if (currentTemp <= stopTemp)
                {
                    //Plate is already cooled
                    peltierState = PELTIER_STATE_AT_TEMP;
                    
#ifdef DEBUG_PRINT
                    compactPrint_sendStringWithNewline("-- PELTIER IDLE --");
#endif
                }
                else
                {
                    //Plate needs to be cooled
                    peltierState = PELTIER_STATE_COOLING;
                    PELTIER_ENABLE();
                    
#ifdef DEBUG_PRINT
                    compactPrint_sendStringWithNewline("-- PELTIER ON --");
#endif
                }
            }

            break;
        }
        case PELTIER_STATE_AT_TEMP:
        {
            //Plate is cooled, waiting to restart

            if (currentTemp >= startTemp)
            {
                //Need to restart the peltier
                peltierState = PELTIER_STATE_COOLING;
                PELTIER_ENABLE();
                
#ifdef DEBUG_PRINT
                compactPrint_sendStringWithNewline("-- PELTIER ON --");
#endif
            }
            break;
        }
        case PELTIER_STATE_COOLING:
        {
            //Actively Cooling the Plate
            
            //No power detected
            if (POWER_FAIL_CMP_GetOutputStatus())
            {
                error = PELTIER_POWER_ERROR;
            }

            if (currentTemp <= stopTemp)
            {
                //At Temperature
                peltierState = PELTIER_STATE_AT_TEMP;
                PELTIER_DISABLE();
                
#ifdef DEBUG_PRINT
                compactPrint_sendStringWithNewline("-- PELTIER IDLE --");
#endif
            }
            break;
        }
    }

    if (error != PELTIER_ERROR_NONE)
    {
        peltierControl_stop();
    }    
}

//Returns the current state of the Peltier
PeltierState peltierControl_getState(void)
{
    return peltierState;
}

//Attempt to start the Peltier Regulator. Returns false if an error has occurred
void peltierControl_start(void)
{
    //Update State Machine
    peltierState = PELTIER_STATE_STARTUP;
    
    //Clear Errors
    error = PELTIER_ERROR_NONE;
    
    //Enable WWDT
    WWDT_start();
    
#ifdef DEBUG_PRINT
    compactPrint_sendStringWithNewline("-- PELTIER STARTUP --");
#endif
}

//Stop the Peltier Regulator
void peltierControl_stop(void)
{   
//#ifdef DEBUG_PRINT
//    if (error != PELTIER_ERROR_NONE)
//    {
//        compactPrint_sendErrorCode("Peltier Control Error, Code ", error);
//    }
//#endif
    
    //Disable Output
    PELTIER_DISABLE();

    //Disable WWDT
    WWDT_stop();
    
    if (peltierState != PELTIER_STATE_DISABLED)
    {
        //Update State Machine
        peltierState = PELTIER_STATE_DISABLED;
        
#ifdef DEBUG_PRINT
        compactPrint_sendStringWithNewline("-- PELTIER OFF --");
#endif
    }
       
}

void peltierControl_fastStop(void)
{
    //Disable Output
    PELTIER_DISABLE();
}

//Returns the error code from the Peltier regulator. Does NOT clear the error
PeltierError peltierControl_getError(void)
{
    return error;
}

// Clears error code
void peltierControl_clearError(void){
    error = PELTIER_ERROR_NONE;
}
