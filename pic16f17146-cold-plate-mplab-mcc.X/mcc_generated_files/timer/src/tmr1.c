/**
  * TMR1 Generated Driver File
  *
  * @file tmr1.c
  *
  * @ingroup tmr1
  *
  * @brief This file contains the driver code for TMR1 module.
  *
  * @version TMR1 Driver Version 3.0.1
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
#include "../tmr1.h"

/**
 * Section: Global Variables Definitions
*/
volatile uint16_t timer1ReloadVal;
void (*Timer1_InterruptHandler)(void);

const struct TMR_INTERFACE Timer1 = {
    .Initialize = Timer1_Initialize,
    .Start = Timer1_Start,
    .Stop = Timer1_Stop,
    .PeriodCountSet = Timer1_Write,
    .TimeoutCallbackRegister = Timer1_OverflowCallbackRegister,
    .Tasks = Timer1_Tasks
};
static void (*Timer1_OverflowCallback)(void);
static void Timer1_DefaultOverflowCallback(void);

void Timer1_Initialize(void)

{
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x0;
    //TGSS T1GPPS; 
    T1GATE = 0x0;
    //TMRCS CLC1_OUT; 
    T1CLK = 0xE;
    //TMRH 0; 
    TMR1H = 0x0;
    //TMRL 1; 
    TMR1L = 0x1;

    // Load the TMR1 value to reload variable
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    //Set default callback for TMR1 overflow interrupt
    Timer1_OverflowCallbackRegister(Timer1_DefaultOverflowCallback);

    //Clear interrupt flags
    PIR1bits.TMR1IF = 0;
    PIR1bits.TMR1GIF = 0;
    
    //TMRON enabled; TRD16 disabled; nTSYNC synchronize; TCKPS 1:1; 
    T1CON = 0x1;
}

void Timer1_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void Timer1_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t Timer1_Read(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
	
    readValLow = TMR1L;
    readValHigh = TMR1H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void Timer1_Write(size_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON = 1;
    }
    else
    {
        // Write to the Timer1 register
        TMR1H = (uint8_t)(timerVal >> 8);
        TMR1L = (uint8_t)timerVal;
    }
}

void Timer1_Reload(void)
{
    Timer1_Write(timer1ReloadVal);
}

void Timer1_StartSinglePulseAcquisition(void)
{
    T1GCONbits.T1GGO = 1;
}

uint8_t Timer1_CheckGateValueStatus(void)
{
    return (T1GCONbits.T1GVAL);
}


void Timer1_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    Timer1_OverflowCallback = CallbackHandler;
}

static void Timer1_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use Timer1_OverflowCallbackRegister function to use Custom ISR
}

bool Timer1_HasOverflowOccured(void)
{
    return(PIR1bits.TMR1IF);
}

void Timer1_GateISR(void)
{
    // clear the TMR1 interrupt flag
    PIR1bits.TMR1GIF = 0;
}

void Timer1_Tasks(void)
{
    if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        Timer1_OverflowCallback();
    }
}

/**
  End of File
*/