/**
 * NCO1 Generated Driver API Header File
 * 
 * @file nco1.h
 * 
 * @defgroup  nco1 NCO1
 * 
 * @brief This is the generated header file for the NCO1 driver.
 *
 * @version NCO1 Driver Version 2.0.1
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


#ifndef NCO1_H
#define NCO1_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
 * @ingroup nco1
 * @brief  This routine initializes the NCO1_Initialize. Initializes the NCO1_Initialize
 * @param none
 * @return none
 * 
 */
void NCO1_Initialize(void);


/**
 * @ingroup nco1
 * @brief This routine is used to implement the ISR for the interrupt-driven implementations.
 * @param none
 * @return none
 */
void NCO1_ISR(void);
;

/**
 * @ingroup nco1
 * @brief This routine returns the NCO1 output status.
 * @pre NCO1_Initialize() function should have been called before calling this function.
 * @param none
 * @retval 1 - Indicates output is high.
 * @retval 0 - Indicates output is low.
 * 
 */
bool NCO1_GetOutputStatus(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //NCO1_H
/**
 End of File
*/
