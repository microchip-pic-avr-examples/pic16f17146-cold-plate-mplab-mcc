/**
 * CLC1 Generated Driver API Header File
 * 
 * @file clc1.h
 * 
 * @defgroup  clc1 CLC1
 * 
 * @brief This is the generated header file for the CLC1 driver.
 *
 * @version CLC1 Driver Version 1.0.1
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

#ifndef CLC1_H
 #define CLC1_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup clc1
 * @brief  Initializes the CLC1. This routine configures the CLC1 specific control registers.
 * @param none
 * @return none
 * 
 */
void CLC1_Initialize(void);


/**
 * @ingroup clc1
 * @brief This routine returns output pin status of the CLC module.
 * @param  none
 * @retval true - if pin Status is true.
 * @retval false - if pin Status is false.
 */
bool CLC1_OutputStatusGet(void);

#endif  // CLC1_H
/**
 End of File
*/

