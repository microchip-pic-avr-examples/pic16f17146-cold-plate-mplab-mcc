/**
 * TMR4 Generated Driver File
 *
 * @file tmr4.c
 * 
 * @ingroup  tmr4
 * 
 * @brief API implementations for the TMR4 module.
 *
 * @version TMR4 Driver Version 3.0.1
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
#include "../tmr4.h"

const struct TMR_INTERFACE Timer4 = {
    .Initialize = Timer4_Initialize,
    .Start = Timer4_Start,
    .Stop = Timer4_Stop,
    .PeriodCountSet = Timer4_PeriodCountSet,
    .TimeoutCallbackRegister = Timer4_OverflowCallbackRegister,
    .Tasks = Timer4_Tasks
};

static void (*Timer4_OverflowCallback)(void);
static void Timer4_DefaultOverflowCallback(void);

/**
  Section: TMR4 APIs
*/

void Timer4_Initialize(void){

    // Set TMR4 to the options selected in the User Interface
    // TCS T4INPPS; 
    T4CLKCON = 0x0;
    // TMODE Software control; TCKSYNC Not Synchronized; TCKPOL Rising Edge; TPSYNC Not Synchronized; 
    T4HLT = 0x0;
    // TRSEL T4INPPS pin; 
    T4RST = 0x0;
    // PR 255; 
    T4PR = 0xFF;
    // TMR 0x0; 
    T4TMR = 0x0;

    // Set default overflow callback
    Timer4_OverflowCallbackRegister(Timer4_DefaultOverflowCallback);

    // Clearing IF flag.
     PIR2bits.TMR4IF = 0;
    // TCKPS 1:1; TMRON off; TOUTPS 1:1; 
    T4CON = 0x0;
}

void Timer4_ModeSet(Timer4_HLT_MODE mode)
{
   // Configure different types HLT mode
    T4HLTbits.T4MODE = mode;
}

void Timer4_ExtResetSourceSet(Timer4_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T4RSTbits.T4RSEL = reset;
}

void Timer4_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void Timer4_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t Timer4_Read(void)
{
    uint8_t readVal;
    readVal = TMR4;
    return readVal;
}

void Timer4_Write(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;;
}

void Timer4_PeriodCountSet(size_t periodVal)
{
   PR4 = (uint8_t) periodVal;
}

void Timer4_OverflowCallbackRegister(void (* InterruptHandler)(void)){
    Timer4_OverflowCallback = InterruptHandler;
}

static void Timer4_DefaultOverflowCallback(void){
    // add your TMR4 interrupt custom code
    // or set custom function using Timer4_OverflowCallbackRegister()
}

void Timer4_Tasks(void)
{
    if(PIR2bits.TMR4IF)
    {
        // Clearing IF flag.
        PIR2bits.TMR4IF = 0;
        Timer4_OverflowCallback();
    }
}

