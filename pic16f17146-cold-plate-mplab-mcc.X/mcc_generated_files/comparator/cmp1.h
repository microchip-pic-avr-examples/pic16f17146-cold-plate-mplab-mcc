/**
 * CMP1 Generated Driver API Header File
 * 
 * @file cmp1.h
 * 
 * @defgroup cmp1 CMP1
 * 
 * @brief This file contains API prototypes and other datatypes for the CMP1 module.
 *
 * @version CMP1 Driver Version 2.12.0
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

#ifndef CMP1_H
#define CMP1_H

 /**
   Section: Included Files
 */

#include <stdint.h>
#include <stdbool.h>

/**
  Section: CMP1 APIs
*/

/**
 * @ingroup cmp1
 * @brief This routine initializes the CMP1 and must be called before any other CMP1 routine is called.
 * This routine should only be called once during system initialization.
 * @param void
 * @return void
 */
void CURRENT_SENSE_CMP_Initialize(void);

/**
 * @ingroup cmp1
 * @brief This routine gets the CMP1 output status.
 * @pre CURRENT_SENSE_CMP_Initialize() should have been called prior to calling this function.
 * @param void
 * @return bool - true if the CMP1 output is high, false if the output is low
 */
bool CURRENT_SENSE_CMP_GetOutputStatus(void);

/**
 * @ingroup cmp1
 * @brief This routine is used to implement the ISR for the interrupt-driven implementations.
 * @param void
 * @return void
 */
void CURRENT_SENSE_CMP_ISR(void);


#endif // CMP1_H
