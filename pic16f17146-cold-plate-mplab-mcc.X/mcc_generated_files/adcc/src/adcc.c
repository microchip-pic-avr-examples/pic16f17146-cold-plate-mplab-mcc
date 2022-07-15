/**
 * ADCC Generated Driver File
 * 
 * @file adcc.c
 * 
 * @ingroup  adcc
 * 
 * @brief This is the generated driver implementation file for the ADCC driver.
 *
 * @version ADCC Driver Version 1.0.1
*/
/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "../adcc.h"

static void (*ADCC_ADTI_InterruptHandler)(void);
static void ADCC_DefaultADTI_ISR(void);

/**
  Section: ADCC Module APIs
*/

void ADCC_Initialize(void)
{
    // set the ADCC to the options selected in the User Interface
    //ADLTHL 0; 
    ADLTHL = 0x0;
    //ADLTHH 0; 
    ADLTHH = 0x0;
    //ADUTHL 0; 
    ADUTHL = 0x0;
    //ADUTHH 0; 
    ADUTHH = 0x0;
    //ADSTPTL 0; 
    ADSTPTL = 0x0;
    //ADSTPTH 0; 
    ADSTPTH = 0x0;
    //ADACCU 0x0; 
    ADACCU = 0x0;
    //ADRPT 8; 
    ADRPT = 0x8;
    //ADCHS ANA0; 
    ADPCH = 0x0;
    //ADCHS ANA0; 
    ADNCH = 0x0;
    //ADACQL 0; 
    ADACQL = 0x0;
    //ADACQH 0; 
    ADACQH = 0x0;
    //ADCAP Additional uC disabled; 
    ADCAP = 0x0;
    //ADPREL 0; 
    ADPREL = 0x0;
    //ADPREH 0; 
    ADPREH = 0x0;
    //CGA0 disabled; CGA1 disabled; CGA2 disabled; CGA4 disabled; CGA5 disabled; 
    ADCG1A = 0x0;
    //CGB4 disabled; CGB5 disabled; CGB6 disabled; CGB7 disabled; 
    ADCG1B = 0x0;
    //CGC0 disabled; CGC1 disabled; CGC2 disabled; CGC3 disabled; CGC4 disabled; CGC5 disabled; CGC6 disabled; CGC7 disabled; 
    ADCG1C = 0x0;
    //ADDSEN disabled; ADPCSC internal sampling capacitor and ext i/o pin; ADGPOL digital_low; ADIPEN disabled; ADPPOL Vss; 
    ADCON1 = 0x0;
    //ADMD Burst_average_mode; ADACLR disabled; ADCRS 3; ADPSIS RES; 
    ADCON2 = 0x33;
    //ADTMD enabled; ADSOI ADGO not cleared; ADCALC First derivative of Single measurement; 
    ADCON3 = 0x7;
    //ADMATH registers not updated; 
    ADSTAT = 0x0;
    //ADPREF FVR; 
    ADREF = 0x3;
    //ADACT disabled; 
    ADACT = 0x0;
    //ADCCS FOSC/2; 
    ADCLK = 0x0;
    //GO_nDONE undefined; ADIC single-ended mode; ADFM left justified; ADCS ADCRC; ADCONT disabled; ADON enabled; 
    ADCON0 = 0x90;
    
    // Clear the ADC interrupt flag
    PIR6bits.ADIF = 0;

    // Clear the ADC Threshold interrupt flag
    PIR6bits.ADTIF = 0;
    //Configure interrupt handlers
    ADCC_SetADTIInterruptHandler(ADCC_DefaultADTI_ISR);
    // Enabling ADCC threshold interrupt.
    PIE6bits.ADTIE = 1;
}
void ADCC_StartConversion(adcc_channel_t channel)
{
    // select the A/D channel
    ADPCH = channel;
  
    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Start the conversion
    ADCON0bits.ADGO = 1;
}

bool ADCC_IsConversionDone(void)
{
    // Start the conversion
    return ((unsigned char)(!ADCON0bits.ADGO));
}

adc_result_t ADCC_GetConversionResult(void)
{
    // Return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

adc_result_t ADCC_GetSingleConversion(adcc_channel_t channel)
{
    // select the A/D channel
    ADPCH = channel;  

    // Turn on the ADC module
    ADCON0bits.ADON = 1;
    
    //Disable the continuous mode.
    ADCON0bits.ADCONT = 0;

    // Start the conversion
    ADCON0bits.ADGO = 1;


    // Wait for the conversion to finish
    while (ADCON0bits.ADGO)
    {
    }
    
    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

inline void ADCC_StopConversion(void)
{
    //Reset the ADGO bit.
    ADCON0bits.ADGO = 0;
}

inline void ADCC_SetStopOnInterrupt(void)
{
    //Set the ADSOI bit.
    ADCON3bits.ADSOI = 1;
}

inline void ADCC_DischargeSampleCapacitor(void)
{
    //Set the ADC channel to AVss.
    ADPCH = 0x3a;   
}

void ADCC_LoadAcquisitionRegister(uint16_t acquisitionValue)
{
    //Load the ADACQH and ADACQL registers.
    ADACQH = (uint8_t) (acquisitionValue >> 8);
    ADACQL = (uint8_t) acquisitionValue;  
}

void ADCC_SetPrechargeTime(uint16_t prechargeTime)
{
    //Load the ADPREH and ADPREL registers.
    ADPREH = (uint8_t) (prechargeTime >> 8);
    ADPREL = (uint8_t) prechargeTime;
}

void ADCC_SetRepeatCount(uint8_t repeatCount)
{
    //Load the ADRPT register.
    ADRPT = repeatCount;   
}

uint8_t ADCC_GetCurrentCountofConversions(void)
{
    //Return the contents of ADCNT register
    return ADCNT;
}

inline void ADCC_ClearAccumulator(void)
{
    //Reset the ADCON2bits.ADACLR bit.
    ADCON2bits.ADACLR = 1;
}

uint24_t ADCC_GetAccumulatorValue(void)
{
    //Return the contents of ADACCU, ADACCH and ADACCL registers
    return (((uint24_t)ADACCU << 16)+((uint24_t)ADACCH << 8) + ADACCL);
}

void ADCC_DefineSetPoint(uint16_t setPoint)
{
    //Sets the ADSTPTH and ADSTPTL registers
    ADSTPTH = (uint8_t) (setPoint >> 8);
    ADSTPTL = (uint8_t) setPoint;
}

uint16_t ADCC_GetErrorCalculation(void)
{
    //Return the contents of ADERRH and ADERRL registers
    return ((uint16_t)((ADERRH << 8) + ADERRL));
}

void ADCC_SetUpperThreshold(uint16_t upperThreshold)
{
    //Sets the ADUTHH and ADUTHL registers
    ADUTHH = (uint8_t) (upperThreshold >> 8);
    ADUTHL = (uint8_t) upperThreshold;
}

void ADCC_SetLowerThreshold(uint16_t lowerThreshold)
{
    //Sets the ADLTHH and ADLTHL registers
    ADLTHH = (uint8_t) (lowerThreshold >> 8);
    ADLTHL = (uint8_t) lowerThreshold;
}

uint16_t ADCC_GetFilterValue(void)
{
    //Return the contents of ADFLTRH and ADFLTRL registers
    return ((uint16_t)((ADFLTRH << 8) + ADFLTRL));
}

uint16_t ADCC_GetPreviousResult(void)
{
    //Return the contents of ADPREVH and ADPREVL registers
    return ((uint16_t)((ADPREVH << 8) + ADPREVL));
}

bool ADCC_HasAccumulatorOverflowed(void)
{
    //Return the status of ADSTATbits.ADAOV
    return ADSTATbits.ADAOV;
}

inline void ADCC_EnableDoubleSampling(void)
{
    //Sets the ADCON1bits.ADDSEN
    ADCON1bits.ADDSEN = 1;
}

inline void ADCC_EnableContinuousConversion(void)
{
    //Sets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 1;
}

inline void ADCC_DisableContinuousConversion(void)
{
    //Resets the ADCON0bits.ADCONT
    ADCON0bits.ADCONT = 0;
}

bool ADCC_HasErrorCrossedUpperThreshold(void)
{
    //Returns the value of ADSTATbits.ADUTHR bit.
    return ADSTATbits.ADUTHR;
}

bool ADCC_HasErrorCrossedLowerThreshold(void)
{
    //Returns the value of ADSTATbits.ADLTHR bit.
    return ADSTATbits.ADLTHR;
}

uint8_t ADCC_GetConversionStageStatus(void)
{
    //Returns the contents of ADSTATbits.ADSTAT field.
    return ADSTATbits.ADSTAT;
}


void ADCC_ThresholdISR(void)
{
    // Clear the ADCC Threshold interrupt flag
    PIR6bits.ADTIF = 0;

    if (ADCC_ADTI_InterruptHandler != NULL)
    {
        ADCC_ADTI_InterruptHandler();
    }
}

void ADCC_SetADTIInterruptHandler(void (* InterruptHandler)(void))
{
    ADCC_ADTI_InterruptHandler = InterruptHandler;
}

static void ADCC_DefaultADTI_ISR(void)
{
    //Add your interrupt code here or
    //Use ADCC_SetADTIInterruptHandler() function to use Custom ISR
}
