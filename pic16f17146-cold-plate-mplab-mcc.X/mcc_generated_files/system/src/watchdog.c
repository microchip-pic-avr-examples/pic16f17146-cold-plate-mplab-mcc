/**
 * WWDT Generated Driver File
 * 
 * @file wwdt.c
 * 
 * @ingroup  wwdt
 * 
 * @brief This is the generated driver implementation file for the WWDT driver.
 *
 * @version WWDT Driver Version 2.0.0
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

#include "../watchdog.h"

void WWDT_Initialize(void)
{
    //WDTSEN OFF; WDTPS 1:32; 
    WDTCON0 = 0x0;
    //WDTCS LFINTOSC 31kHz; WDTWINDOW Window delay time 87.5%; 
    WDTCON1 = 0x0;
    //nRWDT WDT reset has not occurred; nWDTWV WDT window violation reset has not occurred; 
    PCON0 = 0x30;
}
/**
 End of File
*/