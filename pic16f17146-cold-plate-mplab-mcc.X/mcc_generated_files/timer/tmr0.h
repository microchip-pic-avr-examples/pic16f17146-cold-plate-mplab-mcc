/**
 * TMR0 Generated Driver API Header File
 * 
 * @file tmr0.h
 * 
 * @defgroup tmr0 TMR0
 * 
 * @brief This file contains API prototypes and other datatypes for the TMR0 module.
 *
 * @version TMR0 Driver Version 2.0.2
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

#ifndef TMR0_H
#define TMR0_H

#include <stdint.h>
#include <stdbool.h>
#include "timer_interface.h"


/**
 @ingroup tmr0
 @struct TMR_INTERFACE
 @brief This is an instance of TMR_INTERFACE for Timer-0 module
 */
extern const struct TMR_INTERFACE Timer0;

/**
 * @ingroup tmr0
 * @brief This API initializes the Timer-0 module.
 *        This routine must be called before any other Timer-0 routines.
 * @param void.
 * @return void.
 */
void Timer0_Initialize(void);

/**
 * @ingroup tmr0
 * @brief This function starts Timer-0.
 * @pre Timer-0 should be initialized with Timer0_Initialize() before calling this API.
 * @param void.
 * @return void.
 */
void Timer0_Start(void);

/**
 * @ingroup tmr0
 * @brief This function stops Timer-0.
 * @pre Timer-0 should be initialized with Timer0_Initialize() before calling this API.
 * @param void.
 * @return void.
 */
void Timer0_Stop(void);

/**
 * @ingroup tmr0
 * @brief This function reads the 8 bits from TMRTMR0 register.
 * @pre Timer-0 should be initialized with Timer0_Initialize() before calling this API.
 * @param void.
 * @return 8-bit data from TMRTMR0 register.
 */
uint8_t Timer0_Read(void);

/**
 * @ingroup tmr0
 * @brief This function writes 8-bit value to TMRTMR0 register.
 * @pre Timer-0 should be initialized with Timer0_Initialize() before calling this API.
 * @param 8-bit value to be written to TMRTMR0 register.
 * @return void.
 */
void Timer0_Write(size_t timerVal);

/**
 * @ingroup tmr0
 * @brief This function loads 8 bit value to TMRTMR0H register.
 * @pre Timer-0 should be initialized with Timer0_Initialize() before calling this API.
 * @param 8-bit value to be written to TMRTMR0H register.
 * @return void.
 */
void Timer0_Reload(uint8_t periodVal);

/**
 * @ingroup tmr0
 * @brief Interrupt Service Routine for Timer-0 overflow interrupt.
 * @param void
 * @return void
 */
void Timer0_OverflowISR(void);

/**
 * @ingroup tmr0
 * @brief Setter function for Timer-0 overflow Callback.
 * @param CallbackHandler - Pointer to custom Callback.
 * @return void
 */
 void Timer0_OverflowCallbackRegister(void (* CallbackHandler)(void));


/**
 * @}
 */
#endif //TMR0_H
