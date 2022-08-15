#include "peltierControl.h"

#include <xc.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"
#include "utility.h"
#include "fanControl.h"
#include "tempMonitor.h"

#define FET_PWM_DISABLE_PERIOD_INT() do { PIR3bits.PWM1PIF = 0; PIE3bits.PWM1PIE = 0; } while (0)
#define FET_PWM_ENABLE_PERIOD_INT() do { PIR3bits.PWM1PIF = 0; PIE3bits.PWM1PIE = 1; } while (0)

#define CWG_ENABLE() do { CWG1CON0bits.EN = 1; } while (0)

//State machine for DAC updates
enum CurrentLimitState {
    CURRENT_LIMIT_NO_CHANGE = 0, CURRENT_LIMIT_SET_DAC, CURRENT_LIMIT_SETTLE
};

//DAC Update State Machine w/ Anti-Glitch Operation
static enum CurrentLimitState dacUpdateState = CURRENT_LIMIT_NO_CHANGE;
static uint8_t newDACValue = 0;

//Average Duty Cycle of FET
static uint8_t averageDutyCycle = 0;

//True if Peltier is on
static bool peltierOn = false;

//Error for Peltier
static PeltierError error = PELTIER_ERROR_NONE;

//Target Peltier Temperature
static int8_t targetTemp = 0;
static int8_t maxHeatsinkTemp = 0;
static int8_t maxIntTemp = 0;

//Init the Peltier Current Controller
void peltierControl_init(void)
{    
    //Disable Period Interrupt for PWM
    FET_PWM_DISABLE_PERIOD_INT();
    
    //Enable CWG
    CWG_ENABLE();
    
    //For freq. counting, increment is 1
    NCO1INC = 1;
    NCO1CONbits.EN = 1;
    
    DAC2_SetOutput(255);    
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
    
    if (peltierOn)
    {
        //Peltier is active
        if (fanControl_getFan1RPM() == 0)
        {
            //Fan Error!
            error = PELTIER_FAN1_ERROR;
            peltierControl_stop();
        }
        if (tempMonitor_getLastHotTemp() > 0x00)
        {
            //Overheat - Heatsink
            error = PELTIER_HEATSINK_OVERHEAT;
            peltierControl_stop();
        }
        if (tempMonitor_getLastIntTemp() > 0x00)
        {
            error = PELTIER_INT_OVERHEAT;
            
        }
    }
    else
    {
        //Peltier is not on
    }
    
    
}

void peltierControl_calculateDutyCycle(void)
{
    //Calculate the number of pulses
    
    //Turn off NCO
    NCO1CONbits.EN = 0;
    
    //Clear the duty cycle count
    averageDutyCycle = 0;
    
    //Assumes a 32MHz Clock, once every 10ms
    uint32_t pulses = NCO1ACC;
    
    while (pulses >= 3200)
    {
        pulses -= 3200;
        averageDutyCycle++;
    }
    
    //Basic Rounding - if over 50%, round up
    if (pulses > 1600)
    {
        averageDutyCycle++;
    }

    //If we somehow got over 100% (probably due to delays)
    if (averageDutyCycle > 100)
    {
        averageDutyCycle = 100;
    }
    
    //Clear Accumulator
    NCO1ACCU = 0;
    NCO1ACCH = 0;
    NCO1ACCL = 0;
    
    //Restart NCO
    NCO1CONbits.EN = 1;
}

//Calculate the average duty cycle of the PWM
uint8_t peltierControl_getAverageDutyCycle(void)
{
    return averageDutyCycle;
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
            //Steer CWG to Logic-0
            CWG1STRbits.CWG1STRA = 0;
            
            //Update DAC Value
            DAC2_SetOutput(newDACValue);
            
            //Update State
            dacUpdateState = CURRENT_LIMIT_SETTLE;            
            break;
        }
        case CURRENT_LIMIT_SETTLE:
        {            
            //Release CWG
            CWG1STRbits.CWG1STRA = 1;
            
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
    peltierOn = true;
    
    //Enable WWDT
    WWDT_start();
    return false;
}

//Stop the Peltier Regulator
void peltierControl_stop(void)
{    
    peltierOn = false;
    
    //Disable WWDT
    WWDT_stop();
}

//Set the max current through the loop
void peltierControl_setMaxCurrent(uint8_t lim)
{
    static uint8_t counter = 10;
    newDACValue = counter;
    
    counter++;
    
    if (counter == 0)
        counter = 10;
    
    dacUpdateState = CURRENT_LIMIT_SET_DAC;
    FET_PWM_ENABLE_PERIOD_INT();
}

//Returns the error code from the Peltier regulator. Does NOT clear the error
PeltierError peltierControl_getError(void)
{
    return error;
}

