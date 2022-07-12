/**
  * TMR3 Generated Driver File
  *
  * @file tmr3.c
  *
  * @ingroup tmr3
  *
  * @brief This file contains the driver code for TMR3 module.
  *
  * @version TMR3 Driver Version 3.0.1
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
 * Section: Included Files
*/

#include <xc.h>
#include "../tmr3.h"

/**
 * Section: Global Variables Definitions
*/
volatile uint16_t timer3ReloadVal;
void (*Timer3_InterruptHandler)(void);

const struct TMR_INTERFACE Timer3 = {
    .Initialize = Timer3_Initialize,
    .Start = Timer3_Start,
    .Stop = Timer3_Stop,
    .PeriodCountSet = Timer3_Write,
    .TimeoutCallbackRegister = Timer3_OverflowCallbackRegister,
    .Tasks = Timer3_Tasks
};
static void (*Timer3_OverflowCallback)(void);
static void Timer3_DefaultOverflowCallback(void);

void Timer3_Initialize(void)

{
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T3GCON = 0x0;
    //TGSS T3GPPS; 
    T3GATE = 0x0;
    //TMRCS CLC2_OUT; 
    T3CLK = 0xF;
    //TMRH 0; 
    TMR3H = 0x0;
    //TMRL 1; 
    TMR3L = 0x1;

    // Load the TMR3 value to reload variable
    timer3ReloadVal=(uint16_t)((TMR3H << 8) | TMR3L);

    //Set default callback for TMR3 overflow interrupt
    Timer3_OverflowCallbackRegister(Timer3_DefaultOverflowCallback);

    //Clear interrupt flags
    PIR2bits.TMR3IF = 0;
    PIR2bits.TMR3GIF = 0;
    
    //TMRON disabled; TRD16 disabled; nTSYNC synchronize; TCKPS 1:1; 
    T3CON = 0x0;
}

void Timer3_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 1;
}

void Timer3_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 0;
}

uint16_t Timer3_Read(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR3L;
    readValHigh = TMR3H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void Timer3_Write(size_t timerVal)
{
    if (T3CONbits.nT3SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T3CONbits.TMR3ON = 0;

        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T3CONbits.TMR3ON = 1;
    }
    else
    {
        // Write to the Timer3 register
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;
    }
}

void Timer3_Reload(void)
{
    Timer3_Write(timer3ReloadVal);
}

void Timer3_StartSinglePulseAcquisition(void)
{
    T3GCONbits.T3GGO = 1;
}

uint8_t Timer3_CheckGateValueStatus(void)
{
    return (T3GCONbits.T3GVAL);
}


void Timer3_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    Timer3_OverflowCallback = CallbackHandler;
}

static void Timer3_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use Timer3_OverflowCallbackRegister function to use Custom ISR
}

bool Timer3_HasOverflowOccured(void)
{
    return(PIR2bits.TMR3IF);
}

void Timer3_GateISR(void)
{
    // clear the TMR3 interrupt flag
    PIR2bits.TMR3GIF = 0;
}

void Timer3_Tasks(void)
{
    if(PIR2bits.TMR3IF)
    {
        PIR2bits.TMR3IF = 0;
        Timer3_OverflowCallback();
    }
}

/**
  End of File
*/