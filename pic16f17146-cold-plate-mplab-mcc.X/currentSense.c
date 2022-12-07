#include "currentSense.h"
#include "mcc_generated_files/system/system.h"
#include "config.h"
#include "compactPrint.h"
#include "peltierControl.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

//1x, 2x, 4x, 8x, 16x Gains + OFFSET
static float OPAMPGain = 8.0;
static int8_t offset = 0;

//If true, an overcurrent event has occurred
static bool isOvercurrent = false, gainOK = false;

static CurrentSenseGain systemGain = UNITY;

//Init Current Sense System
void currentSense_init(void)
{
    //Set gain
    currentSense_setConfiguration(SYSTEM_GAIN);
    
    //Select VSS as a negative source
    OPA1_SetNegativeSource(OPA1_Vss);
}

//Runs current sense - self test
//Blocking Code
void currentSense_selfTest(void)
{
    //Disable CMP2 to prevent overcurrent trigger
    CM2CON0bits.EN = 0;
    
    //Gain Self-Test
    currentSense_gainSelfTest();
    
    //Configure Current Limits
    currentSense_setCurrentLimits();
    
    //Re-enable CMP2
    CM2CON0bits.EN = 1;
}

//Tests the gain of the current sense system
//Blocking Code - only run on startup
void currentSense_gainSelfTest(void)
{
    //2.048V for VREF DAC
    //~100mV output
    
    //Set Output
    DAC2_SetOutput(13);
    
    //Set VDD as ADC Reference
    ADREFbits.PREF = 0b00;
        
    //~10us per bit
    ADACQ = 255;
    
    /* To find gain...
     * 
     * Measure Output of OPAMP at UG
     * Measure Output of OPAMP at Gain ???
     * 
     * Divide Output @ Gain/UG to find Gain
     */
    
    //First, configure OPAMP
    //Select the DAC
    OPA1_SetPositiveChannel(OPA1_posChannel_DAC2);
    
    //Select Unity Gain
    currentSense_setConfiguration(UNITY);
    
    //Measure the DAC at 1x
    ADCC_StartConversion(channel_OPA1OUT);
    while (!ADCC_IsConversionDone())
    {
        asm("SLEEP");
    }
    uint16_t unityGainResult = ADCC_GetFilterValue();

    //Measure with Gain
    currentSense_setConfiguration(SYSTEM_GAIN);
        
    //Measure the OPAMP with gain
    ADCC_StartConversion(channel_OPA1OUT);
    while (!ADCC_IsConversionDone())
    {
        asm("SLEEP");
    }
    uint16_t gainResult = ADCC_GetFilterValue();

    //Calculate Gain
    OPAMPGain = (((float)gainResult) / unityGainResult);
    
    //Check to see if gain is within tolerance
    
    //Calculate Gain Ranges
    uint8_t idealGain = (1 << SYSTEM_GAIN);
    float minGain = idealGain * (1 - GAIN_TOLERANCE);
    float maxGain = idealGain * (1 + GAIN_TOLERANCE);
    
    if ((OPAMPGain >= minGain) && (OPAMPGain <= maxGain))
    {
        //Gain is within tolerance
        gainOK = true;
    }
    else
    {
        //Not within tolerance
        gainOK = false;
    }
    
    //Return OPAMP to Input Pin
    OPA1_SetPositiveChannel(OPA1_posChannel_OPA1IN);
    
    //Set VREF as ADC Reference
    ADREFbits.PREF = 0b11;
    
    //Clear Flag
    PIR6bits.ADTIF = 0;
}

//Sets the current limit of the demo
//Units are 100s of mA (e.g.: 100mA = 1, 1A = 10, etc...)
void currentSense_setCurrentLimits(void)
{
    //At a gain of 8x, no changes are needed
    
    uint8_t minLevel, maxLevel;
    
    //Load initial values
    minLevel = PELTIER_CURRENT_MIN;
    maxLevel = PELTIER_CURRENT_MAX;
    
    //DAC precision at 2.048V, 8mV per bit
    switch (currentSense_getConfiguration())
    {
        case UNITY:
        {
            //Unity (1x) gain
            //100mA x 0.01 ohm x 1 = 1mV per 100mA
            //Divide by 8
            
            minLevel >>= 3;
            maxLevel >>= 3;
            break;
        }
        case GAIN_2:
        {
            //2x gain
            //100mA x 0.01 ohm x 2 = 2mV per 100mA
            //Divide by 4
            
            minLevel >>= 2;
            maxLevel >>= 2;
            break;
        }
        case GAIN_4:
        {
            //4x gain
            //100mA x 0.01 ohm x 4 = 4mV per 100mA
            //Divide by 2
            
            minLevel >>= 1;
            maxLevel >>= 1;
            break;
        }
        case GAIN_8:
        {
            //At 8x gain, no changes are needed
            //100mA x 0.01 ohm x 8 = 8mV per 100mA
            break;
        }
        case GAIN_16:
        {
            //16x gain
            //100mA x 0.01 ohm x 16 = 16mV per 100mA
            //Multiple by 2
            
            minLevel <<= 1;
            maxLevel <<= 1;
            break;
        }
    }
    
    //Set Power Detect Threshold
    DAC1_SetOutput(minLevel);
    
    //Set Overcurrent Limits
    DAC2_SetOutput(maxLevel);
}

//Sets the gain of the current sense amplifier
void currentSense_setConfiguration(CurrentSenseGain gain)
{
    //Set to VDD
    OPA1_SetSoftwareOverride(0x02);
    
    if ((systemGain == UNITY) && (gain != UNITY))
    {
        //Disable Unity Gain
        OPA1_DisableSoftwareUnityGain();
        
        //Enable Feedback
        OPA1CON3bits.FMS = 0b10;
                
        //Re-enable Resistor ladder
        OPA1CON1bits.RESON = 1;
        
        //Select Ladder for input
        OPA1_SetNegativeChannel(OPA1_negChannel_GSEL);
    }
    
    switch (gain)
    {
        case UNITY:
        {
            //Enable Unity Gain
            OPA1_EnableSoftwareUnityGain();

            //Disable Feedback
            OPA1CON3bits.FMS = 0b00;

            //Disable Resistor Ladder
            OPA1CON1bits.RESON = 0;

            //Disconnect Resistor Ladder
            OPA1_SetNegativeChannel(OPA1_negChannel_No_Connection);
            break;
        }
        case GAIN_2:
        {
            OPA1_SetResistorLadder(OPA1_R2byR1_is_1);
            break;
        }
        case GAIN_4:
        {
            OPA1_SetResistorLadder(OPA1_R2byR1_is_3);
            break;
        }
        case GAIN_8:
        {
            OPA1_SetResistorLadder(OPA1_R2byR1_is_7);
            break;
        }
        case GAIN_16:
        {
            OPA1_SetResistorLadder(OPA1_R2byR1_is_15);
            break;
        }
    }
    
    //Update Current Gain
    systemGain = gain;
    
    //Set to VDD
    OPA1_SetSoftwareOverride(0x00);
}

//Gets the gain configuration of the amplifier
CurrentSenseGain currentSense_getConfiguration(void)
{
    return systemGain;
}

//Overcurrent event has occurred
void currentSense_overcurrentCallback(void)
{
    peltierControl_fastStop();
    isOvercurrent = true;
}

//Returns true if an overcurrent event was detected
bool currentSense_hasOvercurrentOccurred(void)
{
    return isOvercurrent;
}

bool currentSense_isGainOK(void)
{
    return gainOK;
}