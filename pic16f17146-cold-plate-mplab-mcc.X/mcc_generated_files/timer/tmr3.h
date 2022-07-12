/**
 * TMR3 Generated Driver API Header File
 *
 * @file tmr3.h
 *
 * @defgroup tmr3 TMR3
 *
 * @brief This header file provides APIs for the TMR3 driver.
 *
 * @version TMR3 Driver Version 3.0.1
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

#ifndef TMR3_H
#define TMR3_H

#include <stdbool.h>
#include <stdint.h>
#include "timer_interface.h"


/**
 * @ingroup tmr3
 * @struct TMR_INTERFACE
 * @brief This is an instance of TMR_INTERFACE for Timer module
 */
extern const struct TMR_INTERFACE Timer3;

/**
 * @ingroup tmr3
 * @brief This API initializes the Timer module.
 *        This routine must be called before any other Timer routines.
 * @param none
 * @return none
 */
void Timer3_Initialize(void);

/**
 * @ingroup tmr3
 * @brief This function starts Timer.
 * @pre Timer should be initialized with Timer3_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer3_Start(void);

/**
 * @ingroup tmr3
 * @brief This function stops Timer.
 * @pre Timer should be initialized with Timer3_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer3_Stop(void);

/**
 * @ingroup tmr3
 * @brief This function reads the 16-bits from TMR3 register.
 *        Timer should be initialized with Timer3_Initialize() before calling this API.
 * @param none
 * @return uint16_t - 16-bit data from TMR3 register.
 */
uint16_t Timer3_Read(void);

/**
 * @ingroup tmr3
 * @brief This function writes 16-bit value to TMR3 register.
 * @pre Timer should be initialized with Timer3_Initialize() before calling this API.
 * @param size_t timerVal - 16-bit value to be written to TMR3 register.
 * @return none
 */
void Timer3_Write(size_t timerVal);

/**
 * @ingroup tmr3
 * @brief This function loads 8 bit value to TMR3 register.
 * @pre Timer should be initialized with Timer3_Initialize() before calling this API.
 * @param none
 * @return none
 */
void Timer3_Reload(void);


/**
 * @ingroup tmr3
 * @brief This function starts the single pulse acquisition in TMR3 gate operation.
 * @Pre This function must be used when the TMR3 gate is enabled.
 * @param none
 * @return none
 */
void Timer3_StartSinglePulseAcquisition(void);

/**
 * @ingroup tmr3
 * @brief This function reads the TMR3 gate value and return it.
 * @pre This function must be used when the TMR3 gate is enabled.
 * @param none
 * @return uint8_t - Gate value status.
 */
uint8_t Timer3_CheckGateValueStatus(void);


/**
 * @ingroup tmr3
 * @brief Setter function for Timer overflow Callback.
 * @param void (* CallbackHandler)(void) - Pointer to custom Callback.
 * @return none
 */
 void Timer3_OverflowCallbackRegister(void (* CallbackHandler)(void));

/**
 * @ingroup tmr3
 * @brief This function performs tasks to be executed on timer overflow event
 * @param none
 * @return none
 */
void Timer3_Tasks(void);

/**
 * @ingroup tmr3
 * @brief This function is called to check for the timer overflow flag when in polling mode.
 * @param none
 * @retval true  - timer overflow has occured.
 * @retval false - timer overflow has not occured.
 */
bool Timer3_HasOverflowOccured(void);


/**
 * @ingroup tmr3
 * @brief Timer Gate Interrupt Service Routine is called by the Interrupt Manager.
 * @param none
 * @return none
 */
void Timer3_GateISR(void);

#endif // TMR3_H