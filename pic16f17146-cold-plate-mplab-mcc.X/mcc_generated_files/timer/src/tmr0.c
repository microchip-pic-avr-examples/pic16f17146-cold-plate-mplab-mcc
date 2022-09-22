/**
 * TMR0 Generated Driver File
 * 
 * @file tmr0.c
 * 
 * @ingroup tmr0
 * 
 * @brief  Driver implementation for the TMR0 driver
 *
 * @version TMR0 Driver Version 2.0.2
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

#include <xc.h>
#include "../tmr0.h"


const struct TMR_INTERFACE Timer0 = {
    .Initialize = Timer0_Initialize,
    .Start = Timer0_Start,
    .Stop = Timer0_Stop,
    .PeriodCountSet = Timer0_Write,
    .TimeoutCallbackRegister = Timer0_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*Timer0_OverflowCallback)(void);
static void Timer0_DefaultOverflowCallback(void);

void Timer0_Initialize(void)
{
    //TMR0H 14; 
    TMR0H = 0xE;

    //TMR0L 0; 
    TMR0L = 0x0;

    //T0CS LFINTOSC; T0CKPS 1:2; T0ASYNC not_synchronised; 
    T0CON1 = 0x91;


    //Set default callback for TMR0 overflow interrupt
    Timer0_OverflowCallbackRegister(Timer0_DefaultOverflowCallback);

    //Clear Interrupt flag before enabling the interrupt
    PIR0bits.TMR0IF = 0;
	
    //Enable TMR0 interrupt.
    PIE0bits.TMR0IE = 1;
	
    //T0OUTPS 1:1; T0EN disabled; T016BIT 8-bit; 
    T0CON0 = 0x0;
}

void Timer0_Start(void)
{
    T0CON0bits.T0EN = 1;
}

void Timer0_Stop(void)
{
    T0CON0bits.T0EN = 0;
}

uint8_t Timer0_Read(void)
{
    uint8_t readVal;

    //Read TMR0 register, low byte only
    readVal = TMR0L;

    return readVal;
}

void Timer0_Write(size_t timerVal)
{
    //Write to TMR0 register, low byte only
    TMR0L = (uint8_t)timerVal;
 }

void Timer0_Reload(uint8_t periodVal)
{
   //Write to TMR0 register, high byte only
   TMR0H = periodVal;
}

void Timer0_OverflowISR(void)
{
    //Clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    if(Timer0_OverflowCallback)
    {
        Timer0_OverflowCallback();
    }
}

void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    Timer0_OverflowCallback = CallbackHandler;
}

static void Timer0_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use Timer0_OverflowCallbackRegister function to use Custom ISR
}

