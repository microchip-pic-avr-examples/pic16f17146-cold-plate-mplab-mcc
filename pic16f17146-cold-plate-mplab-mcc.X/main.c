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
#include "tempControl.h"
#include "fanControl.h"

#include <stdint.h>
#include <stdbool.h>

static volatile bool timerActive = false;

//This is called every 10ms from Timer 0
void Timer_10ms_Callback(void)
{
    static uint8_t delayCounter = 1;
    
    //Call these functions every 10ms
    {
        
    }
    //End of 10ms Period
    
    if (delayCounter == 100)
    {
        LED_ERROR_Toggle();
        
        delayCounter = 0;
        timerActive = true;
        
        //Call these functions every second
        {
            //Update Count
            fanControl_timerCallback();

        }
        //End of 1s Period
        
        LED_ERROR_Toggle();
    }
    
    //Increment Counter
    delayCounter++;
}

int main(void)
{
    SYSTEM_Initialize();
    UART1_TransmitEnable();
    
    printf("Start\r\n");
    
    //Configure 10ms Callback
    Timer0_OverflowCallbackRegister(&Timer_10ms_Callback);
    
    //Init Peltier Controls
    tempControl_init();
    
    //Init Fan Controls
    fanControl_init();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 
    
    //Start Timer 0 (10ms)
    Timer0_Start();
    
    while(1)
    {
        //Debug Print (1s)
        if (timerActive == true)
        {
            timerActive = false;
            printf("Fan 1 RPM: %u\r\n", fanControl_getFan1RPM());
            printf("Fan 2 RPM: %u\r\n", fanControl_getFan2RPM());
        }
    }    
}