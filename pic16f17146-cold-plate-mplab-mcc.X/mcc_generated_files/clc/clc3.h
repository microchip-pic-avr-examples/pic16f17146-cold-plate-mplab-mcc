/**
 * CLC3 Generated Driver API Header File
 * 
 * @file clc3.h
 * 
 * @defgroup  clc3 CLC3
 * 
 * @brief This is the generated header file for the CLC3 driver.
 *
 * @version CLC3 Driver Version 1.0.1
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

#ifndef CLC3_H
 #define CLC3_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup clc3
 * @brief  Initializes the CLC3. This routine configures the CLC3 specific control registers.
 * @param none
 * @return none
 * 
 */
void CLC3_Initialize(void);


/**
 * @ingroup clc3
 * @brief This routine returns output pin status of the CLC module.
 * @param  none
 * @retval true - if pin Status is true.
 * @retval false - if pin Status is false.
 */
bool CLC3_OutputStatusGet(void);

#endif  // CLC3_H
/**
 End of File
*/

