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
� [2022] Microchip Technology Inc. and its subsidiaries.

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
#include "measurements.h"
#include "fanControl.h"
#include "NTC_ROM.h"
#include "testing.h"
#include "peltierControl.h"
#include "utility.h"
#include "currentSense.h"
#include "OLED.h"
#include "UI.h"
#include "mssp1_host.h"
#include "settings.h"
#include "config.h"
#include "compactPrint.h"

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

static volatile bool selfCheck = false, dispRefresh = false;

//This is called every 10ms from Timer 0
//DO NOT ADD BLOCKING CODE HERE
void Timer0_1ms_Callback(void)
{
    static volatile uint8_t counter10ms = 1;
    static volatile uint8_t counter100ms = 1;
    static volatile uint16_t counter1s = 1;
    
    if (counter10ms == 10)
    {
        //Call these functions every 10ms
        Measurements_runStateMachine();

        // update breathing effect every 10ms
        encoderControl_updateLEDs();
        
        counter10ms = 0;
    }
    else
    {
        counter10ms++;
    }
    //End of 10ms Period
    
    if (counter100ms == 100)
    {
        counter100ms = 0;
        dispRefresh = true;
    }
    else
    {
        counter100ms++;
    }
    
    if (counter1s == 1000)
    {
        counter1s = 0;
        
        //Call these functions every second
        
        //Update RPMs
        fanControl_timerCallback();
        
        //Set flags
        selfCheck = true;
    }
    else
    {
        counter1s++;
    }
}

int main(void)
{
    SYSTEM_Initialize();    
    UART1_TransmitEnable();
       
    // init i2c
    initI2CPins();
    MSSP_HostInit();
    
#ifdef DEBUG_PRINT
    compactPrint_sendStringWithNewline("\r\n--STARTING UP--");
#endif
    
    //Print the Reset Registers
    System_printResetRegisters();
    
    //Init and Verify Settings / EEPROM
    settings_init();
    
    //Init Fan Controls
    fanControl_init();
    
    //Init Temp Monitor
    Measurements_init();
    
    //Init Current Sense Circuit
    currentSense_init();
    
    //Init Peltier Control
    peltierControl_init();
            
    //Configure 10ms Callback
    Timer0_OverflowCallbackRegister(&Timer0_1ms_Callback);
    
    //Setup ADC Results Callback
    ADCC_SetADTIInterruptHandler(&Measurements_loadResults);
    
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 
        
    //Run Gain Self-Test
    //Must be run before Timer0 starts!
    currentSense_selfTest();
        
    //Start Timer 0 (10ms)
    Timer0_Start();
    
    //Pull local coy of settngs before populating UI
    settingMenus_populateSettings();
    
    //Init OLED Display
    OLED_init();

    //Start Fan Controller
    fanControl_start();
    
    // Enable PWM
    LED_PWM_Enable();
    
#ifdef DEBUG_PRINT
    compactPrint_sendStringWithNewline("--STARTUP DONE--\r\n");
#endif    
    while(1)
    {        
        //Note: This must occur every 250ms to 2s or WWDT will reset
        if (selfCheck)
        {
            selfCheck = false;
                        
            //Run Periodic Self-Check
            peltierControl_periodicCheck();
            
#ifdef DEBUG_TELEMETRY
#ifdef DEBUG_PRINT
            compactPrint_sendDebugTelemetry();
#endif
#ifdef DEBUG_RAW_VALUES
            compactPrint_sendRawValues();
#endif
#endif
        }
        
        if(dispRefresh){ // update UI every 100ms
            UI_refresh();
            dispRefresh = false;
        }

    }    
}