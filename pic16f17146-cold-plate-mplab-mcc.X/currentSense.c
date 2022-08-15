#include "currentSense.h"
#include "mcc_generated_files/opa/opa1.h"
#include "mcc_generated_files/adcc/adcc.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//1x, 2x, 4x, 8x, 16x Gains + OFFSET
static float OPAMPGain16 = 16.0;
static int16_t OPAMPOffset = 0.0;

static CURRENT_SENSE_GAIN systemGain = UNITY;

//Init Current Sense System
void currentSense_init(void)
{
    //Set gain to 16x
    currentSense_setConfiguration(GAIN_16);
    
    //Select VSS as a negative source
    OPA1_SetNegativeSource(OPA1_Vss);
        
    //Self-Calibrate
    //currentSense_selfCalibrate();
}

//Runs current sense - self calibration
//Blocking Code
void currentSense_selfCalibrate(void)
{
    //Disable ADC Interrupts    
    PIE6bits.ADTIE = 0;

    //Set VDD as ADC Reference
    ADREFbits.PREF = 0b00;
        
    //~10us per bit
    ADACQ = 255;
    
    /* To find gain...
     * 
     * Connect the resistor ladder as voltage divider
     * Measure the Output Voltage in Unity Gain
     */
    
    //16x
    //Find Gain Error
    currentSense_setConfiguration(MEASURE_GAIN_16);
        
    //Measure the OPAMP at 16x
    ADCC_StartConversion(channel_OPA1OUT);
    while (!ADCC_IsConversionDone());
    uint16_t opampResult = ADCC_GetFilterValue();

    //Calculate Gain
    OPAMPGain16 = (float)(4096.0 / opampResult);
    
    //Return OPAMP to Input Pin
    currentSense_setConfiguration(GAIN_16);
    
    //Set VREF as ADC Reference
    ADREFbits.PREF = 0b11;
    
    //Clear Flag
    PIR6bits.ADTIF = 0;
    
    //Re-enable Interrupts
    PIE6bits.ADTIE = 1;
}

//Sets the gain of the current sense amplifier
void currentSense_setConfiguration(CURRENT_SENSE_GAIN gain)
{
    //Force the OPAMP to VDD
    OPA1CON0bits.SOC = 0b10;
    
    if (((systemGain == UNITY) || (systemGain == MEASURE_GAIN_16)) && (gain != UNITY))
    {
        //Disable Unity Gain
        OPA1_DisableSoftwareUnityGain();
        
        //Enable Feedback
        OPA1CON3bits.FMS = 0b10;
                
        //Re-enable Resistor ladder
        OPA1CON1bits.RESON = 1;
        
        //Select Ladder for input
        OPA1_SetNegativeChannel(OPA1_negChannel_GSEL);

        //Select analog input
        OPA1_SetPositiveChannel(OPA1_posChannel_OPA1IN);
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
        case MEASURE_GAIN_16:
        {
            //Configures the resistor ladder as a voltage divider, and the OPAMP as a unity gain buffer
            //Nominal Output = VDD/16
//            
//            //Enable Unity Gain
//            OPA1_EnableSoftwareUnityGain();
//
//            //Connect VDD to Resistor Ladder
//            OPA1CON3bits.FMS = 0b01;
//
//            //Set Gain
//            OPA1_SetResistorLadder(OPA1_R2byR1_is_15);
//
//            //Disconnect Resistor Ladder from In-
//            OPA1_SetNegativeChannel(OPA1_negChannel_No_Connection);
//            
//            //Select GSEL as In+
//            OPA1_SetPositiveChannel(OPA1_posChannel_GSEL);
            break;
        }
    }
    
    //Update Current Gain
    systemGain = gain;
    
    //Return the OPAMP to normal operation
    OPA1CON0bits.SOC = 0b00;
}

//Prints OPAMP Calibration to UART
void currentSense_printCalibration(void)
{
    printf("OPAMP Offset: 0x%x\r\nOPAMP Gain at 16x: %2.4f\r\n", OPAMPOffset, OPAMPGain16);
}
