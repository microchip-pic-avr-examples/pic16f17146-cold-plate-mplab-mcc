/**
 * CMP2 Generated Driver File
 * 
 * @file cmp2.c
 * 
 * @ingroup cmp2
 * 
 * @brief This is the generated driver implementation file for the CMP2 driver.
 *
 * @version CMP2 Driver Version 2.12.0
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

 /**
   Section: Included Files
 */

#include <xc.h>
#include "../cmp2.h"

/**
  Section: CMP2 APIs
*/

void OVERCURRENT_CMP_Initialize(void) 
{
    // CHYS enabled; CON disabled; CPOL inverted; CSYNC asynchronous; 
    CM2CON0 = 0x12;

    // CINTN no_intFlag; CINTP no_intFlag; 
    CM2CON1 = 0x0;
    
    // CNCH OPA1OUT; 
    CM2NCH = 0x5;
    
    // CPCH DAC2_OUT; 
    CM2PCH = 0x5;    
}

bool OVERCURRENT_CMP_GetOutputStatus(void) 
{
  return CM2CON0bits.C2OUT; /* Note : As per datasheet, CxOUT bit in CMOUT register (if relevant) 
                                                   is mirror copy of CMxCON0.OUT */
}

void OVERCURRENT_CMP_ISR(void) 
{
    // Clear the CMP2 interrupt flag
    PIR5bits.CM2IF = 0; 
}

