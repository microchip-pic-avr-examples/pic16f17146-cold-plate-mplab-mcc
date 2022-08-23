#include "currentSense.h"
#include "mcc_generated_files/opa/opa1.h"
#include "mcc_generated_files/adcc/adcc.h"
#include "mcc_generated_files/dac/dac1.h"
#include "mcc_generated_files/dac/dac2.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//1x, 2x, 4x, 8x, 16x Gains + OFFSET
static float OPAMPGain = 8.0;
static int16_t OPAMPOffset = 0.0;

static CurrentSenseGain systemGain = UNITY;

#define SYSTEM_GAIN GAIN_8

//Init Current Sense System
void currentSense_init(void)
{
    //Set gain
    currentSense_setConfiguration(SYSTEM_GAIN);
    
    //Select VSS as a negative source
    OPA1_SetNegativeSource(OPA1_Vss);
}

//Runs current sense - self calibration
//Blocking Code
void currentSense_selfCalibrate(void)
{
    //2.048V for VREF DAC
    //~100mV output
    DAC1_SetOutput(13);
    
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
    //Select DAC1
    OPA1_SetPositiveChannel(OPA1_posChannel_DAC1);
    
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
    
    //Return OPAMP to Input Pin
    OPA1_SetPositiveChannel(OPA1_posChannel_OPA1IN);
        
    //Set VREF as ADC Reference
    ADREFbits.PREF = 0b11;
    
    //Clear Flag
    PIR6bits.ADTIF = 0;
}

//Sets the current limit of the demo
//Units are 100s of mA (e.g.: 100mA = 1, 1A = 10, etc...)
void currentSense_setCurrentLimit(uint8_t limit)
{
    DAC1_SetOutput(limit);
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

//Prints OPAMP Calibration to UART
void currentSense_printCalibration(void)
{
    printf("OPAMP Offset: 0x%x\r\nOPAMP Gain: %2.4f\r\n", OPAMPOffset, OPAMPGain);
}
