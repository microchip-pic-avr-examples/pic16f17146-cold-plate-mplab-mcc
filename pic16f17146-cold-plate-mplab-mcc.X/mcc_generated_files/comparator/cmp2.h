/**
 * CMP2 Generated Driver API Header File
 * 
 * @file cmp2.h
 * 
 * @defgroup cmp2 CMP2
 * 
 * @brief This file contains API prototypes and other datatypes for the CMP2 module.
 *
 * @version CMP2 Driver Version 2.12.0
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

#ifndef CMP2_H
#define CMP2_H

 /**
   Section: Included Files
 */

#include <stdint.h>
#include <stdbool.h>

/**
  Section: CMP2 APIs
*/

/**
 * @ingroup cmp2
 * @brief This routine initializes the CMP2 and must be called before any other CMP2 routine is called.
 * This routine should only be called once during system initialization.
 * @param void
 * @return void
 */
void CMP2_Initialize(void);

/**
 * @ingroup cmp2
 * @brief This routine gets the CMP2 output status.
 * @pre CMP2_Initialize() should have been called prior to calling this function.
 * @param void
 * @return bool - true if the CMP2 output is high, false if the output is low
 */
bool CMP2_GetOutputStatus(void);

/**
 * @ingroup cmp2
 * @brief This routine is used to implement the ISR for the interrupt-driven implementations.
 * @param void
 * @return void
 */
void CMP2_ISR(void);


#endif // CMP2_H
