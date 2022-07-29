 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "tempMonitor.h"
#include "fanControl.h"
#include "NTC_ROM.h"
#include "testing.h"
#include "peltierControl.h"

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

static volatile bool timerActive = false;

//This is called every 10ms from Timer 0
//DO NOT ADD BLOCKING CODE HERE
void Timer0_10ms_Callback(void)
{
    static uint8_t delayCounter = 1;
    
    //Call these functions every 10ms
    {
        
    }
    //End of 10ms Period
    
    if (delayCounter == 100)
    {
        delayCounter = 0;
        
        //Call these functions every second
        {
            //Update RPMs
            fanControl_timerCallback();
            tempMonitor_sampleIntTemp();

        }
        //End of 1s Period
        
        timerActive = true;
    }
    
    //Increment Counter
    delayCounter++;
}

void testRead(void)
{
//    while (!ADCC_IsConversionDone());
    tempMonitor_loadResults();
}

int main(void)
{
    SYSTEM_Initialize();
    
    UART1_TransmitEnable();
       
    //printf("Starting Up...\r\n");
    
    //Init Fan Controls
    fanControl_init();
    
    //Init Temp Monitor
    tempMonitor_init();
    
    //Init Peltier Control
    peltierControl_init();
    
    printf("Done initializing...\r\n");
    
    //Configure 10ms Callback
    Timer0_OverflowCallbackRegister(&Timer0_10ms_Callback);
    ADCC_SetADTIInterruptHandler(&testRead);
    
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 
    
    //Start Timer 0 (10ms)
    Timer0_Start();
    
    //RUN ROM TEST PATTERN
    //NTC_ROM_Test();
    
    FAN_PWM_Enable();
    
    while(1)
    {
        asm("CLRWDT");

        //Debug Print (1s)
        if (timerActive)
        {
            timerActive = false;
            printf("Fan 1 RPM: %u\r\n", fanControl_getFan1RPM());
            printf("Fan 2 RPM: %u\r\n", fanControl_getFan2RPM());
            
//            ADSTATbits.MATH = 0b0;
//            tempMonitor_sampleIntTemp();
//            while (!ADSTATbits.MATH);    
//            ADSTATbits.MATH = 0b0;
//            
//            tempMonitor_loadResults();
            
            printf("Int Temp: %d\r\n", tempMonitor_getLastIntTemp());          
            printf("ADC RES: 0x%x\r\n", ADRES);
            printf("ADC FLTR: 0x%x\r\n", ADFLTR);
        }
    }    
}