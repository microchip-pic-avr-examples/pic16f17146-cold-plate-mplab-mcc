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

static volatile bool timerActive = false;

//This is called every 10ms from Timer 0
void Timer_10ms_Callback(void)
{
    //Update Count
    fanControl_timerCallback();
    
    //Set Flag
    timerActive = true;
    
    LED_ERROR_Toggle();
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
    
    uint8_t counter = 0;

    while(1)
    {
        if (timerActive)
        {
            counter++;
            timerActive = false;            
            printf("Timer 2 Count: %u\r\n", fanControl_getFan1RPM());
            printf("Timer 4 Count: %u\r\n", fanControl_getFan2RPM());

            
        }
        
        if (counter == 99)
        {
            counter = 0;
        }
    }    
}