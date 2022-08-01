/**
 * CWG1 Generated Driver API Header File
 * 
 * @file cwg1.h
 * 
 * @defgroup  cwg1 CWG1
 * 
 * @brief This is the generated header file for the CWG1 driver.
 *
 * @version CWG1 Driver Version 2.11.0
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


#ifndef CWG1_H
 #define CWG1_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @ingroup cwg1
 * @brief  This routine configures the CWG1 specific control registers.
 * @param none
 * @return none
 * 
 */
void CWG1_Initialize(void);


/**
 * @ingroup cwg1
 * @brief This function forces the CWG into Shutdown state.
 * 
 * @pre CWG1_Initialize() function should have been called before calling this function.

 * @param none
 * @return none
 * 
 */
void CWG1_AutoShutdownEventSet(void);

/**
 * @ingroup cwg1
 * @brief This function is used to resume operation when auto-restart is disabled.
 * 
 * @pre  CWG1_Initialize() and CWG1_AutoShutdownEventSet() functions should have been called before calling this function.

 * @param none
 * @return none
 * 
 */
void CWG1_AutoShutdownEventClear(void);


#endif  // CWG1_H
