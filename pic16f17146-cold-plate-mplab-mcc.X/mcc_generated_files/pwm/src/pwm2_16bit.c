/**
  * PWM2_16BIT Generated Driver File.
  *
  * @file pwm2_16bit.c
  *
  * @ingroup pwm2_16bit
  *
  * @brief This file contains the API implementation for the PWM2_16BIT module.
  *
  * version PWM2_16BIT Driver Version 1.0.1
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
 * @section: Included Files
 */

#include <xc.h>
#include "../pwm2_16bit.h"

//Pointers to PWM2_16BIT interrupt handlers
//User can use them in application code to initialize with custom ISRs
static void (*FAN_PWM_Slice1Output1_InterruptHandler)(void);   //SaP1IF and hence PWMxIF is set
static void (*FAN_PWM_Slice1Output2_InterruptHandler)(void);   //SaP2IF and hence PWMxIF is set
static void (*FAN_PWM_Period_InterruptHandler)(void);          //PWMxPIF is set
static void FAN_PWM_Slice1Output1_DefaultInterruptHandler(void);
static void FAN_PWM_Slice1Output2_DefaultInterruptHandler(void);
static void FAN_PWM_Period_DefaultInterruptHandler(void);

void FAN_PWM_Initialize(void)
{
    //PWMERS External Reset Disabled; 
    PWM2ERS = 0x0;

    //PWMCLK FOSC; 
    PWM2CLK = 0x2;

    //PWMLDS Autoload disabled; 
    PWM2LDS = 0x0;

    //PWMPRL 255; 
    PWM2PRL = 0xFF;

    //PWMPRH 4; 
    PWM2PRH = 0x4;

    //PWMCPRE No prescale; 
    PWM2CPRE = 0x0;

    //PWMPIPOS No postscale; 
    PWM2PIPOS = 0x0;

    //PWMS1P1IF PWM1 output match did not occur; PWMS1P2IF PWM2 output match did not occur; 
    PWM2GIR = 0x0;

    //PWMS1P1IE disabled; PWMS1P2IE disabled; 
    PWM2GIE = 0x0;

    //PWMPOL1 disabled; PWMPOL2 disabled; PWMPPEN disabled; PWMMODE Left aligned mode; 
    PWM2S1CFG = 0x0;

    //PWMS1P1L 128; 
    PWM2S1P1L = 0x80;

    //PWMS1P1H 2; 
    PWM2S1P1H = 0x2;

    //PWMS1P2L 128; 
    PWM2S1P2L = 0x80;

    //PWMS1P2H 2; 
    PWM2S1P2H = 0x2;
    
    //Clear PWM2_16BIT period interrupt flag
    PIR3bits.PWM2PIF = 0;
    
    //Clear PWM2_16BIT interrupt flag
    PIR3bits.PWM2IF = 0;
    
    //Clear PWM2_16BIT slice 1, output 1 interrupt flag
    PWM2GIRbits.S1P1IF = 0;
    
    //Clear PWM2_16BIT slice 1, output 2 interrupt flag
    PWM2GIRbits.S1P2IF = 0;
    
    //PWM2_16BIT interrupt enable bit
    PIE3bits.PWM2IE = 0;
    
    //PWM2_16BIT period interrupt enable bit
    PIE3bits.PWM2PIE = 0;
    
    //Set default interrupt handlers
    FAN_PWM_Slice1Output1_SetInterruptHandler(FAN_PWM_Slice1Output1_DefaultInterruptHandler);
    FAN_PWM_Slice1Output2_SetInterruptHandler(FAN_PWM_Slice1Output2_DefaultInterruptHandler);
    FAN_PWM_Period_SetInterruptHandler(FAN_PWM_Period_DefaultInterruptHandler);

    //PWMEN enabled; PWMLD disabled; PWMERSPOL disabled; PWMERSNOW disabled; 
    PWM2CON = 0x80;
}

void FAN_PWM_Enable(void)
{
    PWM2CON |= _PWM2CON_EN_MASK;
}

void FAN_PWM_Disable(void)
{
    PWM2CON &= (~_PWM2CON_EN_MASK);
}

void FAN_PWM_WritePeriodRegister(uint16_t periodCount)
{
    PWM2PRL = (uint8_t)periodCount;
    PWM2PRH= (uint8_t)(periodCount >> 8);
}

void FAN_PWM_SetSlice1Output1DutyCycleRegister(uint16_t registerValue)
{    
    PWM2S1P1L = (uint8_t)(registerValue);
    PWM2S1P1H = (uint8_t)(registerValue >> 8);
}

void FAN_PWM_SetSlice1Output2DutyCycleRegister(uint16_t registerValue)
{        
    PWM2S1P2L = (uint8_t)(registerValue);
    PWM2S1P2H = (uint8_t)(registerValue >> 8);
}

void FAN_PWM_LoadBufferRegisters(void)
{
    //Load the period and duty cycle registers on the next period event
    PWM2CONbits.LD = 1;
}

void FAN_PWM_PWMI_ISR(void)
{
    PIR3bits.PWM2IF = 0;
    if((PWM2GIEbits.S1P1IE == 1) && (PWM2GIRbits.S1P1IF == 1))
    {
        PWM2GIRbits.S1P1IF = 0;
        if(FAN_PWM_Slice1Output1_InterruptHandler != NULL)
            FAN_PWM_Slice1Output1_InterruptHandler();
    }
    else if((PWM2GIEbits.S1P2IE == 1) && (PWM2GIRbits.S1P2IF == 1))
    {
        PWM2GIRbits.S1P2IF = 0;
        if(FAN_PWM_Slice1Output2_InterruptHandler != NULL)
            FAN_PWM_Slice1Output2_InterruptHandler();
    }
}

void FAN_PWM_PWMPI_ISR(void)
{
    PIR3bits.PWM2PIF = 0;
    if(FAN_PWM_Period_InterruptHandler != NULL)
        FAN_PWM_Period_InterruptHandler();
}

void FAN_PWM_Slice1Output1_SetInterruptHandler(void (* InterruptHandler)(void))
{
    FAN_PWM_Slice1Output1_InterruptHandler = InterruptHandler;
}

void FAN_PWM_Slice1Output2_SetInterruptHandler(void (* InterruptHandler)(void))
{
    FAN_PWM_Slice1Output2_InterruptHandler = InterruptHandler;
}

void FAN_PWM_Period_SetInterruptHandler(void (* InterruptHandler)(void))
{
    FAN_PWM_Period_InterruptHandler = InterruptHandler;
}

static void FAN_PWM_Slice1Output1_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use FAN_PWM_Slice1Output1_SetInterruptHandler() function to use Custom ISR
}

static void FAN_PWM_Slice1Output2_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use FAN_PWM_Slice1Output2_SetInterruptHandler() function to use Custom ISR
}

static void FAN_PWM_Period_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use FAN_PWM_Period_SetInterruptHandler() function to use Custom ISR
}
